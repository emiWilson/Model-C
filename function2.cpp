#include <iostream>
#include <fstream>
#include <math.h> /*pow*/
#include <random>
#include <cstdlib>

using namespace std;

#include "function1.h"
#include "function2.h"

//model C specific variables
double epsilon_4 = 1; //anisotropy parameter form equation 5.25
double a_s = 1 - 3 * epsilon_4;
double epsilon_prime = 4 * epsilon_4;
double a12 = 4  * a_s * epsilon_prime;

double tao = 3;
double dt_bar = dt / tao;
double dx_bar = dx / pow(0.25, 1/2);

int isEdge(int i, int j){
	int edge = 0;
	if (i == 0) {edge = 1;}; // top edge
	if (i == N) {edge = 2;}; // bottom edge
	if (j == 0) {edge = 3;}; // left edge
	if (j == N) {edge = 4;}; // right edge

	return edge;
}

// -------------------------DERX, DERY FUNCTIONS---------------------------------------
double iDERX(int i, int j, int sign)
{
	double derx = 0;

	//if DERX(i + 1/2, j) (at left and right edges)
    if(sign == 1){
    	derx = ( phi(i + 1,j) - phi(i,j) ) / dx_bar;
    }
    //if DERX(i - 1/2, j) (at left and right edges)
    else if(sign == -1){
    	derx = ( phi(i, j) - phi(i - 1, j) ) /dx_bar;
    }

    return derx;
}

double jDERX(int i, int j, int sign)
{
	double derx = 0;
	//if DERX(i, j + 1/2)
	if(sign == 1){
		derx = (1 / ( 4 * dx_bar )) * 
		( phi(i + 1, j + 1) + phi(i + 1, j) + phi(i,j) + phi(i, j + 1) 
		- (phi(i, j + 1) + phi(i,j) + phi(i - 1, j) + phi(i - 1, j + 1)));
	}
	//if DERX(i, j - 1/2)
	else if (sign == -1){
		derx = (1 / ( 4 * dx_bar )) * 
		( phi(i + 1, j) + phi(i + 1, j - 1) + phi(i, j - 1) + phi(i, j) 
		- (phi(i, j) + phi(i,j - 1) + phi(i - 1, j - 1) + phi(i - 1, j)));
	}
	return derx;
}

double iDERY(int i, int j, int sign)
{
	double dery = 0;
	//if DERY(i + 1/2, j)
	if(sign == 1){
		dery = (1 / ( 4 * dx_bar )) * 
		( phi(i + 1, j + 1) + phi(i, j + 1) + phi(i,j) + phi(i + 1, j) 
		- (phi(i + 1, j) + phi(i,j) + phi(i, j - 1) + phi(i + 1, j - 1)));

	}
	//if DERY(i - 1/2, j)
	else if (sign == - 1){
		dery = (1 / ( 4 * dx_bar )) * 
		( phi(i, j + 1) + phi(i - 1, j + 1) + phi(i - 1, j) + phi(i, j) 
		- (phi(i, j) + phi(i - 1,j) + phi(i - 1, j - 1) + phi(i, j - 1)));
	}

	return dery;

}

double jDERY(int i, int j, int sign)
{
	double dery = 0;
	//DERY(i, j + 1/2)
	if(sign == 1){
		dery = ( phi(i, j + 1) - phi(i,j) ) / dx_bar;
	}
	//DERY(i, j - 1/2)
	else if (sign == -1){
		dery = ( phi(i, j) - phi(i, j - 1) ) / dx_bar;
	}

	return dery;
}
//----------------------------------------------MAG2 FUNCTIONS -----------------------------
double iMag2(int i, int j, int sign){
	return pow( pow(iDERX(i,j,sign), 2) + pow(iDERY(i,j,sign), 2) ,  2);
}

double jMag2(int i, int j, int sign){
	return pow( pow(jDERX(i,j,sign), 2) + pow(jDERY(i,j,sign), 2) ,  2);
}

//----------------------------------------------A, A_prime FUNCTIONS -----------------------------
double iA(int i, int j, int sign){
	double A = (pow(iDERX(i, j, sign), 4) + pow(iDERY(i,j, sign), 2 ) ) / iMag2(i, j, sign);
	 
	return ( a_s * (1 + epsilon_prime * A ));
	
}


double jA(int i, int j, int sign){

	double A = (pow(jDERX(i, j, sign), 4) + pow(jDERY(i,j, sign), 2 ) ) / jMag2(i, j, sign);

	return ( a_s * (1 + epsilon_prime * A ));

}
double A(int i, int j){
	return ( 1 / 4 )*( iA(i, j, 1) + iA (i, j, -1) + jA(i,j,1) + jA(i,j, - 1) );
}

double iA_prime(int i, int j, int sign){
	double A = (pow(iDERX(i, j, sign), 2) + pow(iDERY(i,j, sign), 2 ) ) / iMag2(i, j, sign);
	return -a12 * iDERX(i,j,sign) * iDERY(i,j,sign) * A;
}

double jA_prime(int i, int j, int sign){
	double A = (pow(jDERX(i, j, sign), 2) + pow(jDERY(i,j, sign), 2 ) ) / jMag2(i, j, sign);
	return -a12 * jDERX(i,j,sign) * jDERY(i,j,sign) * A;
}
//----------------------------------------------JR,JL, JT, JB FUNCTIONS -----------------------------
double JR(int i, int j){
	
	return iA(i, j, 1) * ( iA(i,j, 1) * iDERX(i,j, 1) - iA_prime(i,j, 1) * iDERY(i,j, 1) );
	
}

double JL(int i, int j){

	return iA(i, j, -1) * ( iA(i,j, -1) * iDERX(i,j, -1) - iA_prime(i,j, -1) * iDERY(i,j, -1) );
}

double JT(int i, int j){

	return jA(i, j, 1) * (jA(i,j, 1) * jDERX(i,j, 1) - jA_prime(i,j, 1) * jDERY(i,j, 1) );

}

double JB(int i, int j){

	return jA(i, j, -1) * (jA(i,j, -1) * jDERX(i,j, -1) - jA_prime(i,j, -1) * jDERY(i,j, -1) );

}
