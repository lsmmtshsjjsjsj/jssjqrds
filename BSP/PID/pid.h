#ifndef __PID_H
#define __PID_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* PID1相关参数 */

#define  INCR_LOCT_SELECT1  1         /* 0：位置式 ，1：增量式 */

#if INCR_LOCT_SELECT1

/* 增量式PID参数相关宏 */
#define  KP1      105.00f               /* P参数*/
#define  KI1      1.00f               /* I参数*/
#define  KD1      0.10f               /* D参数*/
#define  SMAPLSE_PID_SPEED1  5       /* 采样周期 单位ms*/

#else

/* 位置式PID参数相关宏 */
#define  KP1      0.0f               /* P参数*/
#define  KI1      8.00f               /* I参数*/
#define  KD1      0.0f                /* D参数*/
#define  SMAPLSE_PID_SPEED1  10       /* 采样周期 单位ms*/

#endif

/* PID参数结构体 */
typedef struct
{
    __IO float  SetPoint;            /* 设定目标 */
    __IO float  ActualValue;         /* 期望输出值 */
    __IO float  SumError;            /* 误差累计 */
    __IO float  Proportion;          /* 比例常数 P */
    __IO float  Integral;            /* 积分常数 I */
    __IO float  Derivative;          /* 微分常数 D */
    __IO float  Error;               /* Error[1] */
    __IO float  LastError;           /* Error[-1] */
    __IO float  PrevError;           /* Error[-2] */
} PID_TypeDef_1;

extern PID_TypeDef_1  g_speed_pid_1;     /*速度环PID参数结构体*/

/******************************************************************************************/
/* PID2相关参数 */

#define  INCR_LOCT_SELECT2  1         /* 0：位置式 ，1：增量式 */

#if INCR_LOCT_SELECT2

/* 增量式PID参数相关宏 */
#define  KP2      105.00f               /* P参数*/
#define  KI2      1.00f               /* I参数*/
#define  KD2      0.10f               /* D参数*/
#define  SMAPLSE_PID_SPEED2  50       /* 采样周期 单位ms*/

#else

/* 位置式PID参数相关宏 */
#define  KP2      7.0f               /* P参数*/
#define  KI2      1.241f               /* I参数*/
#define  KD2      0.15f                /* D参数*/
#define  SMAPLSE_PID_SPEED2  50       /* 采样周期 单位ms*/

#endif

/* PID参数结构体 */
typedef struct
{
    __IO float  SetPoint;            /* 设定目标 */
    __IO float  ActualValue;         /* 期望输出值 */
    __IO float  SumError;            /* 误差累计 */
    __IO float  Proportion;          /* 比例常数 P */
    __IO float  Integral;            /* 积分常数 I */
    __IO float  Derivative;          /* 微分常数 D */
    __IO float  Error;               /* Error[1] */
    __IO float  LastError;           /* Error[-1] */
    __IO float  PrevError;           /* Error[-2] */
} PID_TypeDef_2;

extern PID_TypeDef_2  g_speed_pid_2;     /*速度环PID参数结构体*/

/******************************************************************************************/

void pid_init_1(void);                 /* pid初始化 */
int32_t increment_pid_ctrl_1(PID_TypeDef_1 *PID,float Feedback_value);      /* pid闭环控制 */

void pid_init_2(void);                 /* pid初始化 */
int32_t increment_pid_ctrl_2(PID_TypeDef_2 *PID,float Feedback_value);      /* pid闭环控制 */

#endif
