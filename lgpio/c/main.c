/***************************************************************************************
 * Project  :PCA9685
 * Describe :Expand 16-channel PWM through PCA9685
 *			 Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
 *			 Two sets of DC motors first turn forward and then reverse
 * Experimental Platform :Raspberry Pi 4B + Motor And Servo Driver HAT
 * Hardware Connection : Switch
 *			A0 -> OFF					A1 -> OFF
 *			A2 -> OFF					A3 -> OFF
 * 			A4 -> OFF					A5 -> OFF
 * Library Version :WiringPi_V2.52
 * Author		   :Christian
 * Web Site		   :www.seengreat.com
***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include "sg_lgpio.h"
#include "pca9685.h"

volatile sig_atomic_t keep_running = 1;

// signal handler
void signal_handler(int signum) {
    printf("\nReceived signal %d (Ctrl+C), stopping program...\n", signum);
    keep_running = 0; // set the flag bit to cause the main loop to exit
}

// cleaning function, used to stop all PWM outputs
void cleanup_pca9685() {
    printf("Stopping all servos and motors...\n");
    
    // stop servo
    pca_setpwm(SERVO_MOTOR_PWM3, 0, 0);
    pca_setpwm(SERVO_MOTOR_PWM4, 0, 0);
    pca_setpwm(SERVO_MOTOR_PWM5, 0, 0);
    pca_setpwm(SERVO_MOTOR_PWM6, 0, 0);
    pca_setpwm(SERVO_MOTOR_PWM7, 0, 0);
    pca_setpwm(SERVO_MOTOR_PWM8, 0, 0);
    
    // stop DC motor
    pca_setpwm(DC_MOTOR_INA1, 0, 0);
    pca_setpwm(DC_MOTOR_INA2, 0, 0);
    pca_setpwm(DC_MOTOR_INB1, 0, 0);
    pca_setpwm(DC_MOTOR_INB2, 0, 0);
    
    // disable PWM
    pca_setpwm(DC_MOTOR_PWM1, 0, 0);
    pca_setpwm(DC_MOTOR_PWM2, 0, 0);
    
    printf("Cleanup complete. Exiting.\n");
}

int main(void)
{	 
    signal(SIGINT, signal_handler); 
    signal(SIGTERM, signal_handler); 
    
    printf("Program started. Press Ctrl+C to exit.\n");
	
	unsigned short j=0;
	Lgpio_export();
	LG_I2C_Init(0x7f);
    pca_write(pca_mode1,0x0);
    pca_setfreq(330);//Setting PWM Frequency
    
    
	while(keep_running)
	{
		/*
		Pulse time 0.5ms-2.5ms(duty cycle 2.5%-12.5%), 
		frequency 330HZ (period 3.03ms), resolution 4096
		0.5ms+(Angle/180)*(2.5ms-0.5ms)=xms
		xms/frequency=off/4096
		
		0�㣬0.5/3.03*4096=675
		45�㣬1.0/3.03*4096=1351
		90�㣬1.5/3.03*4096=2027
		135�㣬2.0/3.03*4096=2703
		180�㣬2.5/3.03*4096=3379
		*/
	printf("SERVO_MOTOR_PWM3 running.\n");
	for(j=675;j<3379 && keep_running;j+=2)//Steering gear,return to 0°,then turn 180°( return to 0° is instantaneous action)
        {
            pca_setpwm(SERVO_MOTOR_PWM3,0,j);
        }
	for(j=3379;j>675 && keep_running;j-=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM3,0,j);
        }
	
	printf("SERVO_MOTOR_PWM4 running.\n");
        for(j=675;j<3379 && keep_running;j+=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM4,0,j);
        }
	for(j=3379;j>675 && keep_running;j-=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM4,0,j);
        }
	
	printf("SERVO_MOTOR_PWM5 running.\n");
        for(j=675;j<3379 && keep_running;j+=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM5,0,j);
        }
	for(j=3379;j>675 && keep_running;j-=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM5,0,j);
        }
	
	printf("SERVO_MOTOR_PWM6 running.\n");
        for(j=675;j<3379 && keep_running;j+=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM6,0,j);
        }
	for(j=3379;j>675 && keep_running;j-=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM6,0,j);
        }
	
	printf("SERVO_MOTOR_PWM7 running.\n");
        for(j=675;j<3379 && keep_running;j+=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM7,0,j);
        }
	for(j=3379;j>675 && keep_running;j-=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM7,0,j);
        }

	printf("SERVO_MOTOR_PWM8 running.\n");
        for(j=675;j<3379 && keep_running;j+=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM8,0,j);
        }
	for(j=3379;j>675 && keep_running;j-=2)
        {
            pca_setpwm(SERVO_MOTOR_PWM8,0,j);
        }
		if (!keep_running) break; 
		printf("DC_MOTOR_A running.\n");
		printf("CW.\n");		
		pca_setpwm(DC_MOTOR_PWM1,0,4095);
		for(j=0;j<4095 && keep_running;j+=2)
		{
			pca_setpwm(DC_MOTOR_INA2,0,0);
			pca_setpwm(DC_MOTOR_INA1,0,j);
		}
		for(j=4095;j>0 && keep_running;j-=2)
		{
			pca_setpwm(DC_MOTOR_INA2,0,0);
			pca_setpwm(DC_MOTOR_INA1,0,j);
		}
		printf("CCW.\n");
		for(j=0;j<4095 && keep_running;j+=2)
		{
			pca_setpwm(DC_MOTOR_INA1,0,0);
			pca_setpwm(DC_MOTOR_INA2,0,j);
		}
		for(j=4095;j>0 && keep_running;j-=2)
		{
			pca_setpwm(DC_MOTOR_INA1,0,0);
			pca_setpwm(DC_MOTOR_INA2,0,j);
		}
		if (!keep_running) break; 
		printf("DC_MOTOR_B running.\n");	
		pca_setpwm(DC_MOTOR_PWM2,0,4095);
		printf("CW.\n");
		for(j=0;j<4095 && keep_running;j+=2)
		{
			pca_setpwm(DC_MOTOR_INB1,0,0);
			pca_setpwm(DC_MOTOR_INB2,0,j);
		}
		for(j=4095;j>0 && keep_running;j-=2)
		{
			pca_setpwm(DC_MOTOR_INB1,0,0);
			pca_setpwm(DC_MOTOR_INB2,0,j);
		}
		printf("CCW.\n");
		for(j=0;j<4095 && keep_running;j+=2)
		{
			pca_setpwm(DC_MOTOR_INB2,0,0);
			pca_setpwm(DC_MOTOR_INB1,0,j);
		}
		for(j=4095;j>0 && keep_running;j-=2)
		{
			pca_setpwm(DC_MOTOR_INB2,0,0);
			pca_setpwm(DC_MOTOR_INB1,0,j);
		}
	}
	   cleanup_pca9685();
    
    return 0;
}

