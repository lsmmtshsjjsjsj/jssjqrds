#include "./BSP/ATIME/atime.h"
#include "./SYSTEM/sys/sys.h"


/*****
**************************���1******************************
*****/

/*******************************����������������Ƴ���**************************************/

TIM_HandleTypeDef g_timx_cplm_pwm_handle_1;                              /* ��ʱ��x��� */
TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config_1 = {0};        /* ����ʱ������ */

/**
 * @brief       �߼���ʱ��TIMX ������� ��ʼ��������ʹ��PWMģʽ1��
 * @note
 *              ���ø߼���ʱ��TIMX �������, һ·OCy һ·OCyN, ���ҿ�����������ʱ��
 *
 *              �߼���ʱ����ʱ������APB2, ��PCLK2 = 168Mhz, ��������PPRE2����Ƶ, ���
 *              �߼���ʱ��ʱ�� = 168Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��, ��λ : Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: Ԥ��Ƶϵ��
 * @retval      ��
 */
void atim_timx_cplm_pwm_init_1(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct_1 = {0};
    TIM_OC_InitTypeDef tim_oc_cplm_pwm_1 = {0};

    ATIM_TIMX_CPLM_CLK_ENABLE_1();            /* TIMx ʱ��ʹ�� */
	
    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_1();   /* ͨ��X��ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_1();  /* ͨ��X����ͨ����ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();  /* ͨ��Xɲ�������ӦIO��ʱ��ʹ�� */
        
    gpio_init_struct_1.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
    gpio_init_struct_1.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct_1.Pull = GPIO_PULLDOWN;
    gpio_init_struct_1.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct_1.Alternate = ATIM_TIMX_CPLM_CHY_GPIO_AF_1;                /* �˿ڸ��� */
    HAL_GPIO_Init(ATIM_TIMX_CPLM_BKIN_GPIO_PORT, &gpio_init_struct_1);

    gpio_init_struct_1.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN_1;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT_1, &gpio_init_struct_1);

    gpio_init_struct_1.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN_1;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHYN_GPIO_PORT_1, &gpio_init_struct_1);

    g_timx_cplm_pwm_handle_1.Instance = ATIM_TIMX_CPLM_1;                       /* ��ʱ��x */
    g_timx_cplm_pwm_handle_1.Init.Prescaler = psc;                            /* Ԥ��Ƶϵ�� */
    g_timx_cplm_pwm_handle_1.Init.CounterMode = TIM_COUNTERMODE_UP;           /* ���ϼ���ģʽ */
    g_timx_cplm_pwm_handle_1.Init.Period = arr;                               /* �Զ���װ��ֵ */
    g_timx_cplm_pwm_handle_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;     /* CKD[1:0] = 10, tDTS = 4 * tCK_INT = Ft / 4 = 42Mhz*/
    g_timx_cplm_pwm_handle_1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;  /* ʹ��Ӱ�ӼĴ���TIMx_ARR */
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle_1) ;

    tim_oc_cplm_pwm_1.OCMode = TIM_OCMODE_PWM1;                               /* PWMģʽ1 */
    tim_oc_cplm_pwm_1.OCPolarity = TIM_OCPOLARITY_HIGH;                       /* OCy �ߵ�ƽ��Ч */
    tim_oc_cplm_pwm_1.OCNPolarity = TIM_OCPOLARITY_HIGH;                      /* OCyN �ߵ�ƽ��Ч */
    tim_oc_cplm_pwm_1.OCIdleState = TIM_OCIDLESTATE_SET;                      /* ��MOE=0��OCx=0 */
    tim_oc_cplm_pwm_1.OCNIdleState = TIM_OCNIDLESTATE_SET;                    /* ��MOE=0��OCxN=0 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle_1, &tim_oc_cplm_pwm_1, ATIM_TIMX_CPLM_CHY_1);

    /* �����������������������ж� */
    g_sbreak_dead_time_config_1.OffStateRunMode = TIM_OSSR_DISABLE;           /* ����ģʽ�Ĺر����״̬ */
    g_sbreak_dead_time_config_1.OffStateIDLEMode = TIM_OSSI_DISABLE;          /* ����ģʽ�Ĺر����״̬ */
    g_sbreak_dead_time_config_1.LockLevel = TIM_LOCKLEVEL_OFF;                /* ���üĴ��������� */
    g_sbreak_dead_time_config_1.BreakState = TIM_BREAK_ENABLE;                /* ʹ��ɲ������ */
    g_sbreak_dead_time_config_1.BreakPolarity = TIM_BREAKPOLARITY_HIGH;       /* ɲ��������Ч�źż���Ϊ�� */
    g_sbreak_dead_time_config_1.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE; /* ʹ��AOEλ������ɲ���������Զ��ָ���� */
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_1, &g_sbreak_dead_time_config_1);

}

