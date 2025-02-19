打开P27(如无特殊说明，该项目中的Pxx均指"OS课程设计指南"的对应页数)  
> 打开Linux终端
> 输入“dpkg --print-architecture”  
> 输入“dpkg --print-foreign-architectures”，发现未输出任何东西，判断为系统多架构功未打开  
> 根据提示输入“sudo dpkg --add-architecture i386”  
> 再次输入“dpkg --print-foreign-architectures”检查，发现输出i386，判断为系统多架构功能已经打开  
> 输入“sudo apt-get install gcc”  
> 输入“sudo apt-get install g++”  
> 输入“sudo apt-get install build-essential g++-multilib gcc-multilib”，遇到报错信息![image](https://github.com/user-attachments/assets/0a4a671e-fa70-4389-a13c-2bd2f98d839f)  
> 我讲报错信息丢给chatGPT，得到了如下反馈![image](https://github.com/user-attachments/assets/253eb207-c32c-4d3b-bd86-6bc24cb8f8e8)此时我打开了VPN，输入sudo apt update，成功执行完毕
> 
