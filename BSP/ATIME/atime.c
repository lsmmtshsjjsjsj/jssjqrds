#include "./BSP/ATIME/atime.h"
#include "./SYSTEM/sys/sys.h"


/*****
**************************电机1******************************
*****/

/*******************************互补输出带死区控制程序**************************************/

TIM_HandleTypeDef g_timx_cplm_pwm_handle_1;                              /* 定时器x句柄 */
TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config_1 = {0};        /* 死区时间设置 */

/**
 * @brief       高级定时器TIMX 互补输出 初始化函数（使用PWM模式1）
 * @note
 *              配置高级定时器TIMX 互补输出, 一路OCy 一路OCyN, 并且可以设置死区时间
 *
 *              高级定时器的时钟来自APB2, 而PCLK2 = 168Mhz, 我们设置PPRE2不分频, 因此
 *              高级定时器时钟 = 168Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率, 单位 : Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 预分频系数
 * @retval      无
 */
void atim_timx_cplm_pwm_init_1(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct_1 = {0};
    TIM_OC_InitTypeDef tim_oc_cplm_pwm_1 = {0};

    ATIM_TIMX_CPLM_CLK_ENABLE_1();            /* TIMx 时钟使能 */
	
    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_1();   /* 通道X对应IO口时钟使能 */
    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_1();  /* 通道X互补通道对应IO口时钟使能 */
    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();  /* 通道X刹车输入对应IO口时钟使能 */
        
    gpio_init_struct_1.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
    gpio_init_struct_1.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct_1.Pull = GPIO_PULLDOWN;
    gpio_init_struct_1.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct_1.Alternate = ATIM_TIMX_CPLM_CHY_GPIO_AF_1;                /* 端口复用 */
    HAL_GPIO_Init(ATIM_TIMX_CPLM_BKIN_GPIO_PORT, &gpio_init_struct_1);

    gpio_init_struct_1.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN_1;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT_1, &gpio_init_struct_1);

    gpio_init_struct_1.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN_1;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHYN_GPIO_PORT_1, &gpio_init_struct_1);

    g_timx_cplm_pwm_handle_1.Instance = ATIM_TIMX_CPLM_1;                       /* 定时器x */
    g_timx_cplm_pwm_handle_1.Init.Prescaler = psc;                            /* 预分频系数 */
    g_timx_cplm_pwm_handle_1.Init.CounterMode = TIM_COUNTERMODE_UP;           /* 向上计数模式 */
    g_timx_cplm_pwm_handle_1.Init.Period = arr;                               /* 自动重装载值 */
    g_timx_cplm_pwm_handle_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;     /* CKD[1:0] = 10, tDTS = 4 * tCK_INT = Ft / 4 = 42Mhz*/
    g_timx_cplm_pwm_handle_1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;  /* 使能影子寄存器TIMx_ARR */
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle_1) ;

    tim_oc_cplm_pwm_1.OCMode = TIM_OCMODE_PWM1;                               /* PWM模式1 */
    tim_oc_cplm_pwm_1.OCPolarity = TIM_OCPOLARITY_HIGH;                       /* OCy 高电平有效 */
    tim_oc_cplm_pwm_1.OCNPolarity = TIM_OCPOLARITY_HIGH;                      /* OCyN 高电平有效 */
    tim_oc_cplm_pwm_1.OCIdleState = TIM_OCIDLESTATE_SET;                      /* 当MOE=0，OCx=0 */
    tim_oc_cplm_pwm_1.OCNIdleState = TIM_OCNIDLESTATE_SET;                    /* 当MOE=0，OCxN=0 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle_1, &tim_oc_cplm_pwm_1, ATIM_TIMX_CPLM_CHY_1);

    /* 设置死区参数，开启死区中断 */
    g_sbreak_dead_time_config_1.OffStateRunMode = TIM_OSSR_DISABLE;           /* 运行模式的关闭输出状态 */
    g_sbreak_dead_time_config_1.OffStateIDLEMode = TIM_OSSI_DISABLE;          /* 空闲模式的关闭输出状态 */
    g_sbreak_dead_time_config_1.LockLevel = TIM_LOCKLEVEL_OFF;                /* 不用寄存器锁功能 */
    g_sbreak_dead_time_config_1.BreakState = TIM_BREAK_ENABLE;                /* 使能刹车输入 */
    g_sbreak_dead_time_config_1.BreakPolarity = TIM_BREAKPOLARITY_HIGH;       /* 刹车输入有效信号极性为高 */
    g_sbreak_dead_time_config_1.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE; /* 使能AOE位，允许刹车结束后自动恢复输出 */
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_1, &g_sbreak_dead_time_config_1);

}

