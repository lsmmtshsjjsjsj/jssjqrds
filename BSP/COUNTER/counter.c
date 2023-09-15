#include "./BSP/COUNTER/counter.h"
#include "./SYSTEM/usart/usart.h"

TIM_HandleTypeDef timx_handler;         /* 定时器参数句柄 */
TIM_HandleTypeDef timx_handler_1;         /* 定时器参数句柄 */

/**
 * @brief       基本定时器TIMX定时中断初始化函数
 * @note
 *              基本定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              基本定时器的时钟为APB1时钟的2倍, 而APB1为42M, 所以定时器时钟 = 84Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    timx_handler.Instance = BTIM_TIMX_INT;                              /* 基本定时器X */
    timx_handler.Init.Prescaler = psc;                                  /* 设置预分频器  */
    timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                 /* 向上计数器 */
    timx_handler.Init.Period = arr;                                     /* 自动装载值 */
    timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;           /* 时钟分频因子 */
    HAL_TIM_Base_Init(&timx_handler);
    
    HAL_TIM_Base_Start_IT(&timx_handler);                               /* 使能基本定时器x和及其更新中断：TIM_IT_UPDATE */
    __HAL_TIM_CLEAR_IT(&timx_handler,TIM_IT_UPDATE);                    /* 清除更新中断标志位 */
}

void btim_timx_int_init_1(uint16_t arr, uint16_t psc)
{
    timx_handler_1.Instance = TIM6;                              /* 基本定时器X */
    timx_handler_1.Init.Prescaler = psc;                                  /* 设置预分频器  */
    timx_handler_1.Init.CounterMode = TIM_COUNTERMODE_UP;                 /* 向上计数器 */
    timx_handler_1.Init.Period = arr;                                     /* 自动装载值 */
    timx_handler_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;           /* 时钟分频因子 */
    HAL_TIM_Base_Init(&timx_handler_1);
    
    HAL_TIM_Base_Start_IT(&timx_handler_1);                               /* 使能基本定时器x和及其更新中断：TIM_IT_UPDATE */
    __HAL_TIM_CLEAR_IT(&timx_handler_1,TIM_IT_UPDATE);                    /* 清除更新中断标志位 */
}

/**
 * @brief       定时器底册驱动，开启时钟，设置中断优先级
                此函数会被HAL_TIM_Base_Init()函数调用
 * @param       无
 * @retval      无
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        BTIM_TIMX_INT_CLK_ENABLE();                                     /*使能TIM时钟*/
        HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3);                 /* 抢占1，子优先级3，组2 */
        HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);                         /*开启ITM3中断*/
    }
	if (htim->Instance == TIM6)
	{
		do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0);    /* TIM9 时钟使能 */
		HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 2);
		HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}
}

/**
 * @brief       基本定时器TIMX中断服务函数
 * @param       无
 * @retval      无
 */

void BTIM_TIMX_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&timx_handler);                                  /*定时器回调函数*/
	
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&timx_handler_1); 
}




/*************************************    第三部分    编码器测速    ****************************************************/

Motor_TypeDef_1 g_motor_data_1;  /*电机参数变量*/
ENCODE_TypeDef_1 g_encode_1;     /*编码器参数变量*/

/**
 * @brief       电机速度计算
 * @param       encode_now：当前编码器总的计数值
 *              ms：计算速度的间隔，中断1ms进入一次，例如ms = 5即5ms计算一次速度
 * @retval      无
 */

void speed_computer_1(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* 存储速度进行滤波运算 */

    if (sp_count == ms)                                     /* 计算一次速度 */
    {
        /* 计算电机转速 
           第一步 ：计算ms毫秒内计数变化量
           第二步 ；计算1min内计数变化量：g_encode.speed * ((1000 / ms) * 60 ，
           第三步 ：除以编码器旋转一圈的计数次数（倍频倍数 * 编码器分辨率）
           第四步 ：除以减速比即可得出电机转速
        */
        g_encode_1.encode_now = encode_now;                                /* 取出编码器当前计数值 */
        g_encode_1.speed = (g_encode_1.encode_now - g_encode_1.encode_old);    /* 计算编码器计数值的变化量 */
        
        speed_arr[k++] = (float)(g_encode_1.speed * ((1000 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* 保存电机转速 */
        
        g_encode_1.encode_old = g_encode_1.encode_now;          /* 保存当前编码器的值 */

        /* 累计10次速度值，后续进行滤波*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* 冒泡排序*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* 数值比较 */
                    { 
                        temp = speed_arr[j];                /* 数值换位 */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* 去除两边高低数据 */
            {
                temp += speed_arr[i];                       /* 将中间数值累加 */
            }
            
            temp = (float)(temp / 6);                       /*求速度平均值*/
            
            /* 一阶低通滤波
             * 公式为：Y(n)= qX(n) + (1-q)Y(n-1)
             * 其中X(n)为本次采样值；Y(n-1)为上次滤波输出值；Y(n)为本次滤波输出值，q为滤波系数
             * q值越小则上一次输出对本次输出影响越大，整体曲线越平稳，但是对于速度变化的响应也会越慢
             */
            g_motor_data_1.speed = (float)( ((float)1 * temp)); //+ (g_motor_data_1.speed * (float)0.52) );
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}

/*************************************    第三部分    编码器测速    ****************************************************/

Motor_TypeDef_2 g_motor_data_2;  /*电机参数变量*/
ENCODE_TypeDef_2 g_encode_2;     /*编码器参数变量*/

/**
 * @brief       电机速度计算
 * @param       encode_now：当前编码器总的计                                       数值
 *              ms：计算速度的间隔，中断1ms进入一次，例如ms = 5即5ms计算一次速度
 * @retval      无
 */

void speed_computer_2(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* 存储速度进行滤波运算 */

    if (sp_count == ms)                                     /* 计算一次速度 */
    {
        /* 计算电机转速 
           第一步 ：计算ms毫秒内计数变化量
           第二步 ；计算1min内计数变化量：g_encode.speed * ((1000 / ms) * 60 ，
           第三步 ：除以编码器旋转一圈的计数次数（倍频倍数 * 编码器分辨率）
           第四步 ：除以减速比即可得出电机转速
        */
        g_encode_2.encode_now = encode_now;                                /* 取出编码器当前计数值 */
        g_encode_2.speed = (g_encode_2.encode_now - g_encode_2.encode_old);    /* 计算编码器计数值的变化量 */
        
        speed_arr[k++] = (float)(g_encode_2.speed * ((1000 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* 保存电机转速 */
        
        g_encode_2.encode_old = g_encode_2.encode_now;          /* 保存当前编码器的值 */

        /* 累计10次速度值，后续进行滤波*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* 冒泡排序*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* 数值比较 */
                    { 
                        temp = speed_arr[j];                /* 数值换位 */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* 去除两边高低数据 */
            {
                temp += speed_arr[i];                       /* 将中间数值累加 */
            }
            
            temp = (float)(temp / 6);                       /*求速度平均值*/
            
            /* 一阶低通滤波
             * 公式为：Y(n)= qX(n) + (1-q)Y(n-1)
             * 其中X(n)为本次采样值；Y(n-1)为上次滤波输出值；Y(n)为本次滤波输出值，q为滤波系数
             * q值越小则上一次输出对本次输出影响越大，整体曲线越平稳，但是对于速度变化的响应也会越慢
             */
            g_motor_data_2.speed = (float)( ((float)0.48 * temp) + (g_motor_data_2.speed * (float)0.52) );
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}






