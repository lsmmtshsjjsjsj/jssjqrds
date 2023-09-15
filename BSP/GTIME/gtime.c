#include "./BSP/GTIME/gtime.h"

#include "./SYSTEM/usart/usart.h"

#include "./BSP/COUNTER/counter.h"

#include "./BSP/PID/pid.h"

#include "./BSP/ATIME/atime.h"

uint8_t  g_run_flag_1 = 1;                                                /* �����ͣ״̬��־��0��ֹͣ��1������ */
uint8_t  g_run_flag_2 = 1;                                                /* �����ͣ״̬��־��0��ֹͣ��1������ */

/*****
**************************���1****************************************************************************************************
*****/

TIM_HandleTypeDef g_timx_encode_chy_handle_1;         /* ��ʱ��x��� */
TIM_Encoder_InitTypeDef g_timx_encoder_chy_handle_1;  /* ��ʱ����������� */


/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y �������ӿ�ģʽ ��ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ42M, ���Զ�ʱ��ʱ�� = 84Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
 
void gtim_timx_encoder_chy_init_1(uint16_t arr, uint16_t psc)
{
    /* ��ʱ��x���� */
    g_timx_encode_chy_handle_1.Instance = GTIM_TIMX_ENCODER_1;                      /* ��ʱ��x */
    g_timx_encode_chy_handle_1.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
    g_timx_encode_chy_handle_1.Init.Period = arr;                                 /* �Զ���װ��ֵ */
    g_timx_encode_chy_handle_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
	g_timx_encode_chy_handle_1.Init.CounterMode = TIM_COUNTERMODE_UP;
    
    /* ��ʱ��x���������� */
    g_timx_encoder_chy_handle_1.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
    g_timx_encoder_chy_handle_1.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_timx_encoder_chy_handle_1.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_timx_encoder_chy_handle_1.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_timx_encoder_chy_handle_1.IC1Filter = 10;                                   /* �˲������� */
    g_timx_encoder_chy_handle_1.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_timx_encoder_chy_handle_1.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_timx_encoder_chy_handle_1.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_timx_encoder_chy_handle_1.IC2Filter = 10;                                   /* �˲������� */
    HAL_TIM_Encoder_Init(&g_timx_encode_chy_handle_1, &g_timx_encoder_chy_handle_1);/* ��ʼ����ʱ��x������ */
     
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_1,GTIM_TIMX_ENCODER_CH1_1);     /* ʹ�ܱ�����ͨ��1 */
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_1,GTIM_TIMX_ENCODER_CH2_1);     /* ʹ�ܱ�����ͨ��2 */
	
    
    __HAL_TIM_CLEAR_FLAG(&g_timx_encode_chy_handle_1,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
	__HAL_TIM_ENABLE_IT(&g_timx_encode_chy_handle_1,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */

}


/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_ENCODER_INT_IRQHandler_1(void)
{
    HAL_TIM_IRQHandler(&g_timx_encode_chy_handle_1);
}


	 


/**
 * @brief       ����������
 * @param       ��
 * @note        ��
 * @retval      ��
 */
extern int g_timex_encode_count_1 ;

int32_t gtime_get_encode_1(void)
{
	return (int32_t)(__HAL_TIM_GET_COUNTER(&g_timx_encode_chy_handle_1)+g_timex_encode_count_1*65536);
}

/*****
**************************���2****************************************************************************************************
*****/
TIM_HandleTypeDef g_timx_encode_chy_handle_2;         /* ��ʱ��x��� */
TIM_Encoder_InitTypeDef g_timx_encoder_chy_handle_2;  /* ��ʱ����������� */


/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y �������ӿ�ģʽ ��ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ42M, ���Զ�ʱ��ʱ�� = 84Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_encoder_chy_init_2(uint16_t arr, uint16_t psc)
{
    /* ��ʱ��x���� */
    g_timx_encode_chy_handle_2.Instance = GTIM_TIMX_ENCODER_2;                      /* ��ʱ��x */
    g_timx_encode_chy_handle_2.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
    g_timx_encode_chy_handle_2.Init.Period = arr;                                 /* �Զ���װ��ֵ */
    g_timx_encode_chy_handle_2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
	g_timx_encode_chy_handle_2.Init.CounterMode = TIM_COUNTERMODE_UP;
    
    /* ��ʱ��x���������� */
    g_timx_encoder_chy_handle_2.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
    g_timx_encoder_chy_handle_2.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_timx_encoder_chy_handle_2.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_timx_encoder_chy_handle_2.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_timx_encoder_chy_handle_2.IC1Filter = 10;                                   /* �˲������� */
    g_timx_encoder_chy_handle_2.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_timx_encoder_chy_handle_2.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_timx_encoder_chy_handle_2.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_timx_encoder_chy_handle_2.IC2Filter = 10;                                   /* �˲������� */
    HAL_TIM_Encoder_Init(&g_timx_encode_chy_handle_2, &g_timx_encoder_chy_handle_2);/* ��ʼ����ʱ��x������ */
     
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_2,GTIM_TIMX_ENCODER_CH1_2);     /* ʹ�ܱ�����ͨ��1 */
    HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle_2,GTIM_TIMX_ENCODER_CH2_2);     /* ʹ�ܱ�����ͨ��2 */
	
    
    __HAL_TIM_CLEAR_FLAG(&g_timx_encode_chy_handle_2,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
	__HAL_TIM_ENABLE_IT(&g_timx_encode_chy_handle_2,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
    
}

/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_TIM_Encoder_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_ENCODER_2)
    {
		
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIMX_ENCODER_CH1_GPIO_CLK_ENABLE_2();                                 /* ����ͨ��y��GPIOʱ�� */
        GTIM_TIMX_ENCODER_CH2_GPIO_CLK_ENABLE_2();
        GTIM_TIMX_ENCODER_CH1_CLK_ENABLE_2();                                      /* ������ʱ��ʱ�� */
        GTIM_TIMX_ENCODER_CH2_CLK_ENABLE_2();

        gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH1_GPIO_PIN_2;                   /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
        gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH1_GPIO_AF_2;               /* �˿ڸ��� */
        HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH1_GPIO_PORT_2, &gpio_init_struct);  
        
        gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH2_GPIO_PIN_2;                   /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
        gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH2_GPIO_AF_2;               /* �˿ڸ��� */
        HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH2_GPIO_PORT_2, &gpio_init_struct);         
       
        HAL_NVIC_SetPriority(GTIM_TIMX_ENCODER_INT_IRQn_2, 0, 3);                  /* �ж����ȼ����� */
        HAL_NVIC_EnableIRQ(GTIM_TIMX_ENCODER_INT_IRQn_2);                          /* �����ж� */
    }
	if (htim->Instance == GTIM_TIMX_ENCODER_1)
	{
		GPIO_InitTypeDef gpio_init_struct;
		GTIM_TIMX_ENCODER_CH1_GPIO_CLK_ENABLE_1();                                 /* ����ͨ��y��GPIOʱ�� */
		GTIM_TIMX_ENCODER_CH2_GPIO_CLK_ENABLE_1();
		GTIM_TIMX_ENCODER_CH1_CLK_ENABLE_1();                                      /* ������ʱ��ʱ�� */
		GTIM_TIMX_ENCODER_CH2_CLK_ENABLE_1();

		gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH1_GPIO_PIN_1;                   /* ͨ��y��GPIO�� */
		gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
		gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ���� */
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
		gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH1_GPIO_AF_1;               /* �˿ڸ��� */
		HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH1_GPIO_PORT_1, &gpio_init_struct);  
		
		gpio_init_struct.Pin = GTIM_TIMX_ENCODER_CH2_GPIO_PIN_1;                   /* ͨ��y��GPIO�� */
		gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
		gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ���� */
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
		gpio_init_struct.Alternate = GTIM_TIMX_ENCODERCH2_GPIO_AF_1;               /* �˿ڸ��� */
		HAL_GPIO_Init(GTIM_TIMX_ENCODER_CH2_GPIO_PORT_1, &gpio_init_struct);         
	   
		HAL_NVIC_SetPriority(GTIM_TIMX_ENCODER_INT_IRQn_1, 0, 2);                  /* �ж����ȼ����� */
		HAL_NVIC_EnableIRQ(GTIM_TIMX_ENCODER_INT_IRQn_1);                          /* �����ж� */
	}
}

