// Part of this code is taken from: https://www.codeproject.com/Articles/813185/Calculating-the-Number-PI-Through-Infinite-Sequenc
// Approximation of the number PI
// Language: C
// Author: Jose Cintra (jose.cintra@html-apps.info)

#define WITH_POSIT
// #define WITH_SQRT

#ifdef PFDEBUG
#include <stdio.h>
#endif

#ifdef WITH_SQRT
#include <math.h>
#endif

#include<stdint.h>

typedef float element_t;

// variables
element_t pi = 0.0;
element_t sign = 1.0;
element_t i;

// constants
element_t one = 1.0;
element_t two = 2.0;
element_t three = 3.0;
element_t four = 4.0;

#ifdef WITH_POSIT
/*
// posit(32,2)
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x48000000;
uint32_t posit_three = 0x4c000000;
uint32_t posit_four = 0x50000000;
*/
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x44000000;
uint32_t posit_three = 0x46000000;
uint32_t posit_four = 0x48000000;

void posit_init() {
  *((uint32_t*)&pi) = posit_zero;
  *((uint32_t*)&one) = posit_one;
  *((uint32_t*)&two) = posit_two;
  *((uint32_t*)&three) = posit_three;
  *((uint32_t*)&four) = posit_four;
  *((uint32_t*)&sign) = posit_one;
}
#endif /* WITH_POSIT */

#ifdef WITH_SQRT
void viete(int n) {
   int k, j;
   pi = one;
          
   for(k = n; k > 1; k--) {
      i = two;
      for(j = 1; j < k; j++){
         i = two + sqrt(i);
      }
      i = sqrt(i);
      pi = pi * i / two;
   }
   pi = pi * sqrt(two) / two;
   pi = two / pi;

#ifdef PFDEBUG   
   printf("\nAproximated value of PI = %1.16lf\n", pi);  
#endif
}
#endif /* WITH_SQRT */

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
#ifdef WITH_POSIT
  *((uint32_t*)&pi) = posit_three;
  *((uint32_t*)&i) = posit_two;
#else
  pi = three;
  i = two;
#endif
  int j;
  for(j = 2; j <= n*2; j += 2){
     pi = pi + sign * (four / (i * (i + one) * (i + two)));
     sign = -sign;
     i = i + two;
  }
#ifdef PFDEBUG
  printf("\nAproximated value of PI = %1.16lf\n", pi);  
#endif
}

int main() {
#ifdef WITH_POSIT
  posit_init();
#endif
// leibniz(100000000);
// viete(100);
  nilakantha(200);
	return 0;
}
