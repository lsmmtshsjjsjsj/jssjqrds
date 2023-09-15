#ifndef __ATIME_H
#define __ATIME_H

#include "./SYSTEM/sys/sys.h"


/*****
**************************���1******************************
*****/

/* TIMX �������ģʽ ���� 
 * �������û���������Ӳ������, CHY���������, CHYN���������
 * �޸�CCRx�����޸�ռ�ձ�.
 * Ĭ�������TIM1.
 * ע��: ͨ���޸���Щ�궨��,����֧��TIM1/TIM8��ʱ��, ����һ��IO���������PWM(ǰ���Ǳ����л����������)
 */

/* ���ͨ������ */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_1            GPIOA
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_1             GPIO_PIN_8
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_1()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* �������ͨ������ */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_1           GPIOB
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_1            GPIO_PIN_13
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_1()   do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* ɲ���������� */
#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */


#define ATIM_TIMX_CPLM_CHY_GPIO_AF_1             GPIO_AF1_TIM1

/* �������ʹ�õĶ�ʱ�� */
#define ATIM_TIMX_CPLM_1                          TIM1
#define ATIM_TIMX_CPLM_CHY_1                      TIM_CHANNEL_1
#define ATIM_TIMX_CPLM_CHY_CCRY_1                 TIM1->CCR1
#define ATIM_TIMX_CPLM_CLK_ENABLE_1()             do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)    /* TIM1 ʱ��ʹ�� */

/*****
**************************���2******************************
*****/

/* TIMX �������ģʽ ���� 
 * �������û���������Ӳ������, CHY���������, CHYN���������
 * �޸�CCRx�����޸�ռ�ձ�.
 * Ĭ�������TIM1.
 * ע��: ͨ���޸���Щ�궨��,����֧��TIM1/TIM8��ʱ��, ����һ��IO���������PWM(ǰ���Ǳ����л����������)
 */

/* ���ͨ������ */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_2            GPIOE
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_2             GPIO_PIN_11
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_2()    do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* �������ͨ������ */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_2           GPIOE
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_2            GPIO_PIN_10
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_2()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

///* ɲ���������� */
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* SDֹͣ���� */
#define ATIM_TIMX_CPLM_CHYN_GPIO_SD_2           GPIOF
#define ATIM_TIMX_GPIO_SD_CLK_ENABLE_2          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
#define ATIM_TIMX_CPLM_SD_GPIO_PIN_2            GPIO_PIN_2


#define ATIM_TIMX_CPLM_CHY_GPIO_AF_2             GPIO_AF1_TIM1

/* �������ʹ�õĶ�ʱ�� */
#define ATIM_TIMX_CPLM_2                          TIM1
#define ATIM_TIMX_CPLM_CHY_2                      TIM_CHANNEL_2
#define ATIM_TIMX_CPLM_CHY_CCRY_2                 TIM1->CCR2
#define ATIM_TIMX_CPLM_CLK_ENABLE_2()             do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)    /* TIM1 ʱ��ʹ�� */

/*****
**************************���3******************************
*****/

/* TIMX �������ģʽ ���� 
 * �������û���������Ӳ������, CHY���������, CHYN���������
 * �޸�CCRx�����޸�ռ�ձ�.
 * Ĭ�������TIM1
 * ע��: ͨ���޸���Щ�궨��,����֧��TIM1/TIM8��ʱ��, ����һ��IO���������PWM(ǰ���Ǳ����л����������)
 */

/* ���ͨ������ */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_3            GPIOC
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_3             GPIO_PIN_6
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_3()    do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* �������ͨ������ */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_3           GPIOA
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_3            GPIO_PIN_7
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_3()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

///* ɲ���������� */
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* SDֹͣ���� */
#define ATIM_TIMX_CPLM_CHYN_GPIO_SD_3           GPIOG
#define ATIM_TIMX_CPLM_SD_GPIO_PIN_3            GPIO_PIN_11
#define ATIM_TIMX_GPIO_SD_CLK_ENABLE_3          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
/* TIMX REMAP����*/

#define ATIM_TIMX_CPLM_CHY_GPIO_AF_3             GPIO_AF3_TIM8

/* �������ʹ�õĶ�ʱ�� */
#define ATIM_TIMX_CPLM_3                          TIM8
#define ATIM_TIMX_CPLM_CHY_3                      TIM_CHANNEL_1
#define ATIM_TIMX_CPLM_CHY_CCRY_3                 TIM8->CCR1
#define ATIM_TIMX_CPLM_CLK_ENABLE_3()             do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)    /* TIM1 ʱ��ʹ�� */

/*****
**************************���4******************************
*****/

/* TIMX �������ģʽ ���� 
 * �������û���������Ӳ������, CHY���������, CHYN���������
 * �޸�CCRx�����޸�ռ�ձ�.
 * Ĭ�������TIM1
 * ע��: ͨ���޸���Щ�궨��,����֧��TIM1/TIM8��ʱ��, ����һ��IO���������PWM(ǰ���Ǳ����л����������)
 */

/* ���ͨ������ */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT_4            GPIOB
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN_4              GPIO_PIN_0
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_4()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* �������ͨ������ */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT_4            GPIOC
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN_4             GPIO_PIN_7
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_4()   do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

///* ɲ���������� */
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOE
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_15
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/* SDֹͣ���� */
#define ATIM_TIMX_CPLM_CHYN_GPIO_SD_4            GPIOG
#define ATIM_TIMX_CPLM_SD_GPIO_PIN_4             GPIO_PIN_12
#define ATIM_TIMX_GPIO_SD_CLK_ENABLE_4           do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
/* TIMX REMAP����*/

#define ATIM_TIMX_CPLM_CHY_GPIO_AF_4              GPIO_AF3_TIM8

/* �������ʹ�õĶ�ʱ�� */
#define ATIM_TIMX_CPLM_4                           TIM8
#define ATIM_TIMX_CPLM_CHY_4                       TIM_CHANNEL_2
#define ATIM_TIMX_CPLM_CHY_CCRY_4                  TIM8->CCR2
#define ATIM_TIMX_CPLM_CLK_ENABLE_4()             do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)    /* TIM1 ʱ��ʹ�� */

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
