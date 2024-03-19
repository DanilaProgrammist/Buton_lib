/*
 * button.h
 *
 *  Created on: Mar 1, 2024
 *      Author: Danchkin_Sab
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "stdint.h"
#include "stdbool.h"
#include "at32f425_gpio.h"
typedef enum{
	BUTTON_RIGH = 0x0001,
	BUTTON_LEFT = 0x0002,
	BUTTON_UP = 0x0003,
	BUTTON_DOWN = 0x0004,
	BUTTON_CENTER = 0x0005
}JoyStick_Code;

typedef enum{
	DOWN,
	UP
}Flag;
typedef enum{
	CLICK,
	RETENTION
}MODE;
typedef enum{
	LOW,
	HIGH
}State;
typedef struct{
	uint16_t address;
	gpio_init_type *port;
	Flag flag;
	State state;
	MODE mode;
	uint32_t time;
	uint16_t click_time;

}Button;

void ButtInit(Button* btn, uint16_t address, gpio_init_type* port, MODE mode,...);
uint8_t getButtHold(Button *btn);
uint8_t getClickListen(Button *btn);
uint8_t ButtTrigg(Button* btn);

#endif /* INC_BUTTON_H_ */