/**
 * @brief       定时器TIMX 设置输出比较值 & 死区时间
 * @param       ccr: 输出比较值
 * @param       dtg: 死区时间
 *   @arg       dtg[7:5]=0xx时, 死区时间 = dtg[7:0] * tDTS
 *   @arg       dtg[7:5]=10x时, 死区时间 = (64 + dtg[6:0]) * 2  * tDTS
 *   @arg       dtg[7:5]=110时, 死区时间 = (32 + dtg[5:0]) * 8  * tDTS
 *   @arg       dtg[7:5]=111时, 死区时间 = (32 + dtg[5:0]) * 16 * tDTS
 *   @note      tDTS = 1 / (Ft /  CKD[1:0]) = 1 / 42M = 23.8ns
 * @retval      无
 */
void atim_timx_cplm_pwm_set_1(uint16_t ccr)
{
       g_sbreak_dead_time_config_1.DeadTime = 0X0F;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_1, &g_sbreak_dead_time_config_1);      /*重设死区时间*/
    __HAL_TIM_MOE_ENABLE(&g_timx_cplm_pwm_handle_1);      /* MOE=1,使能主输出 */    
    ATIM_TIMX_CPLM_CHY_CCRY_1 = ccr;                      /* 设置比较寄存器 */
}

//电机停止
void  dcmotor_stop_1()
{
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//关闭互补路PWM输出
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//关闭输出路PWM输出
}

//电机旋转方向设置
void dcmotor_dir_1(uint8_t para)
{
	if(para == 0)
	{
		HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//关闭输出路PWM输出
	}
	else if(para == 1)
	{
		
		
		HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//关闭互补路PWM输出
	}
}

void atime_motor_speed_dirset_1(int32_t pwm)
{
	int val = (int)pwm;
	if(val > 0)
	{
		dcmotor_dir_1(1);
		atim_timx_cplm_pwm_set_1(val);
	}
	else
	{
		dcmotor_dir_1(0);
		atim_timx_cplm_pwm_set_1(-val);
	}
		
}

/*****
**************************电机2******************************
*****/
/*******************************互补输出带死区控制程序**************************************/

TIM_HandleTypeDef g_timx_cplm_pwm_handle_2;                              /* 定时器x句柄 */
TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config_2 = {0};        /* 死区时间设置 */

/**
 * @brief       高级定时器TIMX 互补输出 初始化函数（使用PWM模式1）
 * @note
 *              配置高级定时器TIMX 互补输出, 一路OCy 一路OCyN, 并且可以设置死区时间
 *
 *              高级定时器的时钟来自APB2, 而PCLK2 = 168Mhz, 我们设置PPRE2不分频, 因此
 *              高级定时器时钟 = 168Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率, 单位 : Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 预分频系数
 * @retval      无
 */
