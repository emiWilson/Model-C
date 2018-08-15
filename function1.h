#ifndef FUNCTION1_H
#define FUNCTION1_H

/************************************ GLOBAL VARIABLES ******************************************/

// N is the number of grid points in the numerical array. N = L / (delta_x), where L is the domain length in each direction
extern int N, T, skipPrint; //number of physical and temporal iterations


//ptrPHI will be used to navigate the NxN phi array: phi[i][j] = *(ptr + (i * N) + j))
extern double * ptrPHI , * ptrU, *ptr_dPHI;

extern double q; //imposed boundary flux condition used for Model C.
extern double tao;

//this pointer will always point to the start of the PHI array and will remain unaltered. Can't make "const" variable type b/c don't know the phi array before the program starts. 
extern double * begining_Of_PHI;
extern double * begining_Of_U;

extern double dx_bar;

 /****************************** FUNCTIONS **************************************************/

//clear old data from output file
void wipeOutput();


void writeConstantsToFile(int N, int T, int p, double dt, double dx);

//periodic boundary conditions for the discreet laplacian

static int BC(int i);

//gets values in the phi array
double phi(int i, int j);

double dPHI(int i, int j);

//gets values in the phi array
double U(int i, int j);

//implements fixed flux boundary conditions for the thermal field U
double BC_U(int i, int j);

double BC_phi(int i, int j);

void printPHI();

#endif