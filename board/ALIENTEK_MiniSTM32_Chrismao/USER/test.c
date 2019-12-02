#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h" 
#include "tos.h"


//ALIENTEK Mini STM32�����巶������3
//����ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

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
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ�� 
	uart_init(72,9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�

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
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			}
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK MiniSTM32������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\r\n");  
//			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(10);   
//		}
	}	 
}














