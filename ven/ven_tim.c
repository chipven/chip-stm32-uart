#include "ven_tim.h"
// #ifndef TIM2_IRQHandler_Rewrite
// #define TIM2_IRQHandler_Rewrite
// void TIM2_IRQHandler()
// {
//     // ven_tim.idle = 0;
//     acc++;
//     TIM2->SR &= 0xfffffffe;
//     // ven_tim.idle = 1;
// }
// #endif // TIM2_IRQHandler_Rewrite
// #ifndef TIM3_IRQHandler_Rewrite
// void TIM3_IRQHandler()
// {
//     ven_tim.idle = 0;
//     TIM2->SR &= 0xfffffffe;
// }
// #endif // TIM2_IRQHandler_Rewrite
// #ifndef TIM4_IRQHandler_Rewrite
// void TIM4_IRQHandler()
// {
//     ven_tim.idle = 0;
//     TIM2->SR &= 0xfffffffe;
// }
// #endif // TIM2_IRQHandler_Rewrite
// #ifndef TIM5_IRQHandler_Rewrite
// void TIM5_IRQHandler()
// {
//     ven_tim.idle = 0;
//     TIM2->SR &= 0xfffffffe;
// }
// #endif // TIM2_IRQHandler_Rewrite

void ven_delay_tim2(unsigned int ms_5000_max)
{
    // initial timer
    ven_tim.idle = 1;
    // initial interrupt setting
    NVIC->ISER[0] |= 0x10000000;
    RCC->APB1ENR |= 0x00000001;
    TIM2->PSC = RCC->CFGR == 0x001d040a ? 7199 : 7; // 799 7199
    TIM2->ARR = 1 * ms_5000_max;
    TIM2->DIER = 0x1;
    TIM2->CR1 = 0x9;
    // in idle

    Device_8digi d8;
    d8.number_system = 10;
    d8.type_digital = 1;
    d8.chip_74hc595.serialInput = B12_out;
    d8.chip_74hc595.resetClock = B13_out;
    d8.chip_74hc595.shiftClock = B14_out;
    while (1)
    {
        // device_8digi_show(d8, ven_tim.acc);
        device_8digi_show(d8, 0xfc);
    }
}
void ven_TIM2_init()
{
    NVIC->ISER[0] = 0x10000000;
    RCC->APB1ENR |= 0x00000001;
    TIM2->PSC = RCC->CFGR == 0x001d040a ? 7199 : 799; // 799 7199
    TIM2->ARR = 10000;
    TIM2->CR1 = 0x1;
    TIM2->DIER = 0x1;
}