void atim_timx_cplm_pwm_init_2(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    TIM_OC_InitTypeDef tim_oc_cplm_pwm = {0};

    ATIM_TIMX_CPLM_CLK_ENABLE_2();            /* TIMx 时钟使能 */
	
    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_2();   /* 通道X对应IO口时钟使能 */
    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_2();  /* 通道X互补通道对应IO口时钟使能 */
    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();  /* 通道X刹车输入对应IO口时钟使能 */
        
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = ATIM_TIMX_CPLM_CHY_GPIO_AF_2;                /* 端口复用 */
    HAL_GPIO_Init(ATIM_TIMX_CPLM_BKIN_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN_2;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT_2, &gpio_init_struct);

    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN_2;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHYN_GPIO_PORT_2, &gpio_init_struct);

    g_timx_cplm_pwm_handle_2.Instance = ATIM_TIMX_CPLM_2;                       /* 定时器x */
    g_timx_cplm_pwm_handle_2.Init.Prescaler = psc;                            /* 预分频系数 */
    g_timx_cplm_pwm_handle_2.Init.CounterMode = TIM_COUNTERMODE_UP;           /* 向上计数模式 */
    g_timx_cplm_pwm_handle_2.Init.Period = arr;                               /* 自动重装载值 */
    g_timx_cplm_pwm_handle_2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;     /* CKD[1:0] = 10, tDTS = 4 * tCK_INT = Ft / 4 = 42Mhz*/
    g_timx_cplm_pwm_handle_2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;  /* 使能影子寄存器TIMx_ARR */
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle_2) ;

    tim_oc_cplm_pwm.OCMode = TIM_OCMODE_PWM1;                               /* PWM模式1 */
    tim_oc_cplm_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                       /* OCy 高电平有效 */
    tim_oc_cplm_pwm.OCNPolarity = TIM_OCPOLARITY_HIGH;                      /* OCyN 高电平有效 */
    tim_oc_cplm_pwm.OCIdleState = TIM_OCIDLESTATE_SET;                      /* 当MOE=0，OCx=0 */
    tim_oc_cplm_pwm.OCNIdleState = TIM_OCNIDLESTATE_SET;                    /* 当MOE=0，OCxN=0 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle_2, &tim_oc_cplm_pwm, ATIM_TIMX_CPLM_CHY_2);

    /* 设置死区参数，开启死区中断 */
    g_sbreak_dead_time_config_2.OffStateRunMode = TIM_OSSR_DISABLE;           /* 运行模式的关闭输出状态 */
    g_sbreak_dead_time_config_2.OffStateIDLEMode = TIM_OSSI_DISABLE;          /* 空闲模式的关闭输出状态 */
    g_sbreak_dead_time_config_2.LockLevel = TIM_LOCKLEVEL_OFF;                /* 不用寄存器锁功能 */
    g_sbreak_dead_time_config_2.BreakState = TIM_BREAK_ENABLE;                /* 使能刹车输入 */
    g_sbreak_dead_time_config_2.BreakPolarity = TIM_BREAKPOLARITY_HIGH;       /* 刹车输入有效信号极性为高 */
    g_sbreak_dead_time_config_2.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE; /* 使能AOE位，允许刹车结束后自动恢复输出 */
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_2, &g_sbreak_dead_time_config_2);

}

/**
 * @brief       定时器TIMX 设置输出比较值 & 死区时间
 * @param       ccr: 输出比较值
 * @param       dtg: 死区时间
 *   @arg       dtg[7:5]=0xx时, 死区时间 = dtg[7:0] * tDTS
 *   @arg       dtg[7:5]=10x时, 死区时间 = (64 + dtg[6:0]) * 2  * tDTS
 *   @arg       dtg[7:5]=110时, 死区时间 = (32 + dtg[5:0]) * 8  * tDTS
 *   @arg       dtg[7:5]=111时, 死区时间 = (32 + dtg[5:0]) * 16 * tDTS
 *   @note      tDTS = 1 / (Ft /  CKD[1:0]) = 1 / 42M = 23.8ns
 * @retval      无
 */
void atim_timx_cplm_pwm_set_2(uint16_t ccr)
{
       g_sbreak_dead_time_config_2.DeadTime = 0X0F;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_2, &g_sbreak_dead_time_config_2);      /*重设死区时间*/
    __HAL_TIM_MOE_ENABLE(&g_timx_cplm_pwm_handle_2);      /* MOE=1,使能主输出 */    
    ATIM_TIMX_CPLM_CHY_CCRY_2 = ccr;                      /* 设置比较寄存器 */
}

//电机停止
void  dcmotor_stop_2()
{
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//关闭互补路PWM输出
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//关闭输出路PWM输出
}

//电机旋转方向设置
void dcmotor_dir_2(uint8_t para)
{
	if(para == 0)
	{
		HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//关闭互补路PWM输出
	}
	else if(para == 1)
	{
		HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//关闭输出路PWM输出
	}
}

void atime_motor_speed_dirset_2(int32_t pwm)
{
	int val = (int)pwm;
	if(val > 0)
	{
		dcmotor_dir_2(1);
		atim_timx_cplm_pwm_set_2(val);
	}
	else
	{
		dcmotor_dir_2(0);
		atim_timx_cplm_pwm_set_2(-val);
	}
		
}
