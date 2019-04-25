//DNN
// https://cognitivedemons.wordpress.com/2017/07/06/a-neural-network-in-10-lines-of-c-code/
// https://www.geeksforgeeks.org/program-to-efficiently-calculate-ex/

#include <stdlib.h>
#include "util.h"


void sigmoid_d (double input[], int n, double output[]) {
    /*  Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)), 
        where f(x) is sigmoid function.
        Input: input, a vector.
        Output: x(1 - x) for every element of the input vector input.
    */
    int i;
    for (i = 0; i < n; i++) {
        output[i] = input[i] * (1 - input[i]);
    }
}

// Returns approximate value of e^x 
// using sum of first n terms of Taylor Series 
double exponential(int n, double x) 
{ 
	double sum = 1.0; // initialize sum of series 
    int i;
	for (i = n - 1; i > 0; --i ) 
		sum = 1 + x * sum / i; 

	return sum; 
}

void sigmoid (double input[], int n, double output[]) {
    /*  Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
        Input: input, a vector.
        Output: 1/(1 + e^-x) for every element of the input vector input.
    */
    
    int i;
    for (i = 0; i < n; i++) {
        output[i] = 1 / (1 + exponential(50,-input[i]));
    }
}


void sum (double input1[], double input2[], int n, double output[]) {
    /*  Returns the elementwise sum of two vectors.
        Inputs: 
            input1: a vector
            input2: a vector
        Output: a vector, sum of the vectors input1 and input2.
    */
    int i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] + input2[i];
    }
}

void difference (double input1[], double input2[], int n, double output[]) {
    /*  Returns the elementwise difference of two vectors.
        Inputs: 
            input1: a vector
            input2: a vector
        Output: a vector, difference of the vectors input1 and input2.
    */
    int i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] - input2[i];
    }
}

void multiply (double input1[], double input2[], int n, double output[]) {
    /*  Returns the elementwise multiplication of two vectors.
        Inputs: 
            input1: a vector
            input2: a vector
        Output: a vector, product of the vectors input1 and input2.
    */
    int i;
    for (i = 0; i < n; i++) {
        output[i] = input1[i] * input2[i];
    }
}

void transpose(double input[][4], int n, int m, double output[][4]) {
    /*  Returns a transpose matrix of input matrix.
        Inputs:
            input: input matrix
            n: int, number of columns in the input matrix
            m: int, number of rows in the input matrix
        Output: transpose matrix of input matrix
    */
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            output[i][j] = input[j][i];
        }
    }
}

    /*
vector <float> dot (const vector <float>& m1, const vector <float>& m2, const int m1_rows, const int m1_columns, const int m2_columns) {
    
    /*  Returns the product of two matrices: m1 x m2.
        Inputs:
            m1: vector, left matrix of size m1_rows x m1_columns
            m2: vector, right matrix of size m1_columns x m2_columns (the number of rows in the right matrix 
                must be equal to the number of the columns in the left one)
            m1_rows: int, number of rows in the left matrix m1
            m1_columns: int, number of columns in the left matrix m1
            m2_columns: int, number of columns in the right matrix m2
        Output: vector, m1 * m2, product of two vectors m1 and m2, a matrix of size m1_rows x m2_columns
    
    
    vector <float> output (m1_rows*m2_columns);
    
    for( int row = 0; row != m1_rows; ++row ) {
        for( int col = 0; col != m2_columns; ++col ) {
            output[ row * m2_columns + col ] = 0.f;
            for( int k = 0; k != m1_columns; ++k ) {
                output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
            }
        }
    }
    
    return output;
}*/

//return de product of a matrix and a vector as a vector
void dot_M_V(double input1[][4], int n1, int m1, double input2[], double output[]) {
    int i, k;
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
