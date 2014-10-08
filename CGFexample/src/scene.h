#ifndef SCENE_H
#define SCENE_H
#include "CGFscene.h"
#include "CGFappearance.h"

struct heritage
{
	char * id;
	char * formerInfo;
};

class scene : public CGFscene
{
private:
	std::vector <char*> visitedNodes;
	std::vector <heritage> heritages;
public:
	void init();
	void display();
	void nodeMaster();
	void whileChildren(int w);
	void transformNode(int i);
	void drawNode(int i);
	int getVisitedNodesSize();
	int getHeritagesSize();
	char * getVisitedNodes(int n);
	heritage getHeritages(int n);
	void insertVisitedNodes(char * n);
	void insertHeritages(heritage n);
	//~scene();
};

#endif