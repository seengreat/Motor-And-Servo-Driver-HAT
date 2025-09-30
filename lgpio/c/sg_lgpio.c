
#include "sg_lgpio.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int res;
int I2C_handle;
int SPI_handle;
int Gpio_handle;

void delay(uint32_t xms)
{
    lguSleep(xms/1000.0);
}
int Lgpio_export(void)
{
    FILE *fp;
    char buff[4];
    fp = popen("cat /proc/cpuinfo | grep 'Pi 5'", "r");
    if (fp == NULL) 
    {
        printf("The Raspberry PI model is not determine!\n");
        return -1;
    }

    if(fgets(buff, sizeof(buff), fp) != NULL)//Pi 5
    {
        Gpio_handle = lgGpiochipOpen(4);
        if (Gpio_handle < 0 )
        {
            printf( "gpiochip4 open failed\n");
            return -1;
        }
	    printf("open pi 5 gpiochip\n");
    }
    else //other model of Pi
    {
        Gpio_handle = lgGpiochipOpen(0);
        if (Gpio_handle < 0 )
        {
            printf( "gpiochip0 open failed\n");
            return -1;
        }
	printf("open pi gpiochip\n");
    }
        
    return 0;
}

int Lgpio_set_pinmode(int pin_number,int mode)
{
    if(mode == LGPIO_OUTPUT)
    {
        lgGpioClaimOutput(Gpio_handle, 0, pin_number, LGPIO_LOW);
    }
    if(mode == LGPIO_INPUT)
    {
        lgGpioClaimInput(Gpio_handle, LG_SET_PULL_UP,pin_number);		
    }
    return 0;
    
}

int Lgpio_read_pin(int pin_number)
{
    uint8_t res = 0;
    res = lgGpioRead(Gpio_handle,pin_number);

    return (res);	
}

int Lgpio_write_pin(int pin_number, int value)
{
    lgGpioWrite(Gpio_handle, pin_number, value);
}

void LG_I2C_Init(uint8_t dev_addr)
{
    I2C_handle = lgI2cOpen(1, dev_addr, 0);//use i2c_1
}

void LG_SPI_Init(int dev, int chain, int baud)
{
    SPI_handle = lgSpiOpen(dev, chain, baud, 0);
}

void LG_SPI_writebyte(uint8_t value)
{
   lgSpiWrite(SPI_handle,(char*)&value, 1);
}

void LG_SPI_write_bytes(uint8_t *data, uint32_t len)
{
    lgSpiWrite(SPI_handle,(char*) data, len);
}

//freq:0.1-10000
//duty:pwm duty cycle in %:0-100
void LG_PWM(int pin_number, float freq, float duty)
{
    lgTxPwm(Gpio_handle,pin_number,freq,duty,0,0);//for infinite
}
