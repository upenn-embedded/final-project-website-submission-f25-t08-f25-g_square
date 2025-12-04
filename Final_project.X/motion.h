#ifndef MOTION_H
#define MOTION_H

#include <stdint.h>
#include "pca9685.h"


#define CH_FL 0  // front left
#define CH_FR 1  // front right
#define CH_RL 2  // back left
#define CH_RR 3  // back right

void motion_init(pca9685_t *pwm);


void motion_forward_ms(uint16_t ms);
void motion_backward_ms(uint16_t ms);
void motion_prone(void);  
void motion_stand(void);   

#endif
