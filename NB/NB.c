//NB
// https://msdn.microsoft.com/en-us/magazine/jj891056.aspx
// https://www.machinelearningplus.com/predictive-modeling/how-naive-bayes-algorithm-works-with-example-and-full-code/

#include <stdlib.h>
#include "util.h"


#define TRAINING_DATA_LENGTH 150
#define INPUT_LENGTH 4
#define K_VALUE 5
#define C_VALUE 3

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

int training_data_Y [TRAINING_DATA_LENGTH] = {
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

T_DATA test_data[INPUT_LENGTH] = {5.4,3.7,1.5,0.2};

int training_data_X_BNB [TRAINING_DATA_LENGTH][INPUT_LENGTH];
int test_data_BNB[INPUT_LENGTH]
int joints[INPUT_LENGTH][K_VALUE][C_VALUE];
int dep_joints[C_VALUE];
T_DATA partial_probability[C_VALUE];
T_DATA probability[C_VALUE];

void calculate_inital_part() {
    int index, jindex, kindex;
    T_DATA mins [INPUT_LENGTH];
    T_DATA maxs [INPUT_LENGTH];
    T_DATA values [INPUT_LENGTH][K_VALUE];
    
    for(index = 0; index < INPUT_LENGTH; index++) {
        mins[index] = training_data_X[0][index];
        maxs[index] = training_data_X[0][index];
    }

    for(jindex = 1; jindex < TRAINING_DATA_LENGTH; jindex++) {
        for(index = 0; index < INPUT_LENGTH; index++) {
            if(mins[index] > training_data_X[jindex][index]) {
                mins[index] = training_data_X[jindex][index];
            }
            if(maxs[index] < training_data_X[jindex][index]) {
                maxs[index] = training_data_X[jindex][index];
            }
        }
    }

    for(index = 0; index < INPUT_LENGTH; index++) {
        for(kindex = 0; kindex < K_VALUE; kindex++) {
            values[index][kindex] = mins[index] + ((maxs[index] - mins[index]) * (kindex+1)) / K_VALUE;
        }
    }


    for(jindex = 0; jindex < TRAINING_DATA_LENGTH; jindex++) {
        for(index = 0; index < INPUT_LENGTH; index++) {
            for(kindex = 0; kindex < K_VALUE; kindex++) {
                if(training_data_X[jindex][index] <= values[index][kindex]) {
                    training_data_X_BNB[jindex][index] = kindex;
                    break;
                }
            }
        }
    }


    for(index = 0; index < INPUT_LENGTH; index++) {
        for(kindex = 0; kindex < K_VALUE; kindex++) {
            if(test_data[index] <= values[index][kindex]) {
                test_data_BNB[index] = kindex;
                break;
            }
        }
    }
}

int main(void)
{
    calculate_inital_part();
    int index, jidnex, kindex, vindex;
    int pindex;
    for(index = 0; index < INPUT_LENGTH; index++) {
        for(kindex = 0; kindex < K_VALUE; kindex++) {
            for(vindex = 0; vindex < C_VALUE; vindex++) {
                joints[index][kindex][vindex] = 0;
            }
        }
    }

    for(jindex = 0; jindex < TRAINING_DATA_LENGTH; jindex++) {
        for(index = 0; index < INPUT_LENGTH; index++) {
            for(kindex = 0; kindex < K_VALUE; kindex++) {
                for(vindex = 0; vindex < C_VALUE; vindex++) {
                    if(training_data_Y[jidnex] == vindex && training_data_X_BNB[jidnex][index] == kindex) {
                        joints[index][kindex][vindex] = joints[index][kindex][vindex] + 1;
                    }
                }
            }
        }
    }


    for(vindex = 0; vindex < C_VALUE; vindex++) {
        dep_joints[vindex] = 0;
    }
    for(jindex = 0; jindex < TRAINING_DATA_LENGTH; jindex++) {
        for(vindex = 0; vindex < C_VALUE; vindex++) {
            if(training_data_Y[jidnex] == vindex) {
                dep_joints[vindex] = dep_joints[vindex] + 1;
            }
        }
    }


    for(pindex = 0; pindex < C_VALUE; pindex++) {
        partial_probability[pindex] = 1;
    }

    T_DATA total_sum = 0;
    for(index = 0; index < INPUT_LENGTH; index++) {
        for(pindex = 0; pindex < C_VALUE; pindex++) {
            partial_probability[pindex] = partial_probability[pindex]
            * joints[index][test_data_BNB[index]][pindex] / dep_joints[pindex];
        }
    }
    for(pindex = 0; pindex < C_VALUE; pindex++) {
        total_sum = total_sum + dep_joints[pindex];
    }
    for(pindex = 0; pindex < C_VALUE; pindex++) {
        partial_probability[pindex] = partial_probability[pindex]
        * dep_joints[pindex] / total_sum;
    }
    total_sum = 0;
    for(pindex = 0; pindex < C_VALUE; pindex++) {
        total_sum = total_sum + partial_probability[pindex];
    }
    for(pindex = 0; pindex < C_VALUE; pindex++) {
        probability[pindex] = partial_probability[pindex] / total_sum;
    }
    
    T_DATA max_p = probability[0];
    int poz = 0;
    for(pindex = 1; pindex < C_VALUE; pindex++) {
        if(probability[pindex] > max_p) {
            max_p = probability[pindex];
            poz = pindex;
        }
    }
    
    return 0;
}
