#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

//2.58
/****************************************************************************/
bool is_little_endian(void){
    int val = 0x0011;
    unsigned char *p =(unsigned char *) &val;
    if(*p){
        return 1;
    }
    return false;
}
/****************************************************************************/


//2.60
/****************************************************************************/
unsigned replace_byte(unsigned x, int i, unsigned char b){
    // printf("0x%.8x\n", ~(0xff << (8*i)));
    // printf("0x%.8x\n", (x & ~(0xff << (8*i))));
    // printf("0x%.8x\n", (b << (8*i)));
    return (x & ~(0xff << (i << 3))) | (b << (i << 3));
}
/****************************************************************************/


//2,62
/****************************************************************************/
//判断是否为算数右移
bool int_shifts_are_arithmetic(void){
    int x = ~0;
    return x >> 1 == x;
}
/****************************************************************************/


//2.63
/****************************************************************************/
unsigned srl(unsigned x, int k){
    unsigned xsra = (int) x >> k;

    unsigned mask = (0x1 << k) - 1;
    // printf("0x%.8x\n", mask);
    unsigned w =  sizeof(int) << 3;
    mask = ~(mask << (w - k));
    // printf("0x%.8x\t 0x%.8x\n", xsra, mask);
    return mask & xsra;
}

unsigned sra(int x , int k){
    int xsrl = (unsigned) x >> k;

    unsigned w = sizeof(int) << 3;
    //symbol == 0 -> x为正
    unsigned symbol = (0x1 << (w - k - 1)) & xsrl;
    unsigned mask = ~(symbol - 1);
    // printf("0x%.8x\t 0x%.8x\t 0x%.8x\n", xsrl, symbol, mask);
    return mask | xsrl;
}
/****************************************************************************/


//2.64
/****************************************************************************/
int any_unsigned_odd_one(unsigned x){
    //assum w=32
    unsigned mask = 0xaaaaaaaa;
    return !!(x & mask);
}
/****************************************************************************/


//2.65
/****************************************************************************/
// 将x的高位字节与低位字节异或，对应的位共有三种情况：都为0、都为1、一个为0一个为1
// 都为0可以不用管。
// 都为1，表示高低位的对应位置都为1，则有偶数个1，按题目要求直接为0，也可以不管
// 一个为0一个为1，表示高低位对应位置不全为1，则表示有奇数个1，需要计算奇数个1的个数，若有偶数个奇数1，则返回0，否则返回1
// 只需要再将结果二分，重复上述过程即可
int odd_ones(unsigned x){
    x = x ^ (x >> 16);  
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);

    return x & 1;
}
/****************************************************************************/


//2.66
/******************************************************************************/
int left_most_one(unsigned x){
//  x >> 1,可以将最左边的1移到他自己后面   
//  再和自己做或运算，得到了最左边的两个1
//  之后x每次右移2的n次幂位，就会得到最左边的2^n个1，知道将第一个1后面全变为1
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return ((x + 1) >> 1) | (x & 0x80000000);
    // or (x >> 1) + (x && 1);
    // 若x为0，则后一项也为0，整体为0
    // 若x不为0，则x整体右移一位，再加上1，即得所求
}
/******************************************************************************/


//2.67
/******************************************************************************/
int int_size_is_32(){
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bits(){
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}
/******************************************************************************/


//2.68
/******************************************************************************/
int lower_one_mask(int n){
    // 1 <= n <= w
    int w = sizeof(int) << 3;
    return (unsigned)0xffffffff >> (w - n);
}
/******************************************************************************/


//2.69
/******************************************************************************/
unsigned rotate_left(unsigned x, int n){
    unsigned w = sizeof(unsigned) << 3;
    return (x << n) | (x >> (w - n));
}
/******************************************************************************/


//2.71
/******************************************************************************/
typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum){
    int maxnum = 3;
    return (int)word << ((maxnum - bytenum) << 3) >> (maxnum << 3);
}
/******************************************************************************/


//2.72
/******************************************************************************/
void copy_int(int val, void* buf, int maxbytes) {
  /* compare two signed number, avoid someone set maxbytes a negetive value */
  if (maxbytes >= (int) sizeof(val)) {
    memcpy(buf, (void*)&val, sizeof(val));
  }
}
/******************************************************************************/


//2.73
/******************************************************************************/
int saturating_add(int x, int y){
    int sum = x + y;
    bool pos_over = !(x & INT_MIN) && !(y & INT_MIN) && (sum & INT_MIN);
    bool neg_over = (x & INT_MIN) && (y & INT_MIN) && !(sum & INT_MIN);

    //利用做判断时只要部分满足条件就不会接着往下做的特性
    (pos_over && (sum = INT_MAX)) || (neg_over && (sum = INT_MIN));
    
    return sum;
}
/******************************************************************************/


