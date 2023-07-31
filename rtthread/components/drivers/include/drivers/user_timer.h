/*
 * user_timer.h
 *
 *  Created on: Jul 12, 2023
 *      Author: wysji
 */

#ifndef RTTHREAD_COMPONENTS_DRIVERS_INCLUDE_DRIVERS_USER_TIMER_H_
#define RTTHREAD_COMPONENTS_DRIVERS_INCLUDE_DRIVERS_USER_TIMER_H_

#include <rtdef.h>
#include "ch32v30x.h"

struct rt_device_timer {
    struct rt_device parent;
    const struct rt_timer_ops *ops;
};


struct rt_timer_ops
{
    void (*timer_mode)(void );
    void (*timer_write)(struct rt_device *device, rt_base_t pin, rt_base_t value);
    int (*timer_read)(struct rt_device *device, rt_base_t pin);
    void (*timer_init)(u16 arr, u16 psc);

    /* TODO: add timer interrupt */
    void (*timer_attach_irq)(void (*timer_handler)(void *args), void *args);
    void (*timer_dettach_irq)(struct rt_device *device, rt_int32_t pin);
    void (*timer_irq_enable)(void);
};

int rt_device_timer_register(const char *name, const struct rt_timer_ops *ops, void *user_data);
/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_mode();

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_init(u16 arr, u16 psc);

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_attach_irq(void (*timer_handler)(void *args), void *args);

/* RT-Thread Hardware TIMER APIs */
void rt_user_timer_irq_enable();

#endif /* RTTHREAD_COMPONENTS_DRIVERS_INCLUDE_DRIVERS_USER_TIMER_H_ */
