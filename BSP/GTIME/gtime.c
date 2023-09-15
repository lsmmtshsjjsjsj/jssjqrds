#include "./BSP/GTIME/gtime.h"

#include "./SYSTEM/usart/usart.h"

#include "./BSP/COUNTER/counter.h"

#include "./BSP/PID/pid.h"

#include "./BSP/ATIME/atime.h"

uint8_t  g_run_flag_1 = 1;                                                /* 电机启停状态标志，0：停止，1：启动 */
uint8_t  g_run_flag_2 = 1;                                                /* 电机启停状态标志，0：停止，1：启动 */

/*****
**************************电机1****************************************************************************************************
*****/

TIM_HandleTypeDef g_timx_encode_chy_handle_1;         /* 定时器x句柄 */
TIM_Encoder_InitTypeDef g_timx_encoder_chy_handle_1;  /* 定时器编码器句柄 */


/**
 * @brief       通用定时器TIMX 通道Y 编码器接口模式 初始化函数
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为42M, 所以定时器时钟 = 84Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
 
void gtim_timx_encoder_chy_init_1(uint16_t arr, uint16_t psc)
{
    /* 定时器x配置 */
    g_timx_encode_chy_handle_1.Instance = GTIM_TIMX_ENCODER_1;                      /* 定时器x */
    g_timx_encode_chy_handle_1.Init.Prescaler = psc;                              /* 定时器分频 */
    g_timx_encode_chy_handle_1.Init.Period = arr;                                 /* 自动重装载值 */
    g_timx_encode_chy_handle_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
	g_timx_encode_chy_handle_1.Init.CounterMode = TIM_COUNTERMODE_UP;
    
    /* 定时器x编码器配置 */
    g_timx_encoder_chy_handle_1.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
    g_timx_encoder_chy_handle_1.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_timx_encoder_chy_handle_1.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_timx_encoder_chy_handle_1.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_timx_encoder_chy_handle_1.IC1Filter = 10;                                   /* 滤波器设置 */
    g_timx_encoder_chy_handle_1.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_timx_encoder_chy_handle_1.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_timx_encoder_chy_handle_1.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_timx_encoder_chy_handle_1.IC2Filter = 10;                                   /* 滤波器设置 */
    HAL_TIM_Encoder_Init(&g_timx_encode_chy_handle_1, &g_timx_encoder_chy_handle_1);/* 初始化定时器x编码器 */
     
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_1,GTIM_TIMX_ENCODER_CH1_1);     /* 使能编码器通道1 */
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_1,GTIM_TIMX_ENCODER_CH2_1);     /* 使能编码器通道2 */
	
    
    __HAL_TIM_CLEAR_FLAG(&g_timx_encode_chy_handle_1,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
	__HAL_TIM_ENABLE_IT(&g_timx_encode_chy_handle_1,TIM_IT_UPDATE);               /* 使能更新中断 */

}


/**
 * @brief       定时器中断服务函数
 * @param       无
 * @retval      无
 */
void GTIM_TIMX_ENCODER_INT_IRQHandler_1(void)
{
    HAL_TIM_IRQHandler(&g_timx_encode_chy_handle_1);
}


	 


/**
 * @brief       编码器计数
 * @param       无
 * @note        无
 * @retval      无
 */
extern int g_timex_encode_count_1 ;

int32_t gtime_get_encode_1(void)
{
	return (int32_t)(__HAL_TIM_GET_COUNTER(&g_timx_encode_chy_handle_1)+g_timex_encode_count_1*65536);
}

/*****
**************************电机2****************************************************************************************************
*****/
TIM_HandleTypeDef g_timx_encode_chy_handle_2;         /* 定时器x句柄 */
TIM_Encoder_InitTypeDef g_timx_encoder_chy_handle_2;  /* 定时器编码器句柄 */


