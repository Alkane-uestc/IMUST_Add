#include <REGX52.H>
#include  "intrins.h"
void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main ()
{
	unsigned char i, a[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P2=~a[i];
			Delay(400);
		}
		
	}
}

