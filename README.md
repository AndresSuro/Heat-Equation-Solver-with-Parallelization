# Heat Equation Solver with Parallelization (C++ Implementation)

## Overview

This project implements a numerical solution to the 2D Heat Equation using the Finite Difference Method (FDM). The objective is to efficiently approximate the heat distribution over a given domain using parallel computing techniques with MPI (Message Passing Interface). The entire implementation is done in **C++**.

## The Heat Equation

The heat equation models the distribution of heat in a given region over time. In this project, we focus on solving the two-dimensional form, where the temperature in a domain evolves based on spatial and temporal variations. This equation is widely used in physics and engineering.

---

## Numerical Approximation with Finite Differences

We approximate the solution to the heat equation using finite differences. This involves discretizing the time and spatial dimensions into a grid and updating the temperature at each point based on its neighbors. This discretization converts the continuous problem into a system of equations that can be solved numerically.

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
Ensure you have an MPI compiler installed. Compile the C++ program using:

```bash
mpicxx heat_equation.cpp -o heat_solver
```
### Step 2: Install Dependencies
Make sure to install any required dependencies such as MPI. If you are using Ubuntu, you can install the required packages using:
```bash
sudo apt update
sudo apt install mpich
```
### Step 3: Execute the Program
1. Open your terminal in the directory where the compiled program (`heat_solver`) is located.
2. Use the `mpirun` command to run the program with the desired number of processes. For example, to run with 4 processes, execute the following:

   ```bash
   mpirun -np 4 ./heat_solver
   ```
### Step 4: Adjust Parameters and Analyze Results
Modify simulation parameters in the C++ code to observe how they affect the behavior and performance of the simulation. Below are the key parameters you can adjust:
```cpp
int Nx = 400;
int Ny = 400;
int Nt = 200000;
double alpha = 0.5;
```
By adjusting these parameters, you can observe how the simulation behaves with higher resolution grids or larger time steps. After running the program, analyze the results to evaluate the performance and accuracy of the simulation.

