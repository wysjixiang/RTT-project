
#ifndef __ARGUMENT_H_
#define __ARGUMENT_H_

/* Global define */

/* Global Variant */
volatile u16 Thresh = 300;      //用于判定有效信息起始的阈值数值
volatile u16 JudgeThresh = 400;
//参数
volatile float fac_dtw = 0.75;      // DTW的权重
volatile float fac_Odist = 0.25;    //欧式距离的权重
volatile u32 MedistanceValue[4];    //欧式距离变量
volatile u32 Finaldist[4];          //最终DTW表征值
volatile uint16_t LaserFlag = 0; // 全局变量,表征激光发光or不发光
volatile uint16_t TIMProcessFlag = 0;//全局变量，表征是否重新执行了一次定时器的中断函数
volatile u16 *p_AdcDmaData = NULL;  // 用于存储ADC采集的数据
volatile u16 DataLaserOn = 0;       //激光亮灭标志位
volatile u16 DataLaserOff = 0;      //标志位
volatile u16 DifData = 0;           //预处理后的一个数据点
volatile uint16_t DMAProcessFlag = 0;  //DMA标志位，DMA传送完成后置1
volatile u16 ThreshVolt = 0;     //定义临界电压值，用来判定是否为导轨光信号
volatile u16 *DataStream = NULL; //DataStream数据流，有效传感数据都被存储在这个数组内
volatile u8 offset_p = 0;   // 用于定位当前时间点下数据点在DataStream数组内的起始位置
volatile u8 DTWDataState = 0;   //表征DTW匹配时候的状态
volatile u32 BestDtwValue[4];

// 用于控制LCD屏幕主菜单
volatile u8 KeyValue = 10;  //键值
volatile u8 LcdScreen =0;
volatile u8 DtwRun = 0;
volatile u8 TemplateWanted = 0;
volatile u8 StateFlag = 1;
volatile u8 KeyReg = 0;
// 用于控制LCD屏幕主菜单


// 模板数据在FLASH内存储的位置
uint32_t AddrTemp[4] = {AddrTemplate3,AddrTemplate4,AddrTemplate6,AddrTemplate7 };
uint32_t AddrTempSize[4] = {AddrTemplate3_size,AddrTemplate4_size,
                                    AddrTemplate6_size,AddrTemplate7_size};
uint32_t AddrTempPeak[4] = {AddrTemplate3_Peak,AddrTemplate4_Peak,
                            AddrTemplate6_Peak,AddrTemplate7_Peak};

//直接申明一个足够大的数组以供计算DTW时使用。
u16 D[max_L][2*max_w +1] = {0xFFFF};
u32 DTW[max_L][2*max_w +1] = {0xFFFFFFFF};
u8 DtwResultReg = 99;   //DTW运算最终结果，表征此时判定识别的样本是哪种姿态

Template *Template_Sample;   //定义结构体指针Template_Sample
TemplateData* TemplateDataSample[4];            //定义结构体指针。存放的都是最终训练好的各个模板的数据

#endif
