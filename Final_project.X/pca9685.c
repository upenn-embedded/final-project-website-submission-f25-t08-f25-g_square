#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

#include "pca9685.h"

// TWI0
#ifndef TWSR
  #define TWSR   TWSR0
  #define TWBR   TWBR0
  #define TWCR   TWCR0
  #define TWDR   TWDR0
  #define TWAR   TWAR0
  #define TWAMR  TWAMR0
#endif
#ifndef TWINT
  #define TWINT TWINT0
  #define TWSTA TWSTA0
  #define TWSTO TWSTO0
  #define TWEA  TWEA0
  #define TWEN  TWEN0
#endif


static uint8_t i2c_start(uint8_t addr_rw){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    TWDR = addr_rw;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    return 1;
}
static void i2c_stop(void){
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2c_init(uint32_t i2c_clk_hz){
    // SCL = F_CPU / (16 + 2*TWBR*prescaler), prescaler=1
    TWSR = 0x00;
    TWBR = (uint8_t)((F_CPU / i2c_clk_hz - 16) / 2);
}

bool i2c_write_reg(uint8_t addr7, uint8_t reg, const uint8_t *data, uint8_t len){
    if(!i2c_start((addr7<<1)|0)) return false;
    TWDR = reg; TWCR=(1<<TWINT)|(1<<TWEN); while(!(TWCR&(1<<TWINT)));
    for(uint8_t i=0;i<len;i++){
        TWDR = data[i];
        TWCR = (1<<TWINT)|(1<<TWEN);
        while(!(TWCR & (1<<TWINT)));
    }
    i2c_stop();
    return true;
}
bool i2c_read_reg(uint8_t addr7, uint8_t reg, uint8_t *data, uint8_t len){
    if(!i2c_start((addr7<<1)|0)) return false;
    TWDR = reg; TWCR=(1<<TWINT)|(1<<TWEN); while(!(TWCR&(1<<TWINT)));
    if(!i2c_start((addr7<<1)|1)) return false;
    for(uint8_t i=0;i<len;i++){
        TWCR = (1<<TWINT)|(1<<TWEN)| (i==len-1?0:(1<<TWEA));
        while(!(TWCR & (1<<TWINT)));
        data[i] = TWDR;
    }
    i2c_stop();
    return true;
}

// -------- PCA9685 ----------
static inline bool write8(pca9685_t *dev, uint8_t reg, uint8_t val){
    return i2c_write_reg(dev->addr, reg, &val, 1);
}
static inline bool read8(pca9685_t *dev, uint8_t reg, uint8_t *val){
    return i2c_read_reg(dev->addr, reg, val, 1);
}

bool pca9685_init(pca9685_t *dev, uint8_t addr7, float pwm_freq_hz){
    dev->addr = addr7;
    dev->osc_clk_hz = 25000000.0f; 
    dev->pwm_freq_hz = 0.0f;

    if(!write8(dev, PCA9685_MODE2, MODE2_OUTDRV)) return false;
    if(!write8(dev, PCA9685_MODE1, MODE1_ALLCALL | MODE1_AI | MODE1_SLEEP)) return false;

    return pca9685_set_pwm_freq(dev, pwm_freq_hz);
}

bool pca9685_set_pwm_freq(pca9685_t *dev, float pwm_freq_hz){
    if(pwm_freq_hz < 24.0f)   pwm_freq_hz = 24.0f;
    if(pwm_freq_hz > 1526.0f) pwm_freq_hz = 1526.0f;

    float prescale_f = (dev->osc_clk_hz / (4096.0f * pwm_freq_hz)) - 1.0f;
    uint8_t prescale = (uint8_t)(prescale_f + 0.5f);

    uint8_t oldmode;
    if(!read8(dev, PCA9685_MODE1, &oldmode)) return false;

    uint8_t sleepmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP;
    if(!write8(dev, PCA9685_MODE1, sleepmode)) return false;
    if(!write8(dev, PCA9685_PRE_SCALE, prescale)) return false;
    if(!write8(dev, PCA9685_MODE1, (oldmode & ~MODE1_SLEEP))) return false;
    _delay_us(500);
    if(!write8(dev, PCA9685_MODE1, (oldmode & ~MODE1_SLEEP) | MODE1_RESTART)) return false;

    dev->pwm_freq_hz = pwm_freq_hz;
    return true;
}

bool pca9685_set_channel_pwm(pca9685_t *dev, uint8_t ch, uint16_t on_count, uint16_t off_count){
    if(ch > 15) return false;
    uint8_t base = PCA9685_LED0_ON_L + 4*ch;
    uint8_t buf[4] = {
        (uint8_t)(on_count & 0xFF),
        (uint8_t)((on_count >> 8) & 0x0F),
        (uint8_t)(off_count & 0xFF),
        (uint8_t)((off_count >> 8) & 0x0F)
    };
    return i2c_write_reg(dev->addr, base, buf, 4);
}

bool pca9685_set_channel_us(pca9685_t *dev, uint8_t ch, float pulse_us){
    if(dev->pwm_freq_hz <= 0.0f) return false;
    float period_us = 1e6f / dev->pwm_freq_hz;
    if(pulse_us < 0) pulse_us = 0;
    if(pulse_us > period_us) pulse_us = period_us;
    uint16_t ticks = (uint16_t)((pulse_us / period_us) * 4096.0f + 0.5f);
    if(ticks > 4095) ticks = 4095;
    return pca9685_set_channel_pwm(dev, ch, 0, ticks);
}

bool pca9685_set_channel_duty(pca9685_t *dev, uint8_t ch, float duty_0_1){
    if(ch > 15) return false;
    // 0~13%
    if(duty_0_1 < 0.0f)   duty_0_1 = 0.0f;
    if(duty_0_1 > 0.13f)  duty_0_1 = 0.13f;
    uint16_t ticks = (uint16_t)(duty_0_1 * 4096.0f + 0.5f);
    if(ticks > 4095) ticks = 4095;
    return pca9685_set_channel_pwm(dev, ch, 0, ticks);
}

bool pca9685_all_off(pca9685_t *dev){
    uint8_t buf[4] = {0, 0x10, 0, 0}; // FULL OFF
    return i2c_write_reg(dev->addr, PCA9685_ALL_LED_ON_L, buf, 4);
}
