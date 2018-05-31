#include "entity.h"

Light::Light(double x, double y, double z, double brightness) {
	this->pos = Vect(x, y, z);
	this->brightness = brightness;
}

Object::Object(double x, double y, double z) {
	this->pos = Vect(x, y, z);
}

Sphere::Sphere(double x, double y, double z, double r) : Object(x, y, z) {
	this->r = r;
}
double Sphere::f(Vect pt) {
	return pow(pt.x - pos.x, 2) + pow(pt.y - pos.y, 2) + pow(pt.z - pos.z, 2) - pow(r, 2);
}
double Sphere::dfx(Vect pt) {
	return 2.0 * (pt.x - pos.x);
}
double Sphere::dfy(Vect pt) {
	return 2.0 * (pt.y - pos.y);
}
double Sphere::dfz(Vect pt) {
	return 2.0 * (pt.z - pos.z);
}
