#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

#include "pca9685.h"
#include "motion.h"

#define I2C_FREQ_HZ        400000UL  
#define SERVO_PWM_FREQ_HZ  50.0f      
#define PCA9685_ADDR       PCA9685_BASE_ADDR

/*int main(void){
    i2c_init(I2C_FREQ_HZ);
    pca9685_t pwm;
    pca9685_init(&pwm, PCA9685_ADDR, SERVO_PWM_FREQ_HZ);
    motion_init(&pwm);
/*

    motion_stand();
    _delay_ms(500);

    motion_forward_ms(2000);
    _delay_ms(500);

    motion_prone();
    _delay_ms(1000);

    motion_stand();
    _delay_ms(500);

    motion_backward_ms(1500);

    while(1){
  
    }
}*/
