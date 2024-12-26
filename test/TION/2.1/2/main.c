#include <REGX52.H>
#include <INTRINS.H>
unsigned char KeyNumber=0;

//蜂鸣器端口：
sbit Buzzer=P2^5;
void Delay()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


/**
  * @brief  蜂鸣器私有延时函数，延时500us
  * @param  无
  * @retval 无
  */
void Buzzer_Delay500us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}

/**
  * @brief  蜂鸣器发声
  * @param  ms 发声的时长，范围：0~32767
  * @retval 无
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
	{
		Buzzer=!Buzzer;
		Buzzer_Delay500us();
	}
}
unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){Delay();while(P1_7==0);Delay();KeyNumber=1;}
	if(P1_6==0){Delay();while(P1_6==0);Delay();KeyNumber=5;}
	if(P1_5==0){Delay();while(P1_5==0);Delay();KeyNumber=9;}
	if(P1_4==0){Delay();while(P1_4==0);Delay();KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){Delay();while(P1_7==0);Delay();KeyNumber=2;}
	if(P1_6==0){Delay();while(P1_6==0);Delay();KeyNumber=6;}
	if(P1_5==0){Delay();while(P1_5==0);Delay();KeyNumber=10;}
	if(P1_4==0){Delay();while(P1_4==0);Delay();KeyNumber=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){Delay();while(P1_7==0);Delay();KeyNumber=3;}
	if(P1_6==0){Delay();while(P1_6==0);Delay();KeyNumber=7;}
	if(P1_5==0){Delay();while(P1_5==0);Delay();KeyNumber=11;}
	if(P1_4==0){Delay();while(P1_4==0);Delay();KeyNumber=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){Delay();while(P1_7==0);Delay();KeyNumber=4;}
	if(P1_6==0){Delay();while(P1_6==0);Delay();KeyNumber=8;}
	if(P1_5==0){Delay();while(P1_5==0);Delay();KeyNumber=12;}
	if(P1_4==0){Delay();while(P1_4==0);Delay();KeyNumber=16;}
	
	return KeyNumber;
}

void main ()
{
	while(1)
	{
		KeyNumber=MatrixKey();
		if(KeyNumber==1)
		{
			Buzzer_Time(261);
		}
				if(KeyNumber==2)
		{
			Buzzer_Time(293);
		}
				if(KeyNumber==3)
		{
			Buzzer_Time(329);
		}
				if(KeyNumber==4)
		{
			Buzzer_Time(349);
		}
				if(KeyNumber==5)
		{
			Buzzer_Time(392);
		}
				if(KeyNumber==6)
		{
			Buzzer_Time(440);
		}
				if(KeyNumber==7)
		{
			Buzzer_Time(493);
		}
		
	}
	
}