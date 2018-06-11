#include "entity.h"

// Light
Light::Light(double x, double y, double z, double d) : Light(x, y, z, d, d, d) {}
Light::Light(double x, double y, double z, double r, double g, double b) {
	this->pos = Vect(x, y, z);
	this->brightness = Vect(r, g, b);
}

// Object
Object::Object(Material mat, double x, double y, double z) {
	this->pos = Vect(x, y, z);
	this->mat = mat;
}
Vect Object::grad(Vect& pt) {
	return Vect(dfx(pt), dfy(pt), dfz(pt));
}

// Plane
Plane::Plane(Material mat, double x, double y, double z) : Plane(mat, x, y, z, 0.0, 1.0, 0.0) {}
Plane::Plane(Material mat, double x, double y, double z, double a, double b, double c) : Object(mat, x, y, z) {
	this->normal = Vect(a, b, c).normalize();
}
double Plane::f(Vect& pt) {
	return (pt - pos).dot(normal);
}
double Plane::dfx(Vect& pt) {
	return normal.x;
}
double Plane::dfy(Vect& pt) {
	return normal.y;
}
double Plane::dfz(Vect& pt) {
	return normal.z;
}

// Elllipsoid
Ellipsoid::Ellipsoid(Material mat, double x, double y, double z, double a, double b, double c) : Object(mat, x, y, z) {
	this->a = a;
	this->b = b;
	this->c = c;
}
double Ellipsoid::f(Vect& pt) {
	return pow((pt.x-pos.x) / a, 2) + pow((pt.y-pos.y) / b, 2) + pow((pt.z-pos.z) / c, 2) - 1;
}
double Ellipsoid::dfx(Vect& pt) {
	return 2.0 / (a*a) * (pt.x-pos.x);
}
double Ellipsoid::dfy(Vect& pt) {
	return 2.0 / (b*b) * (pt.y - pos.y);
}
double Ellipsoid::dfz(Vect& pt) {
	return 2.0 / (c*c) * (pt.z - pos.z);
}
// Sphere
Sphere::Sphere(Material mat, double x, double y, double z, double r) : Ellipsoid(mat, x, y, z, r, r, r) {} // Shorter, but slower
/*Sphere::Sphere(Material mat, double x, double y, double z, double r) : Object(mat, x, y, z) {
	this->r = r;
}
double Sphere::f(Vect& pt) {
	return pow(pt.x-pos.x, 2) + pow(pt.y-pos.y, 2) + pow(pt.z-pos.z, 2) - r*r;
}
double Sphere::dfx(Vect& pt) {
	return 2.0 * (pt.x-pos.x);
}
double Sphere::dfy(Vect& pt) {
	return 2.0 * (pt.y-pos.y);
}
double Sphere::dfz(Vect& pt) {
	return 2.0 * (pt.z-pos.z);
}*/

// Torus
Torus::Torus(Material mat, double x, double y, double z, double R, double r) : Object(mat, x, y, z) {
	this->R = R;
	this->r = r;
}
double Torus::f(Vect& pt) {
	return pow(sqrt(pow(pt.x-pos.x, 2) + pow(pt.y-pos.y, 2)) - R, 2) + pow(pt.z-pos.z, 2) - r*r;
}
double Torus::dfx(Vect& pt) {
	return 2.0 * (pt.x - pos.x) * (1.0 - R / sqrt(pow(pt.x-pos.x, 2) + pow(pt.y-pos.y, 2)));
}
double Torus::dfy(Vect& pt) {
	return 2.0 * (pt.y - pos.y) * (1.0 - R / sqrt(pow(pt.x-pos.x, 2) + pow(pt.y-pos.y, 2)));
}
double Torus::dfz(Vect& pt) {
	return 2.0 * (pt.z - pos.z);
}
// Torus aligned with y axis
TorusY::TorusY(Material mat, double x, double y, double z, double R, double r) : Torus(mat, x, y, z, R, r) {}
double TorusY::f(Vect& pt) {
	return pow(sqrt(pow(pt.x-pos.x, 2) + pow(pt.z-pos.z, 2)) - R, 2) + pow(pt.y-pos.y, 2) - r*r;
}
double TorusY::dfx(Vect& pt) {
	return 2.0 * (pt.x - pos.x) * (1.0 - R / sqrt(pow(pt.x-pos.x, 2) + pow(pt.z-pos.z, 2)));
}
double TorusY::dfy(Vect& pt) {
	return 2.0 * (pt.y - pos.y);
}
double TorusY::dfz(Vect& pt) {
	return 2.0 * (pt.z - pos.z) * (1.0 - R / sqrt(pow(pt.x-pos.x, 2) + pow(pt.z-pos.z, 2)));
}

