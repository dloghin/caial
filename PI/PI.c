// Part of this code is taken from: https://www.codeproject.com/Articles/813185/Calculating-the-Number-PI-Through-Infinite-Sequenc
// Approximation of the number PI
// Language: C
// Author: Jose Cintra (jose.cintra@html-apps.info)

#ifdef PFDEBUG
#include <stdio.h>
#endif

#ifdef WITH_SQRT
#include <math.h>
#endif

#include<stdint.h>

typedef double element_t;

// variables
element_t pi = 0.0;
element_t sign = 1.0;
int i;

// constants
element_t one = 1.0;
element_t two = 2.0;
element_t three = 3.0;
element_t four = 4.0;

#ifdef WITH_POSIT
uint32_t posit_zero = 0x00000000;
uint32_t posit_one = 0x40000000;
uint32_t posit_two = 0x48000000;
uint32_t posit_three = 0x4c000000;
uint32_t posit_four = 0x50000000;

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
   int j;         // Number of iterations and control variables
   element_t f;   // factor that repeats
   pi = one;
          
   for(i = n; i > 1; i--) {
      f = two;
      for(j = 1; j < i; j++){
         f = two + sqrt(f);
      }
      f = sqrt(f);
      pi = pi * f / two;
   }
   pi *= sqrt(two) / two;
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
  pi = three;
  for(i = 2; i <= n*2; i += 2){
     pi = pi + sign * (four / (i * (i + 1) * (i + 2)));
     sign = -sign;
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
