
#include <REGX52.H>
void main ()
{
	PCON=0X80;//9600
	SCON=0X50;//UART1
	TMOD=0X20;
	TL1 = 0xFA;		//1/(9600*12/11.0592*16*10^(-6))=6,256-6=250=FA
	TH1 = 0xFA;		//设定定时器重装值
	ET1=0;
	TR1=1;
	EA=1;
	ES=1;
	while(1);
	
}
void CK_send(unsigned char a)
{
	SBUF=a;
	while(TI==0);//TI发送标志位
	TI=0;
}
	
void CK()  interrupt 4
{
	unsigned char a;
	if(RI==1)//RI接收标志位
	{
		P2=~SBUF;
		RI=0;
		if(SBUF=='U')
		{
			a='A';
			
			CK_send(a);
		}
	}
}