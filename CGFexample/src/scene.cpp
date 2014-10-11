#include "scene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFscene.h"
#include "XMLscene.h"
#include "myUnitCube.h"
#include "myRectangle.h"
#include "myCylinder.h"
#include "mySphere.h"
#include "myTriangle.h"

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

std::vector<CGFlight*> lights;
std::vector<CGFcamera*> cameras;
std::vector<nodee> nodesvector;
std::vector<nodee> nodesvector2;


void scene::init() 
{
	XMLScene *qwerty;
	qwerty=new XMLScene("D:\\Documentos\\Universidade\\4.º ano\\1.º semestre\\Laboratório de Aplicações com Interface Gráfica\\laig\\CGFexample\\src\\default.anf");
	nodesvector=qwerty->getNodesvectorFull();

	float globalAmbientLight[4]={0,0,0,0};
	float backgroundvalues[4]={0,0,0,0};

	backgroundvalues[0]=qwerty->getGlobalAmbientLight(0);
	backgroundvalues[1]=qwerty->getGlobalAmbientLight(1);
	backgroundvalues[2]=qwerty->getGlobalAmbientLight(2);
	backgroundvalues[3]=qwerty->getGlobalAmbientLight(3);

	char * drawmode=qwerty->getDrawmode1();
	char * shading=qwerty->getShading1();
	char * cullface=qwerty->getCullface1();
	char * cullorder=qwerty->getCullorder1();

	globalAmbientLight[0]=qwerty->getLightingValuesAmbient(0);
	globalAmbientLight[1]=qwerty->getLightingValuesAmbient(1);
	globalAmbientLight[2]=qwerty->getLightingValuesAmbient(2);
	globalAmbientLight[3]=qwerty->getLightingValuesAmbient(3);

	if(qwerty->getLightingEnabled())
	{
		glEnable(GL_LIGHTING);
	}
	if(qwerty->getLightingDoubleSided())
	{
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	}
	else
	{
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	}
	if(qwerty->getLightingLocal())
	{
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	}
	else
	{
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbientLight); 

	for(int i=0;i<qwerty->getPerspectiveSize();i++)
	{
		CGFcamera* camera0;
		camera0 = new CGFcamera();
		camera0->setX(qwerty->getPerspectiveCameras(i).pos[0]);
		camera0->setY(qwerty->getPerspectiveCameras(i).pos[1]);
		camera0->setZ(qwerty->getPerspectiveCameras(i).pos[2]);

		cameras.push_back(camera0);
	}

	for(int i=0;i<qwerty->getOmniSize();i++)
	{
		CGFlight* light0;
		float light0_pos[4]={0,0,0,0};
		light0_pos[0]=qwerty->getOmniLights(i).location[0];
		light0_pos[1]=qwerty->getOmniLights(i).location[1];
		light0_pos[2]=qwerty->getOmniLights(i).location[2];
		light0_pos[3]=qwerty->getOmniLights(i).location[3];
		light0 = new CGFlight(GL_LIGHT0, light0_pos);
		light0_pos[0]=qwerty->getOmniLights(i).ambient[0];
		light0_pos[1]=qwerty->getOmniLights(i).ambient[1];
		light0_pos[2]=qwerty->getOmniLights(i).ambient[2];
		light0_pos[3]=qwerty->getOmniLights(i).ambient[3];
		light0->setAmbient(light0_pos);
		light0_pos[0]=qwerty->getOmniLights(i).diffuse[0];
		light0_pos[1]=qwerty->getOmniLights(i).diffuse[1];
		light0_pos[2]=qwerty->getOmniLights(i).diffuse[2];
		light0_pos[3]=qwerty->getOmniLights(i).diffuse[3];
		light0->setSpecular(light0_pos);
		light0_pos[0]=qwerty->getOmniLights(i).specular[0];
		light0_pos[1]=qwerty->getOmniLights(i).specular[1];
		light0_pos[2]=qwerty->getOmniLights(i).specular[2];
		light0_pos[3]=qwerty->getOmniLights(i).specular[3];
		light0->setSpecular(light0_pos);
		light0->disable();
		if(qwerty->getOmniLights(i).enabled)
			light0->enable();
		lights.push_back(light0);
	}
	for(int j=0;j<qwerty->getSpotSize();j++)
	{
		CGFlight* light0;
		float light0_pos[4]={0,0,0,0};
		light0_pos[0]=qwerty->getSpotLights(j).location[0];
		light0_pos[1]=qwerty->getSpotLights(j).location[1];
		light0_pos[2]=qwerty->getSpotLights(j).location[2];
		light0_pos[3]=qwerty->getSpotLights(j).location[3];
		light0 = new CGFlight(GL_LIGHT0, light0_pos);
		light0_pos[0]=qwerty->getSpotLights(j).ambient[0];
		light0_pos[1]=qwerty->getSpotLights(j).ambient[1];
		light0_pos[2]=qwerty->getSpotLights(j).ambient[2];
		light0_pos[3]=qwerty->getSpotLights(j).ambient[3];
		light0->setAmbient(light0_pos);
		light0_pos[0]=qwerty->getSpotLights(j).diffuse[0];
		light0_pos[1]=qwerty->getSpotLights(j).diffuse[1];
		light0_pos[2]=qwerty->getSpotLights(j).diffuse[2];
		light0_pos[3]=qwerty->getSpotLights(j).diffuse[3];
		light0->setSpecular(light0_pos);
		light0_pos[0]=qwerty->getSpotLights(j).specular[0];
		light0_pos[1]=qwerty->getSpotLights(j).specular[1];
		light0_pos[2]=qwerty->getSpotLights(j).specular[2];
		light0_pos[3]=qwerty->getSpotLights(j).specular[3];
		light0->setSpecular(light0_pos);
		light0->setAngle(qwerty->getSpotLights(j).angle);
		light0->setKq(qwerty->getSpotLights(j).exponent);
		light0->disable();
		if(qwerty->getSpotLights(j).enabled)
			light0->enable();
		lights.push_back(light0);
	}


	glEnable (GL_NORMALIZE);
}

