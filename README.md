# 🧠 XOR Neural Network in C++

This project implements a simple **neural network from scratch in C++** that learns to perform the **XOR (exclusive OR)** operation using gradient descent and the **sigmoid activation function**.

It demonstrates how logical gates (OR, NAND, AND) can be combined to form a composite network that learns the XOR function — one of the classic problems in neural network learning.

---

## ⚙️ How It Works

The XOR gate cannot be represented by a single linear classifier, so this implementation builds it using three neurons:
- **OR neuron**
- **NAND neuron**
- **AND neuron**

The network is trained using **finite difference gradient estimation** to minimize the cost function.

---
