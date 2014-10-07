#include "myCylinder.h"

myCylinder::myCylinder()
{
		GLUquadricObj * cylinderBody=gluNewQuadric();
		GLUquadricObj * cylinderBase=gluNewQuadric();
		GLUquadricObj * cylinderTop=gluNewQuadric();
		this->cylinderBody=cylinderBody;
		this->cylinderBase=cylinderBase;
		this->cylinderTop=cylinderTop;
}

void myCylinder::draw(float base, float top, float height, int slices, int stacks){
	glPushMatrix();
	gluCylinder(cylinderBody, base, top, height, slices, stacks);
	glRotated(180,0,1,0);
	gluDisk(cylinderBase, 0, base, slices, 1);
	glRotated(180,0,1,0);
	glTranslatef(0,0,height);
	gluDisk(cylinderTop, 0, top, slices, 1);
	glEnd();
	glPopMatrix();
}
