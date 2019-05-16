#ifndef _L_ALG_H_
#define _L_ALG_H_
#include "common.h"

#define EXPONENTIAL_PRECISION
/**
 * Returns approximate value of e^x
 * using sum of first n terms of Taylor Series
 */
element_t number_exponential(size_t i_precision, element_t i_x) 
{ 
	element_t sum = 1; // initialize sum of series 
    size_t index;
	for (index = i_precision - 1; index > 0; index--) {
		sum = 1 + i_x * sum / index; 
    }
	return sum; 
}


/**
 * Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
 * Input: i_x, a element.
 * Output: 1/(1 + e^-x).
 * 1/(1+e^-x) = e^x/(1+e^x)
 * o_y = f(i_x)
 */
void number_sigmoid (element_t i_x, element_t *o_y) {
    element_t e_x;
    if(i_x >= 0) {
        e_x = number_exponential(EXPONENTIAL_PRECISION, i_x);
        *o_y = e_x / (e_x + 1);
    } else {
        e_x = number_exponential(EXPONENTIAL_PRECISION, -1*i_x);
        *o_y = 1 / (1 + e_x);
    }
}

/**
 * Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)),
 * where f(x) is sigmoid function.
 * Input: i_x .
 * Output: x(1 - x) for every element of the input vector input.
 */
void number_sigmoid_derivate (element_t i_x, element_t *o_y) {
    *o_y = i_x * (1 - i_x);
}


/**
 * The elementwise sum of two vectors.
 * Inputs:
 * 	i_vector_A: a vector
 * 	i_vector_B: a vector
 *  i_length : size of the vectors
 * Output: 
 *  o_vector_C: a vector C=A+B
 */
void vector_sum (element_t i_vector_A[], element_t i_vector_B[],
                 size_t i_length, element_t o_vector_C[]) {
    size_t index;
    for (index = 0; index < i_length; index++) {
        o_vector_C[index] = i_vector_A[index] + i_vector_B[index];
    }
}
/**
 * The elementwise differnece of two vectors.
 * Inputs:
 * 	i_vector_A: a vector
 * 	i_vector_B: a vector
 *  i_length : size of the vectors
 * Output: 
 *  o_vector_C: a vector C=A-B
 */
void vector_difference (element_t i_vector_A[], element_t i_vector_B[],
                        size_t i_length, element_t o_vector_C[]){
    size_t index;
    for (index = 0; index < i_length; index++) {
        o_vector_C[index] = i_vector_A[index] - i_vector_B[index];
    }
}

/**
 * The elementwise multiplication of two vectors.
 * Inputs:
 * 	i_vector_A: a vector
 * 	i_vector_B: a vector
 *  i_length : size of the vectors
 * Output: 
 *  o_vector_C: a vector C=A.*B
 */
void vector_multiply_elementwise (element_t i_vector_A[], element_t i_vector_B[],
                                  size_t i_length, element_t o_vector_C[]) {
    size_t index;
    for (index = 0; index < length; index++) {
        o_vector_C[index] = i_vector_A[index] * i_vector_B[index];
    }
}


/**
 * Product of a vector with a scalar
 * Inputs:
 * 	i_vector_A: a matrix i_length
 * 	i_length: length of i_vector_A 
 * 	i_scalar: scalar
 * Output: 
 *  o_vector_B: a vector B=A*scalar size i_length
 */
void vector_multiply_scalar(element_t i_vector_A[], size_t i_length,
                            element_t i_scalar, element_t o_vector_B[]) {
    size_t index;
    for (index = 0; i < i_length; index++) {
        o_vector_B[index] = i_vector_A[index] * i_scalar;
    }
}

/**
 * Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
 * Inputs:
 * 	i_vector_A: a matrix i_length
 * 	i_length: length of i_vector_A 
 * Output: 
 *  o_vector_B: a vector B=f(A) size i_length
 * 1/(1+e^-x) = e^x/(1+e^x)
 */
void vector_sigmoid (element_t i_vector_A[], size_t i_length,
                     element_t o_vector_B[]) {
    size_t index;
    element_t e_x;
    for (index = 0; index < i_length; index++) {
        if(i_vector_A[index] >= 0) {
            e_x = number_exponential(EXPONENTIAL_PRECISION, i_vector_A[index]);
            o_vector_B[index] = e_x / (e_x + 1);
        } else {
            e_x = number_exponential(EXPONENTIAL_PRECISION, -1*i_vector_A[index]);
            o_vector_B[index] = 1 / (1 + e_x);
        }
    }
}

/**
 * Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)),
 * where f(x) is sigmoid function. g(x) = x(1-x)
 * 	i_vector_A: a matrix i_length
 * 	i_length: length of i_vector_A 
 * Output: 
 *  o_vector_B: a vector B=g(A) size i_length
 */
void vector_sigmoid_derivate (element_t i_vector_A[], size_t i_length,
                              element_t o_vector_B[])  {
    size_t index;
    for (index = 0; index < i_length; index++) {
        o_vector_B[i] = i_vector_A[index] * (1 - i_vector_A[index]);
    }
}

