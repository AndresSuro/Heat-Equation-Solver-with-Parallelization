# Heat Equation Solver with Parallelization (C++ Implementation)

## Overview

This project implements a numerical solution to the 2D Heat Equation using the Finite Difference Method (FDM). The objective is to efficiently approximate the heat distribution over a given domain using parallel computing techniques with MPI (Message Passing Interface). The entire implementation is done in **C++**.

## The Heat Equation

The heat equation models the distribution of heat in a given region over time. In this project, we focus on solving the two-dimensional form, where the temperature in a domain evolves based on spatial and temporal variations. This equation is widely used in physics and engineering.

The 2D heat equation is given by:

$$
\frac{\partial u}{\partial t} = \alpha \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)
$$

---

## Numerical Approximation with Finite Differences

To solve this equation numerically, we approximate the derivatives using finite differences:

**Second derivative with respect to x:**

$$
\frac{\partial^2 u}{\partial x^2} \approx \frac{u_{i+1,j} - 2u_{i,j} + u_{i-1,j}}{\Delta x^2}
$$

**Second derivative with respect to y:**

$$
\frac{\partial^2 u}{\partial y^2} \approx \frac{u_{i,j+1} - 2u_{i,j} + u_{i,j-1}}{\Delta y^2}
$$

**Time derivative:**

$$
\frac{\partial u}{\partial t} \approx \frac{u_{i,j}^{n+1} - u_{i,j}^{n}}{\Delta t}
$$

By substituting these approximations into the heat equation, we obtain a discrete update formula that can be implemented in the simulation.

---

## Parallelization Strategy

Since solving the heat equation involves updating a large grid of temperature values over many time steps, parallel computing can significantly improve performance. The following strategy is used:

1. **Domain Decomposition**:  
   - The 2D computational grid is divided into subdomains assigned to different MPI processes. Each process computes temperature updates for its assigned region.

2. **Communication Between Processes**:  
   - Each subdomain requires boundary values from neighboring subdomains. MPI communication functions are used to exchange data efficiently.

3. **Cartesian Topology for Process Arrangement**:  
   - A 2D Cartesian grid topology is created to allow structured communication between neighboring processes.

---

## Summary of Results

The parallel implementation significantly reduced computation time compared to the serial version. We observed the following trends:

- **Speedup**: The computation time decreased as the number of processes increased, with diminishing returns after a certain point due to communication overhead.  
- **Efficiency**: Higher efficiency was achieved with 3–5 processes. Increasing beyond this number reduced efficiency, as communication between processes became more dominant.  
- **Optimal Configuration**: The best trade-off between performance and efficiency was found at around 4 processes. 

---


## How to Run the Code

### Step 1: Compile the Code
Make sure you have a C++ compiler installed that supports OpenMP (e.g., g++).

To compile the C++ code with OpenMP support, use the following command:

```bash
g++ -o heat_solver heat_equation.cpp -fopenmp -lm

```
### Step 2: Run the Program
Once compiled, execute the program using the following command:
```bash
./heat_solver
```
### Step 3: Adjust Parameters and Analyze Results
Modify simulation parameters in the C++ code to observe how they affect the simulation's behavior and performance:
```cpp
int Nx = 200;    // Grid points in the x-direction
int Ny = 200;    // Grid points in the y-direction
int Nt = 100000; // Number of time steps
double alpha = 1.0; // Thermal diffusivity constant
```
- **Grid Resolution (Nx, Ny)**: Higher values increase accuracy but require more computation time.
- **Time Steps (Nt)** : Increasing Nt simulates a longer time period. Ensure numerical stability by checking the CFL condition (rx + ry < 0.5).
- **Thermal Diffusivity (alpha)** : Adjusting this constant changes the rate of heat propagation.

