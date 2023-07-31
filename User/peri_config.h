/*
 * peri_config.h
 *
 *  Created on: Jul 12, 2023
 *      Author: wysji
 */

#ifndef USER_PERI_CONFIG_H_
#define USER_PERI_CONFIG_H_

#include "ch32v30x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/pin.h"
#include "Func.h"


// extern var
extern volatile u8 KeyValue;
extern volatile u8 LcdScreen;
extern volatile u8 DtwRun;
extern struct rt_semaphore sem_key_lock;
extern struct rt_semaphore sem_menu_lock;

/* Global define */
#define rt_pin "pin"
#define pin_wakeup  23
#define pin_up      98
#define pin_down    1
#define pin_back    3
#define pin_confirm 4


// func
void main_init();

//按键中断程序
//该中断是Wake_Up按键，点击进入主菜单
void user_EXTI0_IRQHandler(void *args);

//按键中断程序
void user_EXTI1_IRQHandler(void *args);

//按键中断程序
void user_EXTI2_IRQHandler(void *args);

//按键中断程序
void user_EXTI4_IRQHandler(void *args);

//按键中断程序
void user_EXTI9_5_IRQHandler(void *args);

int key_init();


#endif /* USER_PERI_CONFIG_H_ */
