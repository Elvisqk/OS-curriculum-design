// prodcons++.cc
//	C++ version of producer and consumer problem using a ring buffer.
//
//	Create N_PROD producer threads and N_CONS consumer thread. 
//	Producer and consumer threads are communicating via a shared
//      ring buffer object. The operations on the shared ring buffer
//      are synchronized with semaphores.
//	
//      
// Copyright (c) 1995 The Regents of the University of Southern Queensland.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include <fcntl.h>  // 新增代码 为了包含create()
#include <iostream> // 新增代码 为了包含exit()
#include <unistd.h> // 新增代码 为了包含write()

#include <stdio.h>
#include "copyright.h"
#include "system.h"

#include "synch.h"
#include "ring.h"

enum Scheduling_algorithm{FCFS,RR};//新增代码 枚举调度算法
#define SA RR //新增代码 选择调度算法SA，第二个参数是哪个调度算法，就执行对应的调度算法
#define RR_P 2//新增代码 生产者线程每生产RR_P个message，就让出CPU
#define RR_C 2//新增代码 消费者线程每消费RR_C个message，就让出CPU


#define BUFF_SIZE 20  // the size of the round buffer
#define N_PROD    2  // the number of producers 
#define N_CONS    2  // the number of consumers
#define N_MESSG   5  // the number of messages produced by each producer
#define MAX_NAME  16 // the maximum lengh of a name

#define MAXLEN	48 
#define LINELEN	24


Thread *producers[N_PROD]; //array of pointers to the producer
Thread *consumers[N_CONS];  // and consumer threads;

char prod_names[N_PROD][MAX_NAME];  //array of charater string for prod names
char cons_names[N_CONS][MAX_NAME];  //array of charater string for cons names

Semaphore *nempty, *nfull; //two semaphores for empty and full slots
Semaphore *mutex;          //semaphore for the mutual exclusion
    
Ring *ring;



//----------------------------------------------------------------------
// Producer
// 	Loop N_MESSG times and produce a message and put it in the 
//      shared ring buffer each time.
//	"which" is simply a number identifying the producer thread.
//      
//----------------------------------------------------------------------

void
Producer(_int which)
{
    int num;
    slot *message = new slot(0,0);

//  This loop is to generate N_MESSG messages to put into to ring buffer
//   by calling  ring->Put(message). Each message carries a message id 
//   which is represened by integer "num". This message id should be put 
//   into "value" field of the slot. It should also carry the id 
//   of the producer thread to be stored in "thread_id" field so that 
//   consumer threads can know which producer generates the message later
//   on. You need to put synchronization code
//   before and after the call ring->Put(message). See the algorithms in
//   page 182 of the textbook.

    for (num = 0; num < N_MESSG ; num++) {
      // Put the code to prepare the message here.
      message->value = num; // 新增代码
      message-> thread_id = which; // 新增代码

      // Put the code for synchronization before  ring->Put(message) here.
      nempty->P();  //同步在前 // 新增代码
      mutex->P();   //互斥在后 // 新增代码

      ring->Put(message);

      // Put the code for synchronization after  ring->Put(message) here.
      mutex ->V(); // 新增代码
      nfull ->V(); // 新增代码

      if(SA == RR && (num+1)%RR_P==0){currentThread->Yield();}// 新增代码
    }
}

//----------------------------------------------------------------------
// Consumer
// 	endless loop to fetch messages from the ring buffer and 
//      record these message in the corresponding file.
//      
//----------------------------------------------------------------------

void
Consumer(_int which)
{
    char str[MAXLEN];
    char fname[LINELEN];
    int fd;
    
    slot *message = new slot(0,0);

    // to form a output file name for this consumer thread.
    // all the messages received by this consumer will be recorded in 
    // this file.
    sprintf(fname, "tmp_%d", which);

    // create a file. Note that this is a UNIX system call.
    if ( (fd = creat(fname, 0600) ) == -1) 
    {
      perror("creat: file create failed");
      exit(1);
    }
    
    for (int num=0;;num++) {//修改代码 原为for(;;) {

      // Put the code for synchronization before ring->Get(message) here.
      nfull->P();  //同步在前 //新增代码
      mutex->P();   //互斥在后 //新增代码

      ring->Get(message);

      // Put the code for synchronization after ring->Get(message) here.
      mutex ->V(); //新增代码
      nempty ->V(); //新增代码


      // form a string to record the message
      sprintf(str,"producer id --> %d; Message number --> %d;\n", 
		message->thread_id,
		message->value);
      // write this string into the output file of this consumer. 
      // note that this is another UNIX system call.
      if ( write(fd, str, strlen(str)) == -1 ) {
	    perror("write: write failed");
	    exit(1);
	  }
    if(SA == RR && (num+1)%RR_C==0){currentThread->Yield();}// 新增代码
    }
}



//----------------------------------------------------------------------
// ProdCons
// 	Set up semaphores for shared round buffer and 
//	create and fork producers and consumer threads
//----------------------------------------------------------------------

void
ProdCons()
{
    int i;
    DEBUG('t', "Entering ProdCons");

    // Put the code to construct all the semaphores here.
    mutex = new Semaphore("mutex", 1);// 新增代码
    nfull = new Semaphore("nfull", 0);// 新增代码
    nempty = new Semaphore("nempty", BUFF_SIZE);// 新增代码


    // Put the code to construct a ring buffer object with size 
    //BUFF_SIZE here.
    ring = new Ring(BUFF_SIZE);// 新增代码


    // create and fork N_PROD of producer threads 
    for (i=0; i < N_PROD; i++) 
    {
      // this statemet is to form a string to be used as the name for 
      // produder i. 
      sprintf(prod_names[i], "producer_%d", i);

      // Put the code to create and fork a new producer thread using
      //     the name in prod_names[i] and 
      //     integer i as the argument of function "Producer"
      producers[i] = new Thread(prod_names[i]);// 新增代码
      producers[i]->Fork(Producer, i);// 新增代码
    };

    // create and fork N_CONS of consumer threads 
    for (i=0; i < N_CONS; i++) 
    {
      // this statemet is to form a string to be used as the name for 
      // consumer i. 
      sprintf(cons_names[i], "consumer_%d", i);
      // Put the code to create and fork a new consumer thread using
      //     the name in cons_names[i] and 
      //     integer i as the argument of function "Consumer"
      consumers[i] = new Thread(cons_names[i]);// 新增代码
      consumers[i]->Fork(Consumer, i);// 新增代码

    };
}

