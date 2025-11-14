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

	//constr
	UART_transaction(UART_HandleTypeDef* huart) : HUART(huart)
	{
		msg.clear();
	};

	void message_print(std::string message)
	{
		message.push_back('\n');
		HAL_UART_Transmit(HUART, (uint8_t*)message.c_str(), message.size(), 100);
	}

	virtual void char_receive()
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

class UART_string_comparator : public UART_transaction
{
private:
	std::string msg;
	UART_HandleTypeDef *HUART;
public:
	//constr
	UART_string_comparator(UART_HandleTypeDef* huart) : UART_transaction(huart)
	{
		msg.clear();
	};

	virtual void char_receive()
	{
		if(Received != 'q') //CARRIAGE RETURN
		{
			msg.push_back((char)Received);
		}
		else{
			//ENTER
			message_decode(msg);
			msg.clear();
		}
		if(msg[0] != '#')
		{
			msg.clear();
		}
	}

	void message_decode(std::string msg)
	{
		if(msg.size() == 2)
		{
			if(msg[0] == '#')
			{
				// MAYBE PROTOCOL MESSAGE
				if(msg[1] == '0')
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				}else if (msg[1] == '1')
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
				}else
				{
					// NOT A PROTOCOL MESSAGE
					return;
				}
			}
			else
			{
				// NOT A PROTOCOL MESSAGE
				return;
			}
		}
	}
};


#endif /* CPP_INC_MAIN_CPP_H_ */
