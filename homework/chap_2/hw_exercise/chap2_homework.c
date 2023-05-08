#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

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


//2.74
/******************************************************************************/
int tsub_ok(int x, int y){
    int res = 1;

    // 若y=INT_MIN，则一定溢出
    (y == INT_MIN) && (res = 0);

    // 若正溢出，则pos_over=1
    // 若负溢出，则neg_over=1
    int pos_over = x>0 && y<0 && x-y<0;
    int neg_over = x<0 && y>0 && x-y>0;

    res = res && !(pos_over || neg_over);
    return res;
}
/******************************************************************************/


//2.75
/******************************************************************************/
// use `int signed_high_prod(int x, int y)`
int signed_high_prod(int x, int y) {
  int64_t mul = (int64_t) x * y;
  return mul >> 32;
}

unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  return mul >> 32;
}

// 当调用`signed_high_prod`时，会将32位扩展为64位，式（2.18）可写为：
// (x' * y') mod 2^w = [(x + signed_x*2^w)*(y + signed_y*2^w)] mod 2^w
//                   = [x*y + (signed_y*x + signed_x*y)*2^w + signed_x*signed_y*2^2w] mod 2^W
// x'-x的无符号表示，x-有符号的x，signed_x-x的符号位，w=32
// 取余后得到无符号数乘法与补码乘法的低位表示相同。
// 当不需要取余时，有：
// x' * y' = x*y + (signed_y*x + signed_x*y)*2^w + signed_x*signed_y*2^2w，该式揭示了无符号乘法与补码乘法全部位之间的关系
// 其中 `(signed_y*x + signed_x*y)*2^w` 等价于 `(signed_y*x + signed_x*y) >> w` 即将结果加到高位上
// `signed_x*signed_y*2^2w` 超出了范围，不造成影响。
unsigned unsigned_high_prod(unsigned x, unsigned y){
    int w = sizeof(unsigned) << 3;
    int signed_x = x >> (w - 1);
    int signed_y = y >> (w - 1);
    unsigned mul = signed_high_prod(x, y);
    // mul即为补码乘法的高位表示，不需要再将`(signed_y*x + signed_x*y)`左移w位，直接加即可
    return mul + x*signed_y + y*signed_x;
}
/******************************************************************************/


//2.76
/******************************************************************************/
// int tmult_ok(int x, int y){
//     int p = x*y;
//     return !x || p/x == y;
// }
void *my_calloc(size_t nmemb, size_t size){
    if(nmemb == 0 || size == 0){
        return NULL;
    }
    size_t buf_size = nmemb*size;
    if(buf_size/size == nmemb){
        void *p = malloc(buf_size);
        if(p != NULL)
            memset(p, 0, buf_size);
        return p;
    }
    return NULL;
}
/******************************************************************************/


//2.78
/******************************************************************************/
// assume 0 <= k < w-1
int divide_power2(int x, int k){
    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << k) - 1));
    return x >> k;
}
/******************************************************************************/


//2.79
/******************************************************************************/
int mul3div4(int x){
    int mul = (x << 1) + x;
    return divide_power2(mul, 2);
}
/******************************************************************************/


//2.79
/******************************************************************************/
int threeforths(int x){
    int div = divide_power2(x, 2);
    printf("x/4=%d, x/4*3=%d\n", div, (div << 1) + div);
    return (div << 1) + div;
}
/******************************************************************************/


//2.82
/******************************************************************************/
// n = 0.yyyyyyy...
// n<<k = y.yyyyyy... = Y + n
// n*2^k - n = Y
// n = Y / (2^k - 1)
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


    printf("/2.74*********************************************************************/\n");
    assert(!tsub_ok(0x00, INT_MIN));
    assert(tsub_ok(0x00, 0x00));
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");

    printf("/2.75*********************************************************************/\n");
    unsigned x1 = 0x12345678;
    unsigned y1 = 0xFFFFFFFF;

    assert(another_unsigned_high_prod(x1, y1) == unsigned_high_prod(x1, y1));
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");

    printf("/2.76*********************************************************************/\n");
    void* p;
    p = my_calloc(0x1234, 1);
    assert(p != NULL);
    free(p);

    p = my_calloc(SIZE_MAX, 2);
    assert(p == NULL);
    free(p);

    p = my_calloc(0, 5);
    assert(p == NULL);
    free(p);
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.78*********************************************************************/\n");
    x = 0x80000007;
    assert(divide_power2(x, 0) == x);
    assert(divide_power2(x, 2) == x / 4);
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.79*********************************************************************/\n");
    x = 0x87654321;
    assert(mul3div4(x) == x * 3 / 4);
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");


    printf("/2.80*********************************************************************/\n");
    assert(threeforths(8) == 6);
    assert(threeforths(9) == 6);
    assert(threeforths(10) == 7);
    assert(threeforths(11) == 8);
    assert(threeforths(12) == 9);

    assert(threeforths(-8) == -6);
    assert(threeforths(-9) == -6);
    assert(threeforths(-10) == -7);
    assert(threeforths(-11) == -8);
    assert(threeforths(-12) == -9);
    printf("all test pass!!!\n");
    printf("/**************************************************************************/\n");
    printf("\n");

   

    return 0;
}
