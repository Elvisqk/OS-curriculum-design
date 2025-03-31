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
    int i,j,k;
    k=3;
    i=2;
    j=i-1;
    k=i-j+k;
    Halt();
    /* not reached */
}