/**
 * @brief       通用定时器TIMX 通道Y 编码器接口模式 初始化函数
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为42M, 所以定时器时钟 = 84Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void gtim_timx_encoder_chy_init_2(uint16_t arr, uint16_t psc)
{
    /* 定时器x配置 */
    g_timx_encode_chy_handle_2.Instance = GTIM_TIMX_ENCODER_2;                      /* 定时器x */
    g_timx_encode_chy_handle_2.Init.Prescaler = psc;                              /* 定时器分频 */
    g_timx_encode_chy_handle_2.Init.Period = arr;                                 /* 自动重装载值 */
    g_timx_encode_chy_handle_2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
	g_timx_encode_chy_handle_2.Init.CounterMode = TIM_COUNTERMODE_UP;
    
    /* 定时器x编码器配置 */
    g_timx_encoder_chy_handle_2.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
    g_timx_encoder_chy_handle_2.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_timx_encoder_chy_handle_2.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_timx_encoder_chy_handle_2.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_timx_encoder_chy_handle_2.IC1Filter = 10;                                   /* 滤波器设置 */
    g_timx_encoder_chy_handle_2.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_timx_encoder_chy_handle_2.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_timx_encoder_chy_handle_2.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_timx_encoder_chy_handle_2.IC2Filter = 10;                                   /* 滤波器设置 */
    HAL_TIM_Encoder_Init(&g_timx_encode_chy_handle_2, &g_timx_encoder_chy_handle_2);/* 初始化定时器x编码器 */
     
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_2,GTIM_TIMX_ENCODER_CH1_2);     /* 使能编码器通道1 */
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_2,GTIM_TIMX_ENCODER_CH2_2);     /* 使能编码器通道2 */
	
    
    __HAL_TIM_CLEAR_FLAG(&g_timx_encode_chy_handle_2,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
	__HAL_TIM_ENABLE_IT(&g_timx_encode_chy_handle_2,TIM_IT_UPDATE);               /* 使能更新中断 */
    
}

/**
 * @brief       定时器底层驱动，时钟使能，引脚配置
                此函数会被HAL_TIM_Encoder_Init()调用
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_ENCODER_2)
    {
		
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIMX_ENCODER_CH1_GPIO_CLK_ENABLE_2();                                 /* 开启通道y的GPIO时钟 */
        GTIM_TIMX_ENCODER_CH2_GPIO_CLK_ENABLE_2();
        GTIM_TIMX_ENCODER_CH1_CLK_ENABLE_2();                                      /* 开启定时器时钟 */
        GTIM_TIMX_ENCODER_CH2_CLK_ENABLE_2();

        gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH1_GPIO_PIN_2;                   /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
        gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH1_GPIO_AF_2;               /* 端口复用 */
        HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH1_GPIO_PORT_2, &gpio_init_struct);  
        
        gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH2_GPIO_PIN_2;                   /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
        gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH2_GPIO_AF_2;               /* 端口复用 */
        HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH2_GPIO_PORT_2, &gpio_init_struct);         
       
        HAL_NVIC_SetPriority(GTIM_TIMX_ENCODER_INT_IRQn_2, 0, 3);                  /* 中断优先级设置 */
        HAL_NVIC_EnableIRQ(GTIM_TIMX_ENCODER_INT_IRQn_2);                          /* 开启中断 */
    }
	if (htim->Instance == GTIM_TIMX_ENCODER_1)
	{
		GPIO_InitTypeDef gpio_init_struct;
		GTIM_TIMX_ENCODER_CH1_GPIO_CLK_ENABLE_1();                                 /* 开启通道y的GPIO时钟 */
		GTIM_TIMX_ENCODER_CH2_GPIO_CLK_ENABLE_1();
		GTIM_TIMX_ENCODER_CH1_CLK_ENABLE_1();                                      /* 开启定时器时钟 */
		GTIM_TIMX_ENCODER_CH2_CLK_ENABLE_1();

		gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH1_GPIO_PIN_1;                   /* 通道y的GPIO口 */
		gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
		gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 上拉 */
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
		gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH1_GPIO_AF_1;               /* 端口复用 */
		HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH1_GPIO_PORT_1, &gpio_init_struct);  
		
		gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH2_GPIO_PIN_1;                   /* 通道y的GPIO口 */
		gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
		gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 上拉 */
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
		gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH2_GPIO_AF_1;               /* 端口复用 */
		HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH2_GPIO_PORT_1, &gpio_init_struct);         
	   
		HAL_NVIC_SetPriority(GTIM_TIMX_ENCODER_INT_IRQn_1, 0, 2);                  /* 中断优先级设置 */
		HAL_NVIC_EnableIRQ(GTIM_TIMX_ENCODER_INT_IRQn_1);                          /* 开启中断 */
	}
}

