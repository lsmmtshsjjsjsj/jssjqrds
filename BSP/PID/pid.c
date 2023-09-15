
#include "./BSP/PID/pid.h"
#include "./BSP/ATIME/atime.h"
#include "./BSP/GTIME/gtime.h"

PID_TypeDef_1  g_speed_pid_1;           /* 速度环PID参数结构体 */

PID_TypeDef_2  g_speed_pid_2;           /* 速度环PID参数结构体 */
/**
 * @brief       pid初始化
 * @param       无
 * @retval      无
 */
void pid_init_1(void)
{
    g_speed_pid_1.SetPoint = 0;       /* 设定目标值 */
    g_speed_pid_1.ActualValue = 0.0;  /* 期望输出值 */
    g_speed_pid_1.SumError = 0.0;     /* 积分值 */
    g_speed_pid_1.Error = 0.0;        /* Error[1] */
    g_speed_pid_1.LastError = 0.0;    /* Error[-1] */
    g_speed_pid_1.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid_1.Proportion = KP1;    /* 比例常数 Proportional Const */
    g_speed_pid_1.Integral = KI1;      /* 积分常数 Integral Const */
    g_speed_pid_1.Derivative = KD1;    /* 微分常数 Derivative Const */ 
}

void pid_init_2(void)
{
    g_speed_pid_2.SetPoint = 0;       /* 设定目标值 */
    g_speed_pid_2.ActualValue = 0.0;  /* 期望输出值 */
    g_speed_pid_2.SumError = 0.0;     /* 积分值 */
    g_speed_pid_2.Error = 0.0;        /* Error[1] */
    g_speed_pid_2.LastError = 0.0;    /* Error[-1] */
    g_speed_pid_2.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid_2.Proportion = KP2;    /* 比例常数 Proportional Const */
    g_speed_pid_2.Integral = KI2;      /* 积分常数 Integral Const */
    g_speed_pid_2.Derivative = KD2;    /* 微分常数 Derivative Const */ 
}

/**
 * @brief       pid闭环控制
 * @param       *PID：PID结构体变量地址
 * @param       Feedback_value：当前实际值
 * @retval      期望输出值
 */
int32_t increment_pid_ctrl_1(PID_TypeDef_1 *PID,float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* 计算偏差 */
    
#if  INCR_LOCT_SELECT1                                                       /* 增量式PID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* 比例环节 */
                        + (PID->Integral * PID->Error)                                             /* 积分环节 */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* 微分环节 */
    
    PID->PrevError = PID->LastError;                                        /* 存储偏差，用于下次计算 */
    PID->LastError = PID->Error;
    
#else                                                                       /* 位置式PID */
    
    PID->SumError += PID->Error;
    PID->ActualValue = (PID->Proportion * PID->Error)                       /* 比例环节 */
                       + (PID->Integral * PID->SumError)                    /* 积分环节 */
                       + (PID->Derivative * (PID->Error - PID->LastError)); /* 微分环节 */
    PID->LastError = PID->Error;
    
#endif
    return ((int32_t)(PID->ActualValue));                                   /* 返回计算后输出的数值 */
}


int32_t increment_pid_ctrl_2(PID_TypeDef_2 *PID,float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* 计算偏差 */
    
#if  INCR_LOCT_SELECT2                                                       /* 增量式PID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* 比例环节 */
                        + (PID->Integral * PID->Error)                                             /* 积分环节 */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* 微分环节 */
    
    PID->PrevError = PID->LastError;                                        /* 存储偏差，用于下次计算 */
    PID->LastError = PID->Error;
    
#else                                                                       /* 位置式PID */
    
    PID->SumError += PID->Error;
    PID->ActualValue = (PID->Proportion * PID->Error)                       /* 比例环节 */
                       + (PID->Integral * PID->SumError)                    /* 积分环节 */
                       + (PID->Derivative * (PID->Error - PID->LastError)); /* 微分环节 */
    PID->LastError = PID->Error;
    
#endif
    return ((int32_t)(PID->ActualValue));                                   /* 返回计算后输出的数值 */
}
