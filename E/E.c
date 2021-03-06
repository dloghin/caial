/**
 * Compute e using Euler's formula
 */
// #define PFDEBUG
#define WITH_POSIT_8

#include<stdint.h>

#ifdef PFDEBUG
#include <stdio.h>
#endif

#define N 20

typedef float element_t;

// variables
element_t e, k, fact;

// constants
element_t one, two;
#if defined WITH_POSIT_32
/*
// posit(32,2)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x48000000;
*/

// posit(32,3)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x44000000;
#elif (defined WITH_POSIT_16)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x00004000;
uint32_t posit_two = 0x00004800;
#elif (defined WITH_POSIT_8)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x00000040;
uint32_t posit_two = 0x00000050;
#else
uint32_t fp32_zero = 0x00000000;
uint32_t fp32_one = 0x3f800000;
uint32_t fp32_two = 0x40000000;
#endif /* WITH_POSIT */

int main() {
#if (defined WITH_POSIT_8 || defined WITH_POSIT_16 || defined WITH_POSIT_32)
  *((uint32_t*)&one) = posit_one;
  *((uint32_t*)&two) = posit_two;
  *((uint32_t*)&e) = posit_two;
  *((uint32_t*)&k) = posit_two;
  *((uint32_t*)&fact) = posit_one;
#else
  *((uint32_t*)&one) = fp32_one;
  *((uint32_t*)&two) = fp32_two;
  *((uint32_t*)&e) = fp32_two;
  *((uint32_t*)&k) = fp32_two;
  *((uint32_t*)&fact) = fp32_one;
#endif /* WITH_POSIT */
  int i;
  for (i = 2; i < N; i++) {
    fact = fact * k;
    k = k + one;    
    e = e + one / fact;
  }
#ifdef PFDEBUG
  printf("%15.14f\n", e);
#endif
	return 1;
}
