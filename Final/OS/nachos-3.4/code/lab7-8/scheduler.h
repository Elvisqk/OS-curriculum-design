// scheduler.h 
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"

#include"syscall.h" // 新增代码 包含SpaceId变量(其实就是int)

// The following class defines the scheduler/dispatcher abstraction -- 
// the data structures and operations needed to keep track of which 
// thread is running, and which threads are ready but not running.

class Scheduler {
  public:
    Scheduler();			// Initialize list of ready threads 
    ~Scheduler();			// De-allocate ready list

    void ReadyToRun(Thread* thread);	// Thread can be dispatched.
    Thread* FindNextToRun();		// Dequeue first thread on the ready 
					// list, if any, and return thread.
    void Run(Thread* nextThread);	// Cause nextThread to start running
    void Print();			// Print contents of ready list
    
    List* getWaitingList();    // 新增代码 返回等待进程队列
    List* getReadyList();      // 新增代码 返回就绪进程队列
    List* getTerminatedList(); // 新增代码 返回终止进程队列
    void deleteTerminatedThread(SpaceId spaceID);     // 新增代码 删除停止运行的进程
    void emptyList(List *list);                       // 新增代码 清空进程队列

  private:
    List *readyList;  		// queue of threads that are ready to run,
				// but not running
    List *waitingList;      // 新增代码 等待队列
    List *terminatedList;   // 新增代码 终止队列
};

#endif // SCHEDULER_H