void scene::display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CGFscene::activeCamera->applyView();
	/*for(int i=0;i<cameras.size();i++)
	{
	cameras[i]->applyView();
	}*/
	for(int i=0;i<lights.size();i++)
	{
		lights[i]->draw();
	}

	axis.draw();
	nodeMaster();
	glutSwapBuffers();
}

void scene::nodeMaster()
{
	for(int i=0; i<nodesvector.size();i++)
	{
		glPushMatrix();
		whileChildren(i);
		transformNode(i);
		drawNode(i);
		glPopMatrix();
		if(!(nodesvector[i].childs.noderefV.empty()))
		{
			for(int q=0;q<nodesvector[i].childs.noderefV.size();q++)
			{
				heritage p;
				p.id=nodesvector[i].childs.noderefV[q].id;
				p.formerInfo=nodesvector[i].id;
				insertHeritages(p);
			}
		}
	}
}

void scene::whileChildren(int w){
	for(int a=0; a<getHeritagesSize();a++)
	{
		if(strcmp(nodesvector[w].id,getHeritages(a).id)!=0)
		{
			for(int b=0; b<nodesvector.size();b++)
			{
				if(strcmp(getHeritages(a).id,nodesvector[b].id)!=0)
				{
					transformNode(b);
					whileChildren(b);
				}
			}
		}
	}
}

