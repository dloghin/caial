//NB
// https://msdn.microsoft.com/en-us/magazine/jj891056.aspx
// https://www.machinelearningplus.com/predictive-modeling/how-naive-bayes-algorithm-works-with-example-and-full-code/

#include <stdlib.h>
#include "util.h"



int main(void)
{
    int n = 6;
    int m = 5;
    int indepedent [6][4] = {
        {0,0,1,0},
        {1,0,1,1},
        {1,1,2,1},
        {0,0,0,1},
        {1,0,0,1},
        {1,0,1,0}
    };
    int nr_dif_values[5] = {
        2, 2, 3, 2, 2
    };
    int dependent[6] = {
        0,0,0,0,1,1
    };
    int joints [4][3][2];
    int i,j,k,l;
    for (i = 0; i < 4; i++) {
        for(j = 0; j < 3; j++) {
            for(k = 0; k < 2; k++) {
                joints [i][j][k] = 0;
                for(l = 0; l < n; l++) {
                    if(dependent[l] == k && indepedent[l][i] == j) {
                        joints [i][j][k] = joints [i][j][k] + 1;
                    }
                }
            }
        }
    }
    int dep_joints[2] = {0, 0};
    for (i = 0; i < 2; i++) {
        for(l = 0; l < n; l++) {
            if(dependent[l] == i) {
                dep_joints[i] = dep_joints[i] + 1;
            }
        }
    }
    int test_data[5] = {0,0,0,1,0};
    double pp_1 = 1;
    double pp_2 = 1;
    for(i = 0; i < 4; i++) {
        pp_1 = pp_1 * joints[i][test_data[i]][test_data[4]] / dep_joints[test_data[4]];
        pp_2 = pp_2 * joints[i][test_data[i]][1-test_data[4]] / dep_joints[1-test_data[4]];
    }
    pp_1 = pp_1 * dep_joints[test_data[4]] / (dep_joints[test_data[4]] + dep_joints[1-test_data[4]]);
    pp_2 = pp_2 * dep_joints[1-test_data[4]] / (dep_joints[test_data[4]] + dep_joints[1-test_data[4]]);
    double p;
    p = pp_1 / (pp_1 + pp_2);
    return 0;
}
