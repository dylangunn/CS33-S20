/* 
 * CS:APP Data Lab 
 * 
 * <Dylan Gunn, 805112866>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
/* How I imagine this: I need to determine if odd num 0's, ie odd num 1's. What cancels even 1's? '^'. So I thought
 * about this problem as "stacking" all of the bits on either the far left or right and xoring them repeatedly to cancel
 * any even-numbered 1's. In the end, this should leave me with a 1 or 0 on the far ends. However, if I did this by
 * repeatedly shifting right to stack and there were a 1 in the far-left bit, then I would end up copying that one for every
 * movement (ich maybe works but I really just didn't want to think too hard about it), so instead I shifted left.
 * Now, I realize my method was just as messy because it left trailing 1's and 0's in the right 31 bits, but right-
 * shifting 31 times cleared that out and ensured that the only bit affecting anything was the most significant.
 * If odd, there would be a 1 in the far left. To translate this, I right-shifted 31 spaces to fill everything
 * with 1's or 0's, took the inverse, (now 00000 if odd or 11111 if even) and banged it. Banging the odd returns 1,
 * banging the even is 0. */
  x = x ^ (x << 16);
  x = x ^ (x << 8);
  x = x ^ (x << 4);
  x = x ^ (x << 2);
  x = x ^ (x << 1);
  x = x >> 31;
  return !(~x);
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
/* Thinking: have n bits on end need to preserve. shift left until only those n bits on left and store them. Get set of n 1's then 0s.
 * Set left n bits of x to 0 by & with inverse of the n 1's, then xor it with stored. */
  int move, stored, nOnes;
  move = 32 + (~n + 1);
  stored = x << move;
  nOnes = (1 << 31) >> (n + ~1 + 1);
  return ((~nOnes & (x >> n)) ^ stored);
  
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
/* Adjust n and m (mult by 8) so that they deal with 8 bits (1 byte) each. Shift x over by n and m to get the two bytes we want.
 * to switch to the first byte and xor them. This gets which bits of the two bytes are different from one another. & this with
 * 0xff to clear out the rest of the bytes, so now the data in y holds those bits in byte n and m that need to be changed. This
 * is then applied to the appropriate bytes in x by moving the translator over to the correct byte and xoring it with the original */  
  int y;
  y = 0;
  n = n << 3;
  m = m << 3;
  y = ((x >> n) ^ (x >> m)) & 0xff;
  x = x ^ (y << n);
  x = x ^ (y << m);
  return x;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
/* All need to do is shift 15 over, means should be all 0 if pos and all 1 if neg. Check if x or ~x is zero, if so, then fits! */
  int isZero;
  x = (x >> 15);
  isZero = !(x ^ 0) | !(~x ^ 0);
  return isZero; 
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/* Logically, I just need the 1s to match with 1s. Doing complement, 0's become 1 and 1's 0.
 *| Makes everything not a pair of 0 -> 1, and the inverse means I essentially made everything not 1 -> 0. */
  return ~(~x | ~y);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) { //ok
  /* Issues only occur with diff signs (potential for overflow) and results in diff signage.
   * xSign checks if x diff sign from sub, xSign ^ ySign checks if x and y diff signs. */
  int sub, xSign, ySign;
  sub = x + ~y + 1;
  xSign = ((x ^ sub) >> 31) & 0x1;
  ySign = ((y ^ sub) >> 31) & 0x1;
  return !(xSign & (xSign ^ ySign));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) { //ok
/* Check equal, check sign, subtract. If equal, not greater. If positive and same sign 
 * and diff > 0, greater. If x pos and y neg, greater. if y neg and x pos, not greater. */
  int equal, xSign, ySign, sameSign, difference, diffPos;
  equal = !(x ^ y);
  xSign = (x >> 31) & 0x1;
  ySign = (y >> 31) & 0x1;
  sameSign = !(xSign ^ ySign);
  difference = (x + ~y + 1);
  diffPos = !((difference >> 31) & 0x1);
  return ((ySign & !sameSign) | ((!equal) & sameSign & diffPos));
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) { //ok
/* Get diff between 32 and n so can shift, shift left numbits; if fits, then most significant
   bit of n would be for sign. if this is the case, (x << numBits) >> numBits == x. The
   xor makes everything 0 if result == x, then !0 = 1 */
  int numBits;
  numBits = 32 + ~n + 1;
  return (!(((x << numBits) >> numBits)^x));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { //ok
  // ~x is -x-1, so doing it and adding one is all good
  return (~x + 1); 
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/* if isTmax, bits are 0111111...111. Doing TMAX + 1 gets 100000...000. Sum and complement is 000...000
 * and check equality. Also, make sure the number isn't -1 bc would also have overflow with -1+1. */
  int isNegOne;
  isNegOne = !(x ^ (~1 + 1));
  return !((~(x+1) ^ x) ^ isNegOne);
}
