// MM
// https://msdn.microsoft.com/en-us/magazine/jj891056.aspx
// https://www.machinelearningplus.com/predictive-modeling/how-naive-bayes-algorithm-works-with-example-and-full-code/

#include <stdlib.h>
#include "util.h"


#define T_DATA float
#define DATA_LENGTH 10


T_DATA matrix1[DATA_LENGTH][DATA_LENGTH] = {
    {1, 1, 1, 1}, 
    {2, 2, 2, 2}, 
    {3, 3, 3, 3}, 
    {4, 4, 4, 4}
}; 
T_DATA matrix2[DATA_LENGTH][DATA_LENGTH] = {
    {1, 1, 1, 1}, 
    {2, 2, 2, 2}, 
    {3, 3, 3, 3}, 
    {4, 4, 4, 4}
}; 
T_DATA result_matrix[DATA_LENGTH][DATA_LENGTH];

int main(void)
{
    int index,jindex,kindex;
    T_DATA aux;
    for(index = 0; index < DATA_LENGTH; index++) {
        for(jindex = 0; jindex < DATA_LENGTH; jindex++) {
            aux = 0;
            for(kindex = 0; kindex < DATA_LENGTH; kindex++) {
                aux = aux + matrix1[index][kindex]*matrix2[kindex][jindex];
            }
            result_matrix[index][jindex] = aux;
        }
    }
    return 0;
}
