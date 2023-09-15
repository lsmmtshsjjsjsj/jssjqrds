
#include "./BSP/PID/pid.h"
#include "./BSP/ATIME/atime.h"
#include "./BSP/GTIME/gtime.h"

PID_TypeDef_1  g_speed_pid_1;           /* �ٶȻ�PID�����ṹ�� */

PID_TypeDef_2  g_speed_pid_2;           /* �ٶȻ�PID�����ṹ�� */
/**
 * @brief       pid��ʼ��
 * @param       ��
 * @retval      ��
 */
void pid_init_1(void)
{
    g_speed_pid_1.SetPoint = 0;       /* �趨Ŀ��ֵ */
    g_speed_pid_1.ActualValue = 0.0;  /* �������ֵ */
    g_speed_pid_1.SumError = 0.0;     /* ����ֵ */
    g_speed_pid_1.Error = 0.0;        /* Error[1] */
    g_speed_pid_1.LastError = 0.0;    /* Error[-1] */
    g_speed_pid_1.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid_1.Proportion = KP1;    /* �������� Proportional Const */
    g_speed_pid_1.Integral = KI1;      /* ���ֳ��� Integral Const */
    g_speed_pid_1.Derivative = KD1;    /* ΢�ֳ��� Derivative Const */ 
}

void pid_init_2(void)
{
    g_speed_pid_2.SetPoint = 0;       /* �趨Ŀ��ֵ */
    g_speed_pid_2.ActualValue = 0.0;  /* �������ֵ */
    g_speed_pid_2.SumError = 0.0;     /* ����ֵ */
    g_speed_pid_2.Error = 0.0;        /* Error[1] */
    g_speed_pid_2.LastError = 0.0;    /* Error[-1] */
    g_speed_pid_2.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid_2.Proportion = KP2;    /* �������� Proportional Const */
    g_speed_pid_2.Integral = KI2;      /* ���ֳ��� Integral Const */
    g_speed_pid_2.Derivative = KD2;    /* ΢�ֳ��� Derivative Const */ 
}

/**
 * @brief       pid�ջ�����
 * @param       *PID��PID�ṹ�������ַ
 * @param       Feedback_value����ǰʵ��ֵ
 * @retval      �������ֵ
 */
int32_t increment_pid_ctrl_1(PID_TypeDef_1 *PID,float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* ����ƫ�� */
    
#if  INCR_LOCT_SELECT1                                                       /* ����ʽPID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* �������� */
                        + (PID->Integral * PID->Error)                                             /* ���ֻ��� */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* ΢�ֻ��� */
    
    PID->PrevError = PID->LastError;                                        /* �洢ƫ������´μ��� */
    PID->LastError = PID->Error;
    
#else                                                                       /* λ��ʽPID */
    
    PID->SumError += PID->Error;
    PID->ActualValue = (PID->Proportion * PID->Error)                       /* �������� */
                       + (PID->Integral * PID->SumError)                    /* ���ֻ��� */
                       + (PID->Derivative * (PID->Error - PID->LastError)); /* ΢�ֻ��� */
    PID->LastError = PID->Error;
    
#endif
    return ((int32_t)(PID->ActualValue));                                   /* ���ؼ�����������ֵ */
}


int32_t increment_pid_ctrl_2(PID_TypeDef_2 *PID,float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* ����ƫ�� */
    
#if  INCR_LOCT_SELECT2                                                       /* ����ʽPID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* �������� */
                        + (PID->Integral * PID->Error)                                             /* ���ֻ��� */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* ΢�ֻ��� */
    
    PID->PrevError = PID->LastError;                                        /* �洢ƫ������´μ��� */
    PID->LastError = PID->Error;
    
#else                                                                       /* λ��ʽPID */
    
    PID->SumError += PID->Error;
    PID->ActualValue = (PID->Proportion * PID->Error)                       /* �������� */
                       + (PID->Integral * PID->SumError)                    /* ���ֻ��� */
                       + (PID->Derivative * (PID->Error - PID->LastError)); /* ΢�ֻ��� */
    PID->LastError = PID->Error;
    
#endif
    return ((int32_t)(PID->ActualValue));                                   /* ���ؼ�����������ֵ */
}
