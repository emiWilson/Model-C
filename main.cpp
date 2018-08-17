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


	//start stopwatch
	//auto start = std::chrono::high_resolution_clock::now();


	double phi[N][N];	

	begining_Of_PHI = & phi[0][0]; //point ptrPHI to start of 2D phi array
	

	//have "ghost node" along edge of thermal field, U
	double U[N][N];
	begining_Of_U = &U[0][0];
	

	double newPHI;
	double dPhi[N][N];
	ptr_dPHI = &dPhi[0][0];


	fillPHI();

	printPHI();


	for(int timestep = 0; timestep < T; timestep++){


		
		for (int i = 1; i < N; i ++){
			for (int j = 0; j < N ; j ++){
			
				newPHI = timeMarchC_phi(i,j);
				dPhi[i][j] = (newPHI - phi[i][j]);
				phi[i][j] = newPHI;
			}
			
		}
	
/*	for (int i = 0; i < N; i ++){
		for (int j = 0; j < N; j ++){

			cout << U[i][j] << " ";

		}
		cout << endl;
	}
	printU();
*/
		for (int i = 0; i < N; i ++){
			for (int j = 0; j < N; j ++){
				U[i][j] = timeMarchC_U(i,j);

			}
		}

//		cout << endl << "-----------------------------------------------" << endl;
	
		//print phi array for every 10th timestep
		if( timestep % skipPrint == 0 ){
			printPHI();
		}

	} 


	//stop stopwatch
	//auto finish = std::chrono::high_resolution_clock::now();

	//should print parameters and other info to top of the output file.
	//writeConstantsToFile(N, T, skipPrint, dt, dx);

	//auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    //    std::cout << microseconds.count() << "µs\n";
    //    if (microseconds > std::chrono::seconds(1))
	//

	return 0;
}