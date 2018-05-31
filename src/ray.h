#ifndef _ray_h
#define _ray_h

#include "vect.h"

class Ray {
private:
public:
	Vect origin;
	Vect dir;

	Ray(Vect origin, Vect dir);
};

#endif
