#include <reg52.h>

sbit Duoji = P0^0;
sbit C1 = P2^0;
sbit C2 = P2^1;
sbit C3 = P2^2;
sbit C4 = P2^3;
sbit C5 = P2^4;
sbit C6 = P2^5;
sbit C7 = P2^6;
sbit C8 = P2^7;
sbit C9 = P1^0;

sbit IN1=P0^1;
sbit IN2=P0^2;//控制引脚
sbit IN3=P0^3;//控制引脚
sbit IN4=P0^4;

unsigned int Lift_Value = 100,Right_value = 100,Duoji_Value = 16,duoji;
unsigned int motor_Count = 0,Duoji_Count = 0;
unsigned int flag=0;
void delayms(unsigned int i)
{
    unsigned int j;
    for(; i>0; i--)
        for(j=114; j>0; j--);
}

void System_Init(void)
{
	TMOD = 0x12;
	TH1 = 0xFF;
  TL1 = 0xD2;
	TH0 = 164;
	TL0 = 164;
	
	ET1 = 1;
	ET0 = 1;
	EA = 1;
	
	TR1 = 1;
	TR0 = 1;
}

unsigned char Search_Line(void)
{
	if((C1==1) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 1;
		if((C1==1) && (C2==1) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 2;
	if((C1==0) && (C2==1) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 2;
	if((C1==0) && (C2==1) &&(C3==1) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 3;
	if((C1==0) && (C2==0) &&(C3==1) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 3;
		if((C1==0) && (C2==0) &&(C3==1) &&(C4==1) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 4;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==1) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 4;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==1) &&(C5==1) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 5;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==1) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 5;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==1) &&(C6==1) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 5;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==1) &&(C7==0) &&(C8==0) &&(C9== 0))
		return 6;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==1) &&(C7==1) &&(C8==0) &&(C9== 0))
		return 6;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==1) &&(C8==0) &&(C9== 0))
		return 7;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==1) &&(C8==1) &&(C9== 0))
		return 7;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==1) &&(C9== 0))
		return 8;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==1) &&(C9== 1))
		return 8;
	if((C1==0) && (C2==0) &&(C3==0) &&(C4==0) &&(C5==0) &&(C6==0) &&(C7==0) &&(C8==0) &&(C9== 1))
		return 9;
//	if((C1==0) && (C2==0) &&(C3==0) &&(C4==1) &&(C5==1) &&(C6==1) &&(C7==0) &&(C8==0) &&(C9== 0))
//	return 0;
	else
		return 0;
}

void main(void)
{
	unsigned char dadt,dadt_1;
	duoji = Duoji_Value;
//	delayms(1000);
	System_Init();	
	while(1)
	{
		dadt = Search_Line();
		if(dadt == 0)
		{
				dadt=dadt_1;
		}
		dadt_1=dadt;
		switch(dadt)
		{
			case 0: duoji = Duoji_Value+0; Lift_Value = 50;break;//三灯减速
			case 1: duoji = Duoji_Value-5;	Lift_Value = 50;  flag=1;	 	 break;//左电机和右电机的值
			case 2: duoji = Duoji_Value-5 ;	Lift_Value = 60;	flag=0;  break;
			case 3: duoji = Duoji_Value-3;	Lift_Value = 40;	flag=0;   break;
			case 4: duoji = Duoji_Value-2;	Lift_Value = 50;	flag=0;   break;
			
			case 5: duoji = Duoji_Value+0;	Lift_Value = 85;	flag=0;  break;
			
			case 6: duoji = Duoji_Value+1;	Lift_Value = 50;	flag=0;   break;
			case 7: duoji = Duoji_Value+2;	Lift_Value = 35;	flag=0;   break;
			case 8: duoji = Duoji_Value+3;	Lift_Value = 45;  flag=0;  break;
			case 9: duoji = Duoji_Value+4;	Lift_Value = 55;  flag=2;		 break;
//			case 10: duoji = Duoji_Value+0;	Lift_Value = 30;    		 break;
		}
//		if(flag==1 && dadt==0)
//		{
//			//if(dadt==1)
//				
////			flag=0;
//			 duoji = Duoji_Value-7;	
//			Lift_Value = 55; 
////			delayms(500);
//			while(Search_Line()==0);
//			
//		}
//		if(flag==2 && dadt==0)
//		{
////			flag=0;
//			duoji = Duoji_Value+4;	
//			Lift_Value = 40;
////			delayms(500);
//			while(Search_Line()==0);
//		}
//		
	}
}
/*
控制两路电机
*/
void Timer0_Init(void) interrupt 1
{
	motor_Count++;
	if(motor_Count == 100)/* 一个脉冲分成200分 */
	{
		motor_Count = 0;
	}
/*****************************************************************/	
	if(motor_Count <= Lift_Value)
	{	
		IN1=0;
		IN2=1;
	}
	else
	{
		IN1=0;
		IN2=0;
	}
/*****************************************************************/
	if(motor_Count <= Right_value)
	{	
		IN3=1;
		IN4=0;
	}
	else
	{
		IN3=0;
		IN4=0;
	}
/*****************************************************************/	
}

/*
控制舵机，0.5ms=0°，1.5ms=90°，2.5ms=180°，
因为T0会打断T1，所以周期计算不对，不过现在的数正好能使用，
Duoji_Value=15，高电平持续时间1.5ms。
*/
void Timer1_Init(void) interrupt 3
{	
	TH1=0xFF;
  TL1=0xD1;
	Duoji_Count++;
	if(Duoji_Count==300)
	{
		Duoji_Count = 0;
	}
	if(Duoji_Count < duoji)
	{
		Duoji = 1;
	}
	else
	{
		Duoji = 0;
	}
}
