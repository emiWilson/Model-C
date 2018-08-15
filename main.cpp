/* Dependancy tree
/main.cpp -  finiteVol.cpp - finiteVol.h
		|
		|
*/
#include <iostream>
#include <fstream>
#include <math.h> /*pow*/
#include <random>
#include <cstdlib>
#include <chrono> //time of execution of program, want to scale with system size t^(1/2)



using namespace std;

#include "function1.h" 
#include "function2.h"
#include "function3.h"

int main(){

	wipeOutput(); //ensure all old data is deleted from file.

	int edges[2] = {0, N + 1};

	//start stopwatch
	//auto start = std::chrono::high_resolution_clock::now();


	double phi[N + 1][N + 1];	

	begining_Of_PHI = & phi[0][0]; //point ptrPHI to start of 2D phi array
	

	//have "ghost node" along edge of thermal field, U
	double U[N + 1][N + 1];
	begining_Of_U = &U[0][0];
	

	double newPHI;
	double dPhi[N + 1][N + 1];
	ptr_dPHI = &dPhi[0][0];


	std::default_random_engine de(time(0));
  	std::normal_distribution<double> distribution(0, 0.001); // 0 mean and 0.001 standard deviation

  	for (int i = 1; i < N + 1 ; i ++){
		for (int j = 1; j < N + 1; j ++){
			
			phi[i][j] = distribution(de);

			//cout << i << " " << j << " " << phi[i][j] << " but  " << phi[2][1] << endl;
			
	
		}
		
	}
	cout << endl << endl;

	printPHI();


	for(int timestep = 0; timestep < T; timestep++){

		//update edge nodes for boundary conditions
		for (int i : edges){
			for (int j = 1; j < N + 1; j ++){
				//U[i][j] = BC_U(i,j);
				//phi[i][j] = BC_phi(i,j);

				//cout << i << " " << j << " " << phi[i][j] <<  " but " << phi[2][1] << endl << endl;
			} 
		}
		

		for (int j : edges){
			for (int i = 1; i < N + 1 ; i ++){
				//U[i][j] = BC_U(i,j);
				//phi[i][j] = BC_phi(i,j);

				//cout << i << " " << j << " " << phi[i][j] <<  " but " << phi[2][1] << endl << endl;
			}
		}
		//cout << phi[0][4] << endl;
		//checkPHI();
		
		for (int i = 1; i < N; i ++){
			for (int j = 0; j < N ; j ++){
			
				newPHI = timeMarchC_phi(i,j);
				dPhi[i][j] = (newPHI - phi[i][j]);
				phi[i][j] = newPHI;
			}
			
		}
	

		for (int i = 0; i < N; i ++){
			for (int j = 0; j < N; j ++){
				U[i][j] = timeMarchC_U(i,j);
			}
		}

		//print phi array for every 10th timestep
		if( timestep % skipPrint == 0 ){
			printPHI();
		}

	} 

	//stop stopwatch
	//auto finish = std::chrono::high_resolution_clock::now();

	//should print parameters and other info to top of the output file.
	writeConstantsToFile(N, T, skipPrint, dt, dx);

	//auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    //    std::cout << microseconds.count() << "µs\n";
    //    if (microseconds > std::chrono::seconds(1))
	//

	return 0;
}