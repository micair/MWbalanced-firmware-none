
#include <uart.h>   
#include "string.h"
/***************************************************************
** 函数名称: Uart1Init
** 功能描述: UART1初始化函数
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2014年08月01日
***************************************************************/
void Uart1Init(void)		//9600bps@20.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0xF7;			//设定定时初值
	T2H = 0xFD;			//设定定时初值
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x10;		//启动定时器2
//	TI = 1;				
}

/***************************************************************
** 函数名称: Uart2Init
** 功能描述: UART1初始化函数
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2014年08月01日
***************************************************************/
void Uart2Init(void)		//9600bps@20.000MHz
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0xF7;			//设定定时初值
	T2H = 0xFD;			//设定定时初值
	AUXR |= 0x10;		//启动定时器2
	IE2 = 0x01;			//使能串口2中断
}

/***************************************************************
** 函数名称: UART1ReceiveByte
** 功能描述: UART1接收函数
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2014年08月01日
***************************************************************/
unsigned char UART1ReceiveByte(void)
{
    unsigned char xdata ucRxd1; 
    /*if(RI == 1)					     
    {
      RI = 0;
      ucRxd1 = SBUF;
      return(ucRxd1);		 
    }
    //return 0;	  */
	while(RI==0);
	RI = 0;
	ucRxd1 = SBUF;
	return(ucRxd1);
}

/***************************************************************
** 函数名称: UART2ReceiveByte
** 功能描述: UART2接收函数
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2014年08月01日
***************************************************************/
unsigned char UART2ReceiveByte(void)
{
    unsigned char xdata ucRxd2; /*
	if ((S2CON & 0x01) == 1)  
    {  
      S2CON &= 0xFE;  
      ucRxd2 = S2BUF;
	  return(ucRxd2);  
    }     		 	   */
	while((S2CON & 0x01) == 0);
	S2CON &= 0xFE;
	ucRxd2 = S2BUF;
	return(ucRxd2);
}

/***************************************************************
** 函数名称: UART1SendByte
** 功能描述: UART1发送函数
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2014年08月01日
***************************************************************/
void UART1SendByte(unsigned char TxD1)  
{   
    SBUF=TxD1;  
    while(TI == 0);//等待发送完成 
    //while(!TI);//等待发送完成 
    TI=0;   
}  

/***************************************************************
** 函数名称: UART2SendByte
** 功能描述: UART2发送函数
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2014年08月01日
***************************************************************/
void UART2SendByte(unsigned char TxD2)  
{   
    S2BUF=TxD2;  
    while ((S2CON & 0x02) == 0); //等待发送完成 
    S2CON &= 0xFD;    
}

/***************************************************************
** 函数名称: UART2SendStr
** 功能描述: UART2发送字符串
** 输　入:   
** 输　出:   
** 全局变量: 
** 作　者:   喵呜实验室
** 淘  宝：  Http://miaowlabs.taobao.com
** 日　期:   2016年05月04日
***************************************************************/ 
void UART2SendStr(char *str)
{
	unsigned char len=0;
	unsigned char i=0;

	len = strlen(str);
	for(i=0; i<len; i++)
		UART2SendByte(*(str+i));
}   