#ifndef MYCYLINDER_H
#define MYCYLINDER_H

#include "CGFobject.h"

class myCylinder : public CGFobject {
private:
	GLUquadricObj * cylinderBody;
	GLUquadricObj * cylinderBase;
	GLUquadricObj * cylinderTop;
public:
	void draw(float base, float top, float height, int slices, int stacks);
	myCylinder();
	~myCylinder(){};
};
#endif