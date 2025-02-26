	.file	1 "exec.c"
gcc2_compiled.:
__gnu_compiled_c:
	.rdata
	.align	2
$LC0:
	.ascii	"../test/halt.noff\000"	//用户地址空间
	.text
	.align	2			//2字节对齐，即2*2
	.globl	main		//全局变量
	.ent	main		//main函数入口
main:
#汇编伪指令  frame 用来声明堆栈布局。 
#它有三个参数： 
# 1）第一个参数 framereg：声明用于访问局部堆栈的寄存器，一般为 $sp。 
# 2）第二个参数 framesize：申明该函数已分配堆栈的大小，应该符合 $sp ＋ framesize ＝ 原来的 $sp。 
# 3）第三个参数 returnreg：这个寄存器用来保存返回地址。 
#.frame：$fp为栈指针，该函数层栈大小为32字节，函数返回地址存放在$31
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, extra= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
#栈采用向下生长的方式，即由大地址向小地址生长，栈指针指向栈的最小地址
	subu	$sp,$sp,32 # $sp - 32->$sp
#构造main()的栈frame，$sp的原值应该是执行main()之前的栈顶
#上一函数对应栈frmae的顶（最小地址处）
	sw	$31,28($sp)		#$31->memory[$sp+28]  ; 函数返回地址
	sw	$fp,24($sp)		#$fp ->memory[$sp+24]  ;保存fp
	move	$fp,$sp		#$sp->$fp，执行Exec()会修改$sp
	jal	__main			#PC+4->$31, goto __main
	la	$4,$LC0			#$LC0->$4 ,将Exec("../test/halt.noff\000")的参数的地址传给$4
	jal	Exec			#转到start.s 中的Exec 处执行
	sw	$2,16($fp)
	jal	Halt
$L1:
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addu	$sp,$sp,32
	j	$31
	.end	main
