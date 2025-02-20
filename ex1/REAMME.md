打开P27，按照《指南》进行
# 问题1
操作位置：2.2-2.2.1-2-(2)  
输入“sudo apt-get install build-essential g++-multilib gcc-multilib”，遇到报错信息如下  
![image](https://github.com/user-attachments/assets/0a4a671e-fa70-4389-a13c-2bd2f98d839f)  
我讲报错信息丢给chatGPT，得到了如下反馈  
![image](https://github.com/user-attachments/assets/253eb207-c32c-4d3b-bd86-6bc24cb8f8e8)
解决方法：此时我打开了VPN，输入sudo apt update，成功执行完毕
# 问题2
下载Nachos，我个人将压缩包“Nachos-3.4-SDU(for lecture).zip”中的三个文件夹，用一个“Nachos”文件夹包了起来，如下  
![image](https://github.com/user-attachments/assets/e408ccf1-822a-4699-bdb7-6d63ae65855d)
# 问题3
操作位置：2.2-2.2.1-3-(3)  
如果你不知道如何运行make clean，那么记住：在包含Makefile的文件夹下运行，  
但是在这里code文件夹底下拥有“Makefile.common”和“Makefile.dep”文件，这是一个技巧：  
**现分别执行如下命令**  
**make -f Makefile.common clean**  
**make -f Makefile.common**  
执行make -f Makefile.common clean命令，得到报错信息如下：  
Makefile.common:44: ../Makefile.dep: No such file or directory  
make: *** No rule to make target '../Makefile.dep'.  Stop.  
这是因为Makefile.common中44行有“../Makefile.dep”  
也就是它去上级目录寻找Makefile.dep了，但是Makefile.dep是在同级目录的，所以  
**将Makefile.common中44行的../Makefile.dep改为Makefile.dep**  
于是make -f Makefile.common clean可以正确执行
**执行make -f Makefile.common**，得到报错信息如下：  
\>\>\> Linking arch/unknown-i386-linux/bin/nachos <<<
g++  -m32   -o arch/unknown-i386-linux/bin/nachos
g++: fatal error: no input files
compilation terminated.
make: *** [Makefile.common:93: arch/unknown-i386-linux/bin/nachos] Error 1
