//DNN
// https://cognitivedemons.wordpress.com/2017/07/06/a-neural-network-in-10-lines-of-c-code/
// https://www.geeksforgeeks.org/program-to-efficiently-calculate-ex/

#include "../common/common.h"

#define MDIM 4

#include <stdlib.h>
#include "util.h"


#define T_DATA float
#define TRAINING_DATA_LENGTH 150
#define INPUT_LENGTH 4
#define MAX_ITERATIONS 40


/**
 * Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)),
 * where f(x) is sigmoid function.
 * Input: input, a vector.
 * Output: x(1 - x) for every element of the input vector input.
 */
void sigmoid_d (T_DATA input[], size_t n, T_DATA output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = input[i] * (1 - input[i]);
    }
}

/**
 * Returns approximate value of e^x
 * using sum of first n terms of Taylor Series
 */
T_DATA exponential(size_t n, T_DATA x) 
{ 
	T_DATA sum = 1.0; // initialize sum of series 
  size_t i;
	for (i = n - 1; i > 0; --i ) 
		sum = 1 + x * sum / i; 

	return sum; 
}

/**
 * Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
 * Input: input, a vector.
 * Output: 1/(1 + e^-x) for every element of the input vector input.
 */
void sigmoid (T_DATA input[], size_t n, T_DATA output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = 1 / (1 + exponential(50,-input[i]));
    }
}

/**
 * Returns the elementwise sum of two vectors.
 * Inputs:
 * 	input1: a vector
 * 	input2: a vector
 * Output: a vector, sum of the vectors input1 and input2.
 */
void sum (T_DATA input1[], T_DATA input2[], size_t n, T_DATA output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] + input2[i];
    }
}

void difference (T_DATA input1[], T_DATA input2[], size_t n, T_DATA output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] - input2[i];
    }
}

/**
 * Returns the elementwise multiplication of two vectors.
 * Inputs:
 * 	input1: a vector
 * 	input2: a vector
 * Output: a vector, product of the vectors input1 and input2.
 */
void multiply (T_DATA input1[], T_DATA input2[], size_t n, T_DATA output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] * input2[i];
    }
}

/**
 * Returns a transpose matrix of input matrix.
 * Inputs:
 *  input: input matrix
 *  n: int, number of columns in the input matrix
 *  m: int, number of rows in the input matrix
 * Output: transpose matrix of input matrix
 */
void transpose(T_DATA input[][4], size_t n, size_t m, T_DATA output[][4]) {
    size_t i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            output[i][j] = input[j][i];
        }
    }
}

/**
 * Return the product of a matrix and a vector as a vector
 */
void dot_M_V(T_DATA input1[][], int n1, int m1, T_DATA input2[], T_DATA output[]) {
    int i, k;
    for(i = 0; i < n1; i++) {
        output[i] = 0;
        for(k = 0; k < m1; k++) {
            output[i] = output[i] + input1[i][k] * input2[k];
        }
    }
}

