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
![image](https://github.com/user-attachments/assets/0e768e4a-1ff0-4cab-a64f-08e2b0b6d311)

# 问题3
操作位置：2.2-2.2.1-3-(3)  
如果你不知道如何运行make clean，那么记住：在包含Makefile的文件夹下运行，  
所以现在我在code的每一个包含Makefile的子文件夹中执行make clean和make  
在bin底下执行make clean和make成功，那么就可以继续跟着指南走了
发现在lab3和test中执行make会报错，没关系，暂时用不到，lab3会在实验3解决，而test一会指南会解决
# 问题4
/usr/local是隐藏文件夹，可以通过命令行寻找
![image](https://github.com/user-attachments/assets/a2795046-cf3d-4610-a105-f24b3fc770ce)
# 问题5
su命令执行失败：Authentication failure  
找了半天密码，发现我压根没有设置root用户，解决办法：  
**执行sudo passwd root**
设置密码
然后你就可以用su命令了
# 思考：为什么nachos-3.4.tar.gz一定要安装在/usr/local目录中？
我向chatGPT提问：一个项目要求将名为mips的文件夹装在目录/usr/local/下，请根据文件夹的名字和目录名字推断为什么要将这个文件夹放在该目录下
