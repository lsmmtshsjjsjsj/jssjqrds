#ifndef __GTIME_H
#define __GTIME_H

#include "./SYSTEM/sys/sys.h"


/************************************ A��-ͨ�ö�ʱ�� �������ӿ�ʵ����غ궨�� **************************************/

/* TIMX �������ӿڶ��� */

#define GTIM_TIMX_ENCODER_CH1_GPIO_PORT_1         GPIOA
#define GTIM_TIMX_ENCODER_CH1_GPIO_PIN_1          GPIO_PIN_5
#define GTIM_TIMX_ENCODER_CH1_GPIO_CLK_ENABLE_1() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA��ʱ��ʹ�� */

#define GTIM_TIMX_ENCODER_CH2_GPIO_PORT_1         GPIOB
#define GTIM_TIMX_ENCODER_CH2_GPIO_PIN_1          GPIO_PIN_3
#define GTIM_TIMX_ENCODER_CH2_GPIO_CLK_ENABLE_1() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PB��ʱ��ʹ�� */

/* TIMX ���Ÿ�������
 * ��ΪPA15��PB3Ĭ�ϲ�����TIM2�Ĺ��ܽ�, ���뿪������, ��������TIM2�ı�������������
 */
#define GTIM_TIMX_ENCODERCH1_GPIO_AF_1            GPIO_AF1_TIM2                               /* �˿ڸ��õ�TIM2 */
#define GTIM_TIMX_ENCODERCH2_GPIO_AF_1            GPIO_AF1_TIM2

#define GTIM_TIMX_ENCODER_1                       TIM2                                       /* TIM2 */
#define GTIM_TIMX_ENCODER_INT_IRQn_1              TIM2_IRQn
#define GTIM_TIMX_ENCODER_INT_IRQHandler_1        TIM2_IRQHandler
#define GTIM_TIMX_ENCODER_CH1_1                   TIM_CHANNEL_1                               /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_ENCODER_CH1_CLK_ENABLE_1()      do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)  /* TIM2 ʱ��ʹ�� */

#define GTIM_TIMX_ENCODER_CH2_1                   TIM_CHANNEL_2                               /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_ENCODER_CH2_CLK_ENABLE_1()      do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)  /* TIM2 ʱ��ʹ�� */

/************************************ B��-ͨ�ö�ʱ�� �������ӿ�ʵ����غ궨�� **************************************/

/* TIMX �������ӿڶ��� */

#define GTIM_TIMX_ENCODER_CH1_GPIO_PORT_2         GPIOB
#define GTIM_TIMX_ENCODER_CH1_GPIO_PIN_2          GPIO_PIN_6
#define GTIM_TIMX_ENCODER_CH1_GPIO_CLK_ENABLE_2() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PA��ʱ��ʹ�� */

#define GTIM_TIMX_ENCODER_CH2_GPIO_PORT_2         GPIOB
#define GTIM_TIMX_ENCODER_CH2_GPIO_PIN_2          GPIO_PIN_7
#define GTIM_TIMX_ENCODER_CH2_GPIO_CLK_ENABLE_2() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PB��ʱ��ʹ�� */

/* TIMX ���Ÿ�������
 * ��ΪPA15��PB3Ĭ�ϲ�����TIM2�Ĺ��ܽ�, ���뿪������, ��������TIM2�ı�������������
 */
#define GTIM_TIMX_ENCODERCH1_GPIO_AF_2            GPIO_AF2_TIM4                               /* �˿ڸ��õ�TIM2 */
#define GTIM_TIMX_ENCODERCH2_GPIO_AF_2            GPIO_AF2_TIM4

#define GTIM_TIMX_ENCODER_2                       TIM4                                       /* TIM2 */
#define GTIM_TIMX_ENCODER_INT_IRQn_2              TIM4_IRQn
#define GTIM_TIMX_ENCODER_INT_IRQHandler_2        TIM4_IRQHandler
#define GTIM_TIMX_ENCODER_CH1_2                   TIM_CHANNEL_1                               /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_ENCODER_CH1_CLK_ENABLE_2()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)  /* TIM2 ʱ��ʹ�� */

#define GTIM_TIMX_ENCODER_CH2_2                   TIM_CHANNEL_2                               /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_ENCODER_CH2_CLK_ENABLE_2()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)  /* TIM2 ʱ��ʹ�� */


/*************************************************************************************/


void gtim_timx_encoder_chy_init_1(uint16_t arr, uint16_t psc);
int32_t gtime_get_encode_1(void);                                                     /* ��ȡ�������ܼ���ֵ */

void gtim_timx_encoder_chy_init_2(uint16_t arr, uint16_t psc);
int32_t gtime_get_encode_2(void);                                                     /* ��ȡ�������ܼ���ֵ */



  
#endif
















