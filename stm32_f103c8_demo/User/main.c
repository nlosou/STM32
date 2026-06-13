#include "stm32f10x.h"

void Delay(uint32_t count) {
    while(count--);
}

int main(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启 GPIOC 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // 配置 PC13 为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    while (1) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 点亮 LED
        Delay(0x7FFFF);
        GPIO_SetBits(GPIOC, GPIO_Pin_13);   // 熄灭 LED
        Delay(0x7FFFF);
    }
}
