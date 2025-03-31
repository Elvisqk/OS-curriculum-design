// main.cc 
//	Bootstrap code to initialize the operating system kernel.
//
//	Allows direct calls into internal operating system functions,
//	to simplify debugging and testing.  In practice, the
//	bootstrap code would just initialize data structures,
//	and start a user program to print the login prompt.
//
// 	Most of this file is not needed until later assignments.
//
// 可用的参数列表
// Usage: nachos -d <debugflags> -rs <random seed #>
//		-s -x <nachos file> -c <consoleIn> <consoleOut>
//		-f -cp <unix file> <nachos file>
//		-p <nachos file> 
//      -r <nachos file>
//		-l
//		-D
//		-t
//      -n <network reliability> -e <network orderability>
//      -m <machine id>
//      -o <other machine id>
//      -z
//
//    -d causes certain debugging messages to be printed (cf. utility.h)
//    -rs causes Yield to occur at random (but repeatable) spots
//    -z prints the copyright message
//
//  USER_PROGRAM
//    -s causes user programs to be executed in single-step mode
//    -x runs a user program
//    -c tests the console
//
//  FILESYS
//    -f causes the physical disk to be formatted
//    -cp copies a file from UNIX to Nachos
//    -p prints a Nachos file to stdout
//    -r removes a Nachos file from the file system
//    -l lists the contents of the Nachos directory
//    -D prints the contents of the entire file system 
//    -t tests the performance of the Nachos file system
//
//  NETWORK
//    -n sets the network reliability
//    -e sets the network orderability
//    -m sets this machine's host id (needed for the network)
//    -o runs a simple test of the Nachos network software
//
//  NOTE -- flags are ignored until the relevant assignment.
//  Some of the flags are interpreted here; some in system.cc.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#define MAIN
#include "copyright.h"
#undef MAIN

#include "utility.h"
#include "system.h"


// External functions used by this file

extern void ThreadTest(void), Copy(char *unixFile, char *nachosFile);
extern void Print(char *file), PerformanceTest(void);
extern void StartProcess(char *file), ConsoleTest(char *in, char *out);
extern void MailTest(int networkID);
extern void SynchTest(void);

//----------------------------------------------------------------------
// main
// 	Bootstrap the operating system kernel.  
//	
//	Check command line arguments
//	Initialize data structures
//	(optionally) Call test procedure
//
//	"argc" is the number of command line arguments (including the name
//		of the command) -- ex: "nachos -d +" -> argc = 3 
//	"argv" is an array of strings, one for each command line argument
//		ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}
//----------------------------------------------------------------------