/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_ENCODER_INT_IRQHandler_2(void)
{
    HAL_TIM_IRQHandler(&g_timx_encode_chy_handle_2);
}


	 


/**
 * @brief       ����������
 * @param       ��
 * @note        ��
 * @retval      ��
 */
extern int g_timex_encode_count_2 ;

int32_t gtime_get_encode_2(void)
{
	return (int32_t)(__HAL_TIM_GET_COUNTER(&g_timx_encode_chy_handle_2)+g_timex_encode_count_2*65536);
}

/*************************************��ʱ���жϻص�����*****************************************************/
extern TIM_HandleTypeDef timx_handler;         /* ��ʱ��������� */
extern TIM_HandleTypeDef timx_handler_1;         /* ��ʱ��������� */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static int val = 0;

	
	if(htim->Instance == GTIM_TIMX_ENCODER_1)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_timx_encode_chy_handle_1))//�ж�CR1��DIRλ
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
		
	
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_timx_encode_chy_handle_2))//�ж�CR1��DIRλ
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
		int32_t Encode_now_1 = gtime_get_encode_1();                             /* ��ȡ������ֵ�����ڼ����ٶ� */

        speed_computer_1(Encode_now_1, 5);                                 /* ��λƽ��ֵ�˳��������������ݣ�50ms����һ���ٶ�*/
		
		
		int32_t Encode_now_2 = gtime_get_encode_2();                             /* ��ȡ������ֵ�����ڼ����ٶ� */

        speed_computer_2(Encode_now_2, 5);                                 /* ��λƽ��ֵ�˳��������������ݣ�50ms����һ���ٶ�*/
	}
	if(htim->Instance == TIM6)
	{
	 if(val % 5 == 0)
	 {
		 //g_motor_data_1.speed = 
		if(g_run_flag_1)
		{
			g_motor_data_1.motor_pwm = increment_pid_ctrl_1(&g_speed_pid_1,g_motor_data_1.speed);
			
			    if (g_motor_data_1.motor_pwm >= 82000)                     /* ���� */
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
			
			    if (g_motor_data_2.motor_pwm >= 82000)                     /* ���� */
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




