#include <iostream>
#include <fstream>
#include <math.h> /*pow*/
#include <random>
#include <cstdlib>


using namespace std;

#include "function1.h"
#include "function2.h"
#include "function3.h"

double Temp = 20;
double Tm = 20;
double c_P = 1;
double L = 22;
double alpha = 5;

//other variables
double W = 0.25;
double M = 1; //lookup realistic value for M.

double lambda_bar = 4;
double const_U = (T - Tm) * c_P / L;
double D_bar = (alpha * tao) / pow(W, 2);

//phase field interpolation functions (also used in Karma and Rappel)
double g_Prime(int i, int j){
	double g;
	g = - phi(i,j) + pow( phi(i,j), 3);
	return g;
}

double P_prime(int i, int j){
	double p, p2;
	p = 1 - pow(phi(i,j), 2);
	p2 = pow(phi(i,j), 2);
	return p2;
}

double h_Prime(int i,int j){
	return (1/2);
}


double Laplacian_U(int i,int j){
	double laplacian_u; 

	laplacian_u = U(i + 1 , j) + U(i - 1, j)
			+ U( i, j + 1 ) + U(i, j - 1) 
			- 4 * ( U(i,j) );
	
	return laplacian_u;
}


double timeMarchC_U(int i, int j){

	double newU;


	newU = U(i,j) + ( D_bar * dt_bar / pow(dx_bar, 2) ) * Laplacian_U(i,j)
		+  h_Prime(i,j) * (dPHI(i, j));
	
	return newU;
}

double timeMarchC_phi(int i, int j){
	double newPHI;
	
	// NEED TO FIND A FUNCTION FOR A THAT IS ACTUALLY TRUE
	newPHI = phi(i,j) + (dt_bar / pow(iA(i,j, 1), 2)) * (
			(1 / dx_bar) * ( JR(i,j) - JL(i,j) + JT(i,j) - JB(i,j) )
			- g_Prime(i,j) - lambda_bar * const_U * P_prime(i,j) );
			
	
	return newPHI;
}




