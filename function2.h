#ifndef FUNCTION2_H
#define FUNCTION2_H

extern double  const_U, D_bar, a_s, epsilon_prime, a12, epsilon_4, lambda_bar; //Model C variables

extern double Der;

extern double dx, dy, dt;

extern double dx_bar, dt_bar;

extern double W, M;

/*
checks if (i,j) is an edge node.
*/
int isEdge(int i, int j);

/*
computes the x derivative of phi 
*/
double iDERX(int i, int j, int sign);
double jDERX(int i, int j, int sign);

double iDERY(int i, int j, int sign);
double jDERY(int i, int j, int sign);

double iMag2(int i, int j, int sign);
double jMag2(int i, int j, int sign);

double iA(int i, int j, int sign);
double jA(int i, int j, int sign);

double iA_prime(int i, int j, int sign);
double jA_prime(int i, int j, int sign);

double JR(int i, int j);
double JL(int i, int j);
double JT(int i, int j);
double JB(int i, int j);


#endif