// EllipticParaboloid
EllipticParaboloid::EllipticParaboloid(Material mat, double x, double y, double z, double a) : EllipticParaboloid(mat, x, y, z, a, a) {}
EllipticParaboloid::EllipticParaboloid(Material mat, double x, double y, double z, double a, double b) : Object(mat, x, y, z) {
	this->a = a;
	this->b = b;
}
double EllipticParaboloid::f(Vect& pt) {
	return pow((pt.x-pos.x) / a, 2) + pow((pt.z-pos.z) / b, 2) - (pt.y-pos.y);
}
double EllipticParaboloid::dfx(Vect& pt) {
	return 2.0 / (a*a) * (pt.x-pos.x);
}
double EllipticParaboloid::dfy(Vect& pt) {
	return -1.0;
}
double EllipticParaboloid::dfz(Vect& pt) {
	return 2.0 / (b*b) * (pt.z-pos.z);
}

// Heart
Heart::Heart(Material mat, double x, double y, double z) : Object(mat, x, y, z) {}
double Heart::f(Vect& pt) {
	double x = pt.x - pos.x;
	double y = pt.y - pos.y;
	double z = pt.z - pos.z;
	return pow(x*x + 2.25*z*z + y*y - 1, 3) - x*x*y*y*y - 0.1125*z*z*y*y*y;
}
double Heart::dfx(Vect& pt) {
	double x = pt.x - pos.x;
	double y = pt.y - pos.y;
	double z = pt.z - pos.z;
	return 6.0 * x * pow(x*x + 2.25*z*z + y*y - 1, 2) - 2*x*y*y*y;
}
double Heart::dfy(Vect& pt) {
	double x = pt.x - pos.x;
	double y = pt.y - pos.y;
	double z = pt.z - pos.z;
	return 6.0 * y * pow(x*x + 2.25*z*z + y*y - 1, 2) - 3*x*x*y*y - 0.3375*z*z*y*y;
}
double Heart::dfz(Vect& pt) {
	double x = pt.x - pos.x;
	double y = pt.y - pos.y;
	double z = pt.z - pos.z;
	return 13.5 * z * pow(x*x + 2.25*z*z + y*y - 1, 2) - 0.225*z*y*y*y;
}

// Liquid
Liquid::Liquid(Material mat, double x, double y, double z, double a) : Liquid(mat, x, y, z, a, a, a) {}
Liquid::Liquid(Material mat, double x, double y, double z, double a, double b, double c) : Object(mat, x, y, z) {
	this->a = a;
	this->b = b;
	this->c = c;
}
double Liquid::f(Vect& pt) {	
	return (pt.z - pos.z) - (a * pow((pt.x - pos.x), 3) + b * (pt.x - pos.x) + c * pow((pt.y - pos.y), 2));
}
double Liquid::dfx(Vect& pt) {	
	return -(3 * a * pow((pt.x - pos.x), 2) + b);
}
double Liquid::dfy(Vect& pt) {	
	return -2 * c * (pt.y - pos.y);	
}
double Liquid::dfz(Vect& pt) {	
	return 1.0;
}

// Vibration
Vibration::Vibration(Material mat, double x, double y, double z, double a) : Vibration(mat, x, y, z, a, a, a) {}
Vibration::Vibration(Material mat, double x, double y, double z, double a, double b, double c) : Object(mat, x, y, z) {
	this->a = a;
	this->b = b;
	this->c = c;
}
double Vibration::f(Vect& pt) {
	return (pt.z - pos.z) - pow(sin(sqrt((pt.x - pos.x) * (pt.x - pos.x) + (pt.y - pos.y) * (pt.y - pos.y))), 2);
}
double Vibration::dfx(Vect& pt) {
	double tmp = sqrt((pt.x - pos.x) * (pt.x - pos.x) + (pt.y - pos.y) * (pt.y - pos.y));
	
	return -4 * sin(tmp) * cos(tmp) * (pt.x - pos.x)/ tmp;
}
double Vibration::dfy(Vect& pt) {
	double tmp = sqrt((pt.x - pos.x) * (pt.x - pos.x) + (pt.y - pos.y) * (pt.y - pos.y));
	
	return -4 * sin(tmp) * cos(tmp) * (pt.y - pos.y) / tmp;
}
double Vibration::dfz(Vect& pt) {
	return 1.0;
}
