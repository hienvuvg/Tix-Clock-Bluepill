# TixClock
This is the code for a DIY tix clock on STM32 BluePill using HAL library in KeilC or IAR for ARM.

I have two folders here for STM32F103C8T6 and STM32F334C8 which have the same footprint and can all be used in STM32 BluePill PCB. My folders only contain the source code and you can generate the whole programming files by running the ".ioc" files on STm32CubeMX. 

The version on F334 is more complete than F103. If you want to use the original BluePill board with F103, you should update the user contents from "main.c", "stm32f3xx_it.c" and "main.h" in F334 to corresponding files in F103 folder.


