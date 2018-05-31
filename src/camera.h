#ifndef _camera_h
#define _camera_h

#include "vect.h"

class Camera {
private:
public:
	int fov;
	Vect pos;
	Vect dir;
	Vect vx;
	Vect vy;

	Camera();
	Camera(double xPos, double yPos, double zPos);
};

#endif
