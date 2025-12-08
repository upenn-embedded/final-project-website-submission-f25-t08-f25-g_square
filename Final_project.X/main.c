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
    DDRE |= (1<<DDE3);
    PORTE &= ~(1<<PE3);
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
volatile uint16_t buzzer_duration_ms = 0;
void buzzer_enable(){
//    for (int i = 0; i < 100; i++) {
//        PORTC ^= (1 << PC3);  
//        _delay_us(50);
//    }
//    PORTC &= ~(1 << PC3);
    buzzer_duration_ms = 500; //
}
/*************Ultra sonic & Buzzer *************/


/*************Expressions*************/
void expression(){
    LCD_setScreen(BLACK);
    LCD_drawCircle(120, 35,20, WHITE);
    LCD_drawCircle(120, 95,20, WHITE);
    LCD_drawhalfCircle(60,65,20,WHITE);
}

void Face_Stand(void) {
    LCD_setScreen(BLACK); 
    LCD_drawCircle(45, 50, 18, GREEN); 
    LCD_drawCircle(115, 50, 18, GREEN);
    LCD_drawLine(60, 90, 100, 90, GREEN);
    LCD_drawString(60, 110, "READY", WHITE, BLACK); 
}

void Face_Sit(void) {
    LCD_setScreen(BLACK);
    LCD_drawLine(25, 50, 65, 50, YELLOW);
    LCD_drawLine(95, 50, 135, 50, YELLOW);
    LCD_drawCircle(80, 90, 8, YELLOW);
    LCD_drawString(65, 110, "REST", WHITE, BLACK);
}

void Face_Forward(void) {
    LCD_setScreen(BLACK);
    LCD_drawCircle(45, 50, 20, CYAN);
    LCD_drawCircle(115, 50, 20, CYAN);
    LCD_drawBlock(40, 45, 50, 55, CYAN); 
    LCD_drawBlock(110, 45, 120, 55, CYAN);
    LCD_drawBlock(60, 85, 100, 95, CYAN);
    LCD_drawString(65, 110, "GO >>", WHITE, BLACK);
}

void Face_Backward(void) {
    LCD_setScreen(BLACK);
    
    uint16_t color = RED;
    LCD_drawLine(30, 35, 60, 65, color);
    LCD_drawLine(30, 65, 60, 35, color);
    LCD_drawLine(100, 35, 130, 65, color);
    LCD_drawLine(100, 65, 130, 35, color);
    LCD_drawCircle(80, 95, 12, color);
    LCD_drawString(55, 110, "<< BACK", WHITE, BLACK);
}

/*************Expressions*************/

volatile uint8_t us_send_counter = 0; 
#define US_SEND_INTERVAL 100 // (100 * 10ms)--1s for ultrasonic sensor
volatile uint8_t motion_ready = 0;

void timer2_init(void) {
    //Prescaler=256, OCR2A=624 T=10ms
    TCCR2A = (1 << WGM21); // CTC Mode
    OCR2A = 624; 
    TCCR2B = (1 << CS22); // Prescaler /256
    TIMSK2 = (1 << OCIE2A); // Enable Output Compare A interrupt
}

// TIMER 2 ISR
ISR(TIMER2_COMPA_vect) {
motion_ready = 1;
    if (us_send_counter > 0) {
        us_send_counter--; 
    }
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
        Face_Stand();
        motion_set_mode(MOTION_MODE_STAND);
        
    }
        if(PIND & (1<<PD3)){
            
        pcint_trig = 0;
        Face_Sit();
        motion_set_mode(MOTION_MODE_PRONE);

    }
        if(PIND & (1<<PD4)){
            
        pcint_trig =0;

        Face_Forward();
        motion_set_mode(MOTION_MODE_WALK_FWD);

    }
        if(PIND & (1<<PD5)){
            
        pcint_trig =0;

        Face_Backward();
        motion_set_mode(MOTION_MODE_WALK_BACK);

    }
}

ISR(PCINT2_vect){
    pcint_trig = 1;
}
/*************Remote Control*************/


int main(){
    lcd_init();
    expression();
//    /*ultrasonic & buzzer & LCD*/
    gpio_init();  // trig+echo+buzzer
    timer3_init();  // for edge capture
//    lcd_init();     //lcd
    PCINT_init();    //for remote control
    timer2_init();
    sei();
//    
    /*motor control*/
    i2c_init(I2C_FREQ_HZ);
    pca9685_t pwm;
    pca9685_init(&pwm, PCA9685_ADDR, SERVO_PWM_FREQ_HZ);
    motion_init(&pwm);
//    
    /*UART*/
    uart_init();
//
    /*IMU*/
    imuInit();
    int16_t ax, ay, az;
//    
//    /*voice control*/
//    adc_init();
//    //printf("Voice burst command demo\r\n");
//    //printf("Clap / shout 1~4 times within ~1 second.\r\n");
// 
    while(1){
        
        /*voice control*/
//        process_voice_frame();
//        _delay_ms(FRAME_MS);
        if(motion_ready){
            motion_ready=0;
            motion_update(10);
            //_delay_ms(5);
         if (us_send_counter == 0) {
                // ultrasoni
                TCCR3B &= ~(1 << ICES3); // 
                TCCR3B |= (1 << ICES3);  // Rising Edge
                TIFR3 |= (1 << ICF3);    // Clear Flag
                captured = 0; 
                send_trig(); 
                us_send_counter = US_SEND_INTERVAL; 
            }
            if (buzzer_duration_ms > 0) {
        buzzer_duration_ms -= 10;
        PORTC ^= (1 << PC3); // Buzzer
    } else {
        PORTC &= ~(1 << PC3); 
    }
        }
        /*remote control*/
        if(pcint_trig){
            PCINT_control();
        }
//    
        
        /*imu detection*/
        imuReadAccel(&ax, &ay, &az);
        //  printf("START!!");

        // Convert to g units 
        float axg = ax * 0.000061;
        float ayg = ay * 0.000061;
        float azg = az * 0.000061;

        // printf("AX=%.3f  AY=%.3f  AZ=%.3f\n", axg, ayg, azg);
        check_fall(axg, ayg, azg);
        //_delay_ms(200);

        /*ultrasonic & buzzer*/

       
        if (captured == 2) {
            unsigned int length = end_ticks - start_ticks;
            
            float distance_cm = length * 0.5f / 58.0f; 

            if (distance_cm < 20.0f) {
                buzzer_enable();
                motion_set_mode(MOTION_MODE_STAND);

            }

        }

}
}