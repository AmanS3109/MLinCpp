#include <iostream>
#include <ctime>
#include<cmath>
using namespace std;

// activation function
float sigmoidf(float x){
	return 1.f / ( 1.f + expf(-x) );
}

//OR gate
float dataset[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

#define DATA_COUNT (sizeof(dataset) / sizeof(dataset[0]))

float rand_float(void) {
    return (float)rand() / (float)RAND_MAX;
}

float cost(float w1, float w2, float b){
	float result  = 0.0;
    	for (size_t i = 0; i < DATA_COUNT; ++i) {
        	float x1 = dataset[i][0];
		float x2 = dataset[i][1];
        	float y_exp = dataset[i][2];
        	float y = sigmoidf((x1 * w1 + x2 * w2) + b);
        	float d = y - y_exp;
        	result += d * d;
   	 }
   	 result /= DATA_COUNT;
	 return result;
}


int main() {
    
   //  srand(time(0));
    srand(69); // seed for reproducibility

    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float eps = 1e-3;
    float rate = 1e-1;
    
    cout << "w1: " << w1 << " | " << "w2: " << w2 << "b: " << " | " <<b << endl;
    cout << "--------------------------------" << endl;
    cout << "cost(before): " <<  cost(w1, w2, b) << endl;
    cout << "--------------------------------" << endl;

    //gradient descent
    for (size_t i = 0; i < 100000; ++i){
    	float c = cost(w1, w2, b);
    	float dw1 = ( cost ( w1 + eps, w2, b ) - c ) / eps;
    	float dw2 = ( cost ( w1, w2 + eps, b ) - c ) / eps;
        float db = ( cost ( w1, w2, b + eps ) - c ) / eps;

    	w1 -= rate * dw1;
    	w2 -= rate * dw2;
	b -= rate * db;
    }
    cout << "w1: " << w1 << " | " << "w2: " << w2 << "b: " << " | " <<b << endl;

    cout << "cost: " << cost(w1, w2, b) << endl;

    for (size_t i = 0; i < 2; ++i){
    	for (size_t j = 0; j < 2; ++j){
		cout << i << " | " << j << " = " << sigmoidf((i*w1 + j*w2) + b) << endl;
	}
    }
}    
