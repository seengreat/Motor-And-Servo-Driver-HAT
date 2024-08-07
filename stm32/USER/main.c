/***************************************************************************************
 * Project  :PCA9685
 * Describe :Expand 16-channel PWM through PCA9685
 *			 Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
 *			 Two sets of DC motors first turn forward and then reverse
 * Experimental Platform :STM32F103C8T6 + Motor And Servo Driver HAT
 * Hardware Connection :STM32F103 -> Motor And Servo Driver HAT
 *			5V	 ->	5V					PB6 -> SCL1
 *			GND	 ->	GND					PB7 -> SDA1
 *			A0 -> OFF					A1 -> OFF
 *			A2 -> OFF					A3 -> OFF
 * 			A4 -> OFF					A5 -> OFF
 * Library Version :ST_V3.5
 * Author		   :Christian
 * Web Site		   :www.seengreat.com
***************************************************************************************/
#include "sys.h"
#include "delay.h"
#include "myiic.h"
#include "pca9685.h"

int main(void)
{	 
	u16 j=0;
	SystemInit();
	delay_init();
	IIC_Init();
    pca_write(pca_mode1,0x0);
    pca_setfreq(330);//Setting PWM Frequency
	while(1)
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
		for(j=675;j<3379;j++)//Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
		{
			pca_setpwm(SERVO_MOTOR_PWM3,0,j);
		}
		for(j=675;j<3379;j++)//Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
		{
			pca_setpwm(SERVO_MOTOR_PWM4,0,j);
		}
		for(j=675;j<3379;j++)//Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
		{
			pca_setpwm(SERVO_MOTOR_PWM5,0,j);
		}
		for(j=675;j<3379;j++)//Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
		{
			pca_setpwm(SERVO_MOTOR_PWM6,0,j);
		}
		for(j=675;j<3379;j++)//Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
		{
			pca_setpwm(SERVO_MOTOR_PWM7,0,j);
		}
		for(j=675;j<3379;j++)//Steering gear,return to 0��,then turn 180��( return to 0�� is instantaneous action)
		{
			pca_setpwm(SERVO_MOTOR_PWM8,0,j);
		}
		
		pca_setpwm(DC_MOTOR_PWM1,0,4095);
		for(j=0;j<4095;j++)
		{
			pca_setpwm(DC_MOTOR_INA2,0,0);
			pca_setpwm(DC_MOTOR_INA1,0,j);
		}
		for(j=4095;j>0;j--)
		{
			pca_setpwm(DC_MOTOR_INA2,0,0);
			pca_setpwm(DC_MOTOR_INA1,0,j);
		}
		for(j=0;j<4095;j++)
		{
			pca_setpwm(DC_MOTOR_INA1,0,0);
			pca_setpwm(DC_MOTOR_INA2,0,j);
		}
		for(j=4095;j>0;j--)
		{
			pca_setpwm(DC_MOTOR_INA1,0,0);
			pca_setpwm(DC_MOTOR_INA2,0,j);
		}

		pca_setpwm(DC_MOTOR_PWM2,0,4095);
		for(j=0;j<4095;j++)
		{
			pca_setpwm(DC_MOTOR_INB1,0,0);
			pca_setpwm(DC_MOTOR_INB2,0,j);
		}
		for(j=4095;j>0;j--)
		{
			pca_setpwm(DC_MOTOR_INB1,0,0);
			pca_setpwm(DC_MOTOR_INB2,0,j);
		}
		for(j=0;j<4095;j++)
		{
			pca_setpwm(DC_MOTOR_INB2,0,0);
			pca_setpwm(DC_MOTOR_INB1,0,j);
		}
		for(j=4095;j>0;j--)
		{
			pca_setpwm(DC_MOTOR_INB2,0,0);
			pca_setpwm(DC_MOTOR_INB1,0,j);
		}
	}
}

