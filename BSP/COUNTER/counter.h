#ifndef __COUNTER_H
#define __COUNTER_H

#include "./SYSTEM/sys/sys.h"

/* ������ʱ�� ���� 
 * ���������ֵ�����ڼ����ٶ�
 */
#define BTIM_TIMX_INT                           TIM7  
#define BTIM_TIMX_INT_IRQn                      TIM7_IRQn
#define BTIM_TIMX_INT_IRQHandler                TIM7_IRQHandler
#define BTIM_TIMX_INT_CLK_ENABLE()              do{ __HAL_RCC_TIM7_CLK_ENABLE(); }while(0)    /* TIM6 ʱ��ʹ�� */

#define ROTO_RATIO      2000  /* ����*��Ƶϵ������11*4=44 */
#define REDUCTION_RATIO 30  /* ���ٱ�30:1 */

/* ���1�����ṹ�� */
typedef struct 
{
  uint8_t state;          /*���״̬*/
  float current;          /*�������*/
  float volatage;         /*�����ѹ*/
  float power;            /*�������*/
  float speed;            /*���ʵ���ٶ�*/
  int32_t motor_pwm;      /*���ñȽ�ֵ��С */
} Motor_TypeDef_1;

typedef struct 
{
  int encode_old;                  /* ��һ�μ���ֵ */
  int encode_now;                  /* ��ǰ����ֵ */
  float speed;                     /* �������ٶ� */
} ENCODE_TypeDef_1;

extern ENCODE_TypeDef_1 g_encode_1;    /* �������������� */
extern Motor_TypeDef_1  g_motor_data_1;  /*�����������*/

void speed_computer_1(int32_t encode_now, uint8_t ms);


/* ���2�����ṹ�� */
typedef struct 
{
  uint8_t state;          /*���״̬*/
  float current;          /*�������*/
  float volatage;         /*�����ѹ*/
  float power;            /*�������*/
  float speed;            /*���ʵ���ٶ�*/
  int32_t motor_pwm;      /*���ñȽ�ֵ��С */
} Motor_TypeDef_2;

typedef struct 
{
  int encode_old;                  /* ��һ�μ���ֵ */
  int encode_now;                  /* ��ǰ����ֵ */
  float speed;                     /* �������ٶ� */
}ENCODE_TypeDef_2;

extern ENCODE_TypeDef_2 g_encode_2;    /* �������������� */
extern Motor_TypeDef_2  g_motor_data_2;  /*�����������*/

void speed_computer_2(int32_t encode_now, uint8_t ms);


void btim_timx_int_init(uint16_t arr, uint16_t psc);
void btim_timx_int_init_1(uint16_t arr, uint16_t psc);

#endif
