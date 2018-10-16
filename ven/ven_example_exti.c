#include "ven_example_exti.h"
void
ven_EXTI_init() {
    NVIC->ISER[0] |= 0x40;
    GPIOA->CRL |= 0x8;
    EXTI->IMR |= 0x1;
    EXTI->RTSR |= 0x1;
}
