/*
 * main_cpp.cpp
 *
 *  Created on: Oct 28, 2025
 *      Author: maciej
 */
#include <main.h>
#include <string>
#include "main_cpp.h"

extern UART_HandleTypeDef huart1;

//UART_transaction uart_port(&huart1);

UART_string_comparator uart_port(&huart1);

int main_cpp(void)
{
	HAL_UART_Receive_IT(&huart1, &uart_port.Received, 1);
	uart_port.message_print("Program start...");
	while(1)
	{
		//infinite loop

		uart_port.message_print("#1q");
		HAL_Delay(1000);
		uart_port.message_print("#0q");
		HAL_Delay(1000);

	}
	return 0;
}

void USART1_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart1);

  uart_port.char_receive();

  HAL_UART_Receive_IT(&huart1, &uart_port.Received, 1);

}
