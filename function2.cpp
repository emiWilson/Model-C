#include <iostream>
#include <fstream>
#include <math.h> /*pow*/
#include <random>
#include <cstdlib>

using namespace std;

#include "function1.h"
#include "function2.h"

//model C specific variables
double epsilon_4 = 0.06; //anisotropy parameter form equation 5.25
double a_s = 1 - 3 * epsilon_4;
double epsilon_prime = 4 * epsilon_4;
double a12 = 4  * a_s * epsilon_prime;

double tao = 3 * 0.00000000000001; //3 * 10 ^ -13

double a, a_prime, mag_2;


double pp(int i, int j){
	return (1 / (4 * dx_bar)) * (phi(i+1, j+1) + phi(i, j+1) + phi(i + 1, j) + phi(i,j));

}

double pm(int i, int j){
	return ( 1 / (4 * dx_bar)) * (phi(i+1, j) + phi(i, j) + phi(i, j - 1) + phi(i + 1, j - 1));

}

double mp(int i, int j){
	return (1 / (4 * dx_bar)) * (phi(i-1, j+1) + phi(i, j+1) + phi(i - 1, j) + phi(i,j));

}

double mm(int i, int j){
	return (1 / (4 * dx_bar)) * (phi(i-1, j-1) + phi(i, j-1) + phi(i - 1, j) + phi(i,j));
}

// -------------------------DERX, DERY FUNCTIONS---------------------------------------
double DERX(int i, int j){
	return (phi(i + 1, j) - phi(i - 1 , j)) / dx_bar;
}

double DERY(int i, int j){
	return ( phi(i, j + 1) - phi(i, j - 1) ) / dx_bar;
}

//----------------------------------------------MAG2 FUNCTIONS -----------------------------
double Mag2(double derx, double dery){
	return pow( pow(derx, 2) + pow(dery, 2) ,  2);

}

//----------------------------------------------A, A_prime FUNCTIONS -----------------------------

double A(double derx, double dery){
	double A = (pow(derx, 4) + pow(dery, 2 ) ) / Mag2(derx, dery);

	return ( a_s * (1 + epsilon_prime * A ));
}

double A_prime(double derx, double dery){
	double A = (pow(derx, 2) + pow(dery, 2 ) ) / Mag2(derx, dery);
	return -a12 * derx * dery * A;
}
//----------------------------------------------JR,JL, JT, JB FUNCTIONS -----------------------------
void getAnisropies(double derx, double dery){
	
	mag_2 = Mag2(derx, dery);

	if (mag_2 < pow(10, -8)){
		a = a_s;
		a_prime = 0;

	}else{
		a = A(derx, dery);
		a_prime = A_prime(derx, dery);
	}


}

//right edge flux
double JR(int i, int j){
	double derx = phi(i + 1, j) - phi(i,j);
	double dery = pp(i,j) - pm(i,j);

	getAnisropies(derx,dery);

	return a * ( a * derx + a_prime * dery );
	
}

//left edge flux
double JL(int i, int j){
	double derx = phi(i, j) - phi(i - 1,j);
	double dery = mp(i,j) - mm(i,j);
	
	getAnisropies(derx, dery);
	

	return a * ( a * derx + a_prime * dery );
}

//top edge flux
double JT(int i, int j){
	double derx = pp(i,j) - mp(i,j);
	double dery = phi(i, j + 1) - phi(i,j);
	
	getAnisropies(derx,dery);

	return a * ( a * dery - a_prime * derx );
}

//bottom edge flux
double JB(int i, int j){
	double derx = pm(i, j) - mm(i, j);
	double dery = phi(i, j) - phi(i, j - 1);
	
	getAnisropies(derx,dery);

	return a * ( a * dery - a_prime * derx );
}


