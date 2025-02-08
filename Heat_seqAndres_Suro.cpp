#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <ctime>
#include <cstdio>

using namespace std;

void clone(double **x_old, double **x,  int M, int N, int Threads){

    for (int i = 0; i < M; i++){
        for (int j = 0; j< N; j++){
            x[i][j] = x_old[i][j];
        }
    }

    /*
    
    int i;
    omp_set_num_threads(Threads);

    #pragma omp parallel for shared(x_old, x, N), private(i)
        for (i = 0; i < N; i++ ){
            x_old[i] = x[i];
        }
    */
}

int main(){
    int threads = 4;
    double kx = 1.0;// termino difusivo en x
    double ky = 1.0;// termino difusivo en y

    //////////////

    double xI = 0;  // Dominios en X y Y
    double xF = 1;
    double yI = 0;
    double yF = 1;

    /////////////////

    double tI = 0; // tiempo inicial
    double tF= 0.5; // tiempo final

    ////////////////

    int Nt = 100000; // Num de divisiones en el tiempo 
    int Nx = 200; // Num de puntos en x, Razon :  si se divide en n, hay n+1 puntos
    int Ny = 200; // Num de puntos en y, Razon : si se divide en n, hay n+1 puntos


    //Discretizacion

    double Dx = (xF- xI)/(Nx - 1); //Dividimos entre el num de intervalos que habra, que es N-1 (N es el num de pts)
    double Dy = (yF - yI)/ (Ny-1);// Mismo pero para el intervalo y
    double Dt = (tF- tI)/ (Nt - 1);
    double rx = kx*( Dt / pow(Dx,2) );// coeficientes
    double ry = ky*( Dt / pow(Dy,2) );

    printf("(Nx,Ny) = %.3f %.3f", Nx, Ny);
    printf("Criterio CFL < 1/2 : ", rx + ry); // se debe cumplir eso para seguir

    double *x =  (double *)malloc(Nx * sizeof(double));
    double *y =  (double *)malloc(Ny * sizeof(double));

    ////// Condiciones iniciales
    for (int i = 0; i < Nx; i++){
        x[i] = xI + (i-1)*Dx;
    }

    for (int j = 0; j < Ny; j++){
        y[j] = yI + (j-1)*Dy;
    }
//////////////////  

    double **Uold = (double **)malloc(Nx * sizeof(double*));
    double **Unew = (double **)malloc(Nx * sizeof(double*));

    double start, end, time; // variables para el tiempo

    start = clock();

    for (int i = 0; i < Nx; i++){
        Uold[i] = (double*)malloc(Ny * sizeof(double));
        Unew[i] = (double*)malloc(Ny * sizeof(double));
    }

    //Condiciones de Iniciales
    for (int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
            Uold[i][j] = ( sin( x[i] + y[j] ) ) * ( sin( x[i] + y[j] ) );
        }
    }
    Unew = Uold;
    clone(Uold, Unew, Nx, Ny, threads);

    
    //Condiciones de Frontera
    for (int j = 0; j < Ny; j++){
        Unew[0][j] = 0.0; // Oeste
        Unew[Nx - 1][j] = 0.0; // Este
    }
    for (int i = 0; i < Nx; i++){
        Unew[i][0] = 0.0; // Sur
        Unew[i][Ny] = 2.0; // Norte
    }
    
    // Ciclo principal 
    for (int k = 0; k < Nt; k++){
        for (int i = 1; i < (Nx - 1) - 1; i++ ){
            for (int j = 1; j < (Ny - 1) - 1; j++){
                double aC = 1 - 2 * (rx + ry);

                double aE = rx;
                double aW = rx;
                double aS = ry;
                double aN = ry;

                Unew[i][j] = aC * Uold[i][j] + aW*Uold[i-1][j]
                + aE * Uold[i+1][j] + aS * Uold[i][j-1]
                + aN * Uold[i][j+1];
            }
        }
        clone(Uold, Unew, Nx, Ny, threads);
    }

    double suma = 0;
    for (int i = 1; i < (Nx - 1) - 1; i++ ){
        for (int j = 1; j < (Ny - 1) - 1; j++){
            suma = suma + Unew[i][j]; 
        }
    }

    end = clock();
    printf("suma es %.3f", suma);

    time = ((double)(end-start))/CLOCKS_PER_SEC;

     printf("tiempo: %f",time);
    //Liberar memoria
    free(x);
    free(y);


    for (long int i = 0; i < Nx; i++){
        free(Uold[i]);
        free(Unew[i]);
    }

    free(Uold);
    free(Unew);


    return 0;
}