/**
 * @brief       定时器中断服务函数
 * @param       无
 * @retval      无
 */
void GTIM_TIMX_ENCODER_INT_IRQHandler_2(void)
{
    HAL_TIM_IRQHandler(&g_timx_encode_chy_handle_2);
}


	 


/**
 * @brief       编码器计数
 * @param       无
 * @note        无
 * @retval      无
 */
extern int g_timex_encode_count_2 ;

int32_t gtime_get_encode_2(void)
{
	return (int32_t)(__HAL_TIM_GET_COUNTER(&g_timx_encode_chy_handle_2)+g_timex_encode_count_2*65536);
}

/*************************************定时器中断回调函数*****************************************************/
extern TIM_HandleTypeDef timx_handler;         /* 定时器参数句柄 */
extern TIM_HandleTypeDef timx_handler_1;         /* 定时器参数句柄 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static int val = 0;

	
	if(htim->Instance == GTIM_TIMX_ENCODER_1)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_timx_encode_chy_handle_1))//判断CR1的DIR位
			{
				g_timex_encode_count_1--;
				  //printf("1\r\n");	

			}
			else
			{
				g_timex_encode_count_1++;
				  //printf("2\r\n");	

			}
			
			
	}
	if (htim->Instance == GTIM_TIMX_ENCODER_2)
    {
		
	
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_timx_encode_chy_handle_2))//判断CR1的DIR位
		{
			g_timex_encode_count_2--;
			 //printf("1\r\n");
			
		}
		else
		{
			g_timex_encode_count_2++;
			//printf("2\r\n");	
		}

     }
	if(htim->Instance == BTIM_TIMX_INT)
	{
		//__HAL_TIM_CLEAR_IT(&timx_handler,TIM_IT_UPDATE); 
		int32_t Encode_now_1 = gtime_get_encode_1();                             /* 获取编码器值，用于计算速度 */

        speed_computer_1(Encode_now_1, 5);                                 /* 中位平均值滤除编码器抖动数据，50ms计算一次速度*/
		
		
		int32_t Encode_now_2 = gtime_get_encode_2();                             /* 获取编码器值，用于计算速度 */

        speed_computer_2(Encode_now_2, 5);                                 /* 中位平均值滤除编码器抖动数据，50ms计算一次速度*/
	}
	if(htim->Instance == TIM6)
	{
	 if(val % 5 == 0)
	 {
		 //g_motor_data_1.speed = 
		if(g_run_flag_1)
		{
			g_motor_data_1.motor_pwm = increment_pid_ctrl_1(&g_speed_pid_1,g_motor_data_1.speed);
			
			    if (g_motor_data_1.motor_pwm >= 82000)                     /* 限速 */
                {
                    g_motor_data_1.motor_pwm = 82000;
                }
                else if (g_motor_data_1.motor_pwm <= -82000)
                {
                    g_motor_data_1.motor_pwm = -82000;
                }
			
			atime_motor_speed_dirset_1(g_motor_data_1.motor_pwm);
			
		}
		if(g_run_flag_2)
		{
			g_motor_data_2.motor_pwm = increment_pid_ctrl_2(&g_speed_pid_2,g_motor_data_2.speed);
			
			    if (g_motor_data_2.motor_pwm >= 82000)                     /* 限速 */
                {
                    g_motor_data_2.motor_pwm = 82000;
                }
                else if (g_motor_data_2.motor_pwm <= -82000)
                {
                    g_motor_data_2.motor_pwm = -82000;
                }
			
			atime_motor_speed_dirset_2(g_motor_data_2.motor_pwm);
			
		}
		val = 0;
	 }
	 val++;
	 
			
	
	}
	
}




