/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c - Auto-generated by Anjuta's Makefile project wizard
 * 
 */
#include <stdlib.h>
#include <t89c51cc02.h>
#include <mytypes.h>
#include <isrvectors.h>
#include <stdio.h>
#include <sysCfg.h>
#include <usart.h>
#include <timer0.h>
#include <timer1.h>
#include <pca.h>
#include <ledtable.h>
#include <adc.h>

void main(void)
{
	__u16 u16AdcWert;
	__u16 u16AdcSpg;
	__u16 u16Loop;
	
	/*
	__u16 u16Baudrate[] = 
	{
		50, 300, 1200, 2400, 4800,
		9600, 19200, 38400, 57600,
		0
	};
	*/
	//Systeminitialisierung
	SysInit(20000000, X2_ON);

	//Interruptvektorsystem initialisieren
	IsrInit();

	//serielle Schnittstelle initialisieren
	UsartInit();
	UsartSetBaudrate(57600);
	UsartRecEna();
	
	//ADC-Initialisieren
	AdcInit(ADC_IN0);
	
	//PCA-Timer initialisieren
	PcaInit(FPCA_2);
	PcaInitModul(Pca0, Pwm);
	PcaInitModul(Pca1, Pwm);

	printf_tiny("\r\nStarting Application-Loop\r\n");
	while (1)
	{
		u16AdcWert = Adc10BitConversion(ADC_CH0);
		u16AdcSpg = (__u16) ((3003L * (__u32)u16AdcWert) >> 10);

		PcaSetPwm(Pca0, u8LedValues[ADDH]);
		PcaSetPwm(Pca1, ADDH);
		printf_tiny("AD-Wert: %d = %dmV        \r",u16AdcWert, u16AdcSpg);
		for (u16Loop = 10000; u16Loop; u16Loop--);
	}
}
