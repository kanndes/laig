#include "myUnitCube.h"


void myUnitCube::draw()
{
	glPushMatrix();
	glTranslated(0,0,0.5);
	//glRectd(-0.5,-0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-0.5,-0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(0.5,-0.5,0);
	glTexCoord2d(1,1);
	glVertex3f(0.5,0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(-0.5,0.5,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,-0.5);
	glRotated(180,1,0,0);
	//glRectd(-0.5,-0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-0.5,-0.5,0);
	glTexCoord2d(1,0);
	glVertex3f(0.5,-0.5,0);
	glTexCoord2d(1,1);
	glVertex3f(0.5,0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(-0.5,0.5,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,-0.5,0);
	glRotated(90,1,0,0);
	//glRectd(-0.5,-0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-0.5,-0.5,0);
	glTexCoord2d(1,0);
	glVertex3f(0.5,-0.5,0);
	glTexCoord2d(1,1);
	glVertex3f(0.5,0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(-0.5,0.5,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0.5,0);
	glRotated(270,1,0,0);
	//glRectd(-0.5,-0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-0.5,-0.5,0);
	glTexCoord2d(1,0);
	glVertex3f(0.5,-0.5,0);
	glTexCoord2d(1,1);
	glVertex3f(0.5,0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(-0.5,0.5,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.5,0,0);
	glRotated(270,0,1,0);
	//glRectd(-0.5,-0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-0.5,-0.5,0);
	glTexCoord2d(1,0);
	glVertex3f(0.5,-0.5,0);
	glTexCoord2d(1,1);
	glVertex3f(0.5,0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(-0.5,0.5,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.5,0,0);
	glRotated(90,0,1,0);
	//glRectd(-0.5,-0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-0.5,-0.5,0);
	glTexCoord2d(1,0);
	glVertex3f(0.5,-0.5,0);
	glTexCoord2d(1,1);
	glVertex3f(0.5,0.5,0);
	glTexCoord2d(0,1);
	glVertex3f(-0.5,0.5,0);
	glEnd();
	glPopMatrix();
}


