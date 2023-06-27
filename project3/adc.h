
/******************************************************************************
 *
 * Module: adc
 *
 * File Name: adc.h
 *
 * Description: header file for the AVR ADC driver dynamic configuration
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 5, 2022
 *
 * Version : v2.0.1
 *
 *******************************************************************************/
#include"std_types.h"

#ifndef ADC_H_
#define ADC_H_

/*******************************************************************************
 *                              type definition                                *
 *******************************************************************************/
typedef enum{
	AREF_VOLTAGE_EXTERNAL=0,AVCC_VOLTAGE=1,AREF_VOLTAGE_INTERNAL=3

}ADC_ReferenceVolatge;

typedef enum{
	PRESCALER_2=0,PRESCALER_4=2,PRESCALER_8=3,
	PRESCALER_16=4,PRESCALER_32=5,PRESCALER_64=6,PRESCALER_128=7
}ADC_Prescaler;

/* Channel at which we will get input from it*/
/*typedef enum{
	ADC_CHANNEL_0,ADC_CHANNEL_1,ADC_CHANNEL_2,ADC_CHANNEL_3,
	ADC_CHANNEL_4,ADC_CHANNEL_5,ADC_CHANNEL_6,ADC_CHANNEL_7
}ADC_channelNumber;*/

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
	/*ADC_channelNumber channel_number;*/
}ADC_ConfigType;

#define ADC_MAX_DIGITAL_VALUE 1023
#define ADC_Vref 2.56
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 * initiate the ADC module
 */
void ADC_init(ADC_ConfigType *config);

/* Description :
 * read the value at the channel ( The produced value of conversation )
 */
uint16 ADC_readChannel(uint8 channel);

#endif /* ADC_H_ */
