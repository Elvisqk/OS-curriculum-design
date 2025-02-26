# 运行Nachos应用程序的方法： 
(1)在../test 目录下运行make，将该目下的几个现有的Nachos应用程序（.c文件）交叉编译，并转换成Nachos可执行的.noff格式文件。 现有的几个应用程序：halt.c，matmult.c，shell.c，sort.c  
(2)在../userprog 目录下运行make编译生成Nachos系统，键入命令./nachos -x ../test/halt.noff可让 Nachos 运行应用程序 halt.noff，参数-x 的作用是 Nachos 运行其应用程序。  
(3)nachos -d m -x ../test/halt.noff  
加上参数 -d m 输出显示 Nachos 模拟的 MIPS CPU 所执行的每条指令  
nachos -d m -s -x ../test/halt.noff  
可以再加上参数-s，以输出每条指令执行后对应寄存器的状态