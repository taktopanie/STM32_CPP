#include <main.h>
#include <vector>
#include <algorithm>

class gpio
{
private:
	uint16_t LED_PIN;
	GPIO_TypeDef * LED_PORT;

public:

	gpio(GPIO_TypeDef * PORT, uint16_t PIN) : LED_PIN(PIN), LED_PORT(PORT){}

	void gpio_toggle()
	{
		HAL_GPIO_TogglePin(LED_PORT, LED_PIN );
	}
	void gpio_setHigh()
	{
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
	}
	void gpio_setLow()
	{
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
	}

};


std::vector<int> values = {111,200,300};
std::vector<int> val_2;

int my_main(void)
{
	gpio LED_1(GPIOC,GPIO_PIN_13);
	std::copy(values.begin(), values.end(), std::back_inserter(val_2));

	while(1)
	{
		for(auto item : val_2)
		{
			LED_1.gpio_toggle();
			HAL_Delay(item);
		}


	}
	return 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_13);
		while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));

	}
}
