/*
 * main_cpp.h
 *
 *  Created on: Oct 29, 2025
 *      Author: maciej
 */

#ifndef CPP_INC_MAIN_CPP_H_
#define CPP_INC_MAIN_CPP_H_


class UART_transaction
{
private:
	std::string msg;
	UART_HandleTypeDef *HUART;
public:
	uint8_t Received;

	UART_transaction(UART_HandleTypeDef* huart) : HUART(huart) {msg.clear();};

	void message_print(std::string message)
	{
		message.push_back('\n');
		HAL_UART_Transmit(HUART, (uint8_t*)message.c_str(), message.size(), 100);
	}

	void char_receive()
	{
		if(Received != 13) //CARRIAGE RETURN
		{
			msg.push_back((char)Received);
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		else{
			  message_print(msg);
			  msg.clear();
		}
	}

};


#endif /* CPP_INC_MAIN_CPP_H_ */
