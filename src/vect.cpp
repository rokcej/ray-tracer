#include "vect.h"

Vect::Vect() : Vect(0.0, 0.0, 0.0) {}
Vect::Vect(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vect Vect::copy() {
	return Vect(x, y, z);
}

Vect& Vect::normalize() {
	double len = length();
	if (len > 0) {
		x /= len;
		y /= len;
		z /= len;
	}
	return *this;
}

double Vect::length() {
	return sqrt(x*x + y*y + z*z);
}

Vect& Vect::operator+=(const Vect& v) { x += v.x; y += v.y; z += v.z; return *this; }
Vect& Vect::operator-=(const Vect& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vect& Vect::operator*=(const double& d) { x *= d; y *= d; z *= d; return *this; }
Vect& Vect::operator*=(const Vect& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
Vect& Vect::operator/=(const double& d) { return *this *= (1 / d); }
Vect& Vect::operator/=(const Vect& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

Vect Vect::operator+(const Vect& v) { return Vect(x+v.x, y+v.y, z+v.z); }
Vect Vect::operator-(const Vect& v) { return Vect(x-v.x, y-v.y, z-v.z); }
Vect Vect::operator*(const double& d) { return Vect(x*d, y*d, z*d); }
Vect Vect::operator*(const Vect& v) { return Vect(x*v.x, y*v.y, z*v.z); }
Vect Vect::operator/(const double& d) { return *this * (1 / d); }
Vect Vect::operator/(const Vect& v) { return Vect(x/v.x, y/v.y, z/v.z); }
