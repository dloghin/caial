//LR
// http://www.code-in-c.com/linear-regression-fitting-a-line-to-data/

#include <stdlib.h>
#include "util.h"

//--------------------------------------------------------
// FUNCTION arithmetic_mean
//--------------------------------------------------------
double arithmetic_mean(double* data, int size)
{
    double total = 0;

    // note that incrementing total is done within the for loop
    for(int i = 0; i < size; total += data[i], i++);

    return total / size;
}

//--------------------------------------------------------
// FUNCTION mean_of_products
//--------------------------------------------------------

double mean_of_products(double* data1, double* data2, int size)
{
    double total = 0;

    // note that incrementing total is done within the for loop
    for(int i = 0; i < size; total += (data1[i] * data2[i]), i++);

    return total / size;
}

//--------------------------------------------------------
// FUNCTION variance
//--------------------------------------------------------
double variance(double* data, int size)
{
    double squares[size];

    for(int i = 0; i < size; i++)
    {
        squares[i] = data[i] * data[i];
    }

    double mean_of_squares = arithmetic_mean(squares, size);
    double mean = arithmetic_mean(data, size);
    double square_of_mean = mean * mean;
    double variance = mean_of_squares - square_of_mean;

    return variance;
}

void linear_regression(double* independent, double* dependent, int size, double* a, double *b)
{
    double independent_mean = arithmetic_mean(independent, size);
    double dependent_mean = arithmetic_mean(dependent, size);
    double products_mean = mean_of_products(independent, dependent, size);
    double independent_variance = variance(independent, size);

    *a = (products_mean - (independent_mean * dependent_mean) ) / independent_variance;

    *b = dependent_mean - (*a * independent_mean);
}



int main(void)
{
    double independent[8] = {10,20,40,45,60,65,75,80};
    double dependent[8] = {32,44,68,74,92,98,110,116};
	double a;
	double b;

	linear_regression(independent, dependent, 8, &a, &b);


    return 0;
}
