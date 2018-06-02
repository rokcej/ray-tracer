#include "material.h"

Material::Material() : Material(1.0, 1.0, 1.0, 0.0, 0.0) {}
Material::Material(double r, double g, double b, double reflection, double transparency) : Material(r, g, b, reflection, transparency, 1.0) {}
Material::Material(double r, double g, double b, double reflection, double transparency, double refractiveIndex) {
    this->color = Vect(r, g, b);
    this->reflection = reflection;
    this->transparency = transparency;
    this->refractiveIndex = refractiveIndex;
}
