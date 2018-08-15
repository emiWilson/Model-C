#include <iostream>
#include <fstream>
#include <math.h> /*pow*/
#include <random>
#include <cstdlib>


using namespace std;

std::ofstream myfile;

#include "function1.h"
//clear old data from output file

//assign vaue for N
int N = 10;
int T = 10; //make sure T is a multiple of 10 to make timesteps are good.
int skipPrint = 1;

double * begining_Of_PHI;
double * begining_Of_U;
double  * ptr_dPHI;

//magnitude of timestep. should obey stability restriction delta_t <  (delta_x ^ 2) / 4
//restriction means that it is not possible to advance a solution explicity faster than the inherent diffusion
//time of the problem.
double dt = 0.05; 
double dx = 0.8;

double q = 1;


void wipeOutput(){
	myfile.open("output.txt", std::ofstream::out | std::ofstream::trunc);
	myfile.close();

}

void writeConstantsToFile(int N, int T, int p, double dt, double dx){
	
	myfile.open ("output.txt", std::fstream::app);
	myfile << N << " " << T << " " << p << " " << dt << " " << dx;
	myfile.close();
}


//enforces periodic boundary conditions for the discreet laplacian

int BC(int i){
	
	int I = (i + N) % N;

	if (I > N - 1)
		cout << "ERROR!!";

	if (I < 0)
		cout << "ERROR!!";

	return I;

}


//gets values in the phi array
double phi(int i, int j){

	double element = * (begining_Of_PHI + (i * N) + j);
	
	return element;

}


double dPHI(int i, int j){
	double element = * (ptr_dPHI + (BC(i) * N) + BC(j));
	return element;
}

//gets values in the phi array
double U(int i, int j){

	

	double element = * (begining_Of_U + (BC(i) * N) + BC(j));
	
	return element;

}

//implements fixed flux boundary conditions for the thermal field U
double BC_U(int i, int j){

	double updateVal;

	if (i == 0)
		updateVal = U(1, j) - q * dx; 

	if (i == N + 1)
		updateVal = U(N - 1, j) + q * dx;

	if (j == 0)
		updateVal = U(i, 1) - q * dx;

	if (j == N + 1)
		updateVal = U(i, N - 1) - q * dx;

	return updateVal;
	
}

double BC_phi(int i, int j){

	double updateVal;

	if (i == 0)
		updateVal = phi(1, j); 

	if (i == N + 1)
		updateVal = phi(N - 1, j);

	if (j == 0)
		updateVal = phi(i, 1);

	if (j == N + 1)
		updateVal = phi(i, N - 1);

	return updateVal;
	
}

//be careful not to print this array every time step. it will quickly fill up disk space
void printPHI(){

  	myfile.open ("output.txt", std::fstream::app);

	for (int i = 0; i < N; i ++){
		for (int j = 0; j < N; j ++){
			myfile << phi(i,j) << " ";
		}
		myfile << endl;
	}

	myfile << endl;

	myfile.close();

}
