#include "main.h"
#include "../ven/device_8digi_test.h"
#include "../ven/system_util.h"
unsigned int *rx = B1_in;
unsigned int *tx = B0_out;
unsigned char rxBuffer = 0;
unsigned char txBuffer = 0;
unsigned char txCount = 0;
unsigned char rxCount = 0;
// unsigned char received = 0;

void send(unsigned char data)
{
    txBuffer = data;
    TIM3->CR1 |= 0x1 << 0; //开始计数
}
void uartInit()
{
    // 外部中断启用
    NVIC->ISER[0] |= 0x1 << 7;   //开启EXTI1,中断向量为7
    RCC->APB2ENR |= 0x1 << 3;    // IOPBEN=1
    RCC->APB2ENR |= 0x1 << 0;    // AFIOEN=1
    GPIOB->CRL &= 0xffffff00;    //与零
    GPIOB->CRL |= 0x00000042;    // b0 推挽输出, b1 推挽输入
    AFIO->EXTICR[0] |= 0x1 << 4; // EXTI1的关联GPIO为GPIOB
    EXTI->FTSR |= 0x1 << 1;      // EXTI1开启下降沿检测
    EXTI->IMR |= 0x1 << 1;       // EXTI1的中断屏蔽打开

    //配置一个RX定时器
    NVIC->ISER[0] |= 0x1 << 28; //开启TIM2中断向量28
    RCC->APB1ENR |= 0x1 << 0;   // TIM2EN=1,开启APB1的TIM2EN
    TIM2->PSC = 71;             //预分频
    TIM2->ARR = 102;            //预装载
    TIM2->DIER |= 0x1 << 0;     // DMA中断使能寄存器UIE允许更新中断
    TIM2->CR1 |= 0x1 << 7;      // ARPE=1允许自动装载
    TIM2->CR1 |= 0x1 << 4;      //向下计数
    TIM2->CR1 |= 0x1 << 0;

    //配置一个TX定时器
    NVIC->ISER[0] |= 0x1 << 29; //开启TIM3中断向量29
    RCC->APB1ENR |= 0x1 << 1;   // TIM3EN=1
    TIM3->PSC = 71;             //预分频
    TIM3->ARR = 102;            //预装载
    TIM3->DIER |= 0x1 << 0;     // UIE=1 允许更新中断
    TIM3->CR1 |= 0x1 << 7;      //允许ARR载入
    TIM3->CR1 |= 0x1 << 4;      //向下计数
    TIM3->CR1 |= 0x1 << 0;      //向下计数
}

int main()
{
    /** 
     * open 72m
     * **/
    FLASH->ACR |= 0x1 << 5; // PRFTBS=1:预取缓冲区启用标记位
    FLASH->ACR |= 0x1 << 4; // PRFTBE=1:启用预取缓冲区
    FLASH->ACR |= 0x2 << 0; // LATENCY=010:flash需要两个等待状态

    RCC->CFGR |= 0x7 << 18; // PLLMUL=0111:PLL提供9倍输出
    RCC->CFGR |= 0x1 << 16; // PLLSRC=1:HSE做为PLL输入时钟
    RCC->CFGR |= 0x4 << 8;  // PPRE1=100:HCLK提供2分频
    RCC->CFGR |= 0x2 << 0;  // SW=10:PLL输出做为系统时钟

    RCC->CR |= 0x1 << 24; // PLLON=1:PLL使能
    RCC->CR |= 0x1 << 16; // HSEON=1:外部高速时钟使能
    // on_72m();
    uartInit();

    //配置led管的针脚
    Device_8digi d8;
    d8.number_system = 16;
    d8.type_digital = 1;
    // IOPBEN=1
    RCC->APB2ENR |= 0x1 << 3;
    // GPIOB 12 13 14 为推挽输出
    GPIOB->CRH &= 0xf000ffff;
    GPIOB->CRH |= 0x03330000;
    //给数码管设置引脚
    d8.chip_74hc595.serialInput = B12_out;
    d8.chip_74hc595.resetClock = B13_out;
    d8.chip_74hc595.shiftClock = B14_out;

    //要显示的数据
    unsigned int numberToShow = 0x00;

    int numberFlag = 0;
    while (1)
    {
        if (rxCount == 8)
        {
            numberFlag = 1;
        }
        if (rxCount == 9 && numberFlag == 1)
        {
            numberFlag = 0;
            //要显示的内容向左移8位;
            numberToShow <<= 8;
            //把buffer的内容或进最后8位;
            numberToShow |= rxBuffer;
            send(rxBuffer);
        }
        if (rxCount == 0)
        {
            device_8digi_show(d8, numberToShow);
        }
    }
}

// uart rx 专用计数器
void TIM2_IRQHandler()
{
    //计数器加1
    rxCount++;
    //如果计数器为1 等待*rx的下拉信号
    if (rxCount == 1)
    {
        // while (*rx != 0)
        ;
    }
    //如果是第2至9位,收取8位rx的信号;
    if (2 <= rxCount && rxCount <= 9)
    {
        rxBuffer >>= 1;
        rxBuffer |= *rx << 7;
    }
    //如果是第十位,等待停止位;
    if (rxCount == 10)
    {
        while (*rx != 1)
            ;

        //关闭TIM2使能
        TIM2->CR1 &= ~(0x1 << 0);
        rxCount = 0;
    }
    //改写TIM2更新标志
    TIM2->SR &= ~(0x1 << 0);
}

void EXTI1_IRQHandler()
{
    //打开TIM2定时器
    TIM2->CR1 |= 0x1 << 0;
    //取反外部中断挂起位
    EXTI->PR |= 0x1 << 1;
}

// tx timer
void TIM3_IRQHandler()
{
    txCount++;
    if (txCount == 1)
    {
        *tx = 0;
    }
    if (txCount > 1 && txCount < 10)
    {
        *tx = txBuffer & 1;
        txBuffer >>= 1;
    }
    if (txCount == 10)
    {
        *tx = 1;
        txCount = 0;
        TIM3->CR1 &= ~(0x1 << 0); //关闭TIM3的CEN
    }
    //改写TIM2更新标志
    TIM3->SR &= ~(0x1 << 0);
}