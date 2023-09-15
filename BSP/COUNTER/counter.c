#include "./BSP/COUNTER/counter.h"
#include "./SYSTEM/usart/usart.h"

TIM_HandleTypeDef timx_handler;         /* ��ʱ��������� */
TIM_HandleTypeDef timx_handler_1;         /* ��ʱ��������� */

/**
 * @brief       ������ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ������ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ������ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ42M, ���Զ�ʱ��ʱ�� = 84Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    timx_handler.Instance = BTIM_TIMX_INT;                              /* ������ʱ��X */
    timx_handler.Init.Prescaler = psc;                                  /* ����Ԥ��Ƶ��  */
    timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                 /* ���ϼ����� */
    timx_handler.Init.Period = arr;                                     /* �Զ�װ��ֵ */
    timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;           /* ʱ�ӷ�Ƶ���� */
    HAL_TIM_Base_Init(&timx_handler);
    
    HAL_TIM_Base_Start_IT(&timx_handler);                               /* ʹ�ܻ�����ʱ��x�ͼ�������жϣ�TIM_IT_UPDATE */
    __HAL_TIM_CLEAR_IT(&timx_handler,TIM_IT_UPDATE);                    /* ��������жϱ�־λ */
}

void btim_timx_int_init_1(uint16_t arr, uint16_t psc)
{
    timx_handler_1.Instance = TIM6;                              /* ������ʱ��X */
    timx_handler_1.Init.Prescaler = psc;                                  /* ����Ԥ��Ƶ��  */
    timx_handler_1.Init.CounterMode = TIM_COUNTERMODE_UP;                 /* ���ϼ����� */
    timx_handler_1.Init.Period = arr;                                     /* �Զ�װ��ֵ */
    timx_handler_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;           /* ʱ�ӷ�Ƶ���� */
    HAL_TIM_Base_Init(&timx_handler_1);
    
    HAL_TIM_Base_Start_IT(&timx_handler_1);                               /* ʹ�ܻ�����ʱ��x�ͼ�������жϣ�TIM_IT_UPDATE */
    __HAL_TIM_CLEAR_IT(&timx_handler_1,TIM_IT_UPDATE);                    /* ��������жϱ�־λ */
}

/**
 * @brief       ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
                �˺����ᱻHAL_TIM_Base_Init()��������
 * @param       ��
 * @retval      ��
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        BTIM_TIMX_INT_CLK_ENABLE();                                     /*ʹ��TIMʱ��*/
        HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3);                 /* ��ռ1�������ȼ�3����2 */
        HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);                         /*����ITM3�ж�*/
    }
	if (htim->Instance == TIM6)
	{
		do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0);    /* TIM9 ʱ��ʹ�� */
		HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 2);
		HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}
}

/**
 * @brief       ������ʱ��TIMX�жϷ�����
 * @param       ��
 * @retval      ��
 */

void BTIM_TIMX_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&timx_handler);                                  /*��ʱ���ص�����*/
	
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&timx_handler_1); 
}




/*************************************    ��������    ����������    ****************************************************/

Motor_TypeDef_1 g_motor_data_1;  /*�����������*/
ENCODE_TypeDef_1 g_encode_1;     /*��������������*/

/**
 * @brief       ����ٶȼ���
 * @param       encode_now����ǰ�������ܵļ���ֵ
 *              ms�������ٶȵļ�����ж�1ms����һ�Σ�����ms = 5��5ms����һ���ٶ�
 * @retval      ��
 */