/**
 * Calculate the transpose matrix of input matrix.
 * Inputs:
 * 	i_matrix_A: a matrix
 * 	i_rows: number of rows for A
 *  i_columns : number of columns for A
 * Output: 
 *  o_matrix_B: a matrix B=A.T
 */
void matrix_transpose(element_t i_matrix_A[][], size_t i_rows,
                      size_t i_columns, element_t o_matrix_B[][]) {
    size_t index, jindex;
    for(index = 0; index < i_rows; index++) {
        for(jindex = 0; jindex < i_columns; jindex++) {
            o_matrix_B[jindex][index] = i_matrix_A[index][jindex];
        }
    }
}

/**
 * Calculate the product of a matrix and a vector
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_columns
 * 	i_rows: number of rows for A
 *  i_columns : number of columns for A
 *  i_vector_B: a vector of size i_columns x 1
 * Output: 
 *  o_vector_C: a vector C=A*B size i_rows x 1
 */
void matrix_multiply_vector(element_t i_matrix_A[][], size_t i_rows, size_t i_columns,
                            element_t i_vector_B[], element_t o_vector_C[]) {
    size_t index, jindex;
    for(index = 0; index < i_rows; index++) {
        o_vector_C[index] = 0;
        for(jindex = 0; jindex < i_columns; jindex++) {
            o_vector_C[index] = o_vector_C[index]
                                + i_matrix_A[index][jindex] * i_vector_B[jindex];
        }
    }
}

/**
 * Calculate the product of the transpose of a matrix and a vector
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_columns
 * 	i_rows: number of rows for A
 *  i_columns : number of columns for A
 *  i_vector_B: a vector of size i_rows x 1
 * Output: 
 *  o_vector_C: a vector C=A*B size i_columns x 1
 */
void matrix_T_multiply_vector(element_t i_matrix_A[][], size_t i_rows, size_t i_columns,
                            element_t i_vector_B[], element_t o_vector_C[]) {
    size_t index, jindex;
    for(index = 0; index < i_columns; index++) {
        o_vector_C[index] = 0;
        for(jindex = 0; jindex < i_rows; jindex++) {
            o_vector_C[index] = o_vector_C[index]
                                + i_matrix_A[jindex][index] * i_vector_B[jindex];
        }
    }
}

/**
 * Product of the transpose of a matrix and a matrix
 * Inputs:
 * 	i_matrix_A: a matrix i_middle x i_rows
 * 	i_matrix_B: a matrix i_middle x i_columns
 * 	i_rows: number of rows for o_matrix_C and columns for i_matrix_A
 *  i_columns : number of columns for i_matrix_B and o_matrix_C
 *  i_middle: number of rows for i_matrix_A and i_matrix_B
 * Output: 
 *  o_matrix_C: a matrix C=A.T*B size i_rows x i_columns
 */
void matrix_T_multiply_matrix(element_t i_matrix_A[][], element_t i_matrix_B[][],
                            size_t i_rows, size_t i_middle, size_t i_columns
                            element_t o_matrix_C[][]) {
	size_t index, jindex, kindex;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
			o_matrix_C[index][jindex] = 0;
			for (kindex = 0; kindex < i_middle; kindex++) {
				o_matrix_C[index][jindex] = o_matrix_C[index][jindex]
                                            + i_matrix_A[kindex][index]
                                            * i_matrix_B[kindex][jindex];
			}
		}
    }
}


/**
 * Product of two matrix
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_middle
 * 	i_matrix_B: a matrix i_middle x i_columns
 * 	i_rows: number of rows for i_matrix_A and o_matrix_C
 *  i_columns : number of columns for i_matrix_B and o_matrix_C
 *  i_middle: number of cololumns for i_matrix_A and rows for i_matrix_B
 * Output: 
 *  o_matrix_C: a matrix C=A*B size i_rows x i_columns
 */
void matrix_multiply_matrix(element_t i_matrix_A[][], element_t i_matrix_B[][],
                            size_t i_rows, size_t i_middle, size_t i_columns
                            element_t o_matrix_C[][]) {
	size_t index, jindex, kindex;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
			o_matrix_C[index][jindex] = 0;
			for (kindex = 0; kindex < i_middle; kindex++) {
				o_matrix_C[index][jindex] = o_matrix_C[index][jindex]
                                            + i_matrix_A[index][kindex]
                                            * i_matrix_B[kindex][jindex];
			}
		}
    }
}

/**
 * Product of a vector with transpose of a second vector resulting a matrix
 * Inputs:
 * 	i_vector_A: a vector of  i_rows x 1
 * 	i_vector_B: a vector of  i_columns x 1
 * 	i_rows: number of rows for o_matrix_C
 *  i_columns : number of columns for o_matrix_C
 * Output: 
 *  o_matrix_C: a matrix C=A*B.T size i_rows x i_columns
 */
