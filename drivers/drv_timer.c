/*
 * drv_timer.c
 *
 *  Created on: Jul 12, 2023
 *      Author: wysji
 */

#include "ch32v30x.h"
#include <rtdef.h>
#include <rtthread.h>

#include "drivers/user_timer.h"


static void (*timer_irq)(void *args) = NULL;
static void *timer_irq_args = NULL;


void ch32_timer_mode(){
    //定时器中断初始化
    NVIC_InitTypeDef NVIC_InitStructure={0};
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void ch32_timer_init(u16 arr, u16 psc){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM7, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    TIM_ARRPreloadConfig( TIM7, ENABLE );

}

void ch32_timer_attach_irq(void (*timer_handler)(void *args), void *args){
    timer_irq = timer_handler;
    timer_irq_args = args;
}

void ch32_timer_irq_enable(){
    TIM7->CNT=0x00;             //定时器计数先重置为0
    TIM_Cmd(TIM7,ENABLE);       //使能定时器
}

const static struct rt_timer_ops _ch32_timer_ops =
{
    .timer_mode = ch32_timer_mode,
    .timer_init = ch32_timer_init,
    .timer_attach_irq = ch32_timer_attach_irq,
    .timer_irq_enable = ch32_timer_irq_enable,
};

int rt_hw_user_timer_init(void)
{
    int result;
    result = rt_device_timer_register("Timer-7", &_ch32_timer_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_user_timer_init);

//
void TIM7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM7_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();

    // user defined irq_func
    timer_irq(timer_irq_args);

    rt_interrupt_leave();
    FREE_INT_SP();
}
