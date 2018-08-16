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
int N = 4;
int T = 1; //make sure T is a multiple of 10 to make timesteps are good.
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

int edges[2] = {0, N + 2};


void wipeOutput(){
	myfile.open("output.txt", std::ofstream::out | std::ofstream::trunc);
	myfile.close();

}

void writeConstantsToFile(int N, int T, int p, double dt, double dx){
	
	myfile.open ("output.txt", std::fstream::app);
	myfile << N << " " << T << " " << p << " " << dt << " " << dx;
	myfile.close();
}


void fillPHI(){

	std::default_random_engine de(time(0));
  	std::normal_distribution<double> distribution(0, 0.001); // 0 mean and 0.001 standard deviation

  	for (int i = 0; i < N; i ++){
		for (int j = 0; j < N; j ++){
			
			 * (begining_Of_PHI + (i * N) + j) = distribution(de);

			 * (begining_Of_U + (i * N) + j) = i * j;//distribution(de) / 10;
			 
		}
		
	}
}

//gets values in the phi array
double phi(int i, int j){
	int I = BC(i);
	int J = BC(j);

	double element = * (begining_Of_PHI + (I * N) + J);
	
	return element;

}
/*
void changeVal(int i, int j, double val){

	* (begining_Of_PHI + (i * N) + j) = val;


}

void changeU(int i, int j, double val){

	* (begining_Of_U + (i * (N)) + j) = val;

}
*/

double dPHI(int i, int j){
	double element = * (ptr_dPHI + (i * N ) + j);
	return element;
}

//gets values in the phi array
double U(int i, int j){

	int edgeFACT = BC_U(i, j);

	double element = * (begining_Of_U + (BC(i) * N) + BC(j)) + edgeFACT * q * dx;
	
	
	return element;

}

//implements fixed flux boundary conditions for the thermal field U
int BC_U(int i, int j){

	double isEdge = 0; //isedge is false when 0

	if (i == -1){
		isEdge = - 1;
	}

	else if (i == N){
		isEdge = + 1;
	}

	else if (j == -1){
		isEdge = - 1;
	}

	else if (j == N){
		isEdge = + 1;
	}

	return isEdge;
	
}

int BC(int i){
	int I = i;
	
	if(i == -1){
		I = 0;

	}
	if(i == N){
		I = N - 1;
	}

	return I;
	

}

//be careful not to print this array every time step. it will quickly fill up disk space
//printing with boundary conditons
void printPHI(){

  	myfile.open ("output.txt", std::fstream::app);
  	myfile << "phi Array" << endl;
	for (int i = -1; i < N + 1; i ++){
		for (int j = -1; j < N + 1; j ++){

			//myfile << phi(i,j) << " ";

		}
		//myfile << endl;
	}

	//myfile << endl;

	cout << q * dx;
	myfile << "U array" << endl;
	for (int i = -1; i < N + 1; i ++){
		for (int j = -1; j < N + 1; j ++){

			myfile << U(i,j) << " ";

		}
		myfile << endl;
	}

	myfile.close();

}






