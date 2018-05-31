#include "camera.h"

Camera::Camera() : Camera(0.0, 0.0, 0.0) {}
Camera::Camera(double xPos, double yPos, double zPos) {
	this->fov = 90;
	this->pos = Vect(xPos, yPos, zPos);
	this->dir = Vect(0.0, 0.0, 1.0).normalize();
	this->vx = Vect(1.0, 0.0, 0.0).normalize();
	this->vy = Vect(0.0, 1.0, 0.0).normalize();
}

