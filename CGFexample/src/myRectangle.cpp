#include "myRectangle.h"


void myRectangle::draw(int x1, int y1, int x2, int y2)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2d(x1,y1);
	glVertex3f(x1,y1,0);
	glTexCoord2d(x1,y2);
	glVertex3f(x2,y1,0);
	glTexCoord2d(x2,y2);
	glVertex3f(x2,y2,0);
	glTexCoord2d(x2,y1);
	glVertex3f(x1,y2,0);
	glEnd();
	glPopMatrix();
}