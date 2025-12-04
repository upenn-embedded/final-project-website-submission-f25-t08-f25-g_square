#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

#include "motion.h"

// ====== ?????????? 3%~11%? ======
#define DUTY_MIN        0.03f     // 3%
#define DUTY_STAND      0.07f     // 7% ??????
#define DUTY_MAX        0.11f     // 11%

// ???? 7% ?????±2%?? 5%~9%
#define DUTY_SWING      0.020f    // ±2.0%

#define STEP_PERIOD_MS  3000      // 1 Hz ??????????? 1000ms?

typedef struct {
    pca9685_t     *pwm;
    motion_mode_t  mode;
    uint16_t       gait_time_ms;  // ???????0..STEP_PERIOD_MS?
} motion_state_t;

static motion_state_t g_motion;

// ?????? -amp..+amp????????
static float triangle_duty(uint16_t phase_ms, uint16_t period_ms, float amp){
    uint16_t q = phase_ms % period_ms;
    uint16_t half = period_ms/2;
    float x;
    if(q < half){
        x = amp * ((float)q / (float)half);                 // 0..+amp
    }else{
        x = amp - 2.0f*amp * ((float)(q - half) / (float)half); // +amp..-amp
    }
    if(x >  amp) x =  amp;
    if(x < -amp) x = -amp;
    return x;
}

// ??? 3%~11% ??????
static void set_hips_dc(float fl, float fr, float rl, float rr){
    if(fl < DUTY_MIN) fl = DUTY_MIN; if(fl > DUTY_MAX) fl = DUTY_MAX;
    if(fr < DUTY_MIN) fr = DUTY_MIN; if(fr > DUTY_MAX) fr = DUTY_MAX;
    if(rl < DUTY_MIN) rl = DUTY_MIN; if(rl > DUTY_MAX) rl = DUTY_MAX;
    if(rr < DUTY_MIN) rr = DUTY_MIN; if(rr > DUTY_MAX) rr = DUTY_MAX;

    pca9685_set_channel_duty(g_motion.pwm, CH_FL, fl);
    pca9685_set_channel_duty(g_motion.pwm, CH_FR, fr);
    pca9685_set_channel_duty(g_motion.pwm, CH_RL, rl);
    pca9685_set_channel_duty(g_motion.pwm, CH_RR, rr);
}

// ????????
void motion_init(pca9685_t *pwm){
    g_motion.pwm = pwm;
    g_motion.mode = MOTION_MODE_STAND;
    g_motion.gait_time_ms = 0;
    // ?????
    set_hips_dc(DUTY_STAND, DUTY_STAND, DUTY_STAND, DUTY_STAND);
}

// ?????????????
void motion_set_mode(motion_mode_t mode){
    g_motion.mode = mode;
    // ????????????????
    switch(mode){
        case MOTION_MODE_STAND:
            set_hips_dc(DUTY_STAND, DUTY_STAND, DUTY_STAND, DUTY_STAND);
            break;
        case MOTION_MODE_PRONE:
            // ????????????
            // ???????FR=11% ???RR=3% ??
            // ???????FL=3% ???RL=11% ??
            set_hips_dc(0.03f, 0.11f, 0.11f, 0.03f);
            break;
        case MOTION_MODE_WALK_FWD:
        case MOTION_MODE_WALK_BACK:
            // ??? 0 ???
            g_motion.gait_time_ms = 0;
            break;
        default:
            break;
    }
}

// ???????????????????? 10ms ?????dt_ms=10?
void motion_update(uint16_t dt_ms){
    // ??/?????????????????????PCA9685 ????
    if(g_motion.mode == MOTION_MODE_STAND ||
       g_motion.mode == MOTION_MODE_PRONE){
        return;
    }

    // ???????????
    int dir = 0;
    if(g_motion.mode == MOTION_MODE_WALK_FWD)  dir = +1;
    if(g_motion.mode == MOTION_MODE_WALK_BACK) dir = -1;
    if(dir == 0) return; // ????

    g_motion.gait_time_ms = (g_motion.gait_time_ms + dt_ms) % STEP_PERIOD_MS;
    uint16_t t    = g_motion.gait_time_ms;
    uint16_t half = STEP_PERIOD_MS / 2;

    // ????????????????????
    float base_fl = triangle_duty(t,           STEP_PERIOD_MS, DUTY_SWING) * dir;
    float base_rr = base_fl;
    float base_fr = triangle_duty(t + half,    STEP_PERIOD_MS, DUTY_SWING) * dir;
    float base_rl = base_fr;

    // ???????????? = ??
    // ???????????? = ?? => ??????
    float d_fl = -base_fl;  // ??
    float d_rl = -base_rl;  // ??
    float d_fr = +base_fr;  // ??
    float d_rr = +base_rr;  // ??

    set_hips_dc(DUTY_STAND + d_fl,
                DUTY_STAND + d_fr,
                DUTY_STAND + d_rl,
                DUTY_STAND + d_rr);
}

