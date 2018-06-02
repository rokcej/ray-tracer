#ifndef _material_h
#define _material_h

#include "vect.h"

class Material {
private:
public:
    Vect color;
    double reflection;
    double transparency;
    double refractiveIndex;

    Material();
    Material(double r, double g, double b, double reflection, double transparency);
    Material(double r, double g, double b, double reflection, double transparency, double refractiveIndex);
};

#endif
