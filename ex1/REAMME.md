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
(b) cd /usr/local 
/usr/local是隐藏文件夹，直接找是找不到的，可以通过命令行寻找  
![image](https://github.com/user-attachments/assets/a2795046-cf3d-4610-a105-f24b3fc770ce)
(c) copy file “gcc-2.8.1-mips.tar.gz” to file fold “/usr/local” with cp command. 
这句话不是命令，
**先把gcc-2.8.1-mips.tar.gz复制到OS文件夹下，在终端进入OS文件夹**
**执行命令cp gcc-2.8.1-mips.tar.gz /usr/local**
# 问题5
su命令执行失败：Authentication failure  
找了半天密码，发现我压根没有设置root用户，解决办法：  
**执行sudo passwd root**
设置密码
然后你就可以用su命令了
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
