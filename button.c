/*
 * button.c
 *
 *  Created on: Mar 1, 2024
 *      Author: Danchkin_Sab
 */
#include "stdint.h"
#include "main.h"
#include "button.h"
void ButtInit(Button* btn, uint16_t address, GPIO_TypeDef* port, MODE mode, ...){
	btn->address = address;
	btn->port = port;
	btn->flag = DOWN;
	btn->mode = mode;
	btn->port->MODER |= (0<<address);
	btn->port->PUPDR |= (01<<address);
}
uint8_t getClickListen(Button *btn){
	btn->state = !gpio_input_data_bit_read(btn->port, btn->address);
	//btn->state = btn->port->IDR;
	if (btn->state && !btn->flag && (HAL_GetTick() - btn->time > btn->click_time)){
		btn->flag = true;
		btn->time = HAL_GetTick();
	}
	if (!btn->state && btn->flag && (HAL_GetTick() - btn->time > btn->click_time)){
		btn->flag = false;
		btn->time = HAL_GetTick();
		return 1;
	}
}
uint8_t getButtHold(Button *btn){
	//btn->state = btn->port->IDR;
	btn->state = !gpio_input_data_bit_read(btn->port, btn->address);
	if (btn->state && !btn->flag && (HAL_GetTick() - btn->time > 100)){
		btn->flag = true;
		btn->time = HAL_GetTick();

	}
	if (btn->state && btn->flag && (HAL_GetTick() - btn->time > btn->click_time)){
		btn->time = HAL_GetTick();
		return 1;
	}
	if (!btn->state && btn->flag && (HAL_GetTick() - btn->time > btn->click_time)){
		btn->flag = false;
		btn->time = HAL_GetTick();

	}
}
uint8_t ButtTrigg(Button* btn){
	switch(btn->mode){
		case CLICK:
			btn->click_time = 100;
			return getClickListen(btn);
			break;
		case RETENTION:
			btn->click_time = 3000;
			return getButtHold(btn);
			break;

	}
	return 0;
}
