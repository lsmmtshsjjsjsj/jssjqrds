#ifndef __PID_H
#define __PID_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* PID1��ز��� */

#define  INCR_LOCT_SELECT1  1         /* 0��λ��ʽ ��1������ʽ */

#if INCR_LOCT_SELECT1

/* ����ʽPID������غ� */
#define  KP1      105.00f               /* P����*/
#define  KI1      1.00f               /* I����*/
#define  KD1      0.10f               /* D����*/
#define  SMAPLSE_PID_SPEED1  5       /* �������� ��λms*/

#else

/* λ��ʽPID������غ� */
#define  KP1      0.0f               /* P����*/
#define  KI1      8.00f               /* I����*/
#define  KD1      0.0f                /* D����*/
#define  SMAPLSE_PID_SPEED1  10       /* �������� ��λms*/

#endif

/* PID�����ṹ�� */
typedef struct
{
    __IO float  SetPoint;            /* �趨Ŀ�� */
    __IO float  ActualValue;         /* �������ֵ */
    __IO float  SumError;            /* ����ۼ� */
    __IO float  Proportion;          /* �������� P */
    __IO float  Integral;            /* ���ֳ��� I */
    __IO float  Derivative;          /* ΢�ֳ��� D */
    __IO float  Error;               /* Error[1] */
    __IO float  LastError;           /* Error[-1] */
    __IO float  PrevError;           /* Error[-2] */
} PID_TypeDef_1;

extern PID_TypeDef_1  g_speed_pid_1;     /*�ٶȻ�PID�����ṹ��*/

/******************************************************************************************/
/* PID2��ز��� */

#define  INCR_LOCT_SELECT2  1         /* 0��λ��ʽ ��1������ʽ */

#if INCR_LOCT_SELECT2

/* ����ʽPID������غ� */
#define  KP2      105.00f               /* P����*/
#define  KI2      1.00f               /* I����*/
#define  KD2      0.10f               /* D����*/
#define  SMAPLSE_PID_SPEED2  50       /* �������� ��λms*/

#else

/* λ��ʽPID������غ� */
#define  KP2      7.0f               /* P����*/
#define  KI2      1.241f               /* I����*/
#define  KD2      0.15f                /* D����*/
#define  SMAPLSE_PID_SPEED2  50       /* �������� ��λms*/

#endif

/* PID�����ṹ�� */
typedef struct
{
    __IO float  SetPoint;            /* �趨Ŀ�� */
    __IO float  ActualValue;         /* �������ֵ */
    __IO float  SumError;            /* ����ۼ� */
    __IO float  Proportion;          /* �������� P */
    __IO float  Integral;            /* ���ֳ��� I */
    __IO float  Derivative;          /* ΢�ֳ��� D */
    __IO float  Error;               /* Error[1] */
    __IO float  LastError;           /* Error[-1] */
    __IO float  PrevError;           /* Error[-2] */
} PID_TypeDef_2;

extern PID_TypeDef_2  g_speed_pid_2;     /*�ٶȻ�PID�����ṹ��*/

/******************************************************************************************/

void pid_init_1(void);                 /* pid��ʼ�� */
int32_t increment_pid_ctrl_1(PID_TypeDef_1 *PID,float Feedback_value);      /* pid�ջ����� */

void pid_init_2(void);                 /* pid��ʼ�� */
int32_t increment_pid_ctrl_2(PID_TypeDef_2 *PID,float Feedback_value);      /* pid�ջ����� */

#endif
