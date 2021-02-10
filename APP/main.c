/*
 * main.c
 *
 *  Created on: Jan 29, 2021
 *      Author: Kishk
 *
 */

#include "../Services/STD_TYPES.h"
#include "../Services/BIT_MATHS.h"

#include "../MCAL/01-DIO/DIO_interface.h"
#include "../HAL/01-LED/LED_interface.h"
#include "../HAL/02-SW/SW_interface.h"

#include <util/delay.h>
#include "../HAL/03-SSD/SSD_interface.h"

#define SSD_REST		10

#define TIME			50
#define FIRST_DIGIT(Number)	 	Number % 10
#define SECOND_DIGIT(Number) 	Number / 10

int main(void) {
	u8 LOC_u8Counter = 0;
	LED_Type RED_LED = { DIO_PORTB_PIN2, LED_ACTIVE_HIGH };
	SSD_Type Segment = { DIO_PORTA, SSD_COMMEN_ANODE };
	SW_Type Switch_1 = { DIO_PORTB_PIN0, SW_PULL_UP };
	SW_Type Switch_2 = { DIO_PORTB_PIN1, SW_PULL_UP };

	DIO_enumSetPortDirection(DIO_PORTB, DIO_DIRECTION_OUTPUT);
	SSD_voidInit(Segment);
	SW_voidInit(Switch_1);
	SW_voidInit(Switch_2);
	LED_voidInit(RED_LED);

	while (1) {
		if (SW_u8GetPressed(Switch_1)) {
			if (LOC_u8Counter == 99) {
				LOC_u8Counter = 0;
				LED_voidLedOn(RED_LED);
			} else {
				LOC_u8Counter++;
			}
		}

		else if (SW_u8GetPressed(Switch_2)) {

			if (LOC_u8Counter == 0) {
				LOC_u8Counter = 99;
				LED_voidLedOn(RED_LED);

			} else {
				LOC_u8Counter--;
			}
		}

		for (u8 LOC_u8Iterator = 0; LOC_u8Iterator < 10; LOC_u8Iterator++) {
			DIO_enumSetPinValue(DIO_PORTB_PIN6, DIO_HIGH);
			DIO_enumSetPinValue(DIO_PORTB_PIN7, DIO_LOW);
			SSD_voidSelectNumber(Segment, FIRST_DIGIT(LOC_u8Counter));
			_delay_ms(SSD_REST);
			DIO_enumSetPinValue(DIO_PORTB_PIN6, DIO_LOW);
			DIO_enumSetPinValue(DIO_PORTB_PIN7, DIO_HIGH);
			SSD_voidSelectNumber(Segment, SECOND_DIGIT(LOC_u8Counter));
			_delay_ms(SSD_REST);
		}

	}

}
