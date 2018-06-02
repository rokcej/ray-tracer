#include "material.h"

Material::Material() : Material(1.0, 1.0, 1.0, 0.0, 0.0) {}
Material::Material(int r, int g, int b, double refl, double trans) : Material(r, g, b, refl, trans, 1.0) {}
Material::Material(int r, int g, int b, double refl, double trans, double refr) : Material(r/255.0, g/255.0, b/255.0, refl, trans, refr) {}
Material::Material(double r, double g, double b, double refl, double trans) : Material(r, g, b, refl, trans, 1.0) {}
Material::Material(double r, double g, double b, double refl, double trans, double refr) {
    this->color = Vect(r, g, b);
    this->reflection = refl;
    this->transparency = trans;
    this->refractiveIndex = refr;
}
