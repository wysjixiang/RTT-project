/*
 * user_timer.c
 *
 *  Created on: Jul 12, 2023
 *      Author: wysji
 */

#include "drivers/user_timer.h"
#include <rtdef.h>
#include <rtthread.h>


static struct rt_device_timer _hw_timer;


int rt_device_timer_register(const char *name, const struct rt_timer_ops *ops, void *user_data)
{
    //_hw_timer.parent.type         = RT_Device_Class_Miscellaneous;
    _hw_timer.parent.type         = RT_Device_Class_Timer;
    _hw_timer.parent.rx_indicate  = RT_NULL;
    _hw_timer.parent.tx_complete  = RT_NULL;

    _hw_timer.parent.init         = RT_NULL;
    _hw_timer.parent.open         = RT_NULL;
    _hw_timer.parent.close        = RT_NULL;
    _hw_timer.parent.read         = RT_NULL;
    _hw_timer.parent.write        = RT_NULL;
    _hw_timer.parent.control      = RT_NULL;

    _hw_timer.ops                 = ops;
    _hw_timer.parent.user_data    = user_data;

    /* register a character device */
    rt_device_register(&_hw_timer.parent, name, RT_DEVICE_FLAG_RDWR);

    return 0;
}

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_mode()
{
    RT_ASSERT(_hw_timer.ops != RT_NULL);
    _hw_timer.ops->timer_mode();
}

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_init(u16 arr, u16 psc)
{
    RT_ASSERT(_hw_timer.ops != RT_NULL);
    _hw_timer.ops->timer_init(arr,psc);
}

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_attach_irq(void (*timer_handler)(void *args), void *args)
{
    RT_ASSERT(_hw_timer.ops != RT_NULL);
    _hw_timer.ops->timer_attach_irq(timer_handler,args);
}

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_irq_enable()
{
    RT_ASSERT(_hw_timer.ops != RT_NULL);
    _hw_timer.ops->timer_irq_enable();
}
