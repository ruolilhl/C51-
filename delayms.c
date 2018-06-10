#include<intrins.h>
typedef unsigned char uchar;   
typedef unsigned int uint;

void delayms(uint xms)	//循环延时Xms函数
{			  
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void delay_10us()  //延时10us函数
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}