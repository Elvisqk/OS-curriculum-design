打开P27，按照《指南》进行
# 问题1
操作位置：2.2-2.2.1-2-(2)  
输入“sudo apt-get install build-essential g++-multilib gcc-multilib”，遇到报错信息如下  
![image](https://github.com/user-attachments/assets/0a4a671e-fa70-4389-a13c-2bd2f98d839f)  
我讲报错信息丢给chatGPT，得到了如下反馈  
![image](https://github.com/user-attachments/assets/253eb207-c32c-4d3b-bd86-6bc24cb8f8e8)
解决方法：此时我打开了VPN，并在终端执行命令sudo apt update，再次执行“sudo apt-get install build-essential g++-multilib gcc-multilib”，成功执行完毕
# 问题2
在用户文件夹底下，我的是“zhang”，建立OS目录，在OS目录底下，建立nachos-3.4目录  
下载Nachos，我个人将压缩包“Nachos-3.4-SDU(for lecture).zip”中的三个文件夹，用“nachos-3.4”文件夹包了起来，如下  
![image](https://github.com/user-attachments/assets/f36dda80-7730-45b5-8e49-8b92d797f96e)

# 问题3
操作位置：2.2-2.2.1-3-(3)  
如果你不知道如何运行make clean，那么记住：在包含Makefile的文件夹下运行，  
所以现在我在code的每一个包含Makefile的子文件夹中执行make clean和make  
在bin底下执行make clean和make成功，那么就可以继续跟着指南走了  
发现在lab3和test中执行make会报错，没关系，暂时用不到，lab3会在实验3解决，而test一会指南会解决
# 问题4
操作位置：2.3-2.3.1  
(a)su命令执行失败：Authentication failure  
找了半天密码，发现我压根没有设置root用户，解决办法：  
**执行sudo passwd root**  
设置密码  
然后你就可以用su命令了  
(b) cd /usr/local  
/usr/local是隐藏文件夹，直接找是找不到的，可以通过命令行寻找  
![image](https://github.com/user-attachments/assets/a2795046-cf3d-4610-a105-f24b3fc770ce)  
(c) copy file “gcc-2.8.1-mips.tar.gz” to file fold “/usr/local” with cp command.  
这句话不是命令，  
**先把gcc-2.8.1-mips.tar.gz复制到OS文件夹下，在终端进入OS文件夹**  
**执行命令cp gcc-2.8.1-mips.tar.gz /usr/local**  
(d) tar xzvf gcc-2.8.1-mips.tar.gz   
**执行命令cd /usr/local进入local目录下再执行tar xzvf gcc-2.8.1-mips.tar.gz**
# 思考：为什么nachos-3.4.tar.gz一定要安装在/usr/local目录中？
答：打开code/Makefile.dep，在大约38行左右，查看变量GCCDIR的值，即GCCDIR = /usr/local/mips/bin/decstation-ultrix-  
交叉编译器用于对../test目录下的Nachos应用程序（如sort.c）进行编译，经转换后会生成Nachos可执行的文件sort.noff：  
.noff可执行文件中的指令基于MIPS架构，Nachos模拟的CPU执行MIPS架构  
指南第1页(不计目录)写道：  
Nachos 模拟的CPU基于MIPS架构，执行MIPS指令集，用来执行Nachos的应用程序；因此Nachos 的编译程序应该将Nachos的应用程序（类似于C程序）编译
成包含MIPS指令集的可执行程序，以便在Nachos系统上运行。  
Nachos 本身没有提供编译器，其应用程序只能在Linux环境下编程，并在Linux环境下将其编译成基于 MIPS 指令集的应用程序，然后利用 Nachos 提供的工具
coff2noff 将其转换成Nachos 的应用程序（noff格式）。  
Nachos 系统提供的交叉编译器gcc-2.8.1-mips.tar.gz 提供的 gcc、g++、as、ld 等工具负责实现该功能。  
个人理解：  
/usr/local/ 目录是 Linux 系统中用于存放本地安装的软件、程序、库文件等内容的标准位置。  
这个压缩包包含与 MIPS 架构相关的工具链、编译器、库或模拟器等，将它们放在 /usr/local/ 下，以便系统的其他程序或开发人员可以访问和使用。
# 问题5
操作位置：2.5  
在c++example目录下**执行make命令**，得到报错：  
![image](https://github.com/user-attachments/assets/dc921de4-957b-4300-92ec-d5feed94f0ad)  
**解决方案：将inheritstack.cc、templatestack.cc和stack.cc中的<iostream.h>改为\<iostream>**  
**再次执行make**，得到报错：  
![image](https://github.com/user-attachments/assets/2bd5ab8f-7d50-475a-82a7-99d5f39aa6da)  
**解决方案，在inheritstack.cc、templatestack.cc和stack.cc中加入using namespace std;**  
建议：有一个warning，可以将copyright.h中25行的char* 前加上const来解决  
**执行gdb stack**，得到报错：  
![image](https://github.com/user-attachments/assets/47057a24-6c5f-4bb0-baaa-be1cc227181e)  
**解决方案：执行sudo apt install gdb**
# gdb记录
l/list ——展示10行代码  
b/break 129 ——在129行打一个断点  
b/break func ——在名为func的函数上打一个断点(进入函数即遇到断点)  
d ——删除所有断点
r/run ——持续运行直到遇到断点或结束  
n/next ——逐语句跟踪程序  
s/step ——逐条汇编指令进行  
p/print/d/display ——输出程序中变量的值  
info reg ——输出当前所有寄存器内容
其余gdb命令随用随查
# p41页回答问题
**注意注意：虽然这些问题是在2.6中给出，但是2.7给出了这些答案的解决方法，很详细，推荐你去看懂并执行**  
我通过跟着指南操作得到了以下地址，并没有遇到什么需要补充的问题(不过看懂指南确实花了我不少力气)  
经过我反复实践，发现这些问题得到的地址不会改变  
不过我得到的地址与指南不同，推测可能是所用虚拟机不同等原因  
(1)三种方法：  
①info address func可以找到函数func()的地址  
②disassemble func可以通过反汇编查看代码并看到func()地址  
③b func可以在函数打断点，系统会提示断点地址(即函数地址)    
Ⅰ.InterruptEnable()的地址为0x3021  
Ⅱ. SimpleThread()的地址为0x326f  
Ⅲ.ThreadFinish()的地址为0x2ff6  
Ⅳ.ThreadRoot()的地址为0x4e72  
(2)  
简述指南：分别找到主线程和其他线程被创建的地方，打断点从相关变量的值中获取  
Ⅰ.the main thread of the Nachos：地址为0x56563ca0  
Ⅱ.the forked thread created by the main thread：的地址为0x56563d00  
(3)  
Ⅰ.当主线程第一次运行 SWITCHO)函数，CPU返回的地址是0x56559e72  
Ⅱ.该地址对应程序的ThreadRoot ()  
第一次调用SWITCH()，是从主线程(main)切换到新建的子线程（forked thread），  
因此第一次调用SWITCH，其返回值是新建子线程（forked thread）的入口ThreadRoot()，  
即切换到ThreadRoot()开始执行新建的子线程。  
(4)  
Ⅰ.当调用Fork0新建的线程首次运行SWITCHO函数时，CPU返回的地址是0x56556a20  
Ⅱ.该地址对应程序的Scheduler::Run()  
子线程开始执行后，后续子线程与主线程main 发生的上下文切换都是从上次被  
中断的地方开始执行，即Scheduler::Run()中语句SWITCH(oldThread, nextThread)之后，  
因此断点地址都是相同的，即后续SWITCH的返回值都是相同的。  
# 问题6
1、doc文件夹是空的，没有文件，我push后发现库里没有，暂时不管他了(毕竟也没文件)，
2、我在完成实验一后，将OS文件夹复制到库里，发现有16个文件无法复制，明明是空文件夹，但是系统提示我这16个文件重名  
当我点击覆盖，会卡死，经过检查发现，这16个文件均是执行make后得到的，所以不上传了，下载后自行make就好
