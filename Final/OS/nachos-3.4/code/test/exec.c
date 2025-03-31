// 此文件为新建文件，全部为新建代码
#include "syscall.h"
int  main() 
{
    SpaceId pid; 
    pid=Exec("../test/halt.noff");//利用实现的Exec()执行../test/halt.noff
    Halt(); 
    /* not reached */ 
} 