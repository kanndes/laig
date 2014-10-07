#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include "CGFobject.h"

#define PI 3.14159265
class myTriangle: public CGFobject
{
private:
	float angle;
	float a;
	float b;
	float c;
public:
	void draw(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);
};
#endif
