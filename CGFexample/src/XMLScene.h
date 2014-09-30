#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include <vector>
using namespace std;

struct translatee{
	float to[3];
};

struct rotatee{
	char * axis;
	float angle;
};

struct scalee{
	float factor[3];
};

struct transformse{
	translatee translate1;
	rotatee rotate1;
	scalee scale1;
};

struct rectanglee{
	float xy1[2];
	float xy2[2];
};

struct trianglee{
	float xyz1[3];
	float xyz2[3];
	float xyz3[3];
};

struct cylindere{
	float base;
	float top;
	float height;
	int slices;
	int stacks;
};

struct spheree{
	float radius;
	int slices;
	int stacks;
};

struct toruse{
	float inner;
	float outer;
	int slices;
	int loops;
};

struct nodereef{
	char *id;
};

struct children{
	std::vector<rectanglee> rectangleV;
	std::vector<trianglee> triangleV;
	std::vector<cylindere> cylinderV;
	std::vector<spheree> sphereV;
	std::vector<toruse> torusV;
	std::vector<nodereef> noderefV;
};

struct texture{
	char * id;
	char * file;
};

struct appearance{
	char * id;
	float emissive[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
	char * textureref;
	float texlength_s;
	float texlength_t;
};

struct nodee{
	char * id;
	std::vector<transformse> transformations;
	char * appearenceref;
	children childs;
	bool visited;
};

struct perspective{
	char * id;
	float near;
	float far;
	float angle;
	float pos[3];
	float target[3];
};

struct ortho{
	char * id;
	float near;
	float far;
	float left;
	float right;
	float top;
	float bottom;
};

struct omni{
	char * id;
	bool enabled;
	float location[3];
	float ambient[4];
	float diffuse[4];
	float specular[4];
};
struct spot{
	char * id;
	bool enabled;
	float location[3];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float angle;
	float exponent;
	float direction[3];
};

class XMLScene
{
public:
	XMLScene(char *filename);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	float getGlobalAmbientLight(int n);
	char * getDrawmode1();
	char * getShading1();
	char * getCullface1();
	char * getCullorder1();
	char * getCamerasInitial();
	bool getLightingDoubleSided();
	bool getLightingLocal();
	bool getLightingEnabled();
	float getLightingValuesAmbient(int n);
	omni getOmniLights(int n); 
	spot getSpotLights(int n);
	int getOmniSize();
	int getSpotSize();
	ortho getOrthoCameras(int n); 
	perspective getPerspectiveCameras(int n);
	int getOrthoSize();
	int getPerspectiveSize();
	texture getTextureEnum(int n);
	int getTextureEnumSize();
	appearance getAppearanceEnum(int n);
	int getAppearanceEnumSize();
	char * getRootid();
	nodee getNodesvector(int n);
	int getNodesvectorSize();
	std::vector<nodee> getNodesvectorFull();

protected:

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* textureElement;
	TiXmlElement* appearenceElement;
	TiXmlElement* graphElement;
	TiXmlElement* nodesElement;
	TiXmlElement* leavesElement;
	float globalAmbientLight[4];
	char * drawmode1;
	char * shading1;
	char * cullface1;
	char * cullorder1;
	char * camerasInitial;
	bool lightingDoubleSided;
	bool lightingLocal;
	bool lightingEnabled;
	float lightingValuesAmbient[4];
	std::vector<omni> omniLights;
	std::vector<spot> spotLights;
	std::vector<ortho> orthoCameras;
	std::vector<perspective> perspectiveCameras;
	std::vector<texture> textureEnum;
	std::vector<appearance> appearanceEnum;
	char * rootid;
	std::vector<nodee> nodesvector;
};

#endif