void scene::transformNode(int i)
{
	for(int j=0;j<nodesvector[i].transformations.size();j++)
	{
		if(nodesvector[i].transformations[j].scale1.factor[0]!=0)
		{
			glScalef(nodesvector[i].transformations[j].scale1.factor[0],nodesvector[i].transformations[j].scale1.factor[1],nodesvector[i].transformations[j].scale1.factor[2]);
		}
		if(nodesvector[i].transformations[j].rotate1.angle!=0)
		{
			if(nodesvector[i].transformations[j].rotate1.axis=="z")
				glRotatef(nodesvector[i].transformations[j].rotate1.angle,0,0,1);
			else if(nodesvector[i].transformations[j].rotate1.axis=="y")
				glRotatef(nodesvector[i].transformations[j].rotate1.angle,0,1,0);
			else 
				glRotatef(nodesvector[i].transformations[j].rotate1.angle,1,0,0);
		}
		if(nodesvector[i].transformations[j].translate1.to[0]!=0 || nodesvector[i].transformations[j].translate1.to[1]!=0 || nodesvector[i].transformations[j].translate1.to[2]!=0)
		{
			glTranslatef(nodesvector[i].transformations[j].translate1.to[0],nodesvector[i].transformations[j].translate1.to[1],nodesvector[i].transformations[j].translate1.to[2]);
		}
	}
}

void scene::drawNode(int i)
{
	/*for(int k=0;k<nodesvector[i].childs.noderefV.size();k++)
	{
	if(nodesvector[i].childs.noderefV[k].id=="origin");
	{
	myUnitCube* cube;
	cube= new myUnitCube();
	cube->draw();
	}
	}*/
	for(int k=0;k<nodesvector[i].childs.cylinderV.size();k++)
	{
		myCylinder* Cylinder;
		Cylinder=new myCylinder();
		Cylinder->draw(nodesvector[i].childs.cylinderV[k].base,nodesvector[i].childs.cylinderV[k].top,nodesvector[i].childs.cylinderV[k].height,nodesvector[i].childs.cylinderV[k].slices,nodesvector[i].childs.cylinderV[k].stacks);
	}
	for(int k=0;k<nodesvector[i].childs.rectangleV.size();k++)
	{
		myRectangle* Rectangle;
		Rectangle= new myRectangle();
		Rectangle->draw(nodesvector[i].childs.rectangleV[k].xy1[0],nodesvector[i].childs.rectangleV[k].xy1[1],nodesvector[i].childs.rectangleV[k].xy2[0],nodesvector[i].childs.rectangleV[k].xy2[1]);
	}
	for(int k=0;k<nodesvector[i].childs.triangleV.size();k++)
	{
		myTriangle* Triangle;
		Triangle= new myTriangle();
		Triangle->draw(nodesvector[i].childs.triangleV[k].xyz1[0],nodesvector[i].childs.triangleV[k].xyz1[1],nodesvector[i].childs.triangleV[k].xyz1[2],nodesvector[i].childs.triangleV[k].xyz2[0],nodesvector[i].childs.triangleV[k].xyz2[1],nodesvector[i].childs.triangleV[k].xyz2[2],nodesvector[i].childs.triangleV[k].xyz3[0],nodesvector[i].childs.triangleV[k].xyz3[1],nodesvector[i].childs.triangleV[k].xyz3[2]);
	}
	for(int k=0;k<nodesvector[i].childs.sphereV.size();k++)
	{
		mySphere* Sphere;
		Sphere= new mySphere();
		Sphere->draw(nodesvector[i].childs.sphereV[k].radius,nodesvector[i].childs.sphereV[k].slices,nodesvector[i].childs.sphereV[k].stacks);
	}
	for(int k=0;k<nodesvector[i].childs.torusV.size();k++)
	{

	}
}

int scene::getVisitedNodesSize()
{
	return visitedNodes.size();
}
int scene::getHeritagesSize()
{
	return heritages.size();
}
char * scene::getVisitedNodes(int n)
{
	return visitedNodes[n];
}
heritage scene::getHeritages(int n)
{
	return heritages[n];
}
void scene::insertVisitedNodes(char * n)
{
	visitedNodes.push_back(n);
}
void scene::insertHeritages(heritage n)
{
	heritages.push_back(n);
}