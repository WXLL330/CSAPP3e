#include <stdio.h>
#include <limits.h>

int main()
{
    // gcc -g -Wa,-adlhn test.c > mytest.s 查看汇编文件
    // 可以看到编译器优化掉了 & 操作，只用了 cmpl 和 setle 指令
    // 即对表达式 !(-x&INT_MIN), 编译器只判断了x是否小于等于0，若是，则整体表达式值为1，这对 -2147483648 < x < 0 都成立
    // 所以当面对 x=INT_MIN 时，编译器不关心 -x 是否会溢出，而是直接套用上面的判断方法，最终导致值为1
    // 而当我直接使用 !(-INT_MIN&INT_MIN) 时，编译器并没有采用上面的方法，而是用 movl 指令直接将 0 放入结果中
    // 其实从 warning 也可以看出，编译时只有 test2 发出警告，提醒 -INT_MIN会溢出，而 -my_int_min 没有提示，说明编译器根本不管这个值是否会溢出
    int my_int_min = INT_MIN, t= 0x9;
    int test1 = !(-my_int_min&INT_MIN);
    int test2 = !(-INT_MIN&INT_MIN);
    int test3 = !(-t&INT_MIN);
    // printf("INT_MIN=%d\t my_int_min=%d\t -INT_MIN=%d\t -my_int_min=%d\n", INT_MIN, my_int_min, -INT_MIN, -my_int_min);
    // printf("!(-INT_MIN&INT_MIN)=%d\t !(-my_int_min&INT_MIN)=%d\n", !(-INT_MIN&INT_MIN), !(-my_int_min&INT_MIN));
    // printf("!(-INT_MIN&my_int_min)=%d\t !(-my_int_min&my_int_min)=%d\n", !(-INT_MIN&my_int_min), !(-my_int_min&my_int_min));
    // printf("(-my_int_min&INT_MIN)=%d\t !(-my_int_min&INT_MIN)=%d\n", (-my_int_min&INT_MIN), !(-my_int_min&INT_MIN));

    return 0;
}