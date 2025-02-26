# 1 "start.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "start.s"
# 10 "start.s"
# 1 "../userprog/syscall.h" 1
# 16 "../userprog/syscall.h"
# 1 "../threads/copyright.h" 1
# 17 "../userprog/syscall.h" 2
# 11 "start.s" 2

        .text
        .align 2
# 24 "start.s"
 .globl __start
 .ent __start
__start:
 jal main
 move $4,$0
 jal Exit
 .end __start
# 45 "start.s"
 .globl Halt
 .ent Halt
Halt:
 addiu $2,$0,0
 syscall
 j $31
 .end Halt

 .globl Exit
 .ent Exit
Exit:
 addiu $2,$0,1
 syscall
 j $31
 .end Exit

 .globl Exec
 .ent Exec
Exec:
 addiu $2,$0,2 ;2 +$0->$2,其中S0=0, 2:系统调用号，即$2存放系统调用号
 syscall ;执行系统调用
 j $31 ;从系统调用中返回到原程序中继续执行,$31存放的是系统调用的返回地址
 .end Exec

 .globl Join
 .ent Join
Join:
 addiu $2,$0,3
 syscall
 j $31
 .end Join

 .globl Create
 .ent Create
Create:
 addiu $2,$0,4
 syscall
 j $31
 .end Create

 .globl Open
 .ent Open
Open:
 addiu $2,$0,5
 syscall
 j $31
 .end Open

 .globl Read
 .ent Read
Read:
 addiu $2,$0,6
 syscall
 j $31
 .end Read

 .globl Write
 .ent Write
Write:
 addiu $2,$0,7
 syscall
 j $31
 .end Write

 .globl Close
 .ent Close
Close:
 addiu $2,$0,8
 syscall
 j $31
 .end Close

 .globl Fork
 .ent Fork
Fork:
 addiu $2,$0,9
 syscall
 j $31
 .end Fork

 .globl Yield
 .ent Yield
Yield:
 addiu $2,$0,10
 syscall
 j $31
 .end Yield


        .globl __main
        .ent __main
__main:
        j $31
        .end __main
