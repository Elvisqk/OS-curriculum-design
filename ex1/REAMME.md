# 心理活动
emmmm，虽然之前用github下载过很多东西，但是还是第一次使用github写项目，包括分支的创建、删除、合并什么的，  
现在还不是很熟悉，我现在打算每进行一个实验就创建一个分支，虽然目前觉得不是那么有这个必要，但是还是多做些吧，  
如果后续觉得这个操作比较冗余，会再修改我的习惯  
目前是打算，按照操作指南进行，然后把我遇到的问题，都会记录在这里，这个项目链接我应该会继续传下去，  
这样，学弟学妹们如果遇到跟我同样的问题就知道如何解决了

# 按照操作指南执行
注:我在先前课程的实验中，已经安装了WSL 2.3.26，所以我要在WSL中进行全部操作，如果你想完全按照我的操作进行，记得安装WSL 2再回到此处  
注:由于有操作指南，我再重复每一操作的作用就显得冗余(而且很多操作我也不是那么清楚，嘿嘿)，所以这里只记录操作，非必要不进行理由阐述  
打开P27(如无特殊说明，该项目中的Pxx均指"OS课程设计指南"的对应页数)  
> 打开Linux终端
> 输入“dpkg --print-architecture”  
> 输入“dpkg --print-foreign-architectures”，发现未输出任何东西，判断为系统多架构功未打开  
> 根据提示输入“sudo dpkg --add-architecture i386”  
> 再次输入“dpkg --print-foreign-architectures”检查，发现输出i386，判断为系统多架构功能已经打开  
> 输入“sudo apt-get install gcc”  
> 输入“sudo apt-get install g++”
> 输入“sudo apt-get install build-essential g++-multilib gcc-multilib”，遇到报错信息![image](https://github.com/user-attachments/assets/0a4a671e-fa70-4389-a13c-2bd2f98d839f)
