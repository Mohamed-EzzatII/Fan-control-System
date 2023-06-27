/************************Libraries and inclusions*******************************/

#include<avr/io.h>
#include"lcd.h"
#include"adc.h"
#include"lm35_sensor.h"
#include"DC_motor.h"

int main(void)
{
	/*initialize LCD module*/
	LCD_init();

	/*setup the configurations of ADC*/
	ADC_ConfigType configurations = {AREF_VOLTAGE_INTERNAL,PRESCALER_8};
	ADC_init(&configurations);

	/* Set I-Bit to enable interrupts*/
	SREG|=(1<<7);

	/*The initial display of LCD*/
	LCD_displayString("FAN IS OFF");
	LCD_moveCursor(1,0);
	LCD_displayString("TEMP IS 0C");

	/*Initialize DC motor*/
	DcMotor_Init();

	/* Variables to detect the change in temperature*/
	uint16 temperature_new=0,temperature_old=1;
	while(1)
	{
		/* get the sensor reading*/
		temperature_new=LM35_getTemperature();

		/*check if the reading is changed or not*/
		if(temperature_new != temperature_old)
		{
			/*The fan is off*/
			if(temperature_new<30)
			{
				/*Display the temperature reading and fan state off*/
				LCD_moveCursor(0,7);
				LCD_displayString("OFF");
				LCD_moveCursor(1,8);
				LCD_integerToString((uint32)temperature_new);

				/*Adjust the fan speed to 0*/
				DcMotor_Rotate(2,0);

				/*adjust the displayed value on screen*/
				if(temperature_new<10)
					LCD_displayString("  C");
				else
					LCD_displayString(" C");
			}

			else if(temperature_new>=30 && temperature_new<60)
			{
				/*Display the temperature reading and fan state on*/
				LCD_moveCursor(0,7);
				LCD_displayString("ON ");
				LCD_moveCursor(1,8);
				LCD_integerToString((uint32)temperature_new);

				/*Adjust the fan speed to 25%*/
				DcMotor_Rotate(1,25);

				LCD_displayString(" C");
			}

			else if(temperature_new>=60 && temperature_new<90)
			{
				/*Display the temperature reading and fan state on*/
				LCD_moveCursor(0,7);
				LCD_moveCursor(0,7);
				LCD_displayString("ON ");
				LCD_moveCursor(1,8);
				LCD_integerToString((uint32)temperature_new);

				/*Adjust the fan speed to 50%*/
				DcMotor_Rotate(2,50);
				LCD_displayString(" C");
			}

			else if(temperature_new>=90 && temperature_new<120)
			{
				/*Display the temperature reading and fan state on*/
				LCD_moveCursor(0,7);
				LCD_displayString("ON ");
				LCD_moveCursor(1,8);
				LCD_integerToString((uint32)temperature_new);

				/*Adjust the fan speed to 75%*/
				DcMotor_Rotate(1,75);

				/*adjust the displayed value on screen*/
				if(temperature_new>99)
					LCD_displayString("C");
				else
					LCD_displayString(" C");
			}

			else if(temperature_new>=120)
			{
				/*Display the temperature reading and fan state on*/
				LCD_moveCursor(0,7);
				LCD_displayString("ON ");
				LCD_moveCursor(1,8);
				LCD_integerToString((uint32)temperature_new);

				/*Adjust the fan speed to 100%*/
				DcMotor_Rotate(2,100);

				LCD_displayString("C");
			}
			/*copy the new value to old one to re-compare:)*/
			temperature_old=temperature_new;
		}
	}
}
