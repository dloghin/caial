#ifdef DEBUG
#include <stdio.h>
#endif

#include <stdint.h>

#define element_t int64_t

#define DIM 64

element_t A[DIM*DIM], B[DIM*DIM], C[DIM*DIM];

void gen_matrix(element_t* A, int n, int m) {
	int i, j, k = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			A[i * DIM + j] = k++;
		}
}

#ifdef DEBUG
void print_matrix(element_t* A, int n, int m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf("%ld ", A[i * DIM + j]);
		printf("\n");
	}
	printf("\n");
}
#endif

void mm(element_t* A, element_t* B, element_t* C, int n, int m, int p) {
	int i, j, k, aidx, bidx, cidx;
	for (i = 0; i < n; i++)
		for (j = 0; j < p; j++) {
			cidx = i * DIM + j;
			C[cidx] = 0;
			for (k = 0; k < m; k++) {
				aidx = i * DIM + k;
				bidx = k * DIM + j;
				C[cidx] += A[aidx] * B[bidx];
			}
		}
}

int main() {
	int n = 4;
	int m = 4;
	int p = 4;
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
