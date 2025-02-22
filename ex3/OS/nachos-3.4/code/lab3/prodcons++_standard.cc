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
#include <fcntl.h>  // 为了包含create()
#include <iostream> // 为了包含exit()
#include <unistd.h> // 为了包含write()
using namespace std;

#include <stdio.h>
#include "copyright.h"
#include "system.h"

#include "synch.h"
#include "ring.h"

#define BUFF_SIZE 3  // the size of the round buffer 缓冲池的大小
#define N_PROD    3  // the number of producers 生产者的数量
#define N_CONS    2  // the number of consumers 消费者的数量
#define N_MESSG   5  // the number of messages produced by each producer 每个生产者产生的消息数
#define MAX_NAME  16 // the maximum lengh of a name 名字的最大长度

#define MAXLEN	48 // 最大长度
#define LINELEN	24 // 行长度


Thread *producers[N_PROD]; //array of pointers to the producer 生产者指针数组
Thread *consumers[N_CONS];  // and consumer threads; 消费者指针数组

char prod_names[N_PROD][MAX_NAME];  //array of charater string for prod names 生产者们的名字
char cons_names[N_CONS][MAX_NAME];  //array of charater string for cons names 消费者们的名字

Semaphore *nempty, *nfull; //two semaphores for empty and full slots 两个信号量
Semaphore *mutex;          //semaphore for the mutual exclusion 锁
    
Ring *ring; // 环形缓冲区，用来存放生产者的产品



//----------------------------------------------------------------------
// Producer
// 	Loop N_MESSG times and produce a message and put it in the shared ring buffer each time.
// producer循环N_MESSG次，则生产一个message，并将它放入共享池
//	"which" is simply a number identifying the producer thread.
//  “which”只是一个标识生产者线程的数字。
//----------------------------------------------------------------------

void
Producer(_int which)
{
    int num;
    slot *message = new slot(0,0);

  // This loop is to generate N_MESSG messages to put into to ring buffer
  // by calling  ring->Put(message). Each message carries a message id 
  // which is represened by integer "num". This message id should be put 
  // into "value" field of the slot. It should also carry the id 
  // of the producer thread to be stored in "thread_id" field so that 
  // consumer threads can know which producer generates the message later
  // on. You need to put synchronization code
  // before and after the call ring->Put(message). See the algorithms in
  // page 182 of the textbook.
  /*
  1、该循环通过调用ring-> put （message）来生成N_MESSG消息，并将其放入环形缓冲区。
  2、每条消息都带有一个消息id，由整数“num”表示。此消息id应放在槽的“value”字段中。
  3、它还应该携带生产者线程的id，存储在“thread_id”字段中，以便消费者线程可以知道稍后哪个生产者生成消息。
  4、您需要在调用ring-> put （message）之前和之后放置同步代码。请参阅教科书第182页的算法。*/
  
    for (num = 0; num < N_MESSG ; num++) {
      // Put the code to prepare the message here.
      // ...
      message->value = num;
      message-> thread_id = which;
      // Put the code for synchronization before  ring->Put(message) here.
      // ...
      nempty->P();  //同步在前 
      mutex->P();   //互斥在后

      ring->Put(message);

      // Put the code for synchronization after  ring->Put(message) here.
      // ...
      mutex ->V(); 
      nfull ->V(); 

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
    
    for (;;) {

      // Put the code for synchronization before ring->Get(message) here.
      // ...
      nfull->P();  //同步在前 
      mutex->P();   //互斥在后

      ring->Get(message);

      // Put the code for synchronization after ring->Get(message) here.
      // ...
      mutex ->V(); 
      nempty ->V(); 

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
    // ....
    mutex = new Semaphore("mutex",1);
    nfull = new Semaphore("nfull",0);
    nempty = new Semaphore("nempty",BUFF_SIZE);

    // Put the code to construct a ring buffer object with size 
    //BUFF_SIZE here.
    // ...    
    ring = new Ring(BUFF_SIZE);


    // create and fork N_PROD of producer threads 
    for (i=0; i < N_PROD; i++) 
    {
      // this statemet is to form a string to be used as the name for 
      // produder i. 
      sprintf(prod_names[i], "producer_%d", i);

      // Put the code to create and fork a new producer thread using
      //     the name in prod_names[i] and 
      //     integer i as the argument of function "Producer"
      //  ...
      producers[i] = new Thread(prod_names[i]);
      producers[i]->Fork(Producer, i);
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
      //  ...
      consumers[i] = new Thread(cons_names[i]); 
      consumers[i]->Fork(Consumer, i); 

    };
}

