#ifndef __COUNTER_H
#define __COUNTER_H

#include "./SYSTEM/sys/sys.h"

/* 基本定时器 定义 
 * 捕获编码器值，用于计算速度
 */
#define BTIM_TIMX_INT                           TIM7  
#define BTIM_TIMX_INT_IRQn                      TIM7_IRQn
#define BTIM_TIMX_INT_IRQHandler                TIM7_IRQHandler
#define BTIM_TIMX_INT_CLK_ENABLE()              do{ __HAL_RCC_TIM7_CLK_ENABLE(); }while(0)    /* TIM6 时钟使能 */

#define ROTO_RATIO      2000  /* 线数*倍频系数，即11*4=44 */
#define REDUCTION_RATIO 30  /* 减速比30:1 */

/* 电机1参数结构体 */
typedef struct 
{
  uint8_t state;          /*电机状态*/
  float current;          /*电机电流*/
  float volatage;         /*电机电压*/
  float power;            /*电机功率*/
  float speed;            /*电机实际速度*/
  int32_t motor_pwm;      /*设置比较值大小 */
} Motor_TypeDef_1;

typedef struct 
{
  int encode_old;                  /* 上一次计数值 */
  int encode_now;                  /* 当前计数值 */
  float speed;                     /* 编码器速度 */
} ENCODE_TypeDef_1;

extern ENCODE_TypeDef_1 g_encode_1;    /* 编码器参数变量 */
extern Motor_TypeDef_1  g_motor_data_1;  /*电机参数变量*/

void speed_computer_1(int32_t encode_now, uint8_t ms);


/* 电机2参数结构体 */
typedef struct 
{
  uint8_t state;          /*电机状态*/
  float current;          /*电机电流*/
  float volatage;         /*电机电压*/
  float power;            /*电机功率*/
  float speed;            /*电机实际速度*/
  int32_t motor_pwm;      /*设置比较值大小 */
} Motor_TypeDef_2;

typedef struct 
{
  int encode_old;                  /* 上一次计数值 */
  int encode_now;                  /* 当前计数值 */
  float speed;                     /* 编码器速度 */
}ENCODE_TypeDef_2;

extern ENCODE_TypeDef_2 g_encode_2;    /* 编码器参数变量 */
extern Motor_TypeDef_2  g_motor_data_2;  /*电机参数变量*/

void speed_computer_2(int32_t encode_now, uint8_t ms);


void btim_timx_int_init(uint16_t arr, uint16_t psc);
void btim_timx_int_init_1(uint16_t arr, uint16_t psc);

#endif
