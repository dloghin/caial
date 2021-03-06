// Part of this code is taken from: https://www.codeproject.com/Articles/813185/Calculating-the-Number-PI-Through-Infinite-Sequenc
// Approximation of the number PI
// Language: C
// Author: Jose Cintra (jose.cintra@html-apps.info)

#define WITH_POSIT_16

#ifdef VIETE
#define WITH_SQRT
#endif

#ifdef PFDEBUG
#include <stdio.h>
#endif

#include<stdint.h>

float sqrt_asm(float x) {
    float res;
    asm("fsqrt.s %0,%1\n\t" : "=f" (res) : "f" (x) : "cc");
    return res;
}

typedef float element_t;

// variables
element_t pi = 0.0;
element_t sign = 1.0;
element_t i = 1.0;

// constants
element_t minus_one = -1.0;
element_t one = 1.0;
element_t two = 2.0;
element_t three = 3.0;
element_t four = 4.0;

#if (defined WITH_POSIT_32)
/*
// posit(32,2)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x48000000;
uint32_t posit_three = 0x4c000000;
uint32_t posit_four = 0x50000000;
*/
// posit(32,3)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x44000000;
uint32_t posit_three = 0x46000000;
uint32_t posit_four = 0x48000000;
uint32_t posit_minus_one = 0xc0000000;
#elif (defined WITH_POSIT_16)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x00004000;
uint32_t posit_two = 0x00004800;
uint32_t posit_three = 0x00004c00;
uint32_t posit_four = 0x00005000;
uint32_t posit_minus_one = 0x0000c000;
#elif (defined WITH_POSIT_8)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x00000040;
uint32_t posit_two = 0x00000048;
uint32_t posit_three = 0x0000004c;
uint32_t posit_four = 0x00000050;
uint32_t posit_minus_one = 0x000000c0;
#else
uint32_t fp32_zero = 0x00000000;
uint32_t fp32_one = 0x3f800000;
uint32_t fp32_two = 0x40000000;
uint32_t fp32_three = 0x40400000;
uint32_t fp32_four = 0x40800000;
uint32_t fp32_minus_one = 0xbf800000;
#endif /* WITH_POSIT */

void init() {
#if (defined WITH_POSIT_8 || defined WITH_POSIT_16 || defined WITH_POSIT_32)
  *((uint32_t*)&pi) = posit_zero;
  *((uint32_t*)&one) = posit_one;
  *((uint32_t*)&two) = posit_two;
  *((uint32_t*)&three) = posit_three;
  *((uint32_t*)&four) = posit_four;
  *((uint32_t*)&sign) = posit_one;
  *((uint32_t*)&minus_one) = posit_minus_one;
#else
  *((uint32_t*)&pi) = fp32_zero;
  *((uint32_t*)&one) = fp32_one;
  *((uint32_t*)&two) = fp32_two;
  *((uint32_t*)&three) = fp32_three;
  *((uint32_t*)&four) = fp32_four;
  *((uint32_t*)&sign) = fp32_one;
  *((uint32_t*)&minus_one) = fp32_minus_one;
#endif /* WITH_POSIT */
}

void viete(int n) {
   int k, j;
#if (defined WITH_POSIT_8 || defined WITH_POSIT_16 || defined WITH_POSIT_32)
  *((uint32_t*)&pi) = posit_one;
#else
  *((uint32_t*)&pi) = fp32_one;
#endif
          
   for(k = n; k > 1; k--) {
#if (defined WITH_POSIT_8 || defined WITH_POSIT_16 || defined WITH_POSIT_32)
      *((uint32_t*)&i) = posit_two;
#else
      *((uint32_t*)&i) = fp32_two;
#endif
      for(j = 1; j < k; j++){
         i = two + sqrt_asm(i);
      }
      i = sqrt_asm(i);
      pi = pi * i / two;
   }
   pi = pi * sqrt_asm(two) / two;
   pi = two / pi;

#ifdef PFDEBUG   
   printf("\nAproximated value of PI = %1.16lf\n", pi);  
#endif
}

void leibniz(int n) {   
   for(i = 0; i < n; i++){
     pi = pi + sign * four / (two * i + one);
     sign = -sign;
   }

#ifdef PFDEBUG
   printf("\nAproximated value of PI = %1.16lf\n", pi);  
#endif
}

void nilakantha(int n) {
#if (defined WITH_POSIT_8 || defined WITH_POSIT_16 || defined WITH_POSIT_32)
  *((uint32_t*)&pi) = posit_three;
  *((uint32_t*)&i) = posit_two;
#else
  *((uint32_t*)&pi) = fp32_three;
  *((uint32_t*)&i) = fp32_two;
#endif
  int j;
  element_t tmp;
  for(j = 2; j <= n*2; j += 2){
     tmp = four / (i * (i + one) * (i + two));
     pi = pi + sign * tmp;
     sign = sign* minus_one;
     i = i + two;
  }
#ifdef PFDEBUG
  printf("\nAproximated value of PI = %1.16lf\n", pi);  
#endif
}

int main() {
  init();
#if defined LEIBNIZ
  leibniz(100000000);
#elif defined VIETE
  viete(100);
#else
  nilakantha(200);
#endif
  return 0;
}
