# balanced_car
balancd_car project base on stm32
-----
#### 项目描述
- 智能小车，能够通过esp8266 wifi模块实现远程控制，加入us_100超声波测距模块检测距离，实现避障自动功能
#### 项目技术点
- stm32
- 接口、串口、定时器、pwm波
- stm32官方库的引用
- qt界面开发平台
- tcp/ip协议
#### 项目实现
1. +小车的驱动：初始化定时器TIM2，设定装载值，设置TIM2的crr1、crr，使对应管脚产生zhanfengbi占空比%60的pwm波
   +小车的控制：通过控制相应管教的输出状态，控制小车的运行状态
2. +初始化WiFi模块：初始化串口3，打开串口中断，
   +运行wifi模块，打开sever服务：给CH_PD管脚高电平，启动WiFi模块，t添加延时（很重要），调用wifi初始化函数通过串口向wifi模块发送命令启动server服务
3. +利用qt编写tcp客户端
   +事项远程控制：通过网络向模块发送数据，模块接受数据、解析数据、改变状态量，控制小成运行
4. +初始化us_100超声波模块：初始化串口2，开开串口中断
   +运行us_100超声波模块：通过定时器中断，每隔一段时间通过串口向模发送命令（0x55），此时串口接收到两个字节的数据，根据文档说明，操作处理数据得到距离
   +实现避障：对计算得到的数据进行判断，根据结果判断小车是否需要避障来改变状态量，在定时器中断中检查状态量，改变小车的运行状态实现避障
   
   

