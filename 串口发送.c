#include<reg52.h>      //单片机向电脑发送字符
typedef unsigned char uchar; 
typedef unsigned int uint;
void init_chuankou()
{		  
	TMOD=0x20;		 //波特率9600，方式1，晶振11.0592
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;	    
}
void send(char str[])
{
	uint i=0;  
	init_chuankou();
	ES=0;
	while(str[i])
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
		i++;  
	}
	ES=1;
}
