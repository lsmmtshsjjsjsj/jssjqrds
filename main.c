#include "./BSP/PID/pid.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/ATIME/atime.h"
#include "./BSP/GTIME/gtime.h"
#include "./BSP/COUNTER/counter.h"

#include "oled.h"

 int g_timex_encode_count_1 = 0;
 int g_timex_encode_count_2 = 0;
 char re_num[8] = {0};
extern TIM_HandleTypeDef g_timx_encode_chy_handle_2;
void modle_exen(void);
int main()
{
	    uint8_t len;
    uint16_t times = 0;
	
	 HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
	delay_init(168);                        /* 延时初始化 */

    atim_timx_cplm_pwm_init_1(10000-1,168);/* 168 000 000 / 1 = 168 000 000 168Mhz的计数频率，计数16800次为100us */
    atim_timx_cplm_pwm_init_2(10000-1,168);/* 168 000 000 / 1 = 168 000 000 168Mhz的计数频率，计数16800次为100us *///高频pwm可防止电机低速异响
	
	gtim_timx_encoder_chy_init_2(0xffff,0);
	gtim_timx_encoder_chy_init_1(0xffff,0);
	
	
	btim_timx_int_init(1000-1,84-1);
	usart_init_1(115200);
	btim_timx_int_init_1(1000-1,84-1);
	
	OLED_Init();
	pid_init_1();
	pid_init_2();
	
	while(1)
	{


	  OLED_ShowSignedNum(1,1,g_motor_data_1.speed,10);
	  OLED_ShowSignedNum(3,1,g_motor_data_2 .speed,10);
	  OLED_ShowSignedNum(2,1,g_speed_pid_1.SetPoint,10);
	  OLED_ShowSignedNum(4,1,g_speed_pid_2.SetPoint,10);
		modle_exen();
		/*
		0150 1023
		:		B1轮以150的速度正转，B2轮以23的速度反转
		
		
		*/
       if (g_usart_rx_sta & 0x8000)         /* 接收到了数据? */
        {
            len = g_usart_rx_sta & 0x3fff;  /* 得到此次接收到的数据长度 */

			re_num[0] = g_usart_rx_buf[0]-'0';//Bl轮的转向 0：正    1：反
			re_num[1] = g_usart_rx_buf[1]-'0';//速度
			re_num[2] = g_usart_rx_buf[2]-'0';
			re_num[3] = g_usart_rx_buf[3]-'0';
			
			re_num[4] = g_usart_rx_buf[4]-'0';//B2轮的转向 0：正    1：反
			re_num[5] = g_usart_rx_buf[5]-'0';
			re_num[6] = g_usart_rx_buf[6]-'0';
			re_num[7] = g_usart_rx_buf[7]-'0';
			
				OLED_ShowChar(5,1,re_num[0]+'0');//B1轮（右上）
				OLED_ShowChar(5,2,re_num[1]+'0');
				OLED_ShowChar(5,3,re_num[2]+'0');
				OLED_ShowChar(5,4,re_num[3]+'0');
			                               
			    OLED_ShowChar(5,5,re_num[4]+'0');//B2轮（左下）
			    OLED_ShowChar(5,6,re_num[5]+'0');
			    OLED_ShowChar(5,7,re_num[6]+'0');
			    OLED_ShowChar(5,8,re_num[7]+'0');
			
            g_usart_rx_sta = 0;
        }

	}
}

void modle_exen()
{
	if(re_num[0] == 1)
	{
		g_speed_pid_1.SetPoint = re_num[1]*100+re_num[2]*10+re_num[3] ;
	}
	else if(re_num[0] == 0)
	{
		g_speed_pid_1.SetPoint = -(re_num[1]*100+re_num[2]*10+re_num[3]) ;
	}
	else
	{
		g_speed_pid_1.SetPoint =0;
	}
	
	if(re_num[4] == 1)
	{
		g_speed_pid_2.SetPoint = re_num[5]*100+re_num[6]*10+re_num[7] ;
	}
	else if(re_num[4] == 0)
	{
		g_speed_pid_2.SetPoint = -(re_num[5]*100+re_num[6]*10+re_num[7]) ;
	}
	else
	{
		g_speed_pid_1.SetPoint =0;
	}	
	

	
}
