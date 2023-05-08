   1              		.file	"test.c"
   2              		.text
   3              	.Ltext0:
   4              		.globl	main
   6              	main:
   7              	.LFB0:
   8              		.file 1 "test.c"
   1:test.c        **** #include <stdio.h>
   2:test.c        **** #include <limits.h>
   3:test.c        **** 
   4:test.c        **** int main()
   5:test.c        **** {
   9              		.loc 1 5 1
  10              		.cfi_startproc
  11 0000 F30F1EFA 		endbr64
  12 0004 55       		pushq	%rbp
  13              		.cfi_def_cfa_offset 16
  14              		.cfi_offset 6, -16
  15 0005 4889E5   		movq	%rsp, %rbp
  16              		.cfi_def_cfa_register 6
   6:test.c        ****     // gcc -g -Wa,-adlhn test.c > mytest.s 查看汇编文件
   7:test.c        ****     // 可以看到编译器优化掉了 & 操作，只用了 cmpl 和 setle 指令
   8:test.c        ****     // 即对表达式 !(-x&INT_MIN), 编译器只判断了x是否小于等于0，若是，则整�
   9:test.c        ****     // 所以当面对 x=INT_MIN 时，编译器不关心 -x 是否会溢出，而是直接套用�
  10:test.c        ****     // 而当我直接使用 !(-INT_MIN&INT_MIN) 时，编译器并没有采用上面的方法，�
  11:test.c        ****     // 其实从 warning 也可以看出，编译时只有 test2 发出警告，提醒 -INT_MIN会�
  12:test.c        ****     int my_int_min = INT_MIN, t= 0x9;
  17              		.loc 1 12 9
  18 0008 C745EC00 		movl	$-2147483648, -20(%rbp)
  18      000080
  19              		.loc 1 12 31
  20 000f C745F009 		movl	$9, -16(%rbp)
  20      000000
  13:test.c        ****     int test1 = !(-my_int_min&INT_MIN);
  21              		.loc 1 13 17
  22 0016 837DEC00 		cmpl	$0, -20(%rbp)
  23 001a 0F9EC0   		setle	%al
  24              		.loc 1 13 9
  25 001d 0FB6C0   		movzbl	%al, %eax
  26 0020 8945F4   		movl	%eax, -12(%rbp)
  14:test.c        ****     int test2 = !(-INT_MIN&INT_MIN);
  27              		.loc 1 14 9
  28 0023 C745F800 		movl	$0, -8(%rbp)
  28      000000
  15:test.c        ****     int test3 = !(-t&INT_MIN);
  29              		.loc 1 15 17
  30 002a 837DF000 		cmpl	$0, -16(%rbp)
  31 002e 0F9EC0   		setle	%al
  32              		.loc 1 15 9
  33 0031 0FB6C0   		movzbl	%al, %eax
  34 0034 8945FC   		movl	%eax, -4(%rbp)
  16:test.c        ****     // printf("INT_MIN=%d\t my_int_min=%d\t -INT_MIN=%d\t -my_int_min=%d\n", INT_MIN, my_int_min, -
  17:test.c        ****     // printf("!(-INT_MIN&INT_MIN)=%d\t !(-my_int_min&INT_MIN)=%d\n", !(-INT_MIN&INT_MIN), !(-my_in
  18:test.c        ****     // printf("!(-INT_MIN&my_int_min)=%d\t !(-my_int_min&my_int_min)=%d\n", !(-INT_MIN&my_int_min),
  19:test.c        ****     // printf("(-my_int_min&INT_MIN)=%d\t !(-my_int_min&INT_MIN)=%d\n", (-my_int_min&INT_MIN), !(-m
  20:test.c        **** 
  21:test.c        ****     return 0;
  35              		.loc 1 21 12
  36 0037 B8000000 		movl	$0, %eax
  36      00
  22:test.c        **** }...
  37              		.loc 1 22 1
  38 003c 5D       		popq	%rbp
  39              		.cfi_def_cfa 7, 8
  40 003d C3       		ret
  41              		.cfi_endproc
  42              	.LFE0:
  44              	.Letext0:
  45              		.file 2 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h"
  46              		.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
  47              		.file 4 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h"
  48              		.file 5 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h"
  49              		.file 6 "/usr/include/stdio.h"
  50              		.file 7 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
 859              		.section	.note.gnu.property,"a"
 860              		.align 8
 861 0000 04000000 		.long	 1f - 0f
 862 0004 10000000 		.long	 4f - 1f
 863 0008 05000000 		.long	 5
 864              	0:
 865 000c 474E5500 		.string	 "GNU"
 866              	1:
 867              		.align 8
 868 0010 020000C0 		.long	 0xc0000002
 869 0014 04000000 		.long	 3f - 2f
 870              	2:
 871 0018 03000000 		.long	 0x3
 872              	3:
 873 001c 00000000 		.align 8
 874              	4:
