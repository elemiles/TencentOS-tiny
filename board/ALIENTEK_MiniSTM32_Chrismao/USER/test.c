#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h" 
#include "tos.h"


//ALIENTEK Mini STM32开发板范例代码3
//串口实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

k_task_t task1;
k_stack_t task_stack1[1024];
k_task_t task2;
k_stack_t task_stack2[1024];

void test_task1(void *Parameter)
{
    while(1)
    {
        printf("task one\r\n");
        tos_task_delay(1000);
    }
}

void test_task2(void *Parameter)
{
    while(1)
    {
        printf("task two\r\n");
        LED0=!LED0;
        tos_task_delay(500);
    }
}
 
int main(void)
{
    k_err_t err;
//	u8 t;
//	u8 len;	
//	u16 times=0;  
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化 
	uart_init(72,9600);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口

    printf("Welcome to TencentOS tiny\r\n");

    tos_knl_init(); // TOS Tiny kernel initialize
                                        
    err = tos_task_create(&task1, 
                          "task1", 
                          test_task1,
                          NULL, 
                          2, 
                          task_stack1,
                          1024,
                          20);
    if(err != K_ERR_NONE)
        printf("TencentOS Create task fail! code : %d \r\n",err);
    
    err = tos_task_create(&task2, 
                      "task2", 
                      test_task2,
                      NULL, 
                      2, 
                      task_stack2,
                      1024,
                      20);
    
    tos_knl_start(); // Start TOS Tiny





    
	//while(1)
	{
//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK MiniSTM32开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
//			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
//			delay_ms(10);   
//		}
	}	 
}














