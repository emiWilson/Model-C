#include <iostream>
#include <fstream>
#include <math.h> /*pow*/



using namespace std;

std::ofstream myfile;

#include "function1.h"
//clear old data from output file

//assign vaue for N
int N = 200;
int T = 400; //make sure T is a multiple of 10 to make timesteps are good.
int skipPrint = 50;

double * begining_Of_PHI;
double * begining_Of_U;
double  * ptr_dPHI;

//magnitude of timestep. should obey stability restriction delta_t <  (delta_x ^ 2) / 4
//restriction means that it is not possible to advance a solution explicity faster than the inherent diffusion
//time of the problem.
//double dt = 0.05; 
//double dx = 0.8;

double W_phi = 0.0000000001;
double dt_bar =  0.014;
double dx_bar =  0.4;

double q = 1;

int edges[2] = {0, N + 2};




void wipeOutput(){
	myfile.open("output.txt", std::ofstream::out | std::ofstream::trunc);
	myfile.close();

}

void writeConstantsToFile(){
	
	myfile.open ("output.txt", std::fstream::app);
	myfile << N << " " << T << " " << skipPrint << " " << dt_bar << " " << dx_bar;
	myfile.close();
}


void fillPHI(){

  	for (int i = 0; i < N ; i ++){
		for (int j = 0; j < N ; j ++){

			double Ro = 10;// * W_phi;
			double dist = pow((i-1) * dx_bar, 2) + pow((j-1) * dx_bar, 2) - Ro * dx_bar;
			

			 * (begining_Of_PHI + (i * N) + j) = - tanh(dist / sqrt(2));

			 * (begining_Of_U + (i * N) + j) = 0;
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

double dPHI(int i, int j){
	//cout << * (ptr_dPHI + (i * N ) + j) << endl;
	int I = BC(i);
	int J = BC(j);

	return * (ptr_dPHI + (I * N ) + J);

	
}

//gets values in the phi array
double U(int i, int j){

	int edgeFACT = BC_U(i, j);
	int I = BC(i);
	int J = BC(j);

	double element = * (begining_Of_U + (I * N) + J) + ( edgeFACT * q * dx_bar);
	
	
	return element;

}

//implements fixed flux boundary conditions for the thermal field U
int BC_U(int i, int j){

	double isEdge = 0; //isedge is false when 0

	if (i == -1){
		isEdge = - 1;
	}

	else if (i == N + 1){
		isEdge = + 1;
	}

	else if (j == -1){
		isEdge = - 1;
	}

	else if (j == N + 1){
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
	for (int i = 0; i < N ; i ++){
		for (int j = 0; j < N ; j ++){

			myfile << phi(i,j) << " ";

		}
		myfile << endl;
	}

	myfile << endl;

	/*
	myfile << "U array" << endl;
	for (int i = 0; i < N; i ++){
		for (int j = 0; j < N; j ++){

			myfile << U(i,j) << " ";

		}
		myfile << endl;
	}
*/
	myfile.close();

}

void printU(){
	cout << endl;
	for (int i = 0; i < N; i ++){
		for (int j = 0; j < N; j ++){

			cout << U(i,j) << " ";

		}
		cout << endl;
	}
}






