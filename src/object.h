#ifndef _object_h
#define _object_h

#include "vect.h"
#include <math.h>

class Object {
private:
protected:
	Vect pos;
public:
	Object(double x, double y, double z);

	virtual double f(Vect pt) {}
	virtual double dfx(Vect pt) {}
	virtual double dfy(Vect p) {}
	virtual double dfz(Vect pt) {}
};

class Sphere : public Object {
private:
protected:
	double r;
public:
	Sphere(double x, double y, double z, double r);

	double f(Vect pt);
	double dfx(Vect pt);
	double dfy(Vect p);
	double dfz(Vect pt);
};

#endif
