// KMEANS
// https://www.geeksforgeeks.org/k-means-clustering-introduction/
// training data: https://github.com/antmarakis/Machine-Learning/blob/master/Clustering/kMeans%20-%20Standard/data.txt

#include <stdlib.h>
#include "util.h"

#define T_DATA float
#define TRAINING_DATA_LENGTH 150
#define INPUT_LENGTH 4
#define K_VALUE 7
#define MAX_ITERATIONS 40

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

int training_position_cluster[TRAINING_DATA_LENGTH];
//cluster
T_DATA cluster_mean[K_VALUE][INPUT_LENGTH];
int cluster_len[K_VALUE];

T_DATA euclidian_distance (T_DATA X[INPUT_LENGTH], T_DATA Y[INPUT_LENGTH]) {
    int index;
    T_DATA sum 0.0;
    for(index = 0; index < INPUT_LENGTH; index++) {
        sum = sum + (X[index]-Y[index])*(X[index]-Y[index]);
    }
    return sum;
}

void calculate_inital_means() {
    int index, jindex, kindex;
    T_DATA mins [INPUT_LENGTH];
    T_DATA maxs [INPUT_LENGTH];
    
    for(index = 0; index < INPUT_LENGTH; index++) {
        mins[index] = training_data_X[0][index];
        maxs[index] = training_data_X[0][index];
    }

    for(jindex = 1; jindex < TRAINING_DATA_LENGTH; jindex++) {
        training_position_cluster[jindex] = -1;
        for(index = 0; index < INPUT_LENGTH; index++) {
            if(mins[index] > training_data_X[jindex][index]) {
                mins[index] = training_data_X[jindex][index];
            }
            if(maxs[index] < training_data_X[jindex][index]) {
                maxs[index] = training_data_X[jindex][index];
            }
        }
    }

    for(kindex = 0; kindex < K_VALUE; kindex++) {
        cluster_len[kindex] = 0;
        for(index = 0; index < INPUT_LENGTH; index++) {
            cluster_mean[kindex][index] = mins[index] + (maxs[index] - mins[index]) * kindex / K_VALUE;
        }
    }
}

int classify_cluster(T_DATA X[INPUT_LENGTH]) {
    int kindex;
    float min = euclidian_distance(X, cluster_mean[0]);
    float aux;
    int return_index = 0;
    for(kindex = 1; kindex < K_VALUE; kindex++) {
        aux = euclidian_distance(X, cluster_mean[kindex]);
        if(min > aux) {
            min = aux;
            return_index = kindex;
        }
    }
    return return_index;
}

void update_mean_minus(T_DATA X[INPUT_LENGTH], int kindex) {
    int index;
    for(index = 0; index < INPUT_LENGTH; index++) {
        cluster_mean[kindex][index] = (cluster_mean[kindex][index] * cluster_len[kindex] - X[index]) / (cluster_len[kindex] - 1);
    }
    cluster_len[kindex] = cluster_len[kindex] - 1;
}


void update_mean_plus(T_DATA X[INPUT_LENGTH], int kindex) {
    int index;
    for(index = 0; index < INPUT_LENGTH; index++) {
        cluster_mean[kindex][index] = (cluster_mean[kindex][index] * cluster_len[kindex] + X[index]) / (cluster_len[kindex] + 1);
    }
    cluster_len[kindex] = cluster_len[kindex] + 1;
}

void creating_clusters() {
    int index, jindex, kindex, old_kindex;
    int has_changed;
    int rindex;
    calculate_inital_means();
    for(rindex = 0; rindex < MAX_ITERATIONS; rindex++) {
        has_changed = 0;
        for(jindex = 0; jindex < TRAINING_DATA_LENGTH; jindex++) {
            old_kindex = training_position_cluster[jindex];
            kindex = classify_cluster(X);
            if(kindex != old_kindex) {
                if(old_kindex != -1) {
                    update_mean_minus(training_data_X[jindex], old_kindex);
                }
                update_mean_plus(training_data_X[jindex], kindex);
                training_position_cluster[jindex] = kindex;
                has_changed = 1;
            }
        }
        if(has_changed == 0) {
            break;
        }
    }
}


int main(void)
{
    T_DATA test_data[INPUT_LENGTH] = {5.4,3.7,1.5,0.2};
    creating_clusters();
    int b = classify_cluster(test_data);
    return 0;
}
