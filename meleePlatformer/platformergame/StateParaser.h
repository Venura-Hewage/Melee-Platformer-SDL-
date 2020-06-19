#ifndef _StateParser_
#define _StateParser_

#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "GameObject.h"
using namespace tinyxml2;

class GameObject;


class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateId,
		std::vector<GameObject*> *pObjects, std::vector <std::string> *pTextureIDs);

private:



	void parseObjects(XMLElement* pStateRoot,std::vector<GameObject*> *pObjects);
	void parseTextures(XMLElement* pStateRoot, std::vector<std::string> *pTextureIDs);

	
};


#endif
