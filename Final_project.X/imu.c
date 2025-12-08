/* 
 * File:   imu.c
 * Author: guan
 *
 * Created on November 15, 2025, 2:18 PM
 */
#define F_CPU 16000000UL

#include "imu.h"


#define ACC_SCALE_G     0.000061f   


#define Z_UP_MIN_G      0.6f       
#define TILT_MIN_G      0.7f       
#define FALL_CONFIRM_N  5         

static uint8_t fall_counter = 0;
static uint8_t fall_reported = 0;

void TWI1_init(void)
{
    // SCL = F_CPU / (16 + 2*TWBR1*Prescaler)
    // 16MHz, 100kHz → TWBR = 72

    TWBR1 = 72;
    TWSR1 &= ~((1<<TWPS1) | (1<<TWPS0)); // Prescaler = 1

    // enable TWI1
    TWCR1 = (1<<TWEN);
}
// generate a START condition
void TWI1_start(void)
{
    TWCR1 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    /*• TWCRn.TWEN must be written to '1' to enable the two-wire serial interface
      • TWCRn.TWSTA must be written to '1' to transmit a START condition
      • TWCRn.TWINT must be cleared by writing a '1' to it
     The TWI will then test the two-wire serial bus and generate a START condition as soon as the bus
     becomes free.*/
    while (!(TWCR1 & (1<<TWINT)));
}

void TWI1_stop(void)
{
    TWCR1 = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

/*Load data into TWDR Register. Clear TWINT bit in TWCR to start transmission of address.*/
void TWI1_write(uint8_t data)
{
    TWDR1 = data;
    TWCR1 = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR1 & (1<<TWINT)));
}
unsigned int TWI1_read_ack(void)
{
    TWCR1 = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR1 & (1<<TWINT)));
    return TWDR1;
}
unsigned int TWI1_read_nack(void)
{
    TWCR1 = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR1 & (1<<TWINT)));
    return TWDR1;
}

void imuWrite(uint8_t reg, uint8_t value)
{
    TWI1_start();
    TWI1_write(0x6B << 1);   // IMU address
    TWI1_write(reg);  //register address 
    TWI1_write(value); //data
    TWI1_stop();
}

void imuInit()
{
    TWI1_init();
    imuWrite(0x10, 0x40); // CTRL1_XL = 104Hz, ±2g
}

void imuReadAccel(int16_t *ax, int16_t *ay, int16_t *az)
{
    TWI1_start();
    TWI1_write(0x6B << 1);
    TWI1_write(0x28); // OUTX_L_XL

    TWI1_start();
    TWI1_write((0x6B << 1) | 1);

    uint8_t xl = TWI1_read_ack();  //read data 16bits 
    uint8_t xh = TWI1_read_ack();
    uint8_t yl = TWI1_read_ack();
    uint8_t yh = TWI1_read_ack();
    uint8_t zl = TWI1_read_ack();
    uint8_t zh = TWI1_read_nack();
    TWI1_stop();

    *ax = (xh << 8) | xl;
    *ay = (yh << 8) | yl;
    *az = (zh << 8) | zl;
}


void check_fall(float axg, float ayg, float azg)
{
    float ax_abs = fabsf(axg);
    float ay_abs = fabsf(ayg);
    float az_abs = fabsf(azg);

    uint8_t tilted = (az_abs < Z_UP_MIN_G) &&
                     (ax_abs > TILT_MIN_G || ay_abs > TILT_MIN_G);

    if (tilted) {
        if (fall_counter < 255) fall_counter++;
    } else {

        fall_counter = 0;
        fall_reported = 0;
    }


    if (!fall_reported && fall_counter >= FALL_CONFIRM_N) {
  
        printf("FALL\n");    
        fall_reported = 1;
    }
}

/*int main(void) {
    uart_init();


    imuInit();

    int16_t ax, ay, az;
   // printf("START!!");

    while (1) {
        imuReadAccel(&ax, &ay, &az);
      //  printf("START!!");

        // Convert to g units (±2g mode: 0.061 mg/LSB)
        float axg = ax * 0.000061;
        float ayg = ay * 0.000061;
        float azg = az * 0.000061;

        char buf[64];
        
       // printf("AX=%.3f  AY=%.3f  AZ=%.3f\n", axg, ayg, azg);
       check_fall(axg, ayg, azg);

        _delay_ms(200);
    }
}
*/