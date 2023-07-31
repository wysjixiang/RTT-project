

#include "peri_config.h"


void main_init(){
    rt_kprintf("\r\n MCU: CH32V307\r\n");
    SystemCoreClockUpdate();
    rt_kprintf(" SysClk: %dHz\r\n",SystemCoreClock);
    rt_kprintf(" ChipID: %08x\r\n",DBGMCU_GetCHIPID());
    rt_kprintf(" www.wch.cn\r\n");
}

//�����жϳ���
//���ж���Wake_Up����������������˵�
void user_EXTI0_IRQHandler(void *args)
{
    DtwRun = 0;
    LcdScreen = ParameterMod;
    rt_sem_release(&sem_menu_lock);
    EXTI_ClearFlag(EXTI_Line0); // ���жϱ�־λΪ��

}

//�����жϳ���
void user_EXTI1_IRQHandler(void *args)
{
    KeyValue = Up;
    rt_sem_release(&sem_key_lock);
    EXTI_ClearFlag(EXTI_Line1); // ���жϱ�־λΪ��
}

//�����жϳ���
void user_EXTI2_IRQHandler(void *args)
{
    KeyValue = Down;
    rt_sem_release(&sem_key_lock);
    EXTI_ClearFlag(EXTI_Line2); // ���жϱ�־λΪ��
}

//�����жϳ���
void user_EXTI4_IRQHandler(void *args)
{
    KeyValue = Back;
    rt_sem_release(&sem_key_lock);
    EXTI_ClearFlag(EXTI_Line4); // ���жϱ�־λΪ��
}

//�����жϳ���
void user_EXTI9_5_IRQHandler(void *args)
{
    KeyValue = Confirm;
    rt_sem_release(&sem_key_lock);
    EXTI_ClearFlag(EXTI_Line5); // ���жϱ�־λΪ��
}

int key_init(){

    int err;
    /* Global Variable */
    static struct rt_device_pin_mode wakeup_mode = {
            .pin = pin_wakeup,
            .mode = PIN_MODE_INPUT_PULLUP,
    };
    static struct rt_device_pin_mode up_mode = {
            .pin = pin_up,
            .mode = PIN_MODE_INPUT_PULLUP,
    };
    static struct rt_device_pin_mode down_mode = {
            .pin = pin_down,
            .mode = PIN_MODE_INPUT_PULLUP,
    };
    static struct rt_device_pin_mode back_mode = {
            .pin = pin_back,
            .mode = PIN_MODE_INPUT_PULLUP,
    };
    static struct rt_device_pin_mode confirm_mode = {
            .pin = pin_confirm,
            .mode = PIN_MODE_INPUT_PULLDOWN,
    };

    // pin device is already init before main
    rt_device_t pin_dev =rt_device_find(rt_pin);
    struct rt_device_pin *pin = (struct rt_device_pin *)pin_dev;

    if(pin_dev == RT_NULL){
        rt_kprintf("Can not find pin_dev!\r\n");
        return -1;
    }

    err = rt_device_control(pin_dev, 0, &wakeup_mode);
    if(err != RT_NULL){
        rt_kprintf("Control Error!\r\n");
        return -1;
    }

    err = rt_device_control(pin_dev, 0, &up_mode);
    if(err != RT_NULL){
        rt_kprintf("Control Error!\r\n");
        return -1;
    }

    err = rt_device_control(pin_dev, 0, &down_mode);
    if(err != RT_NULL){
        rt_kprintf("Control Error!\r\n");
        return -1;
    }

    err = rt_device_control(pin_dev, 0, &back_mode);
    if(err != RT_NULL){
        rt_kprintf("Control Error!\r\n");
        return -1;
    }

    err = rt_device_control(pin_dev, 0, &confirm_mode);
    if(err != RT_NULL){
        rt_kprintf("Control Error!\r\n");
        return -1;
    }


    pin->ops->pin_attach_irq(pin_dev,wakeup_mode.pin ,EXTI_Mode_Interrupt,user_EXTI0_IRQHandler,RT_NULL);
    pin->ops->pin_irq_enable(pin_dev,wakeup_mode.pin ,PIN_IRQ_ENABLE);

    pin->ops->pin_attach_irq(pin_dev,up_mode.pin ,EXTI_Mode_Interrupt,user_EXTI1_IRQHandler,RT_NULL);
    pin->ops->pin_irq_enable(pin_dev,up_mode.pin ,PIN_IRQ_ENABLE);

    pin->ops->pin_attach_irq(pin_dev,down_mode.pin ,EXTI_Mode_Interrupt,user_EXTI2_IRQHandler,RT_NULL);
    pin->ops->pin_irq_enable(pin_dev,down_mode.pin ,PIN_IRQ_ENABLE);

    pin->ops->pin_attach_irq(pin_dev,back_mode.pin ,EXTI_Mode_Interrupt,user_EXTI4_IRQHandler,RT_NULL);
    pin->ops->pin_irq_enable(pin_dev,back_mode.pin ,PIN_IRQ_ENABLE);

    pin->ops->pin_attach_irq(pin_dev,confirm_mode.pin ,EXTI_Mode_Interrupt,user_EXTI9_5_IRQHandler,RT_NULL);
    pin->ops->pin_irq_enable(pin_dev,confirm_mode.pin ,PIN_IRQ_ENABLE);


    // remember you must open a device before read/write...
    err = rt_device_open(pin_dev, RT_DEVICE_OFLAG_RDWR);
    if(err != RT_EOK){
        rt_kprintf("Device open Error!\r\n");
        return -1;
    }
    return 0;
}