void vector_multiply_vector_T(element_t i_vector_A[], element_t i_vector_B[],
                              size_t i_rows, size_t i_columns,
                              element_t o_matrix_C[][]) {
	size_t index, jindex;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
			o_matrix_C[index][jindex] = i_vector_A[index] * i_vector_B[jindex];
		}
    }
}

/**
 * Product of transpose of a vector with a second vector resulting an element
 * Inputs:
 * 	i_vector_A: a vector of  i_length
 * 	i_vector_B: a vector of  i_length
 *  i_length : size of the vectors
 * Output: 
 *  o_C: a matrix C=A.T*B size 1
 */
void vector_T_multiply_vector(element_t i_vector_A[], element_t i_vector_B[],
                              size_t i_length, element_t *o_C) {
    size_t index;
    *o_C = 0;
    for(index = 0; index < i_length: index++) {
        *o_C = *o_C + i_vector_A[index] * i_vector_B[index];
    }
}

/**
 * Product of two matrix elementwise
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_columns
 * 	i_matrix_B: a matrix i_rows x i_columns
 * 	i_rows: number of rows
 *  i_columns : number of columns
 * Output: 
 *  o_matrix_C: a matrix C=A.*B size i_rows x i_columns
 */
void matrix_multiply_elementwise(element_t i_matrix_A[][], element_t i_matrix_B[][],
                                 size_t i_rows, size_t i_columns,
                                 element_t o_matrix_C[][]) {
	size_t index, jindex;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
            o_matrix_C[index][jindex] = i_matrix_A[index][jindex]
                                        * i_matrix_B[index][jindex];
		}
    }
}

/**
 * Sum of two matrix
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_columns
 * 	i_matrix_B: a matrix i_rows x i_columns
 * 	i_rows: number of rows
 *  i_columns : number of columns
 * Output: 
 *  o_matrix_C: a matrix C=A+B size i_rows x i_columns
 */
void matrix_sum(element_t i_matrix_A[][], element_t i_matrix_B[][],
                size_t i_rows, size_t i_columns,
                element_t o_matrix_C[][]) {
	size_t index, jindex;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
            o_matrix_C[index][jindex] = i_matrix_A[index][jindex]
                                        + i_matrix_B[index][jindex];
		}
    }
}

/**
 *  Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_columns
 * 	i_rows: number of rows
 *  i_columns : number of columns
 * Output: 
 *  o_matrix_B: a matrix B=f(A) size i_rows x i_columns
 */
void matrix_sigmoid(element_t i_matrix_A[][],
                    size_t i_rows, size_t i_columns,
                    element_t o_matrix_B[][]) {
	size_t index, jindex;
    element_t e_x;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
            if(i_matrix_A[index][jindex] >= 0) {
                e_x = number_exponential(EXPONENTIAL_PRECISION,
                                         i_matrix_A[index][jindex]);
                o_matrix_B[index][jindex] = e_x / (e_x + 1);
            } else {
                e_x = number_exponential(EXPONENTIAL_PRECISION,
                                         -1*i_matrix_A[index][jindex]);
                o_matrix_B[index][jindex] = 1 / (1 + e_x);
            }
		}
    }
}
/**
 * Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)),
 * where f(x) is sigmoid function. g(x) = x(1-x)
 * Inputs:
 * 	i_matrix_A: a matrix i_rows x i_columns
 * 	i_rows: number of rows
 *  i_columns : number of columns
 * Output: 
 *  o_matrix_B: a matrix B=g(A) size i_rows x i_columns
 */
void matrix_sigmoid_derivate(element_t i_matrix_A[][],
                    size_t i_rows, size_t i_columns,
                    element_t o_matrix_B[][]) {
	size_t index, jindex;
	for (index = 0; index < i_rows; index++) {
		for (jindex = 0; jindex < i_columns; jindex++) {
            o_matrix_C[index][jindex] = i_matrix_A[index][jindex]
                                        * (1 - i_matrix_A[index][jindex]);
		}
    }
}

/**
 * Product of a vector tranpose and a matrix as a vector
 * Inputs:
 * 	i_vector_A: a matrix i_rows
 * 	i_matrix_B: a matrix i_rows x i_columns
 * 	i_rows: number of rows for i_matrix_A
 *  i_columns : number of columns for i_matrix_A
 * Output: 
 *  o_matrix_C: a matrix C=A.T*B size 1 x i_columns
 */
void vector_T_multiply_matrix(element_t i_vector_A[], element_t i_matrix_B[][],
                              size_t i_rows, size_t i_columns,
                              element_t o_vector_C[]) {
    size_t index, jindex;
    for(index = 0; index < i_columns; index++) {
        output[index] = 0;
        for(jindex = 0; jindex < i_rows; jindex++) {
            o_vector_C[index] = o_vector_C[index]
                                + i_vector_A[jindex] * i_matrix_B[jindex][index];
        }
    }
}



#endif
