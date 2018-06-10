#include<reg52.h>

typedef unsigned char uchar; 
typedef unsigned int uint;
typedef unsigned long ulong;
sbit dat=P3^7;	  //dat为DHT11串行数据接口
sbit led1=P1^0;
sbit led2=P1^2;
sbit led3=P1^4;
sbit led4=P1^6;


uchar rec_data[10];

void delayms(uint xms);
void delay_10us();
void sent(uchar code str[]);
void display(uint w1,uint w2,uint w3,uint w4);

char temp_init_l,temp_init_h,humi_init_l,humi_init_h,\
temp_l,temp_h,humi_l,humi_h,data_check;

void dht11_start()
{
	dat=1;
	delay_10us;	// 延时10us
	dat=0;
	delayms(20);
	dat=1;
	delay_10us(); //主机拉高40us
	delay_10us();
	delay_10us();
	delay_10us();
	//dat=1;
 	/*while(dat);
	delay_10us();  //DHT响应80us
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	while(!dat);
	delay_10us();  //DHT拉高80us
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	 */
} 

void dht11_over()	//结束通信
{	
	delay_10us();	  //延时50us
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	dat=1;
}  	   

char dht11_data_analyse()
{
	uchar i,data_analyse=0;
	for(i=0;i<8;i++)
	{
		while(!dat);
		data_analyse=data_analyse<<1;
		delay_10us();    //延时50us，若dat还为高则说明数据为1，否则为0
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();
		if(dat)		 //判断数据为1或者为0
			data_analyse=data_analyse+1;   //数据为1时，使dat加1来接收数据1
		while(dat);	
	}

	return data_analyse;
}

void dht11_data_read()
{
	dht11_start();
	led1=dat;				//标记指示1
	if(!dat)
	{
		led2=0;           //标记指示灯2
		while(!dat);
		led3=0;       //标记指示灯3
		delay_10us();    //延时80us
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();    
		delay_10us();
		delay_10us();
		humi_init_h=dht11_data_analyse();
		humi_init_l=dht11_data_analyse();
		temp_init_h=dht11_data_analyse();
		temp_init_l=dht11_data_analyse();
		data_check=dht11_data_analyse();

		dht11_over();    
		led4=0;       //标记指示灯4
		if((humi_init_h+humi_init_l+temp_init_h+temp_init_l)==data_check)	//数据校验
		{
			humi_h=humi_init_h;
			humi_l=humi_init_l;
			temp_h=temp_init_h;
			temp_l=temp_init_l;	
			
		}
		rec_data[0]='0'+(humi_h/10);	  //将数据储存在数组中，方便发送给串口
 	  	rec_data[1]='0'+(humi_h%10);
 	  	rec_data[2]='R';
 	   	rec_data[3]='H';
	    rec_data[4]=' ';
 	  	rec_data[5]=' ';
 	  	rec_data[6]='0'+(temp_h/10);
	   	rec_data[7]='0'+(temp_h%10);
	    rec_data[8]='C';

	}
		
}

void main()
{
	while(1)
	{
		uint w1,w2,w3,w4;	
		delayms(1000);
		dht11_data_read();
		sent(rec_data);	  //串口发送函数
		while(1);
	}	
}	