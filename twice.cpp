#include <iostream>
#include <ctime>
using namespace std;

float dataset[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};

#define DATA_COUNT (sizeof(dataset) / sizeof(dataset[0]))

float rand_float(void) {
    return (float)rand() / (float)RAND_MAX;
}

float cost(float w, float b){
	float result  = 0.0;
    	for (size_t i = 0; i < DATA_COUNT; ++i) {
        	float x = dataset[i][0];
        	float y_exp = dataset[i][1];
        	float y = x * w + b;
        	float d = y - y_exp;
        	result += d * d;
   	 }
   	 result /= DATA_COUNT;
	 return result;
}


int main() {
    
    srand(time(0));
    // srand(69); // seed for reproducibility

    float w = rand_float()*10.0;
    float b = rand_float()*5.0;

    float eps = 1e-3;
    float rate = 1e-3;

    cout << "--------------------------------" << endl;
    cout << cost(w, b) << endl;
    cout << "--------------------------------" << endl;
    // gradient descent
    for(size_t i = 0; i < 500; ++i){
	float c = cost(w, b);
    	float dw = ( cost(w + eps, b) - c ) / eps;
	float db = ( cost(w, b + eps) - c ) / eps;
	w -= rate * dw;
	b -= rate * db;
    	cout << cost(w, b) <<endl;
    }
    cout << "--------------------------------" << endl;
    cout << "w: " << w << endl;
    cout << "b: " << b << endl;
    return 0;
}