/**
 * @brief       ��ʱ��TIMX ��������Ƚ�ֵ & ����ʱ��
 * @param       ccr: ����Ƚ�ֵ
 * @param       dtg: ����ʱ��
 *   @arg       dtg[7:5]=0xxʱ, ����ʱ�� = dtg[7:0] * tDTS
 *   @arg       dtg[7:5]=10xʱ, ����ʱ�� = (64 + dtg[6:0]) * 2  * tDTS
 *   @arg       dtg[7:5]=110ʱ, ����ʱ�� = (32 + dtg[5:0]) * 8  * tDTS
 *   @arg       dtg[7:5]=111ʱ, ����ʱ�� = (32 + dtg[5:0]) * 16 * tDTS
 *   @note      tDTS = 1 / (Ft /  CKD[1:0]) = 1 / 42M = 23.8ns
 * @retval      ��
 */
void atim_timx_cplm_pwm_set_1(uint16_t ccr)
{
       g_sbreak_dead_time_config_1.DeadTime = 0X0F;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_1, &g_sbreak_dead_time_config_1);      /*��������ʱ��*/
    __HAL_TIM_MOE_ENABLE(&g_timx_cplm_pwm_handle_1);      /* MOE=1,ʹ������� */    
    ATIM_TIMX_CPLM_CHY_CCRY_1 = ccr;                      /* ���ñȽϼĴ��� */
}

//���ֹͣ
void  dcmotor_stop_1()
{
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//�رջ���·PWM���
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//�ر����·PWM���
}

