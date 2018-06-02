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

// EllipticParaboloid
EllipticParaboloid::EllipticParaboloid(Material mat, double x, double y, double z, double a) : EllipticParaboloid(mat, x, y, z, a, a) {}
EllipticParaboloid::EllipticParaboloid(Material mat, double x, double y, double z, double a, double b) : Object(mat, x, y, z) {
	this->a = a;
	this->b = b;
}
double EllipticParaboloid::f(Vect& pt) {
	return pow((pt.x-pos.x) / a, 2) + pow((pt.y-pos.y) / b, 2) - (pt.z-pos.z);
}
double EllipticParaboloid::dfx(Vect& pt) {
	return 2.0 / (a*a) * (pt.x-pos.x);
}
double EllipticParaboloid::dfy(Vect& pt) {
	return 2.0 / (b*b) * (pt.z-pos.z);
}
double EllipticParaboloid::dfz(Vect& pt) {
	return -1.0;
}
