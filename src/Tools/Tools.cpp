#include "Tools.h"

//Kinematic factors
double Kine::ShrockFactor(double M_Meson, double M_Lepton, double M_Sterile) //Correct scaling of flux
{
	double dM_a = pow(M_Lepton/M_Meson, 2.0);
	double dM_i = pow(M_Sterile/M_Meson, 2.0);	

	if (M_Meson >= M_Lepton + M_Sterile)
		return ShrockRho(dM_a, dM_i)/(dM_a * pow(1-dM_a, 2.0));
	else return 0;
}

double Kine::ShrockRho(double X, double Y)
{
	return ShrockFM(X, Y)*sqrt(Lambda(1, X, Y));
}

double Kine::ShrockFM(double X, double Y)
{
	return X+Y - (X-Y)*(X-Y);
}

double Kine::Lambda(double X, double Y, double Z)
{
	double Lambda = X*X + Y*Y + Z*Z - 2*(X*Y + X*Z + Y*Z);
	if (Lambda < 0) return -Lambda;
	else return Lambda;
}

double Kine::I1_f(double t, double X, double Y, double Z)	//To be integrated
{
	return (t-X*X-Y*Y)*(1+Z*Z-t)*sqrt(Lambda(t, X*X, Y*Y)*Lambda(1, t, Z*Z)) / t;
}

double Kine::I1_xyz(double X, double Y, double Z)
{
	double A = (1-Z)*(1-Z);
	double B = (X+Y)*(X+Y);
	if (A > B)
	{
		double tmp = B;
		B = A;
		A = tmp;
	}
	double a, b;
	double h = (B-A)/Sample;
	double Integral = 0;	//Boole's method for integration
	for (a = A; b < B; a = b)
	{
		b = a + h;
		Integral += h/90.0 * (7*I1_f(a, X, Y, Z) + 
				      32*I1_f((3*a+b)/4.0, X, Y, Z) + 
				      12*I1_f((a+b)/2.0, X, Y, Z) + 
				      32*I1_f((a+3*b)/4.0, X, Y, Z) +
				      7*I1_f(b, X, Y, Z));
	}	
	return 12.0 * Integral;
}

double Kine::I1_xy(double X, double Y)
{
	return ((1+X-Y)*(1+X) - 4*X) * sqrt(Lambda(1.0, X, Y));
}

double Kine::I2_f(double t, double X, double Y, double Z)	//To be integrated
{
	return (1+X*X-t)*sqrt(Lambda(t, Y*Y, Z*Z))*sqrt(Lambda(1.0, t, X*X)) / t;
}

double Kine::I2_xyz(double X, double Y, double Z)
{
	double A = (1-X)*(1-X);
	double B = (Y+Z)*(Y+Z);
	if (A > B)
	{
		double tmp = B;
		B = A;
		A = tmp;
	}
	double a, b;
	double h = (B-A)/Sample;
	double Integral = 0.0;	//Boole's method for integration
	for (a = A; b < B; a = b)
	{
		b = a + h;
		Integral += h/90.0 * (7*I2_f(a, X, Y, Z) + 
				      32*I2_f((3*a+b)/4.0, X, Y, Z) + 
				      12*I2_f((a+b)/2.0, X, Y, Z) + 
				      32*I2_f((a+3*b)/4.0, X, Y, Z) +
				      7*I2_f(b, X, Y, Z));
	}	
	return 24.0*Y*Z * Integral;
}

double Kine::I2_xy(double X, double Y)
{
	return ((1+X-Y)*(1+X+2*Y) - 4*X) * sqrt(Lambda(1.0, X, Y));
}

double Kine::I3_xy(double X, double Y)
{
	return (1+2*Y)*(1-Y) * sqrt(Lambda(1.0, X, Y));
}
