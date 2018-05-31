#ifndef _vect_h
#define _vect_h

#include <math.h>

class Vect {
private:
public:
	double x;
	double y;
	double z;

	Vect();
	Vect(double x, double y, double z);

	Vect copy();
	Vect& normalize();
	double length();

	Vect& operator+=(const Vect& v);
	Vect& operator-=(const Vect& v);
	Vect& operator*=(const double& d);
	Vect& operator*=(const Vect& v);
	Vect& operator/=(const double& d);
	Vect& operator/=(const Vect& v);

	Vect operator+(const Vect& v);
	Vect operator-(const Vect& v);
	Vect operator*(const double& d);
	Vect operator*(const Vect& v);
	Vect operator/(const double& d);
	Vect operator/(const Vect& v);
};

#endif
