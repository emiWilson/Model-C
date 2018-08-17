#ifndef FUNCTION2_H
#define FUNCTION2_H

extern double  const_U, D_bar, a_s, epsilon_prime, a12, epsilon_4, lambda_bar; //Model C variables


/*
checks if (i,j) is an edge node.
*/
int isEdge(int i, int j);

/*
computes the x derivative of phi 
*/
double pp(int i, int j);
double pm(int i, int j);
double mp(int i, int j);
double mm(int i, int j);

double DERX(int i, int j);
double DERY(int i, int j);

void getAnisropies(double derx, double dery);

double Mag2(double i, double j);

double A(double i, double j);
double A_prime(double i, double j);

double JR(int i, int j);
double JL(int i, int j);
double JT(int i, int j);
double JB(int i, int j);



#endif