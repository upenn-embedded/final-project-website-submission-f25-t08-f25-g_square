/* 
 * File:   voice_control.h
 * Author: guan
 *
 * Created on November 18, 2025, 2:29 PM
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"      

#define FRAME_SAMPLES   64          // ADC 
#define FRAME_MS        10          //  10ms 
#define ENERGY_TH       170000UL     // thereshold for voice activity
#define GAP_TIMEOUT_MS  500        //  ms 

void adc_init(void);
uint16_t adc_read(void);
uint32_t compute_frame_energy(void);
void decide_command(uint8_t bursts);
void process_voice_frame(void);