T_DATA training_data_X [TRAINING_DATA_LENGTH][INPUT_LENGTH] = {
{5.1,3.5,1.4,0.2},
{4.9,3.0,1.4,0.2},
{4.7,3.2,1.3,0.2},
{4.6,3.1,1.5,0.2},
{5.0,3.6,1.4,0.2},
{5.4,3.9,1.7,0.4},
{4.6,3.4,1.4,0.3},
{5.0,3.4,1.5,0.2},
{4.4,2.9,1.4,0.2},
{4.9,3.1,1.5,0.1},
{5.4,3.7,1.5,0.2},
{4.8,3.4,1.6,0.2},
{4.8,3.0,1.4,0.1},
{4.3,3.0,1.1,0.1},
{5.8,4.0,1.2,0.2},
{5.7,4.4,1.5,0.4},
{5.4,3.9,1.3,0.4},
{5.1,3.5,1.4,0.3},
{5.7,3.8,1.7,0.3},
{5.1,3.8,1.5,0.3},
{5.4,3.4,1.7,0.2},
{5.1,3.7,1.5,0.4},
{4.6,3.6,1.0,0.2},
{5.1,3.3,1.7,0.5},
{4.8,3.4,1.9,0.2},
{5.0,3.0,1.6,0.2},
{5.0,3.4,1.6,0.4},
{5.2,3.5,1.5,0.2},
{5.2,3.4,1.4,0.2},
{4.7,3.2,1.6,0.2},
{4.8,3.1,1.6,0.2},
{5.4,3.4,1.5,0.4},
{5.2,4.1,1.5,0.1},
{5.5,4.2,1.4,0.2},
{4.9,3.1,1.5,0.1},
{5.0,3.2,1.2,0.2},
{5.5,3.5,1.3,0.2},
{4.9,3.1,1.5,0.1},
{4.4,3.0,1.3,0.2},
{5.1,3.4,1.5,0.2},
{5.0,3.5,1.3,0.3},
{4.5,2.3,1.3,0.3},
{4.4,3.2,1.3,0.2},
{5.0,3.5,1.6,0.6},
{5.1,3.8,1.9,0.4},
{4.8,3.0,1.4,0.3},
{5.1,3.8,1.6,0.2},
{4.6,3.2,1.4,0.2},
{5.3,3.7,1.5,0.2},
{5.0,3.3,1.4,0.2},
{7.0,3.2,4.7,1.4},
{6.4,3.2,4.5,1.5},
{6.9,3.1,4.9,1.5},
{5.5,2.3,4.0,1.3},
{6.5,2.8,4.6,1.5},
{5.7,2.8,4.5,1.3},
{6.3,3.3,4.7,1.6},
{4.9,2.4,3.3,1.0},
{6.6,2.9,4.6,1.3},
{5.2,2.7,3.9,1.4},
{5.0,2.0,3.5,1.0},
{5.9,3.0,4.2,1.5},
{6.0,2.2,4.0,1.0},
{6.1,2.9,4.7,1.4},
{5.6,2.9,3.6,1.3},
{6.7,3.1,4.4,1.4},
{5.6,3.0,4.5,1.5},
{5.8,2.7,4.1,1.0},
{6.2,2.2,4.5,1.5},
{5.6,2.5,3.9,1.1},
{5.9,3.2,4.8,1.8},
{6.1,2.8,4.0,1.3},
{6.3,2.5,4.9,1.5},
{6.1,2.8,4.7,1.2},
{6.4,2.9,4.3,1.3},
{6.6,3.0,4.4,1.4},
{6.8,2.8,4.8,1.4},
{6.7,3.0,5.0,1.7},
{6.0,2.9,4.5,1.5},
{5.7,2.6,3.5,1.0},
{5.5,2.4,3.8,1.1},
{5.5,2.4,3.7,1.0},
{5.8,2.7,3.9,1.2},
{6.0,2.7,5.1,1.6},
{5.4,3.0,4.5,1.5},
{6.0,3.4,4.5,1.6},
{6.7,3.1,4.7,1.5},
{6.3,2.3,4.4,1.3},
{5.6,3.0,4.1,1.3},
{5.5,2.5,4.0,1.3},
{5.5,2.6,4.4,1.2},
{6.1,3.0,4.6,1.4},
{5.8,2.6,4.0,1.2},
{5.0,2.3,3.3,1.0},
{5.6,2.7,4.2,1.3},
{5.7,3.0,4.2,1.2},
{5.7,2.9,4.2,1.3},
{6.2,2.9,4.3,1.3},
{5.1,2.5,3.0,1.1},
{5.7,2.8,4.1,1.3},
{6.3,3.3,6.0,2.5},
{5.8,2.7,5.1,1.9},
{7.1,3.0,5.9,2.1},
{6.3,2.9,5.6,1.8},
{6.5,3.0,5.8,2.2},
{7.6,3.0,6.6,2.1},
{4.9,2.5,4.5,1.7},
{7.3,2.9,6.3,1.8},
{6.7,2.5,5.8,1.8},
{7.2,3.6,6.1,2.5},
{6.5,3.2,5.1,2.0},
{6.4,2.7,5.3,1.9},
{6.8,3.0,5.5,2.1},
{5.7,2.5,5.0,2.0},
{5.8,2.8,5.1,2.4},
{6.4,3.2,5.3,2.3},
{6.5,3.0,5.5,1.8},
{7.7,3.8,6.7,2.2},
{7.7,2.6,6.9,2.3},
{6.0,2.2,5.0,1.5},
{6.9,3.2,5.7,2.3},
{5.6,2.8,4.9,2.0},
{7.7,2.8,6.7,2.0},
{6.3,2.7,4.9,1.8},
{6.7,3.3,5.7,2.1},
{7.2,3.2,6.0,1.8},
{6.2,2.8,4.8,1.8},
{6.1,3.0,4.9,1.8},
{6.4,2.8,5.6,2.1},
{7.2,3.0,5.8,1.6},
{7.4,2.8,6.1,1.9},
{7.9,3.8,6.4,2.0},
{6.4,2.8,5.6,2.2},
{6.3,2.8,5.1,1.5},
{6.1,2.6,5.6,1.4},
{7.7,3.0,6.1,2.3},
{6.3,3.4,5.6,2.4},
{6.4,3.1,5.5,1.8},
{6.0,3.0,4.8,1.8},
{6.9,3.1,5.4,2.1},
{6.7,3.1,5.6,2.4},
{6.9,3.1,5.1,2.3},
{5.8,2.7,5.1,1.9},
{6.8,3.2,5.9,2.3},
{6.7,3.3,5.7,2.5},
{6.7,3.0,5.2,2.3},
{6.3,2.5,5.0,1.9},
{6.5,3.0,5.2,2.0},
{6.2,3.4,5.4,2.3},
{5.9,3.0,5.1,1.8}
}

