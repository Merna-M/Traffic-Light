#include "STD_types.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "SEVSEG_interface.h"
#include "TMR0_interface.h"
#define F_CPU 8000000UL
#include "util/delay.h"

sint8 counter_green=19;
sint8 counter_red = 19;
sint8 counter_yellow =9;
volatile uint8 counter_7seg=0;
volatile uint8 flag=0;

void ISR_TMR0(void);

int main(void)
{
	/*Initializations*/
	TMR0_vInit();
	LED_vInit('D',PIN0);
	LED_vInit('D',PIN1);
	LED_vInit('D',PIN2);
	LCD_vInit();
	SEVSEG_vInit('C');
	SEVSEG_vEnableInit('A',PIN0);//en0
	SEVSEG_vEnableInit('A',PIN1);//en1
	//callback
	TMR0_COMP_SetCallBack(ISR_TMR0);
	
	LCD_vMoveCursor(2,1);
	LCD_vSendString("Time Left: ");
	
    while(1)
    {
		//red led on - the rest off
        LED_vSwitchOFF('D',PIN1);
		LED_vSwitchOFF('D',PIN2);
		LED_vSwitchON('D',PIN0);
		LCD_vMoveCursor(1,3);
		LCD_vSendString(" RED Light  ");
		LCD_vMoveCursor(2,12);
		LCD_vSendNumber(counter_red);
		LCD_vSendData(' ');
		
		while(counter_red>=0)
		{
			SEVSEG_vEnableControl('A',PIN1,DISABLE_MUX);
			SEVSEG_vEnableControl('A',PIN0,ENABLE_MUX);
			SEVSEG_vWrite('C',counter_red%10);
			while(flag == 0);
			flag = 0;
			SEVSEG_vEnableControl('A',PIN0,DISABLE_MUX);
			SEVSEG_vEnableControl('A',PIN1,ENABLE_MUX);
			SEVSEG_vWrite('C',counter_red/10);
			while(flag == 0);
			flag = 0;	
			if(counter_7seg>=100)
			{
				counter_7seg=0;
				counter_red--;
				LCD_vMoveCursor(2,12);
				if(counter_red>=0)
				{
					LCD_vSendNumber(counter_red);
					LCD_vSendData(' ');
				}
			}
			
		}
		counter_red=19;
		LED_vSwitchOFF('D',PIN0);
		LED_vSwitchOFF('D',PIN2);
		LED_vSwitchON('D',PIN1);
		LCD_vMoveCursor(1,3);
		LCD_vSendString("YELLOW Light  ");
		LCD_vMoveCursor(2,12);
		LCD_vSendNumber(counter_yellow);
		LCD_vSendData(' ');
		
		while(counter_yellow>=0)
		{
			SEVSEG_vEnableControl('A',PIN1,DISABLE_MUX);
			SEVSEG_vEnableControl('A',PIN0,ENABLE_MUX);
			SEVSEG_vWrite('C',counter_yellow%10);
			while(flag == 0);
			flag = 0;
			SEVSEG_vEnableControl('A',PIN0,DISABLE_MUX);
			SEVSEG_vEnableControl('A',PIN1,ENABLE_MUX);
			SEVSEG_vWrite('C',counter_yellow/10);
			while(flag == 0);
			flag = 0;
			if(counter_7seg>=100)
			{
				counter_7seg=0;
				counter_yellow--;
				LCD_vMoveCursor(2,12);
				if(counter_yellow>=0)
				{
					LCD_vSendNumber(counter_yellow);
					LCD_vSendData(' ');
				}
			}	
			
		}
		counter_yellow=9;
		LED_vSwitchOFF('D',PIN0);
		LED_vSwitchOFF('D',PIN1);
		LED_vSwitchON('D',PIN2);
		LCD_vMoveCursor(1,3);
		LCD_vSendString("GREEN Light  ");
		LCD_vMoveCursor(2,12);
		LCD_vSendNumber(counter_green);
		LCD_vSendData(' ');
		
		while(counter_green>=0)
		{
			SEVSEG_vEnableControl('A',PIN1,DISABLE_MUX);
			SEVSEG_vEnableControl('A',PIN0,ENABLE_MUX);
			SEVSEG_vWrite('C',counter_green%10);
			while(flag == 0);
			flag = 0;
			SEVSEG_vEnableControl('A',PIN0,DISABLE_MUX);
			SEVSEG_vEnableControl('A',PIN1,ENABLE_MUX);
			SEVSEG_vWrite('C',counter_green/10);
			while(flag == 0);
			flag = 0;
			if(counter_7seg>=100)
			{
				counter_7seg=0;
				counter_green--;
				LCD_vMoveCursor(2,12);
				if(counter_green>=0)
				{
					LCD_vSendNumber(counter_green);
					LCD_vSendData(' ');
				}
			}	
			
		}	
		counter_green=19;								
    }
}

void ISR_TMR0(void)
{
	flag=1;
	counter_7seg++;
}