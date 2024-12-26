#include <REGX52.H>
#include <intrins.h>
unsigned char x=0,b=0 ,A[]={0x01,0x02,0x04,0x08,0x10,0x40,0x80};
sbit Buzzer=P2^5;
void Int0_TIME(void)
{
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;//总开关
	ET0=1;//溢出中断
	TR0=1;//定时器启动
}
void Int0_WZD(void)
{
	IT0=0;//电平触发 1，边沿0
	IE0=0;//标志位
	EX0=1;//中断允许
	EA=1;//
	PX0=1;//中断优先级
}
void Buzzer_Delay500us()		
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}

void Buzzer_Time(unsigned int ms)//ms时长
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
	{
		Buzzer=!Buzzer;
		Buzzer_Delay500us();//1kHZ
	}
}
void main ()
{
	P2=0XF0;
  Int0_WZD();
	Int0_TIME();
	while (1)
	{
		if(x>=20)
		{
			x=0;
			P2=~A[b];	
			b++;
			if(b>=7)
			{
				b=0;
			}
		}
	}
}
void WZD() interrupt 0
{
   Buzzer_Time(100);
}
	void TIME() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	x++;
  
}