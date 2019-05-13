//SVM-SMO
// http://cs229.stanford.edu/materials/smo.pdf

#include <stdlib.h>
#include "util.h"


#define TRAINING_DATA_LENGTH 150
#define INPUT_LENGTH 4
#define K_VALUE 7
#define MAX_ITERATIONS 15

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

T_DATA alphas[TRAINING_DATA_LENGTH];

void initialize() {
    int indexl
    for(index = 0; index < TRAINING_DATA_LENGTH; index++) {
        alphas[index] = 0;
        training_data_Y[index] = training_data_Y[index] + 1; //0 not ok for the algorithm
    }
}

T_DATA inner_product (T_DATA X[], T_DATA Y[]) {
    int index;
    T_DATA sum = 0;
    for(index = 0; index < INPUT_LENGTH; index++) {
        sum = sum + X[index] * Y[index];
    }
    return sum;
}

T_DATA kernel_function (T_DATA X[], T_DATA Y[]) {
    return inner_product (X, Y);
}

T_DATA svm_function (T_DATA t_X[], T_DATA alphas[], T_DATA b) {
    int index;
    T_DATA sum = 0;
    for( i = 0; i < TRAINING_DATA_LENGTH; i++) {
        sum = sum + alphas[i] * training_data_Y[i] * kernel_function(training_data_X[i], t_X) + b;
    }
    return sum;
}

int my_random (int i, int j, int m) {
    int a;
    a = (j + 1) % m;
    if (a == i) {
        return my_random(i,a,m);
    }
    return a;
}


int main(void)
{
    int m = 8;
	T_DATA C = 100;
	T_DATA tol = 1;
    T_DATA b = 0;
    T_DATA E_i;
    T_DATA E_j;
    int passes = 0;
    int num_changed_alphas = 0;
    int i, j;
    T_DATA old_alpha_i;
    T_DATA old_alpha_j;
    T_DATA L, H;
    T_DATA miu;
    T_DATA b1, b2;
    while (passes < MAX_ITERATIONS) {
        num_changed_alphas = 0;
        for (i = 0; i <  m; i++) {
            E_i = svm_function(training_data_X[i], alphas, b) - training_data_Y[i];
            if (
                ( (training_data_Y[i] * E_i < -tol) && (alphas[i] < C) ) ||
                ( (training_data_Y[i] * E_i > tol) && (alphas[i] > 0) )
            ) {
                //TODO: select j random
                j = my_random(i,j, m);
                E_j = svm_function(training_data_X[j], alphas, b) - training_data_Y[j];
                old_alpha_i = alphas[i];
                old_alpha_j = alphas[j];
                if(training_data_Y[i] != training_data_Y[j]) {
                    L = ( (alphas[j] - alphas[i]) > 0) ? alphas[j] - alphas[i] : 0;
                    H = ( C < (C + alphas[j] - alphas[i]) ) ? C : C + alphas[j] - alphas[i];
                } else {
                    L = ( (alphas[j] + alphas[i] - C) > 0) ? alphas[j] + alphas[i] - C : 0;
                    H = ( C < (alphas[j] + alphas[i]) ) ? C : alphas[j] + alphas[i];
                }
                if (L == H) {
                    continue;
                }
                miu = 2 * kernel_function(training_data_X[i], training_data_X[j])
                 - kernel_function(training_data_X[i], training_data_X[i])
                  - kernel_function(training_data_X[j], training_data_X[j]);
                if (miu >= 0) {
                    continue;
                }
                alphas[j] = alphas[j] - (training_data_Y[i] * (E_i - E_j)) / miu;
                alphas[j] = (alphas[j] > H) ? H : (
                            (alphas[j] < L) ? L : alphas[j]);
                if (
                    ((alphas[j] - old_alpha_j) < 0.00001) ||
                    ((alphas[j] - old_alpha_j) > -0.00001)
                ) {
                    continue;
                }
                alphas[i] = alphas[i] + training_data_Y[i] * training_data_Y[j] * (old_alpha_j - alphas[j]);
                b1 = b - E_i - training_data_Y[i] * (alphas[i] - old_alpha_i) * kernel_function(training_data_X[i], training_data_X[i]) -
                    training_data_Y[j] * (alphas[j] - old_alpha_j) * kernel_function(training_data_X[i], training_data_X[j]);
                b2 = b - E_j - training_data_Y[i] * (alphas[i] - old_alpha_i) * kernel_function(training_data_X[i], training_data_X[j]) -
                    training_data_Y[j] * (alphas[j] - old_alpha_j) * kernel_function(training_data_X[j], training_data_X[j]);
                if (
                    (alphas[i] > 0) &&
                    (alphas[i] < C)
                ) {
                    b = b1;
                } else {
                    if (
                        (alphas[j] > 0) &&
                        (alphas[j] < C)
                    ) {
                        b = b2;
                    } else {
                        b = (b1+b2)/2;
                    }
                }
                num_changed_alphas = num_changed_alphas + 1;
            }
        }
        if (num_changed_alphas == 0) {
            passes = passes + 1;
        } else {
            passes = 0;
        }
    }
    
    return 0;
}
