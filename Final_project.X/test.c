/* 
 * File:   test.c
 * Author: socold
 *
 * Created on November 21, 2025, 9:50 AM
 */
/* 
 * File:   main.c
 * Author: socold
 *
 * Created on November 12, 2025, 1:14 PM
 */
#define F_CPU 16000000UL

#define I2C_FREQ_HZ        400000UL  
#define SERVO_PWM_FREQ_HZ  50.0f      
#define PCA9685_ADDR       PCA9685_BASE_ADDR

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "LCD_GFX.h"
#include "ST7735.h"
#include "ASCII_LUT.h"
#include "pca9685.h"
#include "motion.h"
#include "voice_control.h"
#include "uart.h"
#include "imu.h"

volatile unsigned int start_ticks = 0;
volatile unsigned int end_ticks = 0;
volatile unsigned int captured = 0;
volatile uint16_t pcint_trig = 0;


void gpio_init(){
    DDRC |= (1 << DDC2);  // trig output PC2 
    DDRE &= ~(1 << DDE2); // echo input PE2 TIMER 3
    PORTC &= ~(1 << PC2);
    DDRC |= (1 << DDC3);  // BUZZER output PC3
}

/************Ultra sonic & Buzzer *************/
void timer3_init() {
    TCCR3A = 0;  
    TCCR3B |= (1 << ICES3) | (1 << CS31);  // prescaler /8 & capture rising edge
    TIFR3  |= (1 << ICF3) | (1 << TOV3); // clean flag
    TIMSK3 |= (1 << ICIE3);                // enable input capture interrupt
}

void send_trig() {
    PORTC |= (1 << PC2);
    _delay_us(15);
    PORTC &= ~(1 << PC2);
}

ISR(TIMER3_CAPT_vect) {   // capture echo
    if (!captured) {
        start_ticks = ICR3;
        TCCR3B &= ~(1 << ICES3);   
        captured = 1;
    } else {
        end_ticks = ICR3;
        captured = 2;
        TCCR3B |= (1 << ICES3);
        TCNT3 = 0;
    }
}

void buzzer_enable(){
    for (int i = 0; i < 100; i++) {
        PORTC ^= (1 << PC3);  
        _delay_us(250);
    }
    PORTC &= ~(1 << PC3);
}
/*************Ultra sonic & Buzzer *************/

void expression(){
    LCD_setScreen(BLACK);
    LCD_drawCircle(120, 35,20, WHITE);
    LCD_drawCircle(120, 95,20, WHITE);
    LCD_drawhalfCircle(60,65,20,WHITE);
}

/*************Remote Control*************/
void PCINT_init(){
    DDRD &= ~(1<<DDD2);
    DDRD &= ~(1<<DDD3);
    DDRD &= ~(1<<DDD4);
    DDRD &= ~(1<<DDD5);
    PCICR |= (1<<PCIE2);
    PCMSK2 |= ((1<<PCINT18)|(1<<PCINT19)|(1<<PCINT20)|(1<<PCINT21));
    
}

void PCINT_control(){
        if(PIND & (1<<PD2)){
        pcint_trig = 0;
        motion_stand();
        
    }
        if(PIND & (1<<PD3)){
            
        pcint_trig = 0;
        motion_prone();
    }
        if(PIND & (1<<PD4)){
            
        pcint_trig =0;
        motion_forward_ms(2000);
    }
        if(PIND & (1<<PD5)){
            
        pcint_trig =0;
        motion_backward_ms(2000);
    }
}

ISR(PCINT2_vect){
    pcint_trig = 1;
}
/*************Remote Control*************/

int main(){
    lcd_init();
    expression();
//    /*ultrasonic & buzzer &LCD*/
//    gpio_init();  // trig+echo+buzzer
//    timer3_init();  // for edge capture
//    lcd_init();     //lcd
//    PCINT_init();    //for remote control
//    sei();
//    
//    /*motor control*/
//    i2c_init(I2C_FREQ_HZ);
//    pca9685_t pwm;
//    pca9685_init(&pwm, PCA9685_ADDR, SERVO_PWM_FREQ_HZ);
//    motion_init(&pwm);
//    
//    /*UART*/
//    uart_init();
//
//    /*IMU*/
//    imuInit();
//    int16_t ax, ay, az;
//    
//    /*voice control*/
//    adc_init();
//    //printf("Voice burst command demo\r\n");
//    //printf("Clap / shout 1~4 times within ~1 second.\r\n");
// 
//    while(1){
//        
//        /*voice control*/
//        process_voice_frame();
//        _delay_ms(FRAME_MS);
//        
//        /*remote control*/
//        if(pcint_trig){
//            PCINT_control();
//        }
//    
//        /*imu detection*/
//        imuReadAccel(&ax, &ay, &az);
//        //  printf("START!!");
//
//        // Convert to g units (?2g mode: 0.061 mg/LSB)
//        float axg = ax * 0.000061;
//        float ayg = ay * 0.000061;
//        float azg = az * 0.000061;
//
//        // printf("AX=%.3f  AY=%.3f  AZ=%.3f\n", axg, ayg, azg);
//        check_fall(axg, ayg, azg);
//        //_delay_ms(200);
//
//        /*ultrasonic & buzzer*/
//        captured = 0;
//        send_trig();// send trig
//
//        while (captured < 2); // wait until capture all
//
//        unsigned int lenghth = end_ticks - start_ticks;
//        float distance_cm = lenghth * 0.5 / 58 ; // Formula: uS / 58 = centimeters
//        if(distance_cm < 30){
//            buzzer_enable();
//            
//            //motion_stand(); wait for confirm
//        }
//        _delay_ms(50);
//  
//}
}
