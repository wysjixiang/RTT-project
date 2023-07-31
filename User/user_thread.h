
#ifndef __USER_THREAD_H__
#define __USER_THREAD_H__

#include "ch32v30x.h"
#include <rtthread.h>
#include <rthw.h>
#include <rtdef.h>
#include "drivers/pin.h"
#include "Func.h"
#include "peri_config.h"
#include "drivers/user_timer.h"
#include "drv_timer.h"
#include <debug.h>

#define THREAD_STACK_SIZE  512
#define THREAD_PRIORITY 10
#define THREAD_TIMESLICE 10

/* Global Var  */
// 用于控制LCD屏幕主菜单
extern volatile u8 KeyValue;  //键值
extern volatile u8 LcdScreen;
extern volatile u8 DtwRun;
extern volatile u8 TemplateWanted;
extern volatile u8 StateFlag;
extern volatile u8 KeyReg;
// 用于控制LCD屏幕主菜单

void LCD_thread_entry(void *param);
void DTW_thread_entry(void *param);
int thread_sema_init();

#endif
