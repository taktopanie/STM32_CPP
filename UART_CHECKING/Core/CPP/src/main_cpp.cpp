/*
 * main_cpp.cpp
 *
 *  Created on: Oct 28, 2025
 *      Author: maciej
 */
#include <main.h>
#include <string>

//Private extern
extern uint8_t Received;
extern UART_HandleTypeDef huart1;

std::string message;

int main_cpp(void)
{

	return 0;
}

void cpp_receive(void)
{
	if(Received != 13) //CARRIAGE RETURN
	{
		message.push_back((char)Received);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
	else{
		  message.push_back('\n');
		  HAL_UART_Transmit(&huart1, (uint8_t*)message.c_str(), message.size(), 100);
		  message.clear();
	}

}
