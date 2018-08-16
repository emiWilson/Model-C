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
int size(){

	return N + 1;

}

void fillPHI(){

	std::default_random_engine de(time(0));
  	std::normal_distribution<double> distribution(0, 0.001); // 0 mean and 0.001 standard deviation

  	for (int i = 0; i < N + 3; i ++){
		for (int j = 0; j < N + 3; j ++){
			
			 * (begining_Of_PHI + (i * (N + 2)) + j) =  i*j;//distribution(de);
			 
		}
		
	}
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

	double element = * (begining_Of_PHI + (i * (N + 2)) + j);
	
	return element;

}

void changeVal(int i, int j, double val){

	* (begining_Of_PHI + (i * N) + j) = val;

	cout << i << " " << j << endl;


}

void changeU(int i, int j, double val){

	* (begining_Of_U + (i * (N + 2)) + j) = val;

}


double dPHI(int i, int j){
	double element = * (ptr_dPHI + (i * N ) + j);
	return element;
}

//gets values in the phi array
double U(int i, int j){

	double element = * (begining_Of_U + (i * N) + j);
	
	return element;

}

//implements fixed flux boundary conditions for the thermal field U
void BC_U(int i, int j){

	double updateVal = U(i,j);

	if (i == 0){
		updateVal = U(1, j) - q * dx; 
	}

	else if (i == N + 1){
		updateVal = U(N, j) + q * dx;
	}

	else if (j == 0){
		updateVal = U(i, 1) - q * dx;
	}

	else if (j == N + 1){
		updateVal = U(i, N) + q * dx;
	}
	
}

void BC_phi(int i, int j){

	double updateVal;


	if (i == 0){
		updateVal = phi(1, j);

	}
	else if (i == N + 2){
		updateVal = phi(N + 1, j);
	}

	else if (j == 0){
		updateVal = phi(i, 1);
	}

	else if (j == N + 2){
		updateVal = phi(i, N + 1);
	}
	
	changeVal(i, j, updateVal);
	

}

void treatBCs(){
	//update edge nodes for boundary conditions
		for (int i : edges){
			for (int j = 1; j < N + 1; j++){
				//BC_U(i,j);
				BC_phi(i,j);
		
			} 
		}
		

		for (int j : edges){
			for (int i = 0; i < N + 1; i ++){
				//BC_U(i,j);
				BC_phi(i,j);

			}
		}
}


//be careful not to print this array every time step. it will quickly fill up disk space
void printPHI(){

  	myfile.open ("output.txt", std::fstream::app);
	for (int i = 0; i < N + 2; i ++){
		for (int j = 0; j < N + 2; j ++){

			myfile << phi(i,j) << " ";

		}
		myfile << endl;
	}

	myfile << endl;

	myfile.close();

}