//�����ת��������
void dcmotor_dir_1(uint8_t para)
{
	if(para == 0)
	{
		HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//�ر����·PWM���
	}
	else if(para == 1)
	{
		
		
		HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_1,ATIM_TIMX_CPLM_CHY_1);//�رջ���·PWM���
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
**************************���2******************************
*****/
/*******************************����������������Ƴ���**************************************/

TIM_HandleTypeDef g_timx_cplm_pwm_handle_2;                              /* ��ʱ��x��� */
TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config_2 = {0};        /* ����ʱ������ */

/**
 * @brief       �߼���ʱ��TIMX ������� ��ʼ��������ʹ��PWMģʽ1��
 * @note
 *              ���ø߼���ʱ��TIMX �������, һ·OCy һ·OCyN, ���ҿ�����������ʱ��
 *
 *              �߼���ʱ����ʱ������APB2, ��PCLK2 = 168Mhz, ��������PPRE2����Ƶ, ���
 *              �߼���ʱ��ʱ�� = 168Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��, ��λ : Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: Ԥ��Ƶϵ��
 * @retval      ��
 */
void atim_timx_cplm_pwm_init_2(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    TIM_OC_InitTypeDef tim_oc_cplm_pwm = {0};

    ATIM_TIMX_CPLM_CLK_ENABLE_2();            /* TIMx ʱ��ʹ�� */
	
    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE_2();   /* ͨ��X��ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE_2();  /* ͨ��X����ͨ����ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();  /* ͨ��Xɲ�������ӦIO��ʱ��ʹ�� */
        
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = ATIM_TIMX_CPLM_CHY_GPIO_AF_2;                /* �˿ڸ��� */
    HAL_GPIO_Init(ATIM_TIMX_CPLM_BKIN_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN_2;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT_2, &gpio_init_struct);

    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN_2;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHYN_GPIO_PORT_2, &gpio_init_struct);

    g_timx_cplm_pwm_handle_2.Instance = ATIM_TIMX_CPLM_2;                       /* ��ʱ��x */
    g_timx_cplm_pwm_handle_2.Init.Prescaler = psc;                            /* Ԥ��Ƶϵ�� */
    g_timx_cplm_pwm_handle_2.Init.CounterMode = TIM_COUNTERMODE_UP;           /* ���ϼ���ģʽ */
    g_timx_cplm_pwm_handle_2.Init.Period = arr;                               /* �Զ���װ��ֵ */
    g_timx_cplm_pwm_handle_2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;     /* CKD[1:0] = 10, tDTS = 4 * tCK_INT = Ft / 4 = 42Mhz*/
    g_timx_cplm_pwm_handle_2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;  /* ʹ��Ӱ�ӼĴ���TIMx_ARR */
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle_2) ;

    tim_oc_cplm_pwm.OCMode = TIM_OCMODE_PWM1;                               /* PWMģʽ1 */
    tim_oc_cplm_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                       /* OCy �ߵ�ƽ��Ч */
    tim_oc_cplm_pwm.OCNPolarity = TIM_OCPOLARITY_HIGH;                      /* OCyN �ߵ�ƽ��Ч */
    tim_oc_cplm_pwm.OCIdleState = TIM_OCIDLESTATE_SET;                      /* ��MOE=0��OCx=0 */
    tim_oc_cplm_pwm.OCNIdleState = TIM_OCNIDLESTATE_SET;                    /* ��MOE=0��OCxN=0 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle_2, &tim_oc_cplm_pwm, ATIM_TIMX_CPLM_CHY_2);

    /* �����������������������ж� */
    g_sbreak_dead_time_config_2.OffStateRunMode = TIM_OSSR_DISABLE;           /* ����ģʽ�Ĺر����״̬ */
    g_sbreak_dead_time_config_2.OffStateIDLEMode = TIM_OSSI_DISABLE;          /* ����ģʽ�Ĺر����״̬ */
    g_sbreak_dead_time_config_2.LockLevel = TIM_LOCKLEVEL_OFF;                /* ���üĴ��������� */
    g_sbreak_dead_time_config_2.BreakState = TIM_BREAK_ENABLE;                /* ʹ��ɲ������ */
    g_sbreak_dead_time_config_2.BreakPolarity = TIM_BREAKPOLARITY_HIGH;       /* ɲ��������Ч�źż���Ϊ�� */
    g_sbreak_dead_time_config_2.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE; /* ʹ��AOEλ������ɲ���������Զ��ָ���� */
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_2, &g_sbreak_dead_time_config_2);

}

/**
 * @brief       ��ʱ��TIMX ��������Ƚ�ֵ & ����ʱ��
 * @param       ccr: ����Ƚ�ֵ
 * @param       dtg: ����ʱ��
 *   @arg       dtg[7:5]=0xxʱ, ����ʱ�� = dtg[7:0] * tDTS
 *   @arg       dtg[7:5]=10xʱ, ����ʱ�� = (64 + dtg[6:0]) * 2  * tDTS
 *   @arg       dtg[7:5]=110ʱ, ����ʱ�� = (32 + dtg[5:0]) * 8  * tDTS
 *   @arg       dtg[7:5]=111ʱ, ����ʱ�� = (32 + dtg[5:0]) * 16 * tDTS
 *   @note      tDTS = 1 / (Ft /  CKD[1:0]) = 1 / 42M = 23.8ns
 * @retval      ��
 */
void atim_timx_cplm_pwm_set_2(uint16_t ccr)
{
       g_sbreak_dead_time_config_2.DeadTime = 0X0F;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle_2, &g_sbreak_dead_time_config_2);      /*��������ʱ��*/
    __HAL_TIM_MOE_ENABLE(&g_timx_cplm_pwm_handle_2);      /* MOE=1,ʹ������� */    
    ATIM_TIMX_CPLM_CHY_CCRY_2 = ccr;                      /* ���ñȽϼĴ��� */
}

//���ֹͣ
void  dcmotor_stop_2()
{
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//�رջ���·PWM���
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//�ر����·PWM���
}

//�����ת��������
void dcmotor_dir_2(uint8_t para)
{
	if(para == 0)
	{
		HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);
		HAL_TIMEx_PWMN_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//�رջ���·PWM���
	}
	else if(para == 1)
	{
		HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);
		HAL_TIM_PWM_Stop(&g_timx_cplm_pwm_handle_2,ATIM_TIMX_CPLM_CHY_2);//�ر����·PWM���
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