int main()
{
    int x = 0x89abdcef;
    int y = 0x76543210;

    if(is_little_endian()){
        printf("is little endian\n");  
    }else{
        printf("is big endian\n");
    }
    printf("\n");


    printf("/2.59**********************************************************************/\n");
    printf("0x%.8x\n", (x & 0xff) | (y & ~0xff));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.60**********************************************************************/\n");
    printf("replacd-->0x%.8x\n", replace_byte(0x12345678, 2, 0xab));
    printf("replace-->0x%.8x\n", replace_byte(0x12345678, 0, 0xab));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.61**********************************************************************/\n");
    x = 0xffffffff;
    y = 0xff0000ff;
    // !(~x)
    printf("a: 0x%.8x\t 0x%.8x\n", !(~x), !(~y));

    x = 0x00000000;
    y = 0x00fb42ac;
    // !x
    printf("b: 0x%.8x\t 0x%.8x\n", !x, !y);

    x = 0x123456ff;
    y = 0x12345678;
    // !(~x << ((sizeof(int) - 1) << 3))
    printf("c: 0x%.8x\t 0x%.8x\n", !(~x << ((sizeof(int) - 1) << 3)), !(~y << (sizeof(int) - 1)<< 3));

    x = 0xff123456;
    y = 0x81123456;
    // !(~x >> ((sizeof(int) - 1) << 3))
    printf("d: 0x%.8x\t 0x%.8x\n", !(~x >> ((sizeof(int) - 1) << 3)), !(~y >> ((sizeof(int) - 1) << 3)));

    x = 0x00123456;
    y = 0x19123456;
    printf("0x%.8x\t 0x%.8x\n", !(x >> ((sizeof(int) - 1) << 3)), !(y >> ((sizeof(int) - 1) << 3)));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.62**********************************************************************/\n");
    //若x右移4位得到0xf8000000,则证明为算数右移
    x = 0x80000000, y = 0x70000000;
    printf("0x%.8x >> 4 --> 0x%.8x\n", x, x >> 4);
    printf("0x%.8x >> 4 --> 0x%.8x\n", y, y >> 4);

    if(int_shifts_are_arithmetic()){
        printf("int shifts are arithemtic\n");
    }else{
        printf("int shifts are logic\n");
    }
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.63**********************************************************************/\n");
    printf("0x%.8x\t srl(4) =  0x%.8x\n", 0x70000008, srl(0x70000008, 4));
    printf("0x%.8x\t srl(4) =  0x%.8x\n", 0x80000100, srl(0x80000100, 4));
    printf("0x%.8x\t sra(4) =  0x%.8x\n", 0x70000008, sra(0x70000008, 4));
    printf("0x%.8x\t sra(4) =  0x%.8x\n", 0x80000100, sra(0x80000100, 4));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.64**********************************************************************/\n");
    printf("0x01 - %d\t 0x02 - %d\n", any_unsigned_odd_one(0x01), any_unsigned_odd_one(0x2));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.65**********************************************************************/\n");
    printf("0xf070 - %d\t 0xf0f0 - %d\n", odd_ones(0xf070), odd_ones(0xf0f0));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.66*********************************************************************/\n");
    printf("0x10000000->0x%.8x\t0x00000000->0x%.8x\t0x00070000->0x%.8x\t0x00000005->0x%.8x\n", left_most_one(0x10000000), left_most_one(0x00000000), left_most_one(0x00070000), left_most_one(0x00000005));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.68*********************************************************************/\n");
    printf("0x%.8x\t0x%.8x\t0x%.8x\n", lower_one_mask(32), lower_one_mask(1), lower_one_mask(17));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.69*********************************************************************/\n");
    printf("0x%.8x\t0x%.8x\t0x%.8x\t0x%.8x\n", rotate_left(0x12345678, 4), rotate_left(0x12345678, 20), rotate_left(0x12345678, 32), rotate_left(0x12345678, 0));
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.71*********************************************************************/\n");
    assert(xbyte(0x00112233, 0) == 0x33);
    assert(xbyte(0x00112233, 1) == 0x22);
    assert(xbyte(0x00112233, 2) == 0x11);
    assert(xbyte(0x00112233, 3) == 0x00);

    assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
    assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
    assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
    assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.72*********************************************************************/\n");
    int maxbytes = sizeof(int) * 10;
    void* buf = malloc(maxbytes);
    int val;

    val = 0x12345678;
    copy_int(val, buf, maxbytes);
    assert(*(int*)buf == val);

    val = 0xAABBCCDD;
    copy_int(val, buf, 0);
    assert(*(int*)buf != val);

    free(buf);
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.73*********************************************************************/\n");
    assert(INT_MAX == saturating_add(INT_MAX, 0x1234));
    assert(INT_MIN == saturating_add(INT_MIN, -0x1234));
    assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");

    return 0;
}
