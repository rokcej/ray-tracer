#include "ray.h"

Ray::Ray(Vect origin, Vect dir) {
	this->origin = origin;
	this->dir = dir;
}

Vect Ray::operator*(const double& t) {
	return origin + dir * t;
}
