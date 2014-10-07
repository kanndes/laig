#include "mySphere.h"

void mySphere::draw(float radius, int slices, int stacks)
{
	glPushMatrix();
	glutSolidSphere(radius,slices,stacks);
	glEnd();
	glPopMatrix();
}