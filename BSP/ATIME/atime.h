#ifndef __ATIME_H
#define __ATIME_H

#include "./SYSTEM/sys/sys.h"


/*****
**************************电机1******************************
*****/

/* TIMX 互补输出模式 定义 
 * 这里设置互补输出相关硬件配置, CHY即正常输出, CHYN即互补输出
 * 修改CCRx可以修改占空比.
 * 默认是针对TIM1.
 * 注意: 通过修改这些宏定义,可以支持TIM1/TIM8定时器, 任意一个IO口输出互补PWM(前提是必须有互补输出功能)
 */

/* 输出通道引脚 */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_1            GPIOA
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_1             GPIO_PIN_8
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_1()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* 互补输出通道引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_1           GPIOB
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_1            GPIO_PIN_13
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_1()   do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* 刹车输入引脚 */
#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */


#define ATIM_TIMX_CPLM_CHY_GPIO_AF_1             GPIO_AF1_TIM1

/* 互补输出使用的定时器 */
#define ATIM_TIMX_CPLM_1                          TIM1
#define ATIM_TIMX_CPLM_CHY_1                      TIM_CHANNEL_1
#define ATIM_TIMX_CPLM_CHY_CCRY_1                 TIM1->CCR1
#define ATIM_TIMX_CPLM_CLK_ENABLE_1()             do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)    /* TIM1 时钟使能 */

/*****
**************************电机2******************************
*****/

/* TIMX 互补输出模式 定义 
 * 这里设置互补输出相关硬件配置, CHY即正常输出, CHYN即互补输出
 * 修改CCRx可以修改占空比.
 * 默认是针对TIM1.
 * 注意: 通过修改这些宏定义,可以支持TIM1/TIM8定时器, 任意一个IO口输出互补PWM(前提是必须有互补输出功能)
 */

/* 输出通道引脚 */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_2            GPIOE
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_2             GPIO_PIN_11
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_2()    do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* 互补输出通道引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_2           GPIOE
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_2            GPIO_PIN_10
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_2()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

///* 刹车输入引脚 */
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* SD停止引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_SD_2           GPIOF
#define ATIM_TIMX_GPIO_SD_CLK_ENABLE_2          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define ATIM_TIMX_CPLM_SD_GPIO_PIN_2            GPIO_PIN_2


#define ATIM_TIMX_CPLM_CHY_GPIO_AF_2             GPIO_AF1_TIM1

/* 互补输出使用的定时器 */
#define ATIM_TIMX_CPLM_2                          TIM1
#define ATIM_TIMX_CPLM_CHY_2                      TIM_CHANNEL_2
#define ATIM_TIMX_CPLM_CHY_CCRY_2                 TIM1->CCR2
#define ATIM_TIMX_CPLM_CLK_ENABLE_2()             do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)    /* TIM1 时钟使能 */

/*****
**************************电机3******************************
*****/

/* TIMX 互补输出模式 定义 
 * 这里设置互补输出相关硬件配置, CHY即正常输出, CHYN即互补输出
 * 修改CCRx可以修改占空比.
 * 默认是针对TIM1
 * 注意: 通过修改这些宏定义,可以支持TIM1/TIM8定时器, 任意一个IO口输出互补PWM(前提是必须有互补输出功能)
 */

/* 输出通道引脚 */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_3            GPIOC
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_3             GPIO_PIN_6
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_3()    do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* 互补输出通道引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_3           GPIOA
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_3            GPIO_PIN_7
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_3()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

///* 刹车输入引脚 */
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* SD停止引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_SD_3           GPIOG
#define ATIM_TIMX_CPLM_SD_GPIO_PIN_3            GPIO_PIN_11
#define ATIM_TIMX_GPIO_SD_CLK_ENABLE_3          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
/* TIMX REMAP设置*/

#define ATIM_TIMX_CPLM_CHY_GPIO_AF_3             GPIO_AF3_TIM8

/* 互补输出使用的定时器 */
#define ATIM_TIMX_CPLM_3                          TIM8
#define ATIM_TIMX_CPLM_CHY_3                      TIM_CHANNEL_1
#define ATIM_TIMX_CPLM_CHY_CCRY_3                 TIM8->CCR1
#define ATIM_TIMX_CPLM_CLK_ENABLE_3()             do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)    /* TIM1 时钟使能 */

/*****
**************************电机4******************************
*****/

/* TIMX 互补输出模式 定义 
 * 这里设置互补输出相关硬件配置, CHY即正常输出, CHYN即互补输出
 * 修改CCRx可以修改占空比.
 * 默认是针对TIM1
 * 注意: 通过修改这些宏定义,可以支持TIM1/TIM8定时器, 任意一个IO口输出互补PWM(前提是必须有互补输出功能)
 */

/* 输出通道引脚 */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_4            GPIOB
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_4              GPIO_PIN_0
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_4()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* 互补输出通道引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_4            GPIOC
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_4             GPIO_PIN_7
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_4()   do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

///* 刹车输入引脚 */
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/* SD停止引脚 */
#define ATIM_TIMX_CPLM_CHYN_GPIO_SD_4            GPIOG
#define ATIM_TIMX_CPLM_SD_GPIO_PIN_4             GPIO_PIN_12
#define ATIM_TIMX_GPIO_SD_CLK_ENABLE_4           do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
/* TIMX REMAP设置*/

#define ATIM_TIMX_CPLM_CHY_GPIO_AF_4              GPIO_AF3_TIM8

/* 互补输出使用的定时器 */
#define ATIM_TIMX_CPLM_4                           TIM8
#define ATIM_TIMX_CPLM_CHY_4                       TIM_CHANNEL_2
#define ATIM_TIMX_CPLM_CHY_CCRY_4                  TIM8->CCR2
#define ATIM_TIMX_CPLM_CLK_ENABLE_4()             do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)    /* TIM1 时钟使能 */

/******************************************************************************************/

/******************************************************************************************/

void  dcmotor_init_1(void);
void  dcmotor_start_1(void);
void  dcmotor_stop_1(void);
void dcmotor_dir_1(uint8_t para);
void atim_timx_cplm_pwm_set_1(uint16_t ccr);
void atim_timx_cplm_pwm_init_1(uint16_t arr, uint16_t psc);

void atime_motor_speed_dirset_1(int32_t pwm);

void  dcmotor_init_2(void);
void  dcmotor_start_2(void);
void  dcmotor_stop_2(void);
void dcmotor_dir_2(uint8_t para);
void atim_timx_cplm_pwm_set_2(uint16_t ccr);
void atim_timx_cplm_pwm_init_2(uint16_t arr, uint16_t psc);

void atime_motor_speed_dirset_2(int32_t pwm);



#endif
