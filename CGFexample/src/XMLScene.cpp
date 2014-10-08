#include "XMLScene.h"
#include <string>
using namespace std;
XMLScene::XMLScene(char *filename)
{

	// Read XML from file

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		exit( 1 );
	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}

	globalsElement = anfElement->FirstChildElement( "globals" );
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightingElement =  anfElement->FirstChildElement( "lighting" );
	nodesElement =  anfElement->FirstChildElement( "nodes" );
	textureElement = anfElement->FirstChildElement("textures");
	appearenceElement = anfElement->FirstChildElement("appearances");
	graphElement =  anfElement->FirstChildElement( "graph" );


	// Init
	// An example of well-known, required nodes

	if (globalsElement == NULL)
		printf("Globals block not found!\n");
	else
	{
		printf("Processing globals:\n");
		bool backgroundElement = false;

		if(globalsElement->Attribute("background"))
		{
			backgroundElement=true;
		}


		if (backgroundElement)
		{
			float f1,f2,f3,f4;
			char *valString=NULL;
			valString=(char *) globalsElement->Attribute("background");
			if(valString && sscanf(valString,"%f %f %f %f",&f1, &f2, &f3, &f4)==4)
			{
				printf("background values: %f %f %f %f\n", f1,f2,f3,f4);
				globalAmbientLight[0]=f1;
				globalAmbientLight[1]=f2;
				globalAmbientLight[2]=f3;
				globalAmbientLight[3]=f4;
			}
		}
		else
		{
			printf("background not found\n");
		}
		bool drawmodeElement = false;

		if(globalsElement->Attribute("drawmode"))
		{
			drawmodeElement=true;
		}
		if (drawmodeElement)
		{
			char * drawmode;
			drawmode=(char *) globalsElement->Attribute("drawmode");
			printf("drawmode value: %s\n", drawmode);
			drawmode1=drawmode;
		}
		else
		{
			printf("drawmode not found\n");
		}

		bool shadingElement = false;

		if(globalsElement->Attribute("shading"))
		{
			shadingElement=true;
		}
		if (shadingElement)
		{
			char *shading;
			shading=(char *) globalsElement->Attribute("shading");
				printf("shading value: %s\n", shading);
				shading1=shading;
		}
		else
		{
			printf("shading not found\n");
		}

		bool cullfaceElement = false;

		if(globalsElement->Attribute("cullface"))
		{
			cullfaceElement=true;
		}
		if (cullfaceElement)
		{
			char *cullface;
			cullface=(char *) globalsElement->Attribute("cullface");
				printf("cullface value: %s\n", cullface);
				cullface1=cullface;
		}
		else
		{
			printf("cullface not found\n");
		}

		bool cullorderElement = false;

		if(globalsElement->Attribute("cullorder"))
		{
			cullorderElement=true;
		}
		if (cullorderElement)
		{
			char *cullorder;
			cullorder=(char *) globalsElement->Attribute("cullorder");
				printf("cullorder value: %s\n", cullorder);
				cullorder1=cullorder;
		}
		else
		{
			printf("cullorder not found\n");
		}
	}

	if (camerasElement == NULL)
		printf("Cameras block not found!\n");
	else
	{
		printf("Processing cameras:\n");
		bool initialElement = false;

		if(camerasElement->Attribute("initial"))
		{
			initialElement=true;
		}
		if (initialElement)
		{
			char *initial;
			initial=(char *) camerasElement->Attribute("initial");
				printf("camera name: %s\n", initial);
				camerasInitial=initial;
		}
		else
		{
			printf("initial not found\n");
		}

		TiXmlElement* perspectiveElement=camerasElement->FirstChildElement("perspective");
		if(perspectiveElement)
			do{
				if(perspectiveElement)
				{
					perspective temp;
					bool idElement = false;

					if(perspectiveElement->Attribute("id"))
					{
						idElement=true;
					}
					if (idElement)
					{
						char *id;
						id=(char *) perspectiveElement->Attribute("id");
							printf("id: %s\n", id);
							temp.id=id;
					}
					else
					{
						printf("id not found\n");
					}

					bool nearElement = false;

					if(perspectiveElement->Attribute("near"))
					{
						nearElement=true;
					}
					if (nearElement)
					{
						float near;
						char *valString=NULL;
						valString=(char *) perspectiveElement->Attribute("near");
						if(valString && sscanf(valString,"%f",&near)==1)
						{
							printf("near value: %f\n", near);
							temp.near=near;
						}
						else
						{
							printf("Error parsing near\n");
						}
					}
					else
					{
						printf("near not found\n");
					}

					bool farElement = false;

					if(perspectiveElement->Attribute("far"))
					{
						farElement=true;
					}
					if (farElement)
					{
						float far;
						char *valString=NULL;
						valString=(char *) perspectiveElement->Attribute("far");
						if(valString && sscanf(valString,"%f",&far)==1)
						{
							printf("far value: %f\n", far);
							temp.far=far;
						}
						else
						{
							printf("Error parsing far\n");
						}
					}
					else
					{
						printf("far not found\n");
					}

					bool angleElement = false;

					if(perspectiveElement->Attribute("angle"))
					{
						angleElement=true;
					}
					if (angleElement)
					{
						float angle;
						char *valString=NULL;
						valString=(char *) perspectiveElement->Attribute("angle");
						if(valString && sscanf(valString,"%f",&angle)==1)
						{
							printf("angle value: %f\n", angle);
							temp.angle=angle;
						}
						else
						{
							printf("Error parsing angle\n");
						}
					}
					else
					{
						printf("angle not found\n");
					}

					bool posElement = false;

					if(perspectiveElement->Attribute("pos"))
					{
						posElement=true;
					}
					if (posElement)
					{
						float x,y,z;
						char *valString=NULL;
						valString=(char *) perspectiveElement->Attribute("pos");
						if(valString && sscanf(valString,"%f %f %f",&x,&y,&z)==3)
						{
							printf("pos values: %f %f %f\n", x,y,z);
							temp.pos[0]=x;
							temp.pos[1]=y;
							temp.pos[2]=z;
						}
						else
						{
							printf("Error parsing pos\n");
						}
					}
					else
					{
						printf("pos not found\n");
					}

					bool targetElement = false;

					if(perspectiveElement->Attribute("target"))
					{
						targetElement=true;
					}
					if (targetElement)
					{
						float x,y,z;
						char *valString=NULL;
						valString=(char *) perspectiveElement->Attribute("target");
						if(valString && sscanf(valString,"%f %f %f",&x,&y,&z)==3)
						{
							printf("target values: %f %f %f\n", x,y,z);
							temp.target[0]=x;
							temp.target[1]=y;
							temp.target[2]=z;
						}
						else
						{
							printf("Error parsing target\n");
						}
					}
					else
					{
						printf("target not found\n");
					}
					perspectiveCameras.push_back(temp);
				}
				
				if(perspectiveElement->NextSiblingElement())
				{
					perspectiveElement=perspectiveElement->NextSiblingElement();
				}
				else
				{
					break;
				}

			}while(1);

		TiXmlElement* orthoElement=camerasElement->FirstChildElement("ortho");
		if(orthoElement)
			do{
				if(orthoElement)
				{
					ortho temp;
					bool idElement = false;

					if(orthoElement->Attribute("id"))
					{
						idElement=true;
					}
					if (idElement)
					{
						char *id;
						id=(char *) orthoElement->Attribute("id");
							printf("id: %s\n", id);
							temp.id=id;
					}
					else
					{
						printf("id not found\n");
					}

					bool nearElement = false;

					if(orthoElement->Attribute("near"))
					{
						nearElement=true;
					}
					if (nearElement)
					{
						float near;
						char *valString=NULL;
						valString=(char *) orthoElement->Attribute("near");
						if(valString && sscanf(valString,"%f",&near)==1)
						{
							printf("near value: %f\n", near);
							temp.near=near;
						}
						else
						{
							printf("Error parsing near\n");
						}
					}
					else
					{
						printf("near not found\n");
					}

					bool farElement = false;

					if(orthoElement->Attribute("far"))
					{
						farElement=true;
					}
					if (farElement)
					{
						float far;
						char *valString=NULL;
						valString=(char *) orthoElement->Attribute("far");
						if(valString && sscanf(valString,"%f",&far)==1)
						{
							printf("far value: %f\n", far);
							temp.far=far;
						}
						else
						{
							printf("Error parsing far\n");
						}
					}
					else
					{
						printf("far not found\n");
					}

					bool leftElement = false;

					if(orthoElement->Attribute("left"))
					{
						leftElement=true;
					}
					if (leftElement)
					{
						float left;
						char *valString=NULL;
						valString=(char *) orthoElement->Attribute("left");
						if(valString && sscanf(valString,"%f",&left)==1)
						{
							printf("left value: %f\n", left);
							temp.left=left;
						}
						else
						{
							printf("Error parsing left\n");
						}
					}
					else
					{
						printf("left not found\n");
					}

					bool rightElement = false;

					if(orthoElement->Attribute("right"))
					{
						rightElement=true;
					}
					if (rightElement)
					{
						float right;
						char *valString=NULL;
						valString=(char *) orthoElement->Attribute("right");
						if(valString && sscanf(valString,"%f",&right)==1)
						{
							printf("right value: %f\n", right);
							temp.right=right;
						}
						else
						{
							printf("Error parsing right\n");
						}
					}
					else
					{
						printf("right not found\n");
					}

					bool topElement = false;

					if(orthoElement->Attribute("top"))
					{
						topElement=true;
					}
					if (topElement)
					{
						float top;
						char *valString=NULL;
						valString=(char *) orthoElement->Attribute("top");
						if(valString && sscanf(valString,"%f",&top)==1)
						{
							printf("top value: %f\n",top);
							temp.top=top;
						}
						else
						{
							printf("Error parsing top\n");
						}
					}
					else
					{
						printf("top not found\n");
					}

					bool bottomElement = false;

					if(orthoElement->Attribute("bottom"))
					{
						bottomElement=true;
					}
					if (bottomElement)
					{
						float bottom;
						char *valString=NULL;
						valString=(char *) orthoElement->Attribute("bottom");
						if(valString && sscanf(valString,"%f",&bottom)==1)
						{
							printf("bottom value: %f\n",bottom);
							temp.bottom=bottom;
						}
						else
						{
							printf("Error parsing bottom\n");
						}
					}
					else
					{
						printf("bottom not found\n");
					}
					orthoCameras.push_back(temp);
				}
				if(orthoElement->NextSiblingElement())
				{
					orthoElement=orthoElement->NextSiblingElement();
				}
				else
				{
					break;
				}
			}while(1);
	}
	if (lightingElement == NULL)
		printf("Lighting block not found!\n");
	else
	{
		
		printf("Processing lighting:\n");
		bool doublesidedElement = false;

		if(lightingElement->Attribute("doublesided"))
		{
			doublesidedElement=true;
		}
		if (doublesidedElement)
		{
			char *doublesided;
			char *valString=NULL;
			valString=(char *) lightingElement->Attribute("doublesided");
			
				printf("doublesided value: %s\n", valString);
				if(strcmp("true\n",valString)!=0)
					lightingDoubleSided=true;
				else lightingDoubleSided=false;
			
		}
		else
		{
			printf("doublesided not found\n");
		}

		bool localElement = false;

		if(lightingElement->Attribute("local"))
		{
			localElement=true;
		}
		if (localElement)
		{
			char *local;
			char *valString=NULL;
			valString=(char *) lightingElement->Attribute("local");
			
				printf("local value: %s\n", valString);
				if(strcmp("true\n",valString)!=0)
					lightingLocal=true;
				else lightingLocal=false;
			
		}
		else
		{
			printf("local not found\n");
		}

		bool enabledElement = false;

		if(lightingElement->Attribute("enabled"))
		{
			enabledElement=true;
		}
		if (enabledElement)
		{
			char *enabled;
			char *valString=NULL;
			valString=(char *) lightingElement->Attribute("enabled");
			
				printf("enabled value: %s\n", valString);
				if(strcmp("true\n",valString)!=0)
					lightingEnabled=true;
				else lightingEnabled=false;
			
		}
		else
		{
			printf("enabled not found\n");
		}

		bool ambientElement = false;

		if(lightingElement->Attribute("ambient"))
		{
			ambientElement=true;
		}
		if (ambientElement)
		{
			float f1,f2,f3,f4;
			char *valString=NULL;
			valString=(char *) lightingElement->Attribute("ambient");
			if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
			{
				printf("ambient values: %f %f %f %f\n", f1,f2,f3,f4);
				lightingValuesAmbient[0]=f1;
				lightingValuesAmbient[1]=f2;
				lightingValuesAmbient[2]=f3;
				lightingValuesAmbient[3]=f4;
			}
			else
			{
				printf("Error parsing ambient\n");
			}
		}
		else
		{
			printf("ambient not found\n");
		}
		TiXmlElement* omniElement=lightingElement->FirstChildElement("omni");
		if(omniElement)
			do{
				omni temp;
				bool idElement = false;

				if(omniElement->Attribute("id"))
				{
					idElement=true;
				}
				if (idElement)
				{
					char *id;
					id=(char *) omniElement->Attribute("id");
						printf("id: %s\n", id);
						temp.id=id;
				}
				else
				{
					printf("id not found\n");
				}

				bool enabledElement = false;

				if(omniElement->Attribute("enabled"))
				{
					enabledElement=true;
				}
				if (enabledElement)
				{
					char *enabled;
					char *valString=NULL;
					valString=(char *) omniElement->Attribute("enabled");
					
						printf("enabled value: %s\n", valString);
						temp.enabled=valString;
					
				}
				else
				{
					printf("enabled not found\n");
				}

				bool locationElement = false;

				if(omniElement->Attribute("location"))
				{
					locationElement=true;
				}
				if (locationElement)
				{
					float f1,f2,f3;
					char *valString=NULL;
					valString=(char *) omniElement->Attribute("location");
					if(valString && sscanf(valString,"%f %f %f",&f1,&f2,&f3)==3)
					{
						printf("location values: %f %f %f %f\n", f1,f2,f3);
						temp.location[0]=f1;
						temp.location[1]=f2;
						temp.location[2]=f3;
					}
					else
					{
						printf("Error parsing location\n");
					}
				}
				else
				{
					printf("location not found\n");
				}

				bool ambientElement = false;

				if(omniElement->Attribute("ambient"))
				{
					ambientElement=true;
				}
				if (ambientElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) omniElement->Attribute("ambient");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("ambient values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.ambient[0]=f1;
						temp.ambient[1]=f2;
						temp.ambient[2]=f3;
						temp.ambient[3]=f4;
					}
					else
					{
						printf("Error parsing ambient\n");
					}
				}
				else
				{
					printf("ambient not found\n");
				}

				bool diffuseElement = false;

				if(omniElement->Attribute("diffuse"))
				{
					diffuseElement=true;
				}
				if (diffuseElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) omniElement->Attribute("diffuse");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("diffuse values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.diffuse[0]=f1;
						temp.diffuse[1]=f2;
						temp.diffuse[2]=f3;
						temp.diffuse[3]=f4;
					}
					else
					{
						printf("Error parsing diffuse\n");
					}
				}
				else
				{
					printf("diffuse not found\n");
				}

				bool specularElement = false;

				if(omniElement->Attribute("specular"))
				{
					specularElement=true;
				}
				if (specularElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) omniElement->Attribute("specular");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("specular values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.specular[0]=f1;
						temp.specular[1]=f2;
						temp.specular[2]=f3;
						temp.specular[3]=f4;
					}
					else
					{
						printf("Error parsing specular\n");
					}
				}
				else
				{
					printf("specular not found\n");
				}
				omniLights.push_back(temp);

				if(omniElement->NextSiblingElement())
				{
					omniElement=omniElement->NextSiblingElement();
				}
				else
				{
					break;
				}
			}while(1);
		TiXmlElement* spotElement=lightingElement->FirstChildElement("spot");
		if(spotElement)
			do{
				bool idElement = false;
				spot temp;
				if(spotElement->Attribute("id"))
				{
					idElement=true;
				}
				if (idElement)
				{
					char *id;
					id=(char *) spotElement->Attribute("id");
						printf("id: %s\n", id);
						temp.id=id;
				}
				else
				{
					printf("id not found\n");
				}

				bool enabledElement = false;

				if(spotElement->Attribute("enabled"))
				{
					enabledElement=true;
				}
				if (enabledElement)
				{
					char *enabled;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("enabled");
					
						printf("enabled value: %s\n", valString);
						temp.enabled=valString;
					
				}
				else
				{
					printf("enabled not found\n");
				}

				bool locationElement = false;

				if(spotElement->Attribute("location"))
				{
					locationElement=true;
				}
				if (locationElement)
				{
					float f1,f2,f3;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("location");
					if(valString && sscanf(valString,"%f %f %f",&f1,&f2,&f3)==3)
					{
						printf("location values: %f %f %f %f\n", f1,f2,f3);
						temp.location[0]=f1;
						temp.location[1]=f2;
						temp.location[2]=f3;
					}
					else
					{
						printf("Error parsing location\n");
					}
				}
				else
				{
					printf("location not found\n");
				}

				bool ambientElement = false;

				if(spotElement->Attribute("ambient"))
				{
					ambientElement=true;
				}
				if (ambientElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("ambient");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("ambient values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.ambient[0]=f1;
						temp.ambient[1]=f2;
						temp.ambient[2]=f3;
						temp.ambient[3]=f4;
					}
					else
					{
						printf("Error parsing ambient\n");
					}
				}
				else
				{
					printf("ambient not found\n");
				}

				bool diffuseElement = false;

				if(spotElement->Attribute("diffuse"))
				{
					diffuseElement=true;
				}
				if (diffuseElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("diffuse");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("diffuse values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.diffuse[0]=f1;
						temp.diffuse[1]=f2;
						temp.diffuse[2]=f3;
						temp.diffuse[3]=f4;
					}
					else
					{
						printf("Error parsing diffuse\n");
					}
				}
				else
				{
					printf("diffuse not found\n");
				}

				bool specularElement = false;

				if(spotElement->Attribute("specular"))
				{
					specularElement=true;
				}
				if (specularElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("specular");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("specular values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.specular[0]=f1;
						temp.specular[1]=f2;
						temp.specular[2]=f3;
						temp.specular[3]=f4;
					}
					else
					{
						printf("Error parsing specular\n");
					}
				}
				else
				{
					printf("specular not found\n");
				}
				bool angleElement = false;

				if(spotElement->Attribute("angle"))
				{
					angleElement=true;
				}
				if (angleElement)
				{
					float f1;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("angle");
					if(valString && sscanf(valString,"%f",&f1)==1)
					{
						printf("angle value: %f", f1);
						temp.angle=f1;
					}
					else
					{
						printf("Error parsing angle\n");
					}
				}
				else
				{
					printf("angle not found\n");
				}

				bool exponentElement = false;

				if(spotElement->Attribute("exponent"))
				{
					exponentElement=true;
				}
				if (exponentElement)
				{
					float f1;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("exponent");
					if(valString && sscanf(valString,"%f",&f1)==1)
					{
						printf("exponent value: %f", f1);
						temp.exponent=f1;
					}
					else
					{
						printf("Error parsing exponent\n");
					}
				}
				else
				{
					printf("exponent not found\n");
				}

				bool directionElement = false;

				if(spotElement->Attribute("direction"))
				{
					directionElement=true;
				}
				if (directionElement)
				{
					float f1,f2,f3;
					char *valString=NULL;
					valString=(char *) spotElement->Attribute("direction");
					if(valString && sscanf(valString,"%f %f %f",&f1,&f2,&f3)==3)
					{
						printf("direction values: %f %f %f", f1,f2,f3);
						temp.direction[0]=f1;
						temp.direction[1]=f2;
						temp.direction[2]=f3;
					}
					else
					{
						printf("Error parsing direction\n");
					}
				}
				else
				{
					printf("direction not found\n");
				}
				spotLights.push_back(temp);
				if(spotElement->NextSiblingElement())
				{
					spotElement=spotElement->NextSiblingElement();
				}
				else
				{
					break;
				}
			}while(1);
	}

	if (textureElement == NULL)
	{
		printf("Textures block not found!\n");
	}
	else
	{
		TiXmlElement* textureTempElement=textureElement->FirstChildElement("texture");
		if (textureTempElement)
		{
			do{
				texture temp;
				printf("Processing texture:\n");
				bool idElement = false;

				if(textureTempElement->Attribute("id"))
				{
					idElement=true;
				}
				if (idElement)
				{
					char *id;
					id=(char *) textureTempElement->Attribute("id");
						printf("id: %s\n", id);
						temp.id=id;
				}
				else
				{
					printf("id not found\n");
				}
				bool fileElement = false;

				if(textureTempElement->Attribute("file"))
				{
					fileElement=true;
				}
				if (fileElement)
				{
					char *file;
					file=(char *) textureTempElement->Attribute("file");
						printf("file name: %s\n", file);
						temp.file=file;
				}
				else
				{
					printf("file not found\n");
				}

				textureEnum.push_back(temp);

				if(textureTempElement->NextSiblingElement())
				{
					textureTempElement=textureTempElement->NextSiblingElement();
				}
				else
				{
					break;
				}
			}while(1);
		}
	}


	if (appearenceElement == NULL)
	{
		printf("appearances block not found!\n");
	}
	else
	{
		TiXmlElement* appearenceTempElement=appearenceElement->FirstChildElement("appearance");
		if (appearenceTempElement)
		{
			do{
				appearance temp;
				printf("Processing appearance:\n");
				bool idElement = false;

				if(appearenceTempElement->Attribute("id"))
				{
					idElement=true;
				}
				if (idElement)
				{
					char *id;
					id=(char *) appearenceTempElement->Attribute("id");
						printf("id: %s\n", id);
						temp.id=id;
				}
				else
				{
					printf("id not found\n");
				}
				bool emissiveElement = false;

				if(appearenceTempElement->Attribute("emissive"))
				{
					emissiveElement=true;
				}
				if (emissiveElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("emissive");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("emissive values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.emissive[0]=f1;
						temp.emissive[1]=f2;
						temp.emissive[2]=f3;
						temp.emissive[3]=f4;
					}
					else
					{
						printf("Error parsing emissive\n");
					}
				}
				else
				{
					printf("emissive not found\n");
				}

				bool ambientElement = false;

				if(appearenceTempElement->Attribute("ambient"))
				{
					ambientElement=true;
				}
				if (ambientElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("ambient");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("ambient values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.ambient[0]=f1;
						temp.ambient[1]=f2;
						temp.ambient[2]=f3;
						temp.ambient[3]=f4;
					}
					else
					{
						printf("Error parsing ambient\n");
					}
				}
				else
				{
					printf("ambient not found\n");
				}

				bool diffuseElement = false;

				if(appearenceTempElement->Attribute("diffuse"))
				{
					diffuseElement=true;
				}
				if (diffuseElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("diffuse");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("diffuse values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.diffuse[0]=f1;
						temp.diffuse[1]=f2;
						temp.diffuse[2]=f3;
						temp.diffuse[3]=f4;
					}
					else
					{
						printf("Error parsing diffuse\n");
					}
				}
				else
				{
					printf("diffuse not found\n");
				}

				bool specularElement = false;

				if(appearenceTempElement->Attribute("specular"))
				{
					specularElement=true;
				}
				if (specularElement)
				{
					float f1,f2,f3,f4;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("specular");
					if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3,&f4)==4)
					{
						printf("specular values: %f %f %f %f\n", f1,f2,f3,f4);
						temp.specular[0]=f1;
						temp.specular[1]=f2;
						temp.specular[2]=f3;
						temp.specular[3]=f4;
					}
					else
					{
						printf("Error parsing specular\n");
					}
				}
				else
				{
					printf("specular not found\n");
				}
				bool shininessElement = false;

				if(appearenceTempElement->Attribute("shininess"))
				{
					shininessElement=true;
				}
				if (shininessElement)
				{
					float f1;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("shininess");
					if(valString && sscanf(valString,"%f",&f1)==1)
					{
						printf("shininess value: %f\n", f1);
						temp.shininess=f1;
					}
					else
					{
						printf("Error parsing shininess\n");
					}
				}
				else
				{
					printf("shininess not found\n");
				}

				bool texturerefElement = false;

				if(appearenceTempElement->Attribute("textureref"))
				{
					texturerefElement=true;
				}
				if (texturerefElement)
				{
					char *f1;
					f1=(char *) appearenceTempElement->Attribute("textureref");
						printf("textureref value: %s\n", f1);
						temp.textureref=f1;
				}
				else
				{
					printf("textureref not found\n");
				}

				bool texlength_sElement = false;

				if(appearenceTempElement->Attribute("texlength_s"))
				{
					texlength_sElement=true;
				}
				if (texlength_sElement)
				{
					float f1;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("texlength_s");
					if(valString && sscanf(valString,"%f",&f1)==1)
					{
						printf("texlength_s value: %f\n", f1);
						temp.texlength_s=f1;
					}
					else
					{
						printf("Error parsing texlength_s\n");
					}
				}
				else
				{
					printf("texlength_s not found\n");
				}

				bool texlength_tElement = false;

				if(appearenceTempElement->Attribute("texlength_t"))
				{
					texlength_tElement=true;
				}
				if (texlength_tElement)
				{
					float f1;
					char *valString=NULL;
					valString=(char *) appearenceTempElement->Attribute("texlength_t");
					if(valString && sscanf(valString,"%f",&f1)==1)
					{
						printf("texlength_t value: %f\n", f1);
						temp.texlength_t=f1;
					}
					else
					{
						printf("Error parsing texlength_t\n");
					}
				}
				else
				{
					printf("texlength_t not found\n");
				}

				appearanceEnum.push_back(temp);

				if(appearenceTempElement->NextSiblingElement())
				{
					appearenceTempElement=appearenceTempElement->NextSiblingElement();
				}
				else
				{
					break;
				}
			}while(1);
		}
	}

	if (graphElement == NULL)
		printf("Graph block not found!\n");
	else
	{
		printf("Processing graph:\n");
		bool rootidElement = false;

		if(graphElement->Attribute("rootid"))
		{
			rootidElement=true;
		}
		if (rootidElement)
		{
			char *f1;
			f1=(char *) graphElement->Attribute("rootid");
				printf("rootid: %s\n", f1);
				rootid=f1;
		}
		else
		{
			printf("rootid not found\n");
		}

		TiXmlElement *node=graphElement->FirstChildElement("node");

		while (node)
		{
			nodee temp1;
			bool nodeidElement = false;
			if(node->Attribute("id"))
			{
				nodeidElement=true;
			}
			if (nodeidElement)
			{
				char *f1;
				f1=(char *) node->Attribute("id");
					printf("nodeid: %s\n", f1);
					temp1.id=f1;
			}
			else
			{
				printf("nodeid not found\n");
			}
			TiXmlElement *transforms=node->FirstChildElement("transforms");
			transformse temp3;
			temp3.rotate1.angle=0;
			temp3.rotate1.axis="x";
			temp3.scale1.factor[0]=0;
			temp3.scale1.factor[1]=0;
			temp3.scale1.factor[2]=0;
			temp3.translate1.to[0]=0;
			temp3.translate1.to[1]=0;
			temp3.translate1.to[2]=0;
			if(transforms)
			{
				
				TiXmlElement *translate=transforms->FirstChildElement("translate");
				if(translate)
					do{
						bool translateElement = false;
						translatee temp2;
						
						if(translate->Attribute("to"))
						{
							translateElement=true;
						}
						if (translateElement)
						{
							float f1,f2,f3;
							char *valString=NULL;
							valString=(char *) translate->Attribute("to");
							if(valString && sscanf(valString,"%f %f %f %f",&f1,&f2,&f3)==3)
							{
								printf("translate to values: %f %f %f\n", f1,f2,f3);
								temp2.to[0]=f1;
								temp2.to[1]=f2;
								temp2.to[2]=f3;
								temp3.translate1=temp2;
								temp1.transformations.push_back(temp3);
							}
							else
							{
								printf("Error parsing translate to\n");
							}
						}
						else
						{
							printf("translate to not found\n");
							break;
						}
						if(translate->NextSiblingElement("translate"))
						{
							translate=translate->NextSiblingElement("translate");
						}
						else
						{
							break;
						}

					}while(1);
			}
			temp3.rotate1.angle=0;
			temp3.rotate1.axis="x";
			temp3.scale1.factor[0]=0;
			temp3.scale1.factor[1]=0;
			temp3.scale1.factor[2]=0;
			temp3.translate1.to[0]=0;
			temp3.translate1.to[1]=0;
			temp3.translate1.to[2]=0;
			if(transforms)
			{
				TiXmlElement *rotate=transforms->FirstChildElement("rotate");
				if(rotate)
					do{
						rotatee temp2;
						
						bool axisElement = false;

						if(rotate->Attribute("axis"))
						{
							axisElement=true;
						}
						if (axisElement)
						{
							char *axis;
							axis=(char *) rotate->Attribute("axis");
								printf("axis attribute: %s\n", axis);
								temp2.axis=axis;
						}
						else
						{
							printf("axis to not found\n");
						}

						bool angleElement = false;

						if(rotate->Attribute("angle"))
						{
							angleElement=true;
						}
						if (angleElement)
						{
							float angle;;
							char *valString=NULL;
							valString=(char *) rotate->Attribute("angle");
							if(valString && sscanf(valString,"%f",&angle)==1)
							{
								printf("angle value: %f\n", angle);
								temp2.angle=angle;
							}
							else
							{
								printf("Error parsing angle\n");
							}
						}
						else
						{
							printf("angle to not found\n");
							break;
						}
						temp3.rotate1=temp2;
						temp1.transformations.push_back(temp3);
						if(rotate->NextSiblingElement("rotate"))
						{
							rotate=rotate->NextSiblingElement("rotate");
						}
						else
						{
							break;
						}

					}while(1);
			}
			temp3.rotate1.angle=0;
			temp3.rotate1.axis="x";
			temp3.scale1.factor[0]=0;
			temp3.scale1.factor[1]=0;
			temp3.scale1.factor[2]=0;
			temp3.translate1.to[0]=0;
			temp3.translate1.to[1]=0;
			temp3.translate1.to[2]=0;
			if(transforms)
			{
				TiXmlElement *scale=transforms->FirstChildElement("scale");
				if(scale)
					do{
						scalee temp2;
						

						bool scaleElement = false;

						if(scale->Attribute("factor"))
						{
							scaleElement=true;
						}
						if (scaleElement)
						{
							float f1,f2,f3;
							char *valString=NULL;
							valString=(char *) scale->Attribute("factor");
							if(valString && sscanf(valString,"%f %f %f",&f1, &f2, &f3)==3)
							{
								printf("factor values: %f %f %f\n", f1,f2,f3);
								temp2.factor[0]=f1;
								temp2.factor[1]=f2;
								temp2.factor[2]=f3;
							}
							else
							{
								printf("Error parsing factor\n");
							}
						}
						else
						{
							printf("factor to not found\n");
							break;
						}
						temp3.scale1=temp2;
						temp1.transformations.push_back(temp3);
						if(scale->NextSiblingElement("scale"))
						{
							scale=scale->NextSiblingElement("scale");
						}
						else
						{
							break;
						}

					}while(1);
				
			}

			TiXmlElement *appref=node->FirstChildElement("appearanceref");

			if(appref)
			{
				bool apprefElement = false;

				if(appref->Attribute("id"))
				{
					apprefElement=true;
				}
				if (apprefElement)
				{
					char *appreff;
					appreff=(char *) appref->Attribute("id");
					printf("appearance id: %s\n", appreff);
					temp1.appearenceref=appreff;
				}
				else
				{
					printf("id to not found\n");
				}
			}

			TiXmlElement *child=node->FirstChildElement("children");
			children temp4;
			TiXmlElement *noderef=child->FirstChildElement("noderef");
			do
			{
				nodereef temp2;
				if(noderef)
				{
					bool noderefElement = false;

					if(noderef->Attribute("id"))
					{
						noderefElement=true;
					}
					if (noderefElement)
					{
						char *nodereftemp;
						nodereftemp=(char *) noderef->Attribute("id");
							printf("noderef id: %s\n", nodereftemp);
							temp2.id=nodereftemp;
					}
					else
					{
						printf("id to not found\n");
					}
					temp4.noderefV.push_back(temp2);
					if(noderef->NextSiblingElement("noderef"))
					{
						noderef=noderef->NextSiblingElement("noderef");
					}
					else
					{
						break;
					}
				}
				else break;
			}
			while(1);
			TiXmlElement *rectangle=child->FirstChildElement("rectangle");

			do
			{
				rectanglee temp2;
				if(rectangle)
				{
					printf("Rectangle\n");
					bool rectangleElement = false;

					if(rectangle->Attribute("xy1"))
					{
						rectangleElement=true;
					}
					if (rectangleElement)
					{
						float f1,f2;
						char *valString=NULL;
						valString=(char *) rectangle->Attribute("xy1");
						if(valString && sscanf(valString,"%f %f",&f1,&f2)==2)
						{
							printf("xy1 attribute: %f %f\n", f1,f2);
							temp2.xy1[0]=f1;
							temp2.xy1[1]=f2;
						}
						else
						{
							printf("Error parsing xy1\n");
						}
					}
					else
					{
						printf("xy1 to not found\n");
					}

					if(rectangle->Attribute("xy2"))
					{
						rectangleElement=true;
					}
					if (rectangleElement)
					{
						float f1,f2;
						char *valString=NULL;
						valString=(char *) rectangle->Attribute("xy2");
						if(valString && sscanf(valString,"%f %f",&f1,&f2)==2)
						{
							printf("xy2 attribute: %f %f\n", f1,f2);
							temp2.xy2[0]=f1;
							temp2.xy2[1]=f2;
						}
						else
						{
							printf("Error parsing xy2\n");
						}
					}
					else
					{
						printf("xy2 to not found\n");
					}
					temp4.rectangleV.push_back(temp2);
					if(rectangle->NextSiblingElement("rectangle"))
					{
						rectangle=rectangle->NextSiblingElement("rectangle");
					}
					else
					{
						break;
					}
				}
				else break;
			}
			while(1);

			TiXmlElement *triangle=child->FirstChildElement("triangle");
			do
			{
				trianglee temp2;
				if(triangle)
				{
					printf("Triangle\n");
					bool triangleElement = false;

					if(triangle->Attribute("xyz1"))
					{
						triangleElement=true;
					}
					if (triangleElement)
					{
						float f1,f2,f3;
						char *valString=NULL;
						valString=(char *)triangle->Attribute("xyz1");
						if(valString && sscanf(valString,"%f %f %f",&f1,&f2,&f3)==3)
						{
							printf("xyz1 attribute: %f %f %f\n", f1,f2,f3);
							temp2.xyz1[0]=f1;
							temp2.xyz1[1]=f2;
							temp2.xyz1[2]=f3;
						}
						else
						{
							printf("Error parsing xyz1\n");
						}
					}
					else
					{
						printf("xyz1 to not found\n");
					}

					if(triangle->Attribute("xyz2"))
					{
						triangleElement=true;
					}
					if (triangleElement)
					{
						float f1,f2,f3;
						char *valString=NULL;
						valString=(char *) triangle->Attribute("xyz2");
						if(valString && sscanf(valString,"%f %f %f",&f1,&f2,&f3)==3)
						{
							printf("xyz2 attribute: %f %f %f\n", f1,f2,f3);
							temp2.xyz2[0]=f1;
							temp2.xyz2[1]=f2;
							temp2.xyz2[2]=f3;
						}
						else
						{
							printf("Error parsing xyz2\n");
						}
					}
					else
					{
						printf("xyz2 to not found\n");
					}

					if(triangle->Attribute("xyz3"))
					{
						triangleElement=true;
					}
					if (triangleElement)
					{
						float f1,f2,f3;
						char *valString=NULL;
						valString=(char *) triangle->Attribute("xyz3");
						if(valString && sscanf(valString,"%f %f %f",&f1,&f2,&f3)==3)
						{
							printf("xyz3 attribute: %f %f %f\n", f1,f2,f3);
							temp2.xyz3[0]=f1;
							temp2.xyz3[1]=f2;
							temp2.xyz3[2]=f3;
						}
						else
						{
							printf("Error parsing xyz3\n");
						}
					}
					else
					{
						printf("xyz3 to not found\n");
					}
					temp4.triangleV.push_back(temp2);
					if(triangle->NextSiblingElement("triangle"))
					{
						triangle=triangle->NextSiblingElement("triangle");
					}
					else
					{
						break;
					}
				}
				else break;
			}
			while(1);

			TiXmlElement *cylinder=child->FirstChildElement("cylinder");

			do
			{
				cylindere temp2;
				if(cylinder)
				{
					printf("Cylinder\n");
					bool cylinderElement = false;

					if(cylinder->Attribute("base"))
					{
						cylinderElement=true;
					}
					if (cylinderElement)
					{
						float f1;
						char *valString=NULL;
						valString=(char *)cylinder->Attribute("base");
						if(valString && sscanf(valString,"%f",&f1)==1)
						{
							printf("base attribute: %f\n", f1);
							temp2.base=f1;
						}
						else
						{
							printf("Error parsing base\n");
						}
					}
					else
					{
						printf("base to not found\n");
					}
					if(cylinder->Attribute("top"))
					{
						cylinderElement=true;
					}
					if (cylinderElement)
					{
						float f1;
						char *valString=NULL;
						valString=(char *)cylinder->Attribute("top");
						if(valString && sscanf(valString,"%f",&f1)==1)
						{
							printf("top attribute: %f\n", f1);
							temp2.top=f1;
						}
						else
						{
							printf("top parsing base\n");
						}
					}
					else
					{
						printf("top to not found\n");
					}
					if(cylinder->Attribute("height"))
					{
						cylinderElement=true;
					}
					if (cylinderElement)
					{
						float f1;
						char *valString=NULL;
						valString=(char *)cylinder->Attribute("height");
						if(valString && sscanf(valString,"%f",&f1)==1)
						{
							printf("height attribute: %f\n", f1);
							temp2.height=f1;
						}
						else
						{
							printf("Error parsing height\n");
						}
					}
					else
					{
						printf("height to not found\n");
					}

					if(cylinder->Attribute("slices"))
					{
						cylinderElement=true;
					}
					if (cylinderElement)
					{
						int f1;
						char *valString=NULL;
						valString=(char *)cylinder->Attribute("slices");
						if(valString && sscanf(valString,"%i",&f1)==1)
						{
							printf("slices attribute: %i\n", f1);
							temp2.slices=f1;
						}
						else
						{
							printf("Error parsing slices\n");
						}
					}
					else
					{
						printf("slices to not found\n");
					}

					if(cylinder->Attribute("stacks"))
					{
						cylinderElement=true;
					}
					if (cylinderElement)
					{
						int f1;
						char *valString=NULL;
						valString=(char *)cylinder->Attribute("stacks");
						if(valString && sscanf(valString,"%i",&f1)==1)
						{
							printf("stacks attribute: %i\n", f1);
							temp2.stacks=f1;
						}
						else
						{
							printf("Error parsing stacks\n");
						}
					}
					else
					{
						printf("stacks to not found\n");
					}
					temp4.cylinderV.push_back(temp2);
					if(cylinder->NextSiblingElement("cylinder"))
					{
						cylinder=cylinder->NextSiblingElement("cylinder");
					}
					else
					{
						break;
					}
				}
				else break;
			}
			while(1);

			TiXmlElement *sphere=child->FirstChildElement("sphere");

			do
			{
				spheree temp2;
				if(sphere)
				{
					printf("Sphere\n");
					bool sphereElement = false;
					if(sphere->Attribute("radius"))
					{
						sphereElement=true;
					}
					if (sphereElement)
					{
						float f1;
						char *valString=NULL;
						valString=(char *)sphere->Attribute("radius");
						if(valString && sscanf(valString,"%f",&f1)==1)
						{
							printf("radius attribute: %f\n", f1);
							temp2.radius=f1;
						}
						else
						{
							printf("Error parsing radius\n");
						}
					}
					else
					{
						printf("radius to not found\n");
					}

					if(sphere->Attribute("slices"))
					{
						sphereElement=true;
					}
					if (sphereElement)
					{
						int f1;
						char *valString=NULL;
						valString=(char *)sphere->Attribute("slices");
						if(valString && sscanf(valString,"%i",&f1)==1)
						{
							printf("slices attribute: %i\n", f1);
							temp2.slices=f1;
						}
						else
						{
							printf("Error parsing slices\n");
						}
					}
					else
					{
						printf("slices to not found\n");
					}

					if(sphere->Attribute("stacks"))
					{
						sphereElement=true;
					}
					if (sphereElement)
					{
						int f1;
						char *valString=NULL;
						valString=(char *)sphere->Attribute("stacks");
						if(valString && sscanf(valString,"%i",&f1)==1)
						{
							printf("stacks attribute: %i\n", f1);
							temp2.stacks=f1;
						}
						else
						{
							printf("Error parsing stacks\n");
						}
					}
					else
					{
						printf("stacks to not found\n");
					}
					temp4.sphereV.push_back(temp2);
					if(sphere->NextSiblingElement("sphere"))
					{
						sphere=sphere->NextSiblingElement("sphere");
					}
					else
					{
						break;
					}
				}
				else break;
			}
			while(1);

			TiXmlElement *torus=child->FirstChildElement("torus");

			do
			{
				toruse temp2;
				if(torus)
				{
					printf("Torus\n");
					bool torusElement = false;
					if(torus->Attribute("inner"))
					{
						torusElement=true;
					}
					if (torusElement)
					{
						float f1;
						char *valString=NULL;
						valString=(char *)torus->Attribute("inner");
						if(valString && sscanf(valString,"%f",&f1)==1)
						{
							printf("inner attribute: %f\n", f1);
							temp2.inner=f1;
						}
						else
						{
							printf("inner parsing base\n");
						}
					}
					else
					{
						printf("inner to not found\n");
					}
					if(torus->Attribute("outer"))
					{
						torusElement=true;
					}
					if (torusElement)
					{
						float f1;
						char *valString=NULL;
						valString=(char *)torus->Attribute("outer");
						if(valString && sscanf(valString,"%f",&f1)==1)
						{
							printf("outer attribute: %f\n", f1);
							temp2.outer=f1;
						}
						else
						{
							printf("Error parsing outer\n");
						}
					}
					else
					{
						printf("outer to not found\n");
					}

					if(torus->Attribute("slices"))
					{
						torusElement=true;
					}
					if (torusElement)
					{
						int f1;
						char *valString=NULL;
						valString=(char *)torus->Attribute("slices");
						if(valString && sscanf(valString,"%i",&f1)==1)
						{
							printf("slices attribute: %i\n", f1);
							temp2.slices=f1;
						}
						else
						{
							printf("Error parsing slices\n");
						}
					}
					else
					{
						printf("slices to not found\n");
					}

					if(torus->Attribute("loops"))
					{
						torusElement=true;
					}
					if (torusElement)
					{
						int f1;
						char *valString=NULL;
						valString=(char *)torus->Attribute("loops");
						if(valString && sscanf(valString,"%i",&f1)==1)
						{
							printf("loops attribute: %i\n", f1);
							temp2.loops=f1;
						}
						else
						{
							printf("Error parsing loops\n");
						}
					}
					else
					{
						printf("loops to not found\n");
					}
					temp4.torusV.push_back(temp2);
					if(torus->NextSiblingElement("torus"))
					{
						torus=torus->NextSiblingElement("torus");
					}
					else
					{
						break;
					}
				}
				else break;
			}
			while(1);
			temp1.childs=temp4;
			temp1.visited=false;
			nodesvector.push_back(temp1);
			if(node->NextSiblingElement())
			{
				node=node->NextSiblingElement();
			}
			else
			{
				break;
			}
		}
	}

}

