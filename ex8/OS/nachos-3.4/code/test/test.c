/*
 * Nachos系统调用测试程序
 * 测试功能：Halt, Exit, Exec, Join, Create, Open, Read, Write, Close, Yield
 */

#include "syscall.h"
#define TEST_FILE "testfile"    // 测试文件名
#define TEST_CONTENT "Hello Nachos File System!\n"  // 测试文件内容
#define BUF_SIZE 256           // 缓冲区大小
static int a[40];//新增代码，分配更大的地址空间
//-------------------------------------
// 测试函数1：文件操作（Create/Open/Write/Read/Close）
//-------------------------------------
void TestFileOps() {
    char buffer[BUF_SIZE];
    OpenFileId fd;
    int bytesRead;

    // 1. 创建并写入文件
    Create(TEST_FILE);                    // 创建文件
    fd = Open(TEST_FILE);                 // 打开文件
    Write(TEST_CONTENT, sizeof(TEST_CONTENT)-1, fd); // 写入内容
    Close(fd);                            // 关闭文件

    // 2. 重新打开并验证内容
    fd = Open(TEST_FILE);
    bytesRead = Read(buffer, sizeof(TEST_CONTENT)-1, fd);
    Close(fd);
}
 
//-------------------------------------
// 测试函数2：进程控制（Exec/Join/Exit）
//-------------------------------------
void ChildProcess() {
    //Write("Child Process Running\n", 22, ConsoleOutput);
    Exit(0);  // 子进程正常退出
}

void TestProcessControl() {
    SpaceId pid;
    int exitStatus;

    // 启动子进程
    pid = Exec("../test/exit.noff");  // 假设test1是另一个测试程序
    exitStatus = Join(pid);

}

//-------------------------------------
// 测试函数3：Fork/Yield协作
//-------------------------------------
void ForkedFunction() {
    int i;
    for (i = 0; i < 3; i++) {
        //Write("Forked Thread Yield\n", 20, ConsoleOutput);
        Yield();  // 主动让出CPU
    }
    Exit(0);
}
 
void TestForkYield() {
    int i; 
    //Fork(ForkedFunction);
    for (i = 0; i < 3; i++) {
        //Write("Main Thread Yield\n", 18, ConsoleOutput);
        Yield();
    }
}
 //-------------------------------------
 // 主测试程序
 //-------------------------------------
int main() {
    // 执行所有测试
    TestFileOps();       // 文件操作测试
    TestProcessControl();// 进程控制测试
    //TestForkYield();     // Fork/Yield测试
    // 最终停机
    Halt();
}