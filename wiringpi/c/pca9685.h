#ifndef __PCA9685_H
#define __PCA9685_H

#define SERVO_MOTOR_PWM3 6
#define SERVO_MOTOR_PWM4 7
#define SERVO_MOTOR_PWM5 8
#define SERVO_MOTOR_PWM6 9
#define SERVO_MOTOR_PWM7 10
#define SERVO_MOTOR_PWM8 11

#define DC_MOTOR_PWM1 0
#define DC_MOTOR_INA1 2
#define DC_MOTOR_INA2 1

#define DC_MOTOR_PWM2 5
#define DC_MOTOR_INB1 3
#define DC_MOTOR_INB2 4

#define PCA9685_SUBADR1 0x2 
#define PCA9685_SUBADR2 0x3 
#define PCA9685_SUBADR3 0x4 
#define pca_mode1 0x0 
#define pca_pre 0xFE 
#define LED0_ON_L 0x6 
#define LED0_ON_H 0x7 
#define LED0_OFF_L 0x8 
#define LED0_OFF_H 0x9 
#define ALLLED_ON_L 0xFA 
#define ALLLED_ON_H 0xFB 
#define ALLLED_OFF_L 0xFC 
#define ALLLED_OFF_H 0xFD 

extern int i2c_Fd;

void pca_write(unsigned char Address,unsigned char value);
unsigned char pca_read(unsigned char Address);
void pca_setfreq(float freq);
void pca_setpwm(unsigned char num, unsigned int on, unsigned int off);

#endif

