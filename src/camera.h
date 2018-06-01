#ifndef _camera_h
#define _camera_h

#include "vect.h"

class Camera {
private:
public:
	int width;
	int height;
	int fov;
	Vect pos;
	Vect dir;
	Vect vx;
	Vect vy;

	Camera();
	Camera(int width, int height, int fov);
	Camera(int width, int height, int fov, double xPos, double yPos, double zPos);
};

#endif