void speed_computer_1(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* �洢�ٶȽ����˲����� */

    if (sp_count == ms)                                     /* ����һ���ٶ� */
    {
        /* ������ת�� 
           ��һ�� ������ms�����ڼ����仯��
           �ڶ��� ������1min�ڼ����仯����g_encode.speed * ((1000 / ms) * 60 ��
           ������ �����Ա�������תһȦ�ļ�����������Ƶ���� * �������ֱ��ʣ�
           ���Ĳ� �����Լ��ٱȼ��ɵó����ת��
        */
        g_encode_1.encode_now = encode_now;                                /* ȡ����������ǰ����ֵ */
        g_encode_1.speed = (g_encode_1.encode_now - g_encode_1.encode_old);    /* �������������ֵ�ı仯�� */
        
        speed_arr[k++] = (float)(g_encode_1.speed * ((1000 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* ������ת�� */
        
        g_encode_1.encode_old = g_encode_1.encode_now;          /* ���浱ǰ��������ֵ */

        /* �ۼ�10���ٶ�ֵ�����������˲�*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* ð������*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* ��ֵ�Ƚ� */
                    { 
                        temp = speed_arr[j];                /* ��ֵ��λ */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* ȥ�����߸ߵ����� */
            {
                temp += speed_arr[i];                       /* ���м���ֵ�ۼ� */
            }
            
            temp = (float)(temp / 6);                       /*���ٶ�ƽ��ֵ*/
            
            /* һ�׵�ͨ�˲�
             * ��ʽΪ��Y(n)= qX(n) + (1-q)Y(n-1)
             * ����X(n)Ϊ���β���ֵ��Y(n-1)Ϊ�ϴ��˲����ֵ��Y(n)Ϊ�����˲����ֵ��qΪ�˲�ϵ��
             * qֵԽС����һ������Ա������Ӱ��Խ����������Խƽ�ȣ����Ƕ����ٶȱ仯����ӦҲ��Խ��
             */
            g_motor_data_1.speed = (float)( ((float)1 * temp)); //+ (g_motor_data_1.speed * (float)0.52) );
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}

/*************************************    ��������    ����������    ****************************************************/

Motor_TypeDef_2 g_motor_data_2;  /*�����������*/
ENCODE_TypeDef_2 g_encode_2;     /*��������������*/

/**
 * @brief       ����ٶȼ���
 * @param       encode_now����ǰ�������ܵļ�                                       ��ֵ
 *              ms�������ٶȵļ�����ж�1ms����һ�Σ�����ms = 5��5ms����һ���ٶ�
 * @retval      ��
 */

void speed_computer_2(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* �洢�ٶȽ����˲����� */

    if (sp_count == ms)                                     /* ����һ���ٶ� */
    {
        /* ������ת�� 
           ��һ�� ������ms�����ڼ����仯��
           �ڶ��� ������1min�ڼ����仯����g_encode.speed * ((1000 / ms) * 60 ��
           ������ �����Ա�������תһȦ�ļ�����������Ƶ���� * �������ֱ��ʣ�
           ���Ĳ� �����Լ��ٱȼ��ɵó����ת��
        */
        g_encode_2.encode_now = encode_now;                                /* ȡ����������ǰ����ֵ */
        g_encode_2.speed = (g_encode_2.encode_now - g_encode_2.encode_old);    /* �������������ֵ�ı仯�� */
        
        speed_arr[k++] = (float)(g_encode_2.speed * ((1000 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* ������ת�� */
        
        g_encode_2.encode_old = g_encode_2.encode_now;          /* ���浱ǰ��������ֵ */

        /* �ۼ�10���ٶ�ֵ�����������˲�*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* ð������*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* ��ֵ�Ƚ� */
                    { 
                        temp = speed_arr[j];                /* ��ֵ��λ */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* ȥ�����߸ߵ����� */
            {
                temp += speed_arr[i];                       /* ���м���ֵ�ۼ� */
            }
            
            temp = (float)(temp / 6);                       /*���ٶ�ƽ��ֵ*/
            
            /* һ�׵�ͨ�˲�
             * ��ʽΪ��Y(n)= qX(n) + (1-q)Y(n-1)
             * ����X(n)Ϊ���β���ֵ��Y(n-1)Ϊ�ϴ��˲����ֵ��Y(n)Ϊ�����˲����ֵ��qΪ�˲�ϵ��
             * qֵԽС����һ������Ա������Ӱ��Խ����������Խƽ�ȣ����Ƕ����ٶȱ仯����ӦҲ��Խ��
             */
            g_motor_data_2.speed = (float)( ((float)0.48 * temp) + (g_motor_data_2.speed * (float)0.52) );
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}






