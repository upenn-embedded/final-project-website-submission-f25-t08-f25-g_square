/* 
 * File:   voice.c
 * Author: socold
 *
 * Created on November 15, 2025, 4:55 PM
 */

 /*
  * Microphone+ADC 
  * not used in this project at all
  * because the integration is hard.
 */

#include "voice_control.h"
#include "motion.h"
#include "LCD_GFX.h"

// ===================== ADC =====================
// ADC0 (PC0) AVcc
void adc_init(void)
{
    // REFS0 = 1 -> = AVcc; ADLAR = 0 
    ADMUX = (1 << REFS0);        //  AVcc  ADC0
    //  ADC 128 16MHz / 128 = 125kHz 
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// ADC (0~1023)
uint16_t adc_read(void)
{
    ADCSRA |= (1 << ADSC);             
    while (ADCSRA & (1 << ADSC));     
    return ADC;
}

uint32_t compute_frame_energy(void)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < FRAME_SAMPLES; i++) {
        uint16_t x = adc_read();       // 0~1023
        int16_t centered = (int16_t)x - 512;   //  512 
        sum += (uint32_t)centered * (uint32_t)centered;
    }
    return sum;
}

// state definition
typedef enum {
    STATE_IDLE,    
    STATE_ACTIVE,  
    STATE_GAP      
} VoiceState;

static VoiceState state = STATE_IDLE;
static uint16_t active_ms = 0;   // command duration
static uint8_t  burst_count = 0; // burst detect
static uint16_t gap_ms = 0;      // command gap

// command recognition
void decide_command(uint8_t bursts)
{
    if (bursts == 0) return;

    printf("Bursts = %u -> ", bursts);

    if (bursts == 1) {
        printf("CMD: STAND\r\n");
        LCD_setScreen(BLACK);
    //LCD_drawCircle(120, 35,20, WHITE);
    LCD_drawCircle(120, 95,20, WHITE);
    LCD_drawhalfCircle(60,65,20,WHITE);
        motion_stand();
    } else if (bursts == 2) {
        printf("CMD: SIT\r\n");
         LCD_setScreen(BLACK);
    LCD_drawCircle(120, 35,20, WHITE);
    LCD_drawCircle(120, 95,20, WHITE);
    LCD_drawhalfCircle(60,65,20,WHITE);
        motion_prone();
    } else if (bursts == 3) {
        printf("CMD: FORWARD\r\n");
        LCD_setScreen(BLACK);
    LCD_drawCircle(120, 35,20, WHITE);
    //LCD_drawCircle(120, 95,20, WHITE);
    LCD_drawhalfCircle(60,65,20,WHITE);
        motion_forward_ms(2000);
    } else if (bursts >= 4) {
        printf("CMD: BACKWARD\r\n");
         LCD_setScreen(BLACK);
    LCD_drawCircle(120, 35,20, WHITE);
    LCD_drawCircle(120, 95,20, WHITE);
    LCD_drawhalfCircle(20,65,20,WHITE);
        motion_backward_ms(2000);
    }
}

void process_voice_frame(void)
{
    uint32_t e = compute_frame_energy();
   //printf("E=%lu  state=%d  bursts=%u gap=%u\r\n",
           //e, state, burst_count, gap_ms);

    switch (state) {
    case STATE_IDLE:
        if (e > ENERGY_TH) {
            burst_count = 1;
            active_ms = FRAME_MS;
            gap_ms = 0;
            state = STATE_ACTIVE;
        }
        break;

    case STATE_ACTIVE:
        if (e > ENERGY_TH) {
            active_ms += FRAME_MS;
        } else {
            gap_ms = FRAME_MS;
            state = STATE_GAP;
        }
        break;

    case STATE_GAP:
        if (e > ENERGY_TH) {
            burst_count++;
            active_ms = FRAME_MS;
            state = STATE_ACTIVE;
        } else {
            gap_ms += FRAME_MS;
            if (gap_ms >= GAP_TIMEOUT_MS) {
                decide_command(burst_count);

                burst_count = 0;
                active_ms = 0;
                gap_ms = 0;
                state = STATE_IDLE;
            }
        }
        break;
    }
}

/*int main(void)
{
    uart_init();   
    adc_init();

    printf("Voice burst command demo\r\n");
    printf("Clap / shout 1~3 times within ~1 second.\r\n");

    while (1) {
        process_voice_frame();
        _delay_ms(FRAME_MS);    
    }
}*/
 