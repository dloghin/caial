//DNN
// https://cognitivedemons.wordpress.com/2017/07/06/a-neural-network-in-10-lines-of-c-code/
// https://www.geeksforgeeks.org/program-to-efficiently-calculate-ex/

#include "../common/common.h"

#define MDIM 4

/**
 * Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)),
 * where f(x) is sigmoid function.
 * Input: input, a vector.
 * Output: x(1 - x) for every element of the input vector input.
 */
void sigmoid_d(element_t input[], size_t n, element_t output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = input[i] * (1 - input[i]);
    }
}

/**
 * Returns approximate value of e^x
 * using sum of first n terms of Taylor Series
 */
double exponential(int n, double x) {
	double sum = 1.0; // initialize sum of series 
    int i;
	for (i = n - 1; i > 0; --i ) 
		sum = 1 + x * sum / i; 

	return sum; 
}

/**
 * Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
 * Input: input, a vector.
 * Output: 1/(1 + e^-x) for every element of the input vector input.
 */
void sigmoid(element_t input[], size_t n, element_t output[]) {
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
void sum(element_t input1[], element_t input2[], size_t n, element_t output[]) {
    size_t i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] + input2[i];
    }
}

/**
 * Returns the elementwise difference of two vectors.
 * Inputs:
 *  input1: a vector
 *  input2: a vector
 * Output: a vector, difference of the vectors input1 and input2.
 */
void difference(element_t input1[], element_t input2[], size_t n, element_t output[]) {
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
void multiply(element_t input1[], element_t input2[], size_t n, element_t output[]) {
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
void transpose(element_t input[][4], size_t n, size_t m, element_t output[][4]) {
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
void dot_M_V(element_t input1[][MDIM], size_t n1, size_t m1, element_t input2[], element_t output[]) {
    size_t i, k;
    for(i = 0; i < n1; i++) {
        output[i] = 0;
        for(k = 0; k < m1; k++) {
            output[i] = output[i] + input1[i][k] * input2[k];
        }
    }
}


int main(void) {
    
    double X[4][4] = {
        5.1, 3.5, 1.4, 0.2,
        4.9, 3.0, 1.4, 0.2,
        6.2, 3.4, 5.4, 2.3,
        5.9, 3.0, 5.1, 1.8
    };
    double XT[4][4] = {
        5.1, 3.5, 1.4, 0.2,
        4.9, 3.0, 1.4, 0.2,
        6.2, 3.4, 5.4, 2.3,
        5.9, 3.0, 5.1, 1.8
    };
    double y[4] = {
        0,
        0,
        1,
        1 };
    double W[4] = {
        0.5,
        0.5,
        0.5,
        0.5};
    int i;
    double pred[4] = {
        0,
        0,
        0,
        0 };
    double pred_error[4] = {
        0,
        0,
        0,
        0 };
    double pred_delta[4] = {
        0,
        0,
        0,
        0 };
    double W_delta[4] = {
        0,
        0,
        0,
        0 };
    double aux1[4] = {
        0,
        0,
        0,
        0 };
    double aux2[4] = {
        0,
        0,
        0,
        0 };

    for (i = 0; i != 50; ++i) {
        dot_M_V(X, 4, 4, W, aux2);
        sigmoid(aux2, 4, pred );
        difference(y, pred, 4, pred_error);
        sigmoid_d(pred, 4, aux1);
        multiply(pred_error, aux1, 4, pred_delta);
        transpose(X,4,4,XT);
        dot_M_V(XT, 4, 4, pred_delta, W_delta);
        sum(W, W_delta, 4, W);
    };

    return 0;
}
