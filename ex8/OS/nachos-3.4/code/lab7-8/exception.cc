// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "openfile.h"
#include "progtest.h"


void  AdvancePC() { 
    machine->WriteRegister(PCReg, machine->ReadRegister(PCReg) + 4); 
    machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg) + 4); 
} 


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------
// 在此处完成系统调用，$4-$7（4到7号寄存器）传递函数的前四个参数给子程序，参数多于4个时，其余的利用堆栈进行传递
void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if ((which == SyscallException)) {
        switch(type){
            case SC_Halt:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of Halt() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                DEBUG('a', "Shutdown, initiated by user program.\n");
   	            interrupt->Halt();
                break;
            }
            case SC_Exec:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of Exec() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                char filename[50]; 
                int addr = machine->ReadRegister(4);
                int i = 0;
                do{
                    machine->ReadMem(addr+i,1,(int*)&filename[i]);
                }while(filename[i++]!='\0');//读出文件名
                OpenFile *executable = fileSystem->Open(filename);//打开可执行文件
                if(executable == NULL){
                    printf("Unable to open file %s\n",filename);
                    return;
                }
                AddrSpace* space = new AddrSpace(executable);//创建地址空间
                space->Print();
                delete executable;//关闭文件
                char* forkedThreadName = filename;
                Thread* thread = new Thread(forkedThreadName);//创建线程
                thread->Fork(StartProcess,space->GetSpaceId());//开始执行线程
                thread->space = space;
                thread->UserProgramId=space->GetSpaceId();
                machine->WriteRegister(2,space->GetSpaceId());//返回子进程的ID
                AdvancePC();
                break;
            }
            case SC_Join:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of Join() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int SpaceID=machine->ReadRegister(4);//读取子进程的ID
                currentThread->Join(SpaceID);//等待子进程结束
                machine->WriteRegister(2,currentThread->waitProcessExitCode);//返回子进程的返回值
                AdvancePC();
                break;
            }
            case SC_Exit:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of Exit() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int ExitStatus = machine->ReadRegister(4); // 读取返回值
                currentThread->setExitCode(ExitStatus); // 设置返回值
                if(ExitStatus == 99){
                    List *terminatedList=scheduler->getTerminatedList();
                    scheduler->emptyList(terminatedList);
                }
                delete currentThread->space; // 删除地址空间
                currentThread->Finish();
                AdvancePC();
                break;
            }
            case SC_Yield:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of Yield() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                currentThread->Yield();
                AdvancePC();
                break;
            }
            case SC_Create:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of FILESYS_STUB_SC_Create() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int base = machine->ReadRegister(4);
                int value;
                int count = 0;
                char *FileName = new char[128];
                do{
                    machine->ReadMem(base + count, 1 ,&value);
                    FileName[count] = (char)value;
                    count++;
                }while((char)value != '\0' && count < 128);
                int fileDescriptor = OpenForWrite(FileName);
                if(fileDescriptor == -1){
                    printf("create file %s failed!\n",FileName);
                }
                else{
                    printf("create file %s succeed!,the file id is %d\n", FileName, fileDescriptor);
                }
                Close(fileDescriptor);
                AdvancePC();
                break;
            }
            case SC_Open:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of FILESYS_STUB_SC_Open() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int base = machine->ReadRegister(4);
                int value;
                int count = 0;
                char *FileName = new char[128];
                do{
                    machine->ReadMem(base + count, 1, &value);
                    FileName[count] = (char)value;
                    count++;
                }while(count < 128 && (char)value != '\0');
                int fileDescriptor = OpenForReadWrite(FileName,FALSE);
                if(fileDescriptor==-1){
                    printf("Open file %s failed!\n",FileName);
                }
                else{
                    printf("Open file %s succeed!, the file id is %d\n",FileName,fileDescriptor); 
                }
                machine->WriteRegister(2,fileDescriptor);
                AdvancePC();
                break;
            }
            case SC_Write:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of FILESYS_STUB_SC_Write() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int base = machine->ReadRegister(4);    // buffer
                int size = machine->ReadRegister(5);    // bytes written to file
                int fileId = machine->ReadRegister(6);  // fd
                int value;
                int count = 0;
                OpenFile *openfile = new OpenFile(fileId);
                ASSERT(openfile != NULL);
                char *buffer = new char[128];
                do{
                    machine->ReadMem(base + count, 1, &value);
                    buffer[count] = (char)value;
                    count++;
                }while((char)value != '\0' && count < size);
                buffer[size] = '\0';
                int WritePostion;
                if (fileId == 1){
                    WritePostion = 0;
                }
                else{
                    WritePostion = openfile->Length();
                }
                int writtenBytes = openfile->WriteAt(buffer,size,WritePostion);
                if(writtenBytes == 0){
                    printf("write file failed!\n");
                }
                else{
                    printf("\"%s\" has wrote in file %d succeed!\n",buffer,fileId);
                }
                AdvancePC();
                break;
            }
            case SC_Read:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of FILESYS_STUB_SC_Read() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int base = machine->ReadRegister(4);
                int size = machine->ReadRegister(5);
                int fileId = machine->ReadRegister(6);
                OpenFile *openfile = new OpenFile(fileId);
                char buffer[size];
                int readnum = 0;
                readnum = openfile->Read(buffer,size);
                for(int i = 0;i < size; i++){
                    if(!machine->WriteMem(base,1,buffer[i])) 
                        printf("This is something wrong.\n"); 
                }
                buffer[size]='\0';
                printf("read succeed!The content is \"%s\",the length is %d\n",buffer,size);
                machine->WriteRegister(2,readnum);
                AdvancePC();
                break;
            }
            case SC_Close:{
                printf("CurrentThreadId: %d Name: %s, Execute system call of FILESYS_STUB_SC_Close() \n",(currentThread->space)->GetSpaceId(),currentThread->getName());
                int fileId = machine->ReadRegister(4);
                Close(fileId);
                printf("File %d closed succeed!\n", fileId);
                AdvancePC();
                break;
            }
            default:{
                printf("Unexpected user mode exception %d %d\n", which, type);
                ASSERT(FALSE);
                break;
            }
        }
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}