T_DATA training_data_Y [TRAINING_DATA_LENGTH] = {
{0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2
}

T_DATA training_data_X_transpose[INPUT_LENGTH][TRAINING_DATA_LENGTH];
T_DATA W[INPUT_LENGTH] = {
    0.5,
    0.5,
    0.5,
    0.5};
T_DATA pred[TRAINING_DATA_LENGTH];
T_DATA pred_error[TRAINING_DATA_LENGTH];
T_DATA pred_delta[TRAINING_DATA_LENGTH];
T_DATA W_delta[INPUT_LENGTH];
T_DATA aux1[TRAINING_DATA_LENGTH];
T_DATA aux2[TRAINING_DATA_LENGTH];
 
T_DATA test_data_X[2][4] = {{5.4,3.7,1.5,0.2},{5.4,3.7,1.5,0.2}};
int main(void) {
    int index;
    transpose(training_data_X, TRAINING_DATA_LENGTH, TRAINING_DATA_LENGTH, training_data_X_transpose);
    for (index = 0; index < MAX_ITERATIONS; index++) {
        dot_M_V(training_data_X, TRAINING_DATA_LENGTH, INPUT_LENGTH, W, aux2);
        sigmoid(aux2, TRAINING_DATA_LENGTH, pred );
        difference(y, pred, TRAINING_DATA_LENGTH, pred_error);
        sigmoid_d(pred, TRAINING_DATA_LENGTH, aux1);
        multiply(pred_error, aux1, TRAINING_DATA_LENGTH, pred_delta);
        dot_M_V(training_data_X_transpose, INPUT_LENGTH, TRAINING_DATA_LENGTH, pred_delta, W_delta);
        sum(W, W_delta, INPUT_LENGTH, W);
    };
    dot_M_V(test_X, 1, INPUT_LENGTH, W, aux2);
    sigmoid(aux2, 1, pred);
    //pred[0] - asnwer
    return 0;
}