int
main(int argc, char **argv)
{
    int argCount;			// the number of arguments 
					// for a particular command

    DEBUG('t', "Entering main");
    (void) Initialize(argc, argv);// 参见（../threads/system.cc）
	/*
	1、处理Nachos内核所使用的一些命令行参数；
	2、根据需要创建了Nachos相应的硬件设备，如中断控制器，定时器、CPU、硬盘；
	3、然后基于这些设备初始化了一个Nachos的内核；
		初始化了一个线程调度程序；
		在 Nachos 模拟的硬盘上创建了一个文件系统；
		创建了Nachos 的主线程（Nachos的第一个线程）；
		网络通信使用的邮箱等；
	4、讨论：main线程创建后，后续的的线程是如何创建的？
		答：直觉猜测：后续线程均有main线程操作
	*/
    
#ifdef THREADS
    ThreadTest();// （参见../threads/thresdtest.cc）
	// 主线程执行SimpleThread(0)，子线程执行 SimpleThread(1)，
	// 由于 SimpleThread()调用了Thread::Yield()，因此两个线程会交替执行；
	// 主线程作为线程0，线程1
	// 创建一个分支线程1，两个线程交替执行五遍循环
	// 虽然这部分是暗的，但是实际上发现这个函数执行了，目前不清楚哪里define了THERADS，待更新
#if 0
    SynchTest();
	// SynchTest()测试Nachos的locks及condition variables实现的线程之间进行互斥与同步功能
	// 将0改为1，这个函数可以执行，不改不执行
#endif 
#endif

    for (argc--, argv++; argc > 0; argc -= argCount, argv += argCount) {
	argCount = 1;
        if (!strcmp(*argv, "-z"))               // print copyright
            printf (copyright);
#ifdef USER_PROGRAM
        if (!strcmp(*argv, "-x")) {        	// run a user program
	    ASSERT(argc > 1);
            StartProcess(*(argv + 1));
            argCount = 2;
        } else if (!strcmp(*argv, "-c")) {      // test the console
	    if (argc == 1)
	        ConsoleTest(NULL, NULL);
	    else {
		ASSERT(argc > 2);
	        ConsoleTest(*(argv + 1), *(argv + 2));
	        argCount = 3;
	    }
	    interrupt->Halt();		// once we start the console, then 
					// Nachos will loop forever waiting 
					// for console input
	}
#endif // USER_PROGRAM
#ifdef FILESYS
	if (!strcmp(*argv, "-cp")) { 		// copy from UNIX to Nachos
	    ASSERT(argc > 2);
	    Copy(*(argv + 1), *(argv + 2));
	    argCount = 3;
	} else if (!strcmp(*argv, "-p")) {	// print a Nachos file
	    ASSERT(argc > 1);
	    Print(*(argv + 1));
	    argCount = 2;
	} else if (!strcmp(*argv, "-r")) {	// remove Nachos file
	    ASSERT(argc > 1);
	    fileSystem->Remove(*(argv + 1));
	    argCount = 2;
	} else if (!strcmp(*argv, "-l")) {	// list Nachos directory
            fileSystem->List();
	} else if (!strcmp(*argv, "-D")) {	// print entire filesystem
            fileSystem->Print();
	} else if (!strcmp(*argv, "-t")) {	// performance test
            PerformanceTest();
	}
#endif // FILESYS
#ifdef NETWORK
        if (!strcmp(*argv, "-o")) {
	    ASSERT(argc > 1);
            Delay(2); 				// delay for 2 seconds
						// to give the user time to 
						// start up another nachos
            MailTest(atoi(*(argv + 1)));
            argCount = 2;
        }
#endif // NETWORK
    }

    currentThread->Finish();	// （参见../threads/thread.cc）
	// 终止主线程
	/*
	我们注意到，Thread::Finish()调用了 Thread::Sleep()，引起线程调度，如果此时就绪队列中尚有就绪
	进程，则调度执行之；
	当该就绪线程执行结束后，也会自动执行Thread::Finish()，致使所有的就绪线程都会被依次调度执行；
	注：每一个线程的所有子线程结束后，该线程才会结束，这是一个递归过程
	*/
	/*
	如果主线程执行Thread::Finish()时就绪队列为空，或者最后一个就绪线程执行结
	束后终止，都会调用Thread::Sleep()，进而循环调用Interrupt:Idle()，当所有的中断请
	求都被处理完后，依然没有就绪线程等待调度，则Interrupt:Idle()调用Interrupt:Halt()
	关闭退出Nachos。
	*/
	/*
	Interrupt:Halt()调用 Cleanup()，将启动时创建的设备（中断控制器、定时器、硬
	盘、CPU），及文件系统、调度程序等一并删除后退出，至此Nachos运行结束。（参
	见../threads/system.cc）
	注：目前来推断，Halt()函数应该无需改动，这里理解就好，如果后续需要改动，该"注"会被删除
	*/
				// NOTE: if the procedure "main" 
				// returns, then the program "nachos"
				// will exit (as any other normal program
				// would).  But there may be other
				// threads on the ready list.  We switch
				// to those threads by saying that the
				// "main" thread is finished, preventing
				// it from returning.
    return(0);			// Not reached...
}
