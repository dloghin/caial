/*
* Matrix multiplication
*
*/
#include <stdlib.h>
#include "util.h"
#include "../common/common.h"

#define DATA_LENGTH 10

element_t A[DATA_LENGTH][DATA_LENGTH], B[DATA_LENGTH][DATA_LENGTH], C[DATA_LENGTH][DATA_LENGTH];

/**
* Initialize matrix A
*
*/
void gen_matrix(element_t A[][], size_t rows, size_t columns) {
	size_t index, jindex, kindex = 0;
	for (index = 0; index < rows; index++)
		for (jindex = 0; jindex < columns; jindex++) {
#ifdef WITHINT
			A[index][jidnex] = kindex++;
#else
			A[index][jindex] = kindex++/3.14;
#endif
		}
}

#ifdef DEBUG
/**
* Print elements of matrix A
*
*/
void print_matrix(element_t A[][], size_t rows, size_t columns) {
	size_t index, jindex;
	for (index = 0; index < rows; index++)
		for (jindex = 0; jindex < columns; jindex++) {
			printf("%ld ", A[index][jindex]);
		printf("\n");
	}
	printf("\n");
}
#endif


/**
* Multiply matrix A (n rows and m columns) 
* with B (m rows and p columns) and put the result
* in matrix C (n rows and p columns)
*/
void matrix_multiplication(element_t A[][], element_t B[][], element_t C[][], size_t n, size_t m, size_t p) {
	size_t index, jindex, kindex;
	for (index = 0; index < n; index++)
		for (jindex = 0; jindex < p; jindex++) {
			C[index][jindex] = 0;
			for (kindex = 0; kindex < m; kindex++) {
				C[index][jindex] = C[index][jindex] + A[index][kindex] * B[kindex][jindex];
			}
		}
}

int main() {
	size_t n = 4;
	size_t m = 4;
	size_t p = 4;
	gen_matrix(A, n, m);
	gen_matrix(B, m, p);
	mm(A, B, C, n, m, p);

#ifdef DEBUG
	print_matrix(A, n, m);
	print_matrix(B, m, p);
	print_matrix(C, n, p);
#endif

	return 0;
}
