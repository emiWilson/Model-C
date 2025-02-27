#ifndef FUNCTION1_H
#define FUNCTION1_H

/************************************ GLOBAL VARIABLES ******************************************/

// N is the number of grid points in the numerical array. N = L / (delta_x), where L is the domain length in each direction
extern int N, T, skipPrint; //number of physical and temporal iterations


//ptrPHI will be used to navigate the NxN phi array: phi[i][j] = *(ptr + (i * N) + j))

extern double q; //imposed boundary flux condition used for Model C.
extern double tao;

//this pointer will always point to the start of the PHI array and will remain unaltered. Can't make "const" variable type b/c don't know the phi array before the program starts. 
extern double * begining_Of_PHI;
extern double * begining_Of_U;
extern double * ptr_dPHI;

extern double dx_bar;
extern double dt_bar;
extern double W_phi;

extern int edges[2];


 /****************************** FUNCTIONS **************************************************/

//clear old data from output file
void wipeOutput();


void writeConstantsToFile();

void fillPHI();

int BC(int i);

//gets values in the phi array
double phi(int i, int j);

double dPHI(int i, int j);

//gets values in the phi array
double U(int i, int j);

//implements fixed flux boundary conditions for the thermal field U
int BC_U(int i, int j);



void checkPHI();

void changeVal(int i, int j, double val);
void changeU(int i, int j, int val);

void printPHI();
void printU();

#endif