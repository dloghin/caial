//CT
// https://www.geeksforgeeks.org/decision-tree-introduction-example/

#include <stdlib.h>
#include "util.h"

double gini_gain (int a, int b) {
    double aux_a = a;
    double aux_b = b;
    return (aux_a/(aux_a+aux_b))*(aux_a/(aux_a+aux_b))+(aux_b/(aux_a+aux_b))*(aux_b/(aux_a+aux_b));
}

void creating_tree(int index,int atr_index[15], int atr_value[15], int class[15], int indepedent[6][4], int dependent[6],
                int n,int atr_remained[4]) {
    int i,j;
    int local_atrr_remained[4];
    int local_indepedent[6][4];
    int local_depedent[6];
    int poz;
    double value;
    double mean;
    double min;
    int count_g_p;
    int count_g_n;
    int count_l_p;
    int count_l_n;
    double g1;
    double g2;
    double g;
    int k;

    int sum = 0;

    //verificare daca avem aceeasi clasa
    for(i = 0; i < n; i++) {
        sum = sum + dependent[i];
    }
    if(sum == 0 || sum == n) {
        class[index] = dependent[0];
        return;
    }

    int sem = 0;
    //verificare daca nu mai avem atribute
    for( j = 0; j < 4; j++) {
        if(atr_remained[j]) {
            sem = 1;
        }
    }

    if (sem == 0) {
        count_g_p = 0;
        count_g_n = 0;
        for(i = 0; i < n; i++) {
            if(dependent[i] > 0) {
                count_g_p = count_g_p + 1;
            } else {
                count_g_n = count_g_n + 1;
            }
        }
        if (count_g_p >= count_g_n) {
            class[index] = 1;
        } else {
            class[index] = 0;
        }
        return;
    }

    //procesare nod curent
    poz = -1;
    min = 2;
    for( j = 0; j < 4; j++) {
        if(atr_remained[j]) {
            mean = 0;
            for(i = 0; i < n; i++) {
                mean = mean + indepedent[i][j];
            }
            mean = mean / n;
            count_g_p = 0;
            count_g_n = 0;
            count_l_p = 0;
            count_l_n = 0;
            for(i = 0; i < n; i++) {
                if(indepedent[i][j] >= mean) {
                    if(dependent[i] > 0) {
                        count_g_p = count_g_p + 1;
                    } else {
                        count_g_n = count_g_n + 1;
                    }
                } else {
                    if(dependent[i] > 0) {
                        count_l_p = count_l_p + 1;
                    } else {
                        count_l_n = count_l_n + 1;
                    }
                }
            }
            g1 = gini_gain(count_g_p, count_g_n);
            g2 = gini_gain(count_l_p, count_l_n);
            g = (count_g_p + count_g_n) * g1 / n + (count_l_p + count_l_n) * g2 / n;
            if (g < min) {
                min = g;
                poz = j;
            }
        }
    }
    
    mean = 0;
    for(i = 0; i < n; i++) {
        mean = mean + indepedent[i][poz];
    }
    mean = mean / n;

    atr_index[index] = poz;
    atr_value[index] = mean;


    for(i = 0; i < 4; i++) {
        local_atrr_remained[i] = atr_remained[i];
    }
    local_atrr_remained[poz] = 0;

    //do the right node
    k = 0;
    for(i = 0; i < n; i++) {
        if(indepedent[i][poz] >= mean) {
            for(j = 0; j < 4; j++) {
                local_indepedent[k][j] = local_indepedent[i][j];
            }
            local_depedent[k] = dependent[i];
            k = k + 1;
        }
    }
    creating_tree(index*2+2,atr_index, atr_value, class, local_indepedent, local_depedent, k, local_atrr_remained);

    //do the left node
    k = 0;
    for(i = 0; i < n; i++) {
        if(indepedent[i][poz] < mean) {
            for(j = 0; j < 4; j++) {
                local_indepedent[k][j] = local_indepedent[i][j];
            }
            local_depedent[k] = dependent[i];
            k = k + 1;
        }
    }
    creating_tree(index*2+1,atr_index, atr_value, class, local_indepedent, local_depedent, k, local_atrr_remained);
            
}


int classify_test_data(int index,int atr_index[15], int atr_value[15], int class[15], int test_data[4]) {
    if(class[index] != -1) {
        return class[index];
    }
    if(test_data[atr_index[index]] >= atr_value[index]) {
        return classify_test_data( 2*index + 2, atr_index, atr_value, class, test_data);
    } else {
        return classify_test_data( 2*index + 1, atr_index, atr_value, class, test_data);
    }
}


int main(void)
{
    int atr_index[15] = {
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1
    };
    int atr_value[15] = {
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1
    };
    int class[15] = {
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1,-1,
        -1,-1,-1
    };
    int atr_remained[4] = {
        1, 1, 1, 1
    };
    int n = 6;
    int m = 5;
    int indepedent [6][4] = {
        {0,0,1,0},
        {1,0,1,1},
        {1,1,0,1},
        {0,0,0,1},
        {1,0,0,1},
        {1,0,1,0}
    };
    int dependent[6] = {
        0,0,0,0,1,1
    };
    int test_data[4] = {0,0,0,1};
    
    creating_tree( 0, atr_index, atr_value, class, indepedent, dependent, n, atr_remained);
    int b = classify_test_data(0, atr_index, atr_value, class, test_data);
    return 0;
}
