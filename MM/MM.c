#include "../common/common.h"

element_t A[DIM*DIM], B[DIM*DIM], C[DIM*DIM];

void gen_matrix(element_t* A, size_t n, size_t m) {
	size_t i, j, k = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
#ifdef WITHINT
			A[i * DIM + j] = k++;
#else
			A[i * DIM + j] = k++/3.14;
#endif
		}
}

#ifdef DEBUG
void print_matrix(element_t* A, size_t n, size_t m) {
	size_t i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf("%ld ", A[i * DIM + j]);
		printf("\n");
	}
	printf("\n");
}
#endif

void mm(element_t* A, element_t* B, element_t* C, size_t n, size_t m, size_t p) {
	size_t i, j, k, aidx, bidx, cidx;
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
