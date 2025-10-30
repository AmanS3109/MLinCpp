#include <iostream>
#include <ctime>
#include<cmath>
#include<iomanip>
using namespace std;

// activation function
float sigmoidf(float x){
	return 1.f / ( 1.f + expf(-x) );
}

typedef float sample[3];

sample or_gate[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

sample and_gate[] = {
	{0, 0, 0},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 1},
};

sample nand_gate[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 0},
};

sample *dataset = nand_gate;

size_t train_count = 4;

float rand_float(void) {
    return (float)rand() / (float)RAND_MAX;
}

float cost(float w1, float w2, float b){
	float result  = 0.0;
    	for (size_t i = 0; i < train_count; ++i) {
        	float x1 = dataset[i][0];
		float x2 = dataset[i][1];
        	float y_exp = dataset[i][2];
        	float y = sigmoidf((x1 * w1 + x2 * w2) + b);
        	float d = y - y_exp;
        	result += d * d;
   	 }
   	 result /= train_count;
	 return result;
}

int main2(){

	// (x|y) & ~(x&y)
	for(size_t x = 0; x < 2; ++x){
		for(size_t y = 0; y < 2; ++y){
			cout << "x ^ y: " << ((x|y) & (~(x&y))) << endl;
		}
	}
	return 0;
}

int main() {
    
    srand(time(0));
    // srand(69); // seed for reproducibility

    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float eps = 1e-1;
    float rate = 1e-1;
    
    cout << fixed << setprecision(6);
    
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
