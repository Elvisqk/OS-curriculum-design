/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"
static int a[40];//新增代码，分配更大的地址空间
#define TEST_FILE "testfile"    // 测试文件名
#define TEST_CONTENT "Hello Nachos File System!"  // 测试文件内容
#define BUF_SIZE 256           // 缓冲区大小
// //-------------------------------------
// // 测试函数2：进程控制（Exec/Join/Exit）
// //-------------------------------------
// void ChildProcess() {
//     Write("Child Process Running\n", 22, ConsoleOutput);
//     Exit(0);  // 子进程正常退出
// }

// void TestProcessControl() {
//     SpaceId pid;
//     int exitStatus;

//     // 启动子进程
//     pid = Exec("test1");  // 假设test1是另一个测试程序
//     exitStatus = Join(pid);

//     // 验证退出码
//     if (exitStatus == 0) {
//         Write("Process Test PASS: Child exited normally\n", 40, ConsoleOutput);
//     } else {
//         Write("Process Test FAIL: Unexpected exit code\n", 39, ConsoleOutput);
//     }
// }
int
main()
{
    /*注释代码 原main函数内容
    char prompt[2];
    prompt[0] = '-';
    prompt[1] = '-';

    Write(prompt, 1, "I will shut down!\n");
    Halt();*/
    //新增代码6行 新main函数内容
    //TestProcessControl();// 进程控制测试
    Halt();
    /* not reached */
}
