//SVM-SMO
// http://cs229.stanford.edu/materials/smo.pdf

#include <stdlib.h>
#include "util.h"


double inner_product (double a_px, double a_py, double b_px, double b_py) {
    double sum;
    sum = a_px + b_px + a_py * b_py;
    return sum;
}

double kernel_function (double a_px, double a_py, double b_px, double b_py) {
    return inner_product (a_px, a_py, b_px, b_py);
}

double svm_function (double t_px, double t_py, double alphas[8], double px[8], double py[8], double y[8], double b, int m) {
    int i;
    double sum = 0;
    for( i = 0; i < m; i++) {
        sum = sum + alphas[i] * y[i] * kernel_function(px[i], py[i], t_px, t_py) + b;
    }
    return sum;
}

int my_random (int i, int j, int m) {
    int a;
    a = (j + 1) % m;
    if (a == i) {
        return (i,a);
    }
    if (a == j) {
        return (i, a);
    }
}


int main(void)
{
    int m = 8;
    double px[8] = {1,1.5,2,3,5,6,6.5,7};
    double py[8] = {1,3.5,3,2,3,5,4,3};
    double y[8] = {-1,-1,-1,-1,1,1,1,1};
	double C = 100;
	double tol = 1;
    int max_passes = 15;
    double alphas[8] = {0,0,0,0,0,0,0,0};
    double E[8] = {0,0,0,0,0,0,0,0};
    double b = 0;
    int passes = 0;
    int num_changed_alphas = 0;
    int i, j;
    i = 0;
    j = 0;
    double old_alpha_i;
    double old_alpha_j;
    double L, H;
    double miu;
    double b1, b2;
    while ( passes < max_passes ) {
        num_changed_alphas = 0;
        for ( i = 0; i <  m; i++) {
            E[i] = svm_function(px[i],py[i], alphas, px, py, y, b, m) - y[i];
            if (
                ( (y[i] * E[i] < -tol) && (alphas[i] < C) ) ||
                ( (y[i] * E[i] > tol) && (alphas[i] > 0) )
            ) {
                //TODO: select j random
                j = my_random(i,j, m);
                E[j] = svm_function(px[j],py[j], alphas, px, py, y, b, m) - y[j];
                old_alpha_i = alphas[i];
                old_alpha_j = alphas[j];
                if(y[i] != y[j]) {
                    L = ( (alphas[j] - alphas[i]) > 0) ? alphas[j] - alphas[i] : 0;
                    H = ( C < (C + alphas[j] - alphas[i]) ) ? C : C + alphas[j] - alphas[i];
                } else {
                    L = ( (alphas[j] + alphas[i] - C) > 0) ? alphas[j] + alphas[i] - C : 0;
                    H = ( C < (alphas[j] + alphas[i]) ) ? C : alphas[j] + alphas[i];
                }
                if (L == H) {
                    continue;
                }
                miu = 2 * kernel_function(px[i], py[i], px[j], py[j]) - kernel_function(px[i], py[i], px[i], py[i]) - kernel_function(px[j], py[j], px[j], py[j]);
                if (miu >= 0) {
                    continue;
                }
                alphas[j] = alphas[j] - (y[i] * (E[i] - E[j])) / miu;
                alphas[j] = (alphas[j] > H) ? H : (
                            (alphas[j] < L) ? L : alphas[j]);
                if (
                    ((alphas[j] - old_alpha_j) < 0.00001) ||
                    ((alphas[j] - old_alpha_j) > -0.00001)
                ) {
                    continue;
                }
                alphas[i] = alphas[i] + y[i] * y[j] * (old_alpha_j - alphas[j]);
                b1 = b - E[i] - y[i] * (alphas[i] - old_alpha_i) * kernel_function(px[i], py[i], px[i], py[i]) -
                    y[j] * (alphas[j] - old_alpha_j) * kernel_function(px[i], py[i], px[j], py[j]);
                b2 = b - E[j] - y[i] * (alphas[i] - old_alpha_i) * kernel_function(px[i], py[i], px[j], py[j]) -
                    y[j] * (alphas[j] - old_alpha_j) * kernel_function(px[j], py[j], px[j], py[j]);
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
