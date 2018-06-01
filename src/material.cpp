#include "material.h"

Material::Material() : Material(1.0, 1.0, 1.0, 0.0, 0.0) {}
Material::Material(double r, double g, double b, double reflection, double transparency) {
    this->color = Vect(r, g, b);
    this->reflection = reflection;
    this->transparency = transparency;
}
