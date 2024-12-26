#include <REGX52.H>

// 定义DA1灯所连接的引脚，这里假设DA1灯连接在P1.0引脚，你可根据实际情况修改
sbit DA1 = P1^0;  

// 定时器0初始化函数声明
void Timer0_Init(void);
// 简单延时函数声明，用于一些非精确延时场景
void Delay(unsigned int xms);

// 全局变量，用于控制呼吸灯的PWM占空比
unsigned char pwm_duty = 0;  
// 全局变量，用于控制呼吸灯占空比的增减方向，1表示增加（变亮），0表示减小（变暗）
unsigned char pwm_direction = 1;  

// 定时器0初始化函数，配置定时器0相关寄存器，使其以合适的定时周期工作并开启中断
void Timer0_Init(void)
{
    TMOD &= 0xF0;  // 先清除TMOD寄存器的低4位，设置定时器0工作模式
    TMOD |= 0x01;  // 设置定时器0为模式1（16位定时器/计数器）
    // 重新计算的定时器初值，用于实现大约1秒的定时周期（基于12MHz晶振）
    TH0 = 0x3C;  
    TL0 = 0xB0;
    ET0 = 1;       // 允许定时器0中断
    EA = 1;        // 打开总中断允许位
    TR0 = 1;       // 启动定时器0开始计数
}

// 简单的延时函数，通过循环消耗时间来实现大致的毫秒级延时
void Delay(unsigned int xms)
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

// 定时器0中断服务函数，在这里实现8个LED依次点亮以及DA1灯呼吸灯效果的逻辑
void Timer0Interrupt() interrupt 1
{
    static unsigned char led_count = 0;  // 用于记录当前要操作的LED序号，静态变量保持值
    static unsigned char pwm_count = 0;  // 用于呼吸灯效果计数，记录定时中断次数

    // 重新装入定时器0初值，保证定时周期稳定，约1秒（12MHz晶振下）
    TH0 = 0x3C;  
    TL0 = 0xB0;

    // 控制8个LED依次点亮，每8次定时器中断切换一次点亮的LED（即约每8秒切换一次）
    if (++pwm_count >= 8)
    {
        pwm_count = 0;
        P2 = ~(0x01 << led_count);  // 通过位操作依次点亮连接在P2口的8个LED（低电平点亮）
        if (++led_count >= 8)
        {
            led_count = 0;
        }
    }

    // 控制呼吸灯效果，每10次定时器中断（即约每10秒）调整一次PWM占空比
    if (++pwm_count % 10 == 0)  
    {
        if (pwm_direction)
        {
            pwm_duty++;
            if (pwm_duty >= 100)  // 限制占空比最大值，达到最大值后开始变暗
            {
                pwm_direction = 0;
            }
        }
        else
        {
            pwm_duty--;
            if (pwm_duty <= 0)  // 限制占空比最小值，达到最小值后开始变亮
            {
                pwm_direction = 1;
            }
        }
    }

    // 根据当前的PWM占空比控制DA1灯的亮灭，实现呼吸灯效果
    if (pwm_count < pwm_duty)
    {
        DA1 = 0;  // 点亮DA1灯（假设低电平点亮，按实际硬件调整）
    }
    else
    {
        DA1 = 1;  // 熄灭DA1灯
    }
}

// 主函数，程序入口
void main()
{
    Timer0_Init();  // 初始化定时器0
    while (1)
    {
        // 主循环可添加其他功能代码，这里暂时为空，等待定时器中断实现灯光效果
    }
}