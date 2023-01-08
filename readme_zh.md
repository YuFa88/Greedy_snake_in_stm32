# 贪吃蛇游戏

（oled屏+正点原子战舰开发板）

实验器材:
	战舰STM32F103开发板V3版本
	红外遥控器
	OLED小屏
实验目的:

​	学习oled屏幕使用

​	掌握贪吃蛇游戏算法实现

​     学习红外遥控器的使用.

硬件资源:
	1,DS0(连接在PB5)
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A10接RS) 
	4,定时器4(TIM4),使用TIM4_CH4(PB9)的输入捕获,来解码红外信号.
	3,ALIENTEK红外遥控器

文件树

```
.\Greedy snake
├─CORE
├─HARDWARE
│  ├─24CXX
│  ├─KEY
│  ├─LED
│  ├─OLED
│  └─REMOTE
├─OBJ
├─STM32F10x_FWLib
│  ├─inc
│  └─src
├─SYSTEM
│  ├─delay
│  ├─sys
│  └─usart
└─USER
```

​	



