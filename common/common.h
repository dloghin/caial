#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef DEBUG
#include <stdio.h>
#endif

#ifdef WITHINT
#include <stdint.h>
#define element_t 	int64_t
#else	// WITHFLOAT
#define WITHFLOAT
#define element_t	double
#endif

#define size_t		int

#define DIM 64

#endif // _COMMON_H_
