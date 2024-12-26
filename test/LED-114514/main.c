#include <REGX52.H>

// 数码管段码表
unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//P0

void Nixie(unsigned char Location, unsigned char Number)//P2.2/2.3/2.4
{
    switch (Location)    //位码输出
    {
    case 1:
        P2_4 = 1;
        P2_3 = 1;
        P2_2 = 1;
        break;
    case 2:
        P2_4 = 1;
        P2_3 = 1;
        P2_2 = 0;
        break;
    case 3:
        P2_4 = 1;
        P2_3 = 0;
        P2_2 = 1;
        break;
    case 4:
        P2_4 = 1;
        P2_3 = 0;
        P2_2 = 0;
        break;
    case 5:
        P2_4 = 0;
        P2_3 = 1;
        P2_2 = 1;
        break;
    case 6:
        P2_4 = 0;
        P2_3 = 1;
        P2_2 = 0;
        break;
    case 7:
        P2_4 = 0;
        P2_3 = 0;
        P2_2 = 1;
        break;
    case 8:
        P2_4 = 0;
        P2_3 = 0;
        P2_2 = 0;
        break;
    }
    P0 = NixieTable[Number];  //段码输出
}

void Delay(unsigned int xms)  // 简单的延时函数，用于控制数码管扫描间隔
{
    unsigned char i, j;
    while (xms--)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        } while (--i);
    }
}

void main()
{
    while (1)
    {
        // 依次对四位数码管进行显示设置和短暂延时，实现动态扫描显示效果
        Nixie(1, 1);
        Delay(1);  // 适当延时，这个延时时间可以根据实际情况调整
        Nixie(2, 1);
        Delay(1);
        Nixie(3, 4);
        Delay(1);
        Nixie(4, 5);
        Delay(1);
			  Nixie(5, 1);
        Delay(1);
			Nixie(6, 4);
        Delay(1);
			
			
    }
}