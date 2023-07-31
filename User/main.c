
// Version�� DtwMapping_FinalVersion
//  2022/8/10
// ����ƥ����ԣ����ñȽ�ģʽ���б𣬷�����ֵ���޷�ʽ
// �Ż��˵�����-ɾȥcleartemplate���ܣ�����waveformչʾ���ι���
// �޸�ģ���ȡ����Gettemplate����
// �޸�ģ��ѵ���㷨������������Ⱥ�㷨���ҳ�ȫ�����ŵ�ģ��
// DTW�������а�����ŷʽ�����Ȩ��

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
#include "argument.h"
#include "user_thread.h"


/* Global Variant */
extern volatile uint16_t LaserFlag; // ȫ�ֱ���,�������ⷢ��or������
extern volatile uint16_t TIMProcessFlag;//ȫ�ֱ����������Ƿ�����ִ����һ�ζ�ʱ�����жϺ���
extern volatile u16 *p_AdcDmaData;  // ���ڴ洢ADC�ɼ�������
extern volatile u16 ThreshVolt;     //�����ٽ��ѹֵ�������ж��Ƿ�Ϊ������ź�
extern volatile u16 *DataStream; //DataStream����������Ч�������ݶ����洢�����������
extern volatile u32 BestDtwValue[4];
//ֱ������һ���㹻��������Թ�����DTWʱʹ�á�
extern u16 D[max_L][2*max_w +1];
extern u32 DTW[max_L][2*max_w +1];

extern Template *Template_Sample;   //����ṹ��ָ��Template_Sample
extern TemplateData* TemplateDataSample[4];            //����ṹ��ָ�롣��ŵĶ�������ѵ���õĸ���ģ�������

rt_tick_t tick;

// func init
void data_init();
void peripheral_init();
extern int thread_sema_init();
void user_timer_init();


int main(void)
{
    int err;

    main_init();
    err = key_init();
    if(err != RT_NULL){
        rt_kprintf("key init error\r\n");
        return -1;
    } else{
        rt_kprintf("key init success!\r\n");
    }

    data_init();

    // init thread & sema
    thread_sema_init();
    rt_kprintf("thread_sema init success!\r\n");

    peripheral_init();
    rt_kprintf("Peripheral init success!\r\n");

    return 0;
}

void data_init(){
	int k,kk;
    for(k=0;k<max_L;k++)
    {
        for(kk=0;kk<2*max_w+1;kk++)
        {
            D[k][kk] = 0xFFFF;
            DTW[k][kk] = 0x0;
        }
    }

    for(k=0;k<4;k++)
    {
        BestDtwValue[k] = 0xFFFFFFFF;
    }

    /*********************************************************/
    /*****              �ڴ����                                                  ***********/
    /*********************************************************/
    /*********************************************************/
        DataStream = (u16* )rt_malloc(256*2);   //Ԥ�����ڴ������������ݣ����Դ��256��u16������
        p_AdcDmaData = (u16* )rt_malloc( 26*2);   //Ԥ�����ڴ��ADC�������ݣ�26*2�ֽ�,26��ADC����

        Template_Sample = (Template* )rt_malloc(4);
        Template_Sample->p_data = (u16* )rt_malloc( 400);   //Ԥ�����ڴ����洢�ɼ�����ÿ��������ģ������,400���ֽ�,200��u16data


        TemplateDataSample[0] = (TemplateData* )rt_malloc(8);
        TemplateDataSample[0]->p_data = NULL;
        TemplateDataSample[0]->sz = 0;
        TemplateDataSample[0]->peak = 0;

        TemplateDataSample[1] = (TemplateData* )rt_malloc(8);
        TemplateDataSample[1]->p_data = NULL;
        TemplateDataSample[1]->sz = 0;
        TemplateDataSample[1]->peak = 0;

        TemplateDataSample[2] = (TemplateData* )rt_malloc(8);
        TemplateDataSample[2]->p_data = NULL;
        TemplateDataSample[2]->sz = 0;
        TemplateDataSample[2]->peak = 0;

        TemplateDataSample[3] = (TemplateData* )rt_malloc(8);
        TemplateDataSample[3]->p_data = NULL;
        TemplateDataSample[3]->sz = 0;
        TemplateDataSample[3]->peak = 0;
}

void peripheral_init(){
    /*********************************************************/
    /*****              ��ʼ������                                               ***********/
    /*********************************************************/
    /*********************************************************/

       NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
       Delay_Init();
       //GPIOPB0_INIT();     //�����ź��������
       //GPIOPB1_INIT();     //�����ź��������
       //USART1_Init(115200);  //USART1��ʼ��

       ADC_Function_Init();  //ADC��ʼ��
       ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 ); //ADC����
       ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //������������ADת��
       //����DMA1��ͨ����ͨ��1��ADC�������ݵ��ڴ�
       DMA1_Init( DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)p_AdcDmaData, 26);
       DMA1Interrupt_Init();   //DMA�����жϣ�������Ϻ�����жϳ���
       DMA_ITConfig( DMA1_Channel1, DMA_IT_TC, ENABLE); //����DMAͨ��1�ж�

       //    LCD initial
       RCC_AHBPeriphClockCmd(RCC_AHBPeriph_RNG, ENABLE);
       RNG_Cmd(ENABLE);
       lcd_init();
       lcd_fill(0,0,239,239,BLACK);
       lcd_show_string(20, 80, 24, "Press Wake_Up");
       lcd_show_string(20, 160, 24, "To MainMenu");

       DMA1_Channel1->CNTR = 0; //DMA�������ݸ�����0
       DMA_Cmd( DMA1_Channel1, ENABLE );   //ʹ��DMAͨ��

            //    LCD initial
            Delay_Init();

            for(int i=0;i<10;i++){
                tick = rt_tick_get();
                rt_kprintf("tick = %d\r\n",tick);
            }
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_RNG, ENABLE);
            RNG_Cmd(ENABLE);
            //lcd_init();
            lcd_fill(0,0,239,239,BLACK);
            lcd_show_string(20, 80, 24, "Press Wake_Up");
            lcd_show_string(20, 160, 24, "To MainMenu");

        //for(int i=0;i<10;i++){
        //    tick = rt_tick_get();
        //    rt_kprintf("tick = %d\r\n",tick);
        //}

        user_timer_init();

    //�Ȼ�ȡ����Ĺ��ź�ǿ��    ThreshVolt��
    Delay_Ms(200);
    rt_kprintf("after delay 200ms\r\n");
    ThreshVolt = GetThreshHoldVolt();
    ThreshVolt = 400;
    rt_kprintf("ThreshVolt = %d\r\n",ThreshVolt);
}

//��ʱ���жϳ���
static void user_timer_irq(void *args)
{
    //rt_kprintf("irq\r\n");
    //���Laser״̬��־λ��ʵ�ֹ�����������
    if(1 == LaserFlag)
    {
        LaserFlag = LaserOff;
    }
    else {
        LaserFlag = LaserOn;
    }
    DMA1_Channel1->CNTR = 26; //����DMAͨ��1�������
    TIMProcessFlag = 1;       //�ñ�־λ
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);//�����־λ���˳��ж�
}

void user_timer_init(){
    /* RT-Thread Hardware TIMER APIs */
    rt_user_timer_mode();
    rt_user_timer_init( 50-1, 960-1);
    rt_user_timer_attach_irq(user_timer_irq, RT_NULL);
    rt_user_timer_irq_enable();
}
