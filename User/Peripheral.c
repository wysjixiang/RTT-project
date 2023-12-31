/*
 * Peripheral.c
 *
 *  Created on: Jun 22, 2022
 *      Author: wysji
 */

#include "Func.h"


extern volatile uint16_t LaserFlag; // 全局变量,表征激光发光or不发光
extern volatile u16 *p_AdcDmaData;
extern volatile u16 DataLaserOn;
extern volatile u16 DataLaserOff;
extern volatile u16 DifData;
extern volatile uint16_t DMAProcessFlag;
extern volatile u8 offset_p;
extern volatile u16 *DataStream;

volatile u16 s_dif =0  ;    //差分变量
u8 dma_cnt = 0;             //标志位

//用于计数
u16 i =0      ;
u16 s   =0    ;
u8 j      =0  ;


/********************************************************************
* 函 数 名       : ADC_Function_Init
* 函数功能    : 初始化ADC
* 输    入          : 无
* 输    出          : 无
********************************************************************/
void ADC_Function_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);               //初始化ADC时钟，设置时钟为PCLK2的8分频，最大时钟为14MHz

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //配置PA1口为AD输入口

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //设置AD模式为单独模式，只使用ADC1
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       //禁用多通道模式，启用单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //启动连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //不启用外部触发源，启动软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //要转换通道数量
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_DMACmd(ADC1, ENABLE); //启动DMA
    ADC_Cmd(ADC1, ENABLE);          //使能ADC
    Delay_Ms(20);
    ADC_BufferCmd(ADC1, DISABLE);   //disable buffer
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

    ADC_BufferCmd(ADC1, ENABLE);   //enable buffer
}

//串口初始化
void USART1_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

//    DMA_Cmd(DMA1_Channel4, ENABLE); /* USART1 Tx */

    USART_Cmd(USART1, ENABLE);

}

//DMA初始化
void DMA1_Init( DMA_Channel_TypeDef* DMA_CHx, u32 ppadr,
        u32 memadr, u16 bufsize)
{

    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);


    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;       //源地址
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;          //目的地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;      //DMA方向从外设到MEM
    DMA_InitStructure.DMA_BufferSize = bufsize;             //传输大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;    //外设地址自增关
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             //MEM地址自增开
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //外设传输数据为半字，16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //MEM传输数据为半字，16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;           //普通模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //优先级设置为高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;            //关闭MEM到MEM传输
    DMA_Init( DMA_CHx, &DMA_InitStructure );

}

//GPIO初始化
void GPIOPB0_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//GPIO初始化
void GPIOPB1_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//定时器初始化
void TIM6_Init( u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM6, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM6, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_ARRPreloadConfig( TIM6, ENABLE );

}

//定时器中断初始化
void TimInterrupt_Init(void)
{
   NVIC_InitTypeDef NVIC_InitStructure={0};
   NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}



// DMA传输中断初始化
void DMA1Interrupt_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure={0};
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

// DMA传输中断程序
void DMA1_Channel1_IRQHandler(void)
{

    rt_kprintf("DMA irq!\r\n");

    //判定ADC数据是在光纤亮还是暗状态下得到的
    if(1 == LaserFlag)
    {
        s = 0;
        for(i=18; i<26;i++)  // 由于AD转化时，前面会有过充即不稳定状态，因此只取转换过程后期的8个数据点，然后做平均得到一个有效数据
        {
            s += p_AdcDmaData[i];
        }
        DataLaserOn = s >>3;
        dma_cnt = dma_cnt | 0x01;   //得到有效数据后，将标志位dma_cnt的低位置为1
    }
    else {
        s = 0;
        for(i=18; i<26;i++)
        {
            s += p_AdcDmaData[i];
        }
        DataLaserOff = s >>3;
        dma_cnt = dma_cnt | 0x10;   //得到有效数据后，将标志位dma_cnt的高位置为1
    }

    //检查标志位是否高低位都置1，即此时已经完成了一次光纤亮状态下、暗状态下的数据采集
    if(dma_cnt == 0x11)
    {
        s_dif += DataLaserOn - DataLaserOff;    //做差分得到有效光传感数据
        j++;
        if(j == 4)          //每4个有效差分数据再做平均处理，得到一个处理后的数据，作为最终数据
        {
            j = 0;
            DifData = (s_dif>>2);
            s_dif =0;
            *(u16 *)(DataStream + offset_p) = DifData;  //写入DataStream数据流中
            offset_p ++;                 //将数据标志位前进，当计数到256时，会截断重置为0
            DMAProcessFlag = 1;          //置标志位
        }
        dma_cnt = 0x00;                 //重置标志位
    }
    DMA_ClearFlag(DMA1_FLAG_TC1);       //清除中断标志
}

//定时器中断程序
//void TIM6_IRQHandler(void)
//{
//    //检查Laser状态标志位。实现光纤亮暗交替
//    if(1 == LaserFlag)
//    {
//        GPIO_WriteBit(GPIOB, GPIO_Pin_0, 1);
//        LaserFlag = LaserOff;
//    }
//
//    else {
//        GPIO_WriteBit(GPIOB, GPIO_Pin_0, 0);    //先亮灯
//        LaserFlag = LaserOn;
//    }
//
//    DMA1_Channel1->CNTR = 26; //重置DMA通道1传输计数
//    TIMProcessFlag = 1;       //置标志位
//    TIM_ClearFlag(TIM6, TIM_FLAG_Update);//清除标志位，退出中断
//}
