# HomeWork
软件工程作业
这个项目是实验室一个六自由度机器人的控制系统实现代码，由C++实现。
主要实现了以下功能：
1. 控制6个机器人的步进电机运动
2. 实现和上位机的通信
3. 避免六自由度的奇异位姿的出现
4. 保证机器人动平台仅在运动空间内运动。
主要代码的结构和作用如下：

1.	通信类:负责实现串口通信
communicateClass.h
communicateClass.ino
2.	数学计算类：负责实现机器人运动过程中电机和动平台运动关系的基本计算单元。
mathOperationClass.h
mathOperationClass.ino
3.	电机驱动类：负责实现电动机的占空比控制，提供简洁的仅需角度的借口。
motorClass.h
motorClass.ino
4.	机器人综合运动控制模块：负责机器人在不同种工作模式前提下的运动控制和规划。
SixFreedomPlatformClass.h
SixFreedomPlatformClass.ino
5.	测试程序：按照不同边界条件对程序进行测试。
Test_sixFreedom.h
Test_sixFreedom.ino
