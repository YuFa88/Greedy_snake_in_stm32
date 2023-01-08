# Greedy snake game

(OLED screen + punctual atom battleship development board)

### Experimental equipment:

- Battleship STM32F103 development board V3 version

- Infrared remote control

- OLED small screen

### Purpose of the experiment:

- Learn OLED screen usage

- Master the algorithm implementation of Snake game

- Learn the use of infrared remote control.

### Hardware resources:

​	1, DS0 (connected to PB5)

​	2, serial port 1 (baud rate: 115200, PA9/PA10 is connected to the onboard USB to serial port chip CH340)

​	3, ALIENTEK 2.8/3.5/4.3/7 inch TFTLCD module (driven by FSMC, FSMC_NE4 connected to LCD chip selection/A10 connected to RS) 

​	Timer 4 (TIM4), using TIM4_CH4 (PB9) input capture, to decode the infrared signal.

​	3, ALIENTEK infrared remote control

### File tree

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



