#ifndef MYSPHERE_H
#define MYSPHERE_H

#include "CGFobject.h"

class mySphere : public CGFobject {
public:
	void draw(float radius, int slices, int stacks);
	~mySphere(){};
};
#endif