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
#include "sg_lgpio.h"
#include <math.h>
#include "pca9685.h"

void pca_write(unsigned char Address,unsigned char value)
{ 
	lgI2cWriteByteData (I2C_handle,Address,value);
}

unsigned char pca_read(unsigned char Address)
{
	return lgI2cReadByteData(I2C_handle,Address);
}

void pca_setfreq(float freq)
{
	unsigned char prescale,oldmode,newmode;
	double prescaleval;
	freq *= 0.92;
	prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	prescale =floor(prescaleval + 0.5);

	oldmode = pca_read(pca_mode1);			//pca_mode1 0x0
	newmode = (oldmode&0x7F) | 0x10;		// sleep  0x0&0x7f=0x0  0x0|0x10=0x10
	pca_write(pca_mode1, newmode);			//go to sleep  
	pca_write(pca_pre, prescale); 			//set the prescaler 
	pca_write(pca_mode1, oldmode);			//oldmode 0x0
	delay(2);
	pca_write(pca_mode1, oldmode | 0xa1); 	//0x0|0xa1=10100001
}

/*num: 0~15, on: 0~4096,off: 0~4096
A PWM cycle is divided into 4096 parts, counting from 0 to +1, jumping to high level when counting to ON, counting to off
Jump to low until 4096 is reached and restart. So we can delay when on is not equal to 0, and when on is equal to 0,
The value of off/4096 is the PWM duty cycle. */
void pca_setpwm(unsigned char num, unsigned int on, unsigned int off)
{
	pca_write(LED0_ON_L+4*num,on);
	pca_write(LED0_ON_H+4*num,on>>8);
	pca_write(LED0_OFF_L+4*num,off);
	pca_write(LED0_OFF_H+4*num,off>>8);
}

