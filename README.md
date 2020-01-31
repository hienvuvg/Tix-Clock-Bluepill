# Tix Clock DIY

This is the code for a DIY tix clock with STM32 BluePill using HAL library in KeilC or IAR for ARM.

I have two folders here for STM32F103C8T6 and STM32F334C8 which have the same footprint and can all be used in STM32 BluePill PCB. My folders only contain the source code and you can generate the whole programming files by running the ".ioc" files on STm32CubeMX. All of the peripheral setups can be found in TixClockF334.pdf or the ".ioc" files.

In this design, I use UDN2981A for 27 LED drivers instead of 74HC595 because of the availability. If you want to switch to 74HC595, you need to modify the code and that can save your IC a lot of pins. Otherwise, you can find several alternatives for UDN2981A or make the drivers yourself by using BJTs. 

All of the LEDs are not displayed with similar brightness. Thus, you should calculate the needed current and suitable resistors for them to get the same brightness.

For time setting, I use 3 buttons for increasing hour and minute. You can modify the code to make it works as you want. There is a variable named setPM in main.c which determines the display type, you should set it to 0 if you want to show 24h time format or leave it there to see time in the PM format.

This is a short demonstration for my clock: https://youtu.be/NBCf8XFfK70
