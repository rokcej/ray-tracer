#include "vect.h"

Vect::Vect() : Vect(0.0) {}
Vect::Vect(double d) : Vect(d, d, d) {}
Vect::Vect(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
// Return vector copy
Vect Vect::copy() {
	return Vect(x, y, z);
}
// Normalize vector
Vect& Vect::normalize() {
	double len = length();
	if (len > 0) {
		x /= len;
		y /= len;
		z /= len;
	}
	return *this;
}
// Return vector length
double Vect::length() {
	return sqrt(x*x + y*y + z*z);
}
// Return vector dot product
double Vect::dot(Vect& v) {
	return x * v.x + y * v.y + z * v.z;
}
// Add the vector so that each component doesn't exceed 1
void Vect::addBalanced(Vect& v) {
	x += (1.0 - x) * v.x;
	y += (1.0 - y) * v.y;
	z += (1.0 - z) * v.z;
}
// Check if vectors are equal
int Vect::equals(Vect& v) {
	return x == v.x && y == v.y && z == v.z;
}

// Overload operators
Vect& Vect::operator+=(const Vect& v) { x += v.x; y += v.y; z += v.z; return *this; }
Vect& Vect::operator-=(const Vect& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vect& Vect::operator*=(const double& d) { x *= d; y *= d; z *= d; return *this; }
Vect& Vect::operator*=(const Vect& v) { x *= v.x; y *= v.y; z *= v.z; return *this; } // Not dot product
Vect& Vect::operator/=(const double& d) { return *this *= (1 / d); }
Vect& Vect::operator/=(const Vect& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

Vect Vect::operator+(const Vect& v) { return Vect(x+v.x, y+v.y, z+v.z); }
Vect Vect::operator-(const Vect& v) { return Vect(x-v.x, y-v.y, z-v.z); }
Vect Vect::operator*(const double& d) { return Vect(x*d, y*d, z*d); }
Vect Vect::operator*(const Vect& v) { return Vect(x*v.x, y*v.y, z*v.z); } // Not dot product
Vect Vect::operator/(const double& d) { return *this * (1 / d); }
Vect Vect::operator/(const Vect& v) { return Vect(x/v.x, y/v.y, z/v.z); }
