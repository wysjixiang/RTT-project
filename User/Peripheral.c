/*
 * Peripheral.c
 *
 *  Created on: Jun 22, 2022
 *      Author: wysji
 */

#include "Func.h"


extern volatile uint16_t LaserFlag; // ȫ�ֱ���,�������ⷢ��or������
extern volatile u16 *p_AdcDmaData;
extern volatile u16 DataLaserOn;
extern volatile u16 DataLaserOff;
extern volatile u16 DifData;
extern volatile uint16_t DMAProcessFlag;
extern volatile u8 offset_p;
extern volatile u16 *DataStream;

volatile u16 s_dif =0  ;    //��ֱ���
u8 dma_cnt = 0;             //��־λ

//���ڼ���
u16 i =0      ;
u16 s   =0    ;
u8 j      =0  ;


/********************************************************************
* �� �� ��       : ADC_Function_Init
* ��������    : ��ʼ��ADC
* ��    ��          : ��
* ��    ��          : ��
********************************************************************/
void ADC_Function_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);               //��ʼ��ADCʱ�ӣ�����ʱ��ΪPCLK2��8��Ƶ�����ʱ��Ϊ14MHz

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //����PA1��ΪAD�����

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //����ADģʽΪ����ģʽ��ֻʹ��ADC1
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       //���ö�ͨ��ģʽ�����õ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //��������ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //�������ⲿ����Դ��������������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //Ҫת��ͨ������
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_DMACmd(ADC1, ENABLE); //����DMA
    ADC_Cmd(ADC1, ENABLE);          //ʹ��ADC
    Delay_Ms(20);
    ADC_BufferCmd(ADC1, DISABLE);   //disable buffer
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

    ADC_BufferCmd(ADC1, ENABLE);   //enable buffer
}

//���ڳ�ʼ��
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

//DMA��ʼ��
void DMA1_Init( DMA_Channel_TypeDef* DMA_CHx, u32 ppadr,
        u32 memadr, u16 bufsize)
{

    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);


    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;       //Դ��ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;          //Ŀ�ĵ�ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;      //DMA��������赽MEM
    DMA_InitStructure.DMA_BufferSize = bufsize;             //�����С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;    //�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             //MEM��ַ������
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���贫������Ϊ���֣�16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //MEM��������Ϊ���֣�16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;           //��ͨģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //���ȼ�����Ϊ��
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;            //�ر�MEM��MEM����
    DMA_Init( DMA_CHx, &DMA_InitStructure );

}

//GPIO��ʼ��
void GPIOPB0_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//GPIO��ʼ��
void GPIOPB1_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//��ʱ����ʼ��
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

//��ʱ���жϳ�ʼ��
void TimInterrupt_Init(void)
{
   NVIC_InitTypeDef NVIC_InitStructure={0};
   NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}



// DMA�����жϳ�ʼ��
void DMA1Interrupt_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure={0};
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

// DMA�����жϳ���
void DMA1_Channel1_IRQHandler(void)
{

    rt_kprintf("DMA irq!\r\n");

    //�ж�ADC�������ڹ��������ǰ�״̬�µõ���
    if(1 == LaserFlag)
    {
        s = 0;
        for(i=18; i<26;i++)  // ����ADת��ʱ��ǰ����й��伴���ȶ�״̬�����ֻȡת�����̺��ڵ�8�����ݵ㣬Ȼ����ƽ���õ�һ����Ч����
        {
            s += p_AdcDmaData[i];
        }
        DataLaserOn = s >>3;
        dma_cnt = dma_cnt | 0x01;   //�õ���Ч���ݺ󣬽���־λdma_cnt�ĵ�λ��Ϊ1
    }
    else {
        s = 0;
        for(i=18; i<26;i++)
        {
            s += p_AdcDmaData[i];
        }
        DataLaserOff = s >>3;
        dma_cnt = dma_cnt | 0x10;   //�õ���Ч���ݺ󣬽���־λdma_cnt�ĸ�λ��Ϊ1
    }

    //����־λ�Ƿ�ߵ�λ����1������ʱ�Ѿ������һ�ι�����״̬�¡���״̬�µ����ݲɼ�
    if(dma_cnt == 0x11)
    {
        s_dif += DataLaserOn - DataLaserOff;    //����ֵõ���Ч�⴫������
        j++;
        if(j == 4)          //ÿ4����Ч�����������ƽ���������õ�һ������������ݣ���Ϊ��������
        {
            j = 0;
            DifData = (s_dif>>2);
            s_dif =0;
            *(u16 *)(DataStream + offset_p) = DifData;  //д��DataStream��������
            offset_p ++;                 //�����ݱ�־λǰ������������256ʱ����ض�����Ϊ0
            DMAProcessFlag = 1;          //�ñ�־λ
        }
        dma_cnt = 0x00;                 //���ñ�־λ
    }
    DMA_ClearFlag(DMA1_FLAG_TC1);       //����жϱ�־
}

//��ʱ���жϳ���
//void TIM6_IRQHandler(void)
//{
//    //���Laser״̬��־λ��ʵ�ֹ�����������
//    if(1 == LaserFlag)
//    {
//        GPIO_WriteBit(GPIOB, GPIO_Pin_0, 1);
//        LaserFlag = LaserOff;
//    }
//
//    else {
//        GPIO_WriteBit(GPIOB, GPIO_Pin_0, 0);    //������
//        LaserFlag = LaserOn;
//    }
//
//    DMA1_Channel1->CNTR = 26; //����DMAͨ��1�������
//    TIMProcessFlag = 1;       //�ñ�־λ
//    TIM_ClearFlag(TIM6, TIM_FLAG_Update);//�����־λ���˳��ж�
//}