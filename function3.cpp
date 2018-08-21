#include <iostream>
#include <fstream>
#include <math.h> /*pow*/
#include <random>
#include <cstdlib>


using namespace std;

#include "function1.h"
#include "function2.h"
#include "function3.h"


double alpha = 0.00005;
double a2 = 0.6367;
double lambda_bar = 3.19;
double const_U = 0.55;
double D_bar = a2 * lambda_bar;


//phase field interpolation functions (also used in Karma and Rappel)
double g_Prime(int i, int j){
	double g;
	g = - phi(i,j) + pow( phi(i,j), 3);
	return g;
}

double P_prime(int i, int j){
	double p, p2;
	p = 1 - pow(phi(i,j), 2);
	return pow(phi(i,j), 2);
}


double Laplacian_U(int i,int j){
	double laplacian_u; 

	laplacian_u =  (U(i+1,j) + U(i-1,j) + U(i,j+1) +U(i,j-1))/2.0  
               +   ( U(i+1,j+1)+U(i-1,j+1)+U(i+1,j-1) +U(i-1,j-1))/4.0 
               -   3 * U(i,j) ;	

	return laplacian_u / pow(dx_bar,2);
}

double timeMarchC_phi(int i, int j){
	double newPHI;
	double derx = phi(i + 1, j) - phi(i - 1, j);
	double dery = phi(i, j + 1) - phi(i, j - 1);
	
	newPHI = phi(i,j) + (dt_bar / pow(A(derx, dery), 2)) * (
			(1 / dx_bar) * ( JR(i,j) - JL(i,j) + JT(i,j) - JB(i,j) ) );
// g_Prime(i,j) - lambda_bar * U(i,j) * P_prime(i,j) );
	//cout << newPHI << "			" //<< A(derx,dery)<< "			" << Mag2(derx,dery) << "			" << derx << "			" << dery << "			" << phi(i, j + 1) << "			" << phi(i,j -1) << endl;
	//	<< JR(i,j) << "		" << JL(i,j) << "		" << JT(i,j) << "		"<< JB(i,j) << endl << endl;
	return newPHI;
}

double timeMarchC_U(int i, int j){

	double newU;
	double alpha = ( D_bar * dt_bar / pow(dx_bar, 2) );
	newU = U(i,j) + alpha * Laplacian_U(i,j) +  (0.5 ) * (dPHI(i, j));

	//cout << newU << "			" << U(i,j) << " 			" << Laplacian_U(i,j) << "			" << dPHI(i,j) << endl;
	return newU;
}





