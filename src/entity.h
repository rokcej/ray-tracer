#ifndef _entity_h
#define _entity_h

#include "vect.h"
#include "material.h"
#include <math.h>

class Light {
private:
public:
	Vect brightness;
	Vect pos;

	Light(double x, double y, double z, double brightness);
	Light(double x, double y, double z, double r, double g, double b);
};

class Object {
private:
protected:
	Vect pos;
public:
	Material mat;
	Object(Material mat, double x, double y, double z);

	virtual double f(Vect& pt) {}
	virtual double dfx(Vect& pt) {}
	virtual double dfy(Vect& pt) {}
	virtual double dfz(Vect& pt) {}
	Vect grad(Vect& pt);
};

class Sphere : public Object {
private:
protected:
	double r;
public:
	Sphere(Material mat, double x, double y, double z, double r);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};

class Plane : public Object {
private:
protected:
	Vect normal;
public:
	Plane(Material mat, double x, double y, double z);
	Plane(Material mat, double x, double y, double z, double a, double b, double c);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};

#endif
