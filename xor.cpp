#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Xor {
    float or_w1, or_w2, or_b;
    float nand_w1, nand_w2, nand_b;
    float and_w1, and_w2, and_b;
};

// Activation function
float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}

float forward(const Xor& m, float x1, float x2) {
    float a = sigmoidf(m.or_w1 * x1 + m.or_w2 * x2 + m.or_b);
    float b = sigmoidf(m.nand_w1 * x1 + m.nand_w2 * x2 + m.nand_b);
    return sigmoidf(a * m.and_w1 + b * m.and_w2 + m.and_b);
}

using sample = float[3];

// XOR training data
sample xor_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample* train = xor_train;
const size_t train_count = 4;

// Cost function
float cost(const Xor& m) {
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = forward(m, x1, x2);
        float d = y - train[i][2];
        result += d * d;
    }
    return result / train_count;
}

float rand_float() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

Xor rand_xor() {
    Xor m;
    m.or_w1 = rand_float();
    m.or_w2 = rand_float();
    m.or_b = rand_float();
    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_b = rand_float();
    m.and_w1 = rand_float();
    m.and_w2 = rand_float();
    m.and_b = rand_float();
    return m;
}

void print_xor(const Xor& m) {
    cout << fixed << setprecision(6);
    cout << "or_w1 = " << m.or_w1 << endl;
    cout << "or_w2 = " << m.or_w2 << endl;
    cout << "or_b  = " << m.or_b << endl;
    cout << "nand_w1 = " << m.nand_w1 << endl;
    cout << "nand_w2 = " << m.nand_w2 << endl;
    cout << "nand_b  = " << m.nand_b << endl;
    cout << "and_w1 = " << m.and_w1 << endl;
    cout << "and_w2 = " << m.and_w2 << endl;
    cout << "and_b  = " << m.and_b << endl;
}

Xor learn(Xor m, const Xor& g, float rate) {
    m.or_w1   -= rate * g.or_w1;
    m.or_w2   -= rate * g.or_w2;
    m.or_b    -= rate * g.or_b;
    m.nand_w1 -= rate * g.nand_w1;
    m.nand_w2 -= rate * g.nand_w2;
    m.nand_b  -= rate * g.nand_b;
    m.and_w1  -= rate * g.and_w1;
    m.and_w2  -= rate * g.and_w2;
    m.and_b   -= rate * g.and_b;
    return m;
}

Xor finite_diff(Xor m, float eps) {
    Xor g{};
    float c = cost(m);
    float saved;

    saved = m.or_w1;  m.or_w1 += eps;  g.or_w1 = (cost(m) - c) / eps;  m.or_w1 = saved;
    saved = m.or_w2;  m.or_w2 += eps;  g.or_w2 = (cost(m) - c) / eps;  m.or_w2 = saved;
    saved = m.or_b;   m.or_b  += eps;  g.or_b  = (cost(m) - c) / eps;  m.or_b  = saved;

    saved = m.nand_w1;  m.nand_w1 += eps;  g.nand_w1 = (cost(m) - c) / eps;  m.nand_w1 = saved;
    saved = m.nand_w2;  m.nand_w2 += eps;  g.nand_w2 = (cost(m) - c) / eps;  m.nand_w2 = saved;
    saved = m.nand_b;   m.nand_b  += eps;  g.nand_b  = (cost(m) - c) / eps;  m.nand_b  = saved;

    saved = m.and_w1;  m.and_w1 += eps;  g.and_w1 = (cost(m) - c) / eps;  m.and_w1 = saved;
    saved = m.and_w2;  m.and_w2 += eps;  g.and_w2 = (cost(m) - c) / eps;  m.and_w2 = saved;
    saved = m.and_b;   m.and_b  += eps;  g.and_b  = (cost(m) - c) / eps;  m.and_b  = saved;

    return g;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Xor m = rand_xor();
    float eps = 1e-1;
    float rate = 1e-1;

    for (size_t i = 0; i < 100000; ++i) {
        Xor g = finite_diff(m, eps);
        m = learn(m, g, rate);
    }

    cout << fixed << setprecision(6);
    cout << "Final cost = " << cost(m) << endl;

    cout << "------------------------------" << endl;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            cout << i << " ^ " << j << " = " << forward(m, i, j) << endl;
        }
    }

    cout << "------------------------------" << endl;
    cout << "\"OR\" neuron:" << endl;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            cout << i << " | " << j << " = " << sigmoidf(m.or_w1 * i + m.or_w2 * j + m.or_b) << endl;
        }
    }

    cout << "------------------------------" << endl;
    cout << "\"NAND\" neuron:" << endl;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            cout << "~(" << i << " & " << j << ") = " << sigmoidf(m.nand_w1 * i + m.nand_w2 * j + m.nand_b) << endl;
        }
    }

    cout << "------------------------------" << endl;
    cout << "\"AND\" neuron:" << endl;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            cout << i << " & " << j << " = " << sigmoidf(m.and_w1 * i + m.and_w2 * j + m.and_b) << endl;
        }
    }

    return 0;
}



