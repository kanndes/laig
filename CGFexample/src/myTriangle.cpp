#include "myTriangle.h"
#include <math.h>

void myTriangle::draw(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3)
{
	float aa=(x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)+(z1-z3)*(z1-z3);
	float bb=(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1);
	float cc=(x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+(z3-z2)*(z3-z2);
	this->a=sqrt(aa);
	this->b=sqrt(bb);
	this->c=sqrt(cc);
	float qq=(a*a-b*b+c*c)/(2*a*c);
	this->angle=cosh (qq) * 180.0 / PI;
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0,0);
	glVertex3f(x1,y1,z1);
	glTexCoord2f(c,0);
	glVertex3f(x2,y2,z2);
	glTexCoord2f(c-a*cos(angle),a*sin(angle));
	glVertex3f(x3,y3,z3);
	glEnd();
	glPopMatrix();
}