float XMLScene::getGlobalAmbientLight(int n){
	return globalAmbientLight[n];
}

char * XMLScene::getDrawmode1(){
	return drawmode1;
}

char * XMLScene::getShading1(){
	return shading1;
}

char * XMLScene::getCullface1(){
	return cullface1;
}

char * XMLScene::getCullorder1(){
	return cullorder1;
}

bool XMLScene::getLightingDoubleSided(){
	return lightingDoubleSided;
}

bool XMLScene::getLightingLocal(){
	return lightingLocal;
}

bool XMLScene::getLightingEnabled(){
	return lightingEnabled;
}

float XMLScene::getLightingValuesAmbient(int n){
	return lightingValuesAmbient[n];
}

omni XMLScene::getOmniLights(int n){
	return omniLights[n];
}
spot XMLScene::getSpotLights(int n){
	return spotLights[n];
}
int XMLScene::getOmniSize(){
	return omniLights.size();
}
int XMLScene::getSpotSize(){
	return spotLights.size();
}

char * XMLScene::getCamerasInitial(){
	return camerasInitial;
}

ortho XMLScene::getOrthoCameras(int n){
	return orthoCameras[n];
}
perspective XMLScene::getPerspectiveCameras(int n){
	return perspectiveCameras[n];
}
int XMLScene::getOrthoSize(){
	return orthoCameras.size();
}
int XMLScene::getPerspectiveSize(){
	return perspectiveCameras.size();
}

texture XMLScene::getTextureEnum(int n){
	return textureEnum[n];
}

int XMLScene::getTextureEnumSize(){
	return textureEnum.size();
}

appearance XMLScene::getAppearanceEnum(int n){
	return appearanceEnum[n];
}

int XMLScene::getAppearanceEnumSize(){
	return appearanceEnum.size();
}

char * XMLScene::getRootid(){
	return rootid;
}

nodee XMLScene::getNodesvector(int n){
	return nodesvector[n];
}
int XMLScene::getNodesvectorSize(){
	return nodesvector.size();
}

std::vector<nodee> XMLScene::getNodesvectorFull(){
	return nodesvector;
}

XMLScene::~XMLScene()
{
	delete(doc);
}
