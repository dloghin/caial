//KNN
// https://www.geeksforgeeks.org/k-nearest-neighbours/

#include "../common/common.h"

#define TRAINING_DATA_LENGTH 17

/* Classify a point by having as
Training data points with
x - x value
y - y value
val - valut of th epoint

distance - array with distances from the point to classify to the training data points
n -number of training points
k - the number of nearest neighbors

Point to classify data:
px - x value
py - y value

return the value of the point to classify
*/
int classifyAPoint(element_t x[], element_t y[], element_t val[], element_t distance[], size_t n, size_t k, element_t px, element_t py)
{ 
	size_t i, j;
	size_t min;
	size_t aux;
	size_t poz;

	//calcualte the distance from the point to training data points
	for (i = 0; i < n; i++) 
		distance[i] = 
			(x[i] - px) * (x[i] - px) + 
				(y[i] - py) * (y[i] - py); 


	//find the closest k training points to our point
	for (i = 0; i < k; i++) {
		min = distance[i];
		poz = i;
		for( j = i + 1; j < n; j++) {
			if (min > distance[j]) {
				min = distance[j];
				poz = j;
			}
		}
		aux = distance[i];
		distance[i] = distance[poz];
		distance[poz] = aux;
		aux = val[i];
		val[i] = val[poz];
		val[poz] = aux;
	}

	// Find the most common value in out k neighbors
	int freq1 = 0; 
	int freq2 = 0;
	for (i = 0; i < k; i++) 
	{ 
		if (val[i] == 0) 
			freq1++; 
		else if (val[i] == 1) 
			freq2++; 
	} 

	return (freq1 > freq2 ? 0 : 1); 
} 

int main() 
{ 
	size_t n = TRAINING_DATA_LENGTH; // Number of data points
	element_t x[TRAINING_DATA_LENGTH];
	element_t y[TRAINING_DATA_LENGTH];
	element_t val[TRAINING_DATA_LENGTH];
	element_t distance[TRAINING_DATA_LENGTH];

	//training data TODO: find something more elegant
	x[0] = 1; 
	y[0] = 12; 
	val[0] = 0; 

	x[1] = 2; 
	y[1] = 5; 
	val[1] = 0; 

	x[2] = 5; 
	y[2] = 3; 
	val[2] = 1; 

	x[3] = 3; 
	y[3] = 2; 
	val[3] = 1; 

	x[4] = 3; 
	y[4] = 6; 
	val[4] = 0; 

	x[5] = 1.5; 
	y[5] = 9; 
	val[5] = 1; 

	x[6] = 7; 
	y[6] = 2; 
	val[6] = 1; 

	x[7] = 6; 
	y[7] = 1; 
	val[7] = 1; 

	x[8] = 3.8; 
	y[8] = 3; 
	val[8] = 1; 

	x[9] = 3; 
	y[9] = 10; 
	val[9] = 0; 

	x[10] = 5.6; 
	y[10] = 4; 
	val[10] = 1; 

	x[11] = 4; 
	y[11] = 2; 
	val[11] = 1; 

	x[12] = 3.5; 
	y[12] = 8; 
	val[12] = 0; 

	x[13] = 2; 
	y[13] = 11; 
	val[13] = 0; 

	x[14] = 2; 
	y[14] = 5; 
	val[14] = 1; 

	x[15] = 2; 
	y[15] = 9; 
	val[15] = 0; 

	x[16] = 1; 
	y[16] = 7; 
	val[16] = 0; 

	// Parameter to decide group of the testing point
	size_t k = 3;
	int a = classifyAPoint(x, y, val, distance, n, k, 2.5, 7);

#ifdef DEBUG
	printf("Result: %d\n", a);
#endif

	return 0; 
} 

