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

	virtual double f(Vect& pt) = 0; // Object function
	virtual double dfx(Vect& pt) = 0; // Partial derivative of x
	virtual double dfy(Vect& pt) = 0; // Partial derivative of y
	virtual double dfz(Vect& pt) = 0; // Partial derivative of z
	Vect grad(Vect& pt); // Gradient
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

class Ellipsoid : public Object {
private:
protected:
	double a;
	double b;
	double c;
public:
	Ellipsoid(Material mat, double x, double y, double z, double a, double b, double c);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};
class Sphere : public Ellipsoid {
private:
protected:
public:
	Sphere(Material mat, double x, double y, double z, double r);
};

class Torus : public Object {
private:
protected:
	double R; // Center radius
	double r; // Tube radius
public:
	Torus(Material mat, double x, double y, double z, double R, double r);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};
class TorusY : public Torus {
private:
protected:
public:
	TorusY(Material mat, double x, double y, double z, double R, double r);

	double f(Vect& pt) override;
	double dfx(Vect& pt) override;
	double dfy(Vect& pt) override;
	double dfz(Vect& pt) override;
};

class EllipticParaboloid : public Object {
private:
protected:
	double a;
	double b;
public:
	EllipticParaboloid(Material mat, double x, double y, double z, double a);
	EllipticParaboloid(Material mat, double x, double y, double z, double a, double b);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};

class Heart : public Object {
private:
protected:
public:
	Heart(Material mat, double x, double y, double z);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};

class Liquid : public Object {
private:
protected:
	double a;
	double b;
    double c;
public:
    Liquid(Material mat, double x, double y, double z, double a);	
    Liquid(Material mat, double x, double y, double z, double a, double b, double c);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};

class Vibration : public Object {
private:
protected:
	double a;
	double b;
    double c;
public:
    Vibration(Material mat, double x, double y, double z, double a);	
    Vibration(Material mat, double x, double y, double z, double a, double b, double c);

	double f(Vect& pt);
	double dfx(Vect& pt);
	double dfy(Vect& pt);
	double dfz(Vect& pt);
};

#endif
