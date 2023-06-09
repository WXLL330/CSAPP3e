/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
// 0100 0101
// 1011&0101 = 0001
// 0100&1010 = 0000
// 0001|0000 = ~(~(0001|0000)) = ~(~0001&~0000) = ~(1110&1111) = ~1110 = 0001
int bitXor(int x, int y) {
  // a = x&~y 将x中为1，y中为0的位置1
  // b = ~x&y 将y中为1，x中为0的位置1
  // 再利用 a|b = ~(~(a|b)) = ~(~a&~b) 即可
  return ~(~(x & ~y) & ~(~x & y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
// tmin = 0x80000000
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
// ~0x0 = 0xffffffff 
int isTmax(int x) {
// tmax = 0x7fffffff
// tmax + 1 = 0x80000000
// ~(tmax + 1) = 0x7ffffffff = tmax
// 还要注意特例-1，也满足上述条件
// !!(1 + x)是想让 1+x 只在0、1中取值，防止取其他值影响后面的判断
  return !!(1 + x) & !((~(x + 1)) ^ x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
// 采用2分法，设x符合要求，则x的每一字节都符合要求
// 那么x的高16位与x的低16位也一定符合要求，所以二者相与也一定符合要求
// 一直重复上述过程直到得到一个字节，用该字节与0xAA相与，结果一定为0xAA，再与0xAA异或得到0，最后取非即可得到1
int allOddBits(int x) {
  x = x & (x >> 16);
  x = x & (x >> 8);
  return !((x & 0xAA) ^ 0xAA);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
// 0x30 <= x <= 0x39
// negate(0x39) <= negate(x) <= negate(0x30)
// 即 ~0x39 + 1 <= -x <= ~0x30 + 1
// 所以 ~0x39 + 1 + x <= 0, ~0x30 + 1 + x >= 0
// 所以 ~0x39 + x < 0, 该项符号位一定为1
//  ~0x30 + 1 + x >= 0，该项符号位一定为0
int isAsciiDigit(int x) {
  int neg_max = ~0x30 + 1;
  int neg_min = ~0x39;
  return !((x + neg_max) >> 31) & ((x + neg_min) >> 31);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
// mask = 0x00000000  (~mask | y) & (mask | z) = z
// mask = 0xffffffff  (~mask | y) & (mask | z) = y
// 利用x构造出mask
// x = 0  -> !x = 1 -> !x + ~1 = 0xffffffff -> !x + ~1 + 1 = 0x00000000
// x != 0 -> !x = 0 -> !x + ~1 = 0xfffffffe -> !x + ~1 + 1 = 0xffffffff
// x  = 0 -> mask = 0x00000000
// x != 0 -> mask = 0xffffffff
int conditional(int x, int y, int z) {
  int mask = !x + ~1 + 1;
  return (~mask | y) & (mask | z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
// 当 x<0,y>0 时，可能会发生负溢出，结果必为1
// 当 x>0,y<0 时，可能会发生正溢出，结果必为0
// 除上述情况外，当 x 与 y 同号时，采用 x + (-y) 是否大于0来判断大小关系
int isLessOrEqual(int x, int y) {
  int Xsign = !!(x >> 31);
  int Ysign = !!(y >> 31);
  int Xpos_Yneg = !Xsign & Ysign;
  int Xneg_Ypos = Xsign & !Ysign;
  return !Xpos_Yneg & (Xneg_Ypos | !!(x + (~y) >> 31));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
// 判断x中是否存在为1的位，采用二分法，一直用x的高位与低位进行或运算
// 如果x中存在为1的位，则二分到最高位位的结果为1，1 >> 31 = 0xffffffff + 1 = 0
// 如果x为0，则二分到最高位位的结果为0, 0 >> 31 = 0x00000000 + 1 = 1
int logicalNeg(int x) {
  x = x | (x << 16);
  x = x | (x << 8);
  x = x | (x << 4);
  x = x | (x << 2);
  x = x | (x << 1);
  return (x >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5       0 1100
 *            howManyBits(298) = 10     01 0010 1010
 *            howManyBits(-5) = 4       1011
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
// 对于 x>0 ,找到最左边的1的位置，再加上1位符号位，即为所求位数
// 对于 x<0 ,对x取反后找到最左边的1的位置，再加上1位符号位，即为所求位数
// 对于 x=0 ,直接返回1
int howManyBits(int x) {
  int isZero = !x;
  int sign = x >> 31;
  int mask = (!!x << 31) >> 31;
  // 任何整数都能表示为 2^n n=0,1,2... 的和
  // 对于32位的数，一定可以表示为 16 8 4 2 1 的和
  int high_16, high_8, high_4, high_2, high_1, high_0, res;
  // x>0 -> x=x
  // x<0 -> x=~x
  x = (~sign | ~x) & (sign | x);

  // 检验高16位中是否有1，若有1，则返回16，没有1，则返回0
  high_16 = (!((!!(x >> 16)) ^ 1)) << 4;
  // 若high_16不为0，说明x中最高位的1在高16位中，则将x左移16位，之后再次判断在高8位还是低8位中，二分思想
  x = x >> high_16;

  high_8 = (!((!!(x >> 8)) ^ 1)) << 3;
  x = x >> high_8;

  high_4 = (!((!!(x >> 4)) ^ 1)) << 2;
  x = x >> high_4;

  high_2 = (!((!!(x >> 2)) ^ 1)) << 1;
  x = x >> high_2;

 
  high_1 = (!((!!(x >> 1)) ^ 1));
  x = x >> high_1;

  high_0 = x;

  res = high_16 + high_8 + high_4 + high_2 + high_1 + high_0 + 1;
  return isZero | (mask & res);
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
