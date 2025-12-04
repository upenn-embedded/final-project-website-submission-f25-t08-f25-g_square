/* 
 * File:   imu.h
 * Author: guan
 *
 * Created on November 18, 2025, 2:19 PM
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "uart.h"
#include <stdint.h>


#define ACC_SCALE_G     0.000061f   // 0.061 mg/LSB = 0.000061 g/LSB

#define Z_UP_MIN_G      0.6f       
#define TILT_MIN_G      0.7f       
#define FALL_CONFIRM_N  5      

void TWI1_init(void);
void TWI1_start(void);
void TWI1_stop(void);
void TWI1_write(uint8_t data);
unsigned int TWI1_read_ack(void);
unsigned int TWI1_read_nack(void);
void imuWrite(uint8_t reg, uint8_t value);
void imuInit();
void imuReadAccel(int16_t *ax, int16_t *ay, int16_t *az);
void check_fall(float axg, float ayg, float azg);
