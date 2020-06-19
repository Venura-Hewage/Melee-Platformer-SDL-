#include "StateParaser.h"
#include <string>
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"



bool StateParser::parseState(const char *stateFile, std::string StateID,
							 std::vector<GameObject*> *pObjects, std::vector<std::string>* pTextureIDs)

{

	//create the XML Document
	XMLDocument xmldoc;
//	XMLPrinter xmlprint;


	

	//load the state file
	//if(!xmldoc.LoadFile(stateFile))
	//{

	//}

	if(xmldoc.LoadFile(stateFile) )
	{
		XMLError xerror;
		xmldoc.PrintError();
		if(xmldoc.ErrorID() ==3)
     		{
				std::cout << "FILE NOT FOUND" << std::endl;
				TheGame::Instance()->clean();
				

			}
					
	}
	//xmldoc.Print(&xmlprint);

	//get the root element
	XMLElement* pRoot = xmldoc.RootElement();

	//pre declare the states root node
	XMLElement* pStateRoot = 0;

	//get this states root node and assignit to pStateRoot
	for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e= e->NextSiblingElement())
	{
		if(e->Value() == StateID)
		{
			pStateRoot = e;
		}

	}

	XMLElement* pTextureRoot = 0;
	//get the root of the texture elements
	for(XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e= e->NextSiblingElement())
	{
		if(e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}

	}
	//now parse the textures
	parseTextures(pTextureRoot,pTextureIDs);

	//pre declare the object root node
	XMLElement* pObjectRoot = 0;

	//get the root node and assign it to pObjectRoot
	for(XMLElement* e = pStateRoot->FirstChildElement(); e!= NULL; e= e->NextSiblingElement())
	{
		if(e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}

	}
	//now parse the objects
	parseObjects(pObjectRoot, pObjects);

	return true;

}

void StateParser::parseTextures(XMLElement*  pStateRoot, std::vector<std::string> *pTextureIDs)
{

	for(XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;  e = e->NextSiblingElement())
	{

		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute); //push into list

		ThetextureManager::Instance()->load(filenameAttribute, idAttribute,
			TheGame::Instance()->getRenderer());

	}


}

void StateParser::parseObjects(XMLElement *pStateRoot, std::vector<GameObject *> *pObjects)
{

	for(XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->QueryIntAttribute("x", &x);
		e->QueryIntAttribute("y", &y);
		e->QueryIntAttribute("width", &width);
		e->QueryIntAttribute("height", &height);
		e->QueryIntAttribute("numFrames", &numFrames);
		e->QueryIntAttribute("callbackID", &callbackID);
		e->QueryIntAttribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
		
		pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x,y,width,height,textureID,numFrames,callbackID,animSpeed)));
		pObjects->push_back(pGameObject);


	}

}




