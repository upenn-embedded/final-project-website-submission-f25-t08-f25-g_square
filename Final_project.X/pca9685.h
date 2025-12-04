#ifndef PCA9685_H
#define PCA9685_H

#include <stdint.h>
#include <stdbool.h>

#define PCA9685_BASE_ADDR 0x40

// Registers
#define PCA9685_MODE1           0x00
#define PCA9685_MODE2           0x01
#define PCA9685_LED0_ON_L       0x06
#define PCA9685_ALL_LED_ON_L    0xFA
#define PCA9685_ALL_LED_OFF_L   0xFC
#define PCA9685_PRE_SCALE       0xFE

// MODE1 bits
#define MODE1_RESTART  (1 << 7)
#define MODE1_EXTCLK   (1 << 6)
#define MODE1_AI       (1 << 5)
#define MODE1_SLEEP    (1 << 4)
#define MODE1_ALLCALL  (1 << 0)

// MODE2 bits
#define MODE2_INVRT    (1 << 4)
#define MODE2_OCH      (1 << 3)
#define MODE2_OUTDRV   (1 << 2)

// I2C (TWI0 on ATmega328PB: SDA=PC4, SCL=PC5)
void i2c_init(uint32_t i2c_clk_hz);
bool i2c_write_reg(uint8_t addr7, uint8_t reg, const uint8_t *data, uint8_t len);
bool i2c_read_reg (uint8_t addr7, uint8_t reg, uint8_t *data, uint8_t len);

// PCA9685 device
typedef struct {
    uint8_t addr;
    float   osc_clk_hz;
    float   pwm_freq_hz;
} pca9685_t;

bool pca9685_init(pca9685_t *dev, uint8_t addr7, float pwm_freq_hz);
bool pca9685_set_pwm_freq(pca9685_t *dev, float pwm_freq_hz);
bool pca9685_set_channel_pwm(pca9685_t *dev, uint8_t ch, uint16_t on_count, uint16_t off_count);
bool pca9685_set_channel_us (pca9685_t *dev, uint8_t ch, float pulse_us);
bool pca9685_set_channel_duty(pca9685_t *dev, uint8_t ch, float duty_0_1);
bool pca9685_all_off(pca9685_t *dev);

#endif
