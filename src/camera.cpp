#include "camera.h"

Camera::Camera() {}
Camera::Camera(int width, int height, int fov) : Camera(width, height, fov, 0.0, 0.0, 0.0) {}
Camera::Camera(int width, int height, int fov, double xPos, double yPos, double zPos) {
	this->width = width;
	this->height = height;
	this->fov = fov;
	this->pos = Vect(xPos, yPos, zPos);
	this->dir = Vect(0.0, 0.0, 1.0).normalize();
	this->vx = Vect(1.0, 0.0, 0.0).normalize();
	this->vy = Vect(0.0, 1.0, 0.0).normalize();
}

