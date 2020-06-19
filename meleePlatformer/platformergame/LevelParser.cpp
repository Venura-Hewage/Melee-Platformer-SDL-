#include "LevelParser.h"
#include<iostream>
#include "Game.h"
#include "TextureManager.h"

#include "Base64.h"
#include <zlib.h>
#include <algorithm>
#include "ObjectLayer.h"
#include "GameObjectFactory.h"


LevelParser::LevelParser()
{



}



Level* LevelParser::parseLevel(const char *levelFile)
{
	//create a TinyXML document and load the map XML
	XMLDocument levelDocument;
	if(levelDocument.LoadFile(levelFile))
	{
		if(levelDocument.ErrorID() ==3)
     		{
				std::cout << "Game Level FILE NOT FOUND" << std::endl;
				TheGame::Instance()->clean();
				
			}

	}

	Level* pLevel = new Level();
	XMLElement* pRoot = levelDocument.RootElement();
	pRoot->QueryIntAttribute("tilewidth", &m_tileSize);
	pRoot->QueryIntAttribute("width",&m_width);
	pRoot->QueryIntAttribute("height",&m_height);
	
	//parse the tilesets
	for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(e->Value() == std::string("tileset"))
		{
		
			parseTilesets(e, pLevel->getTilesets());
		}

	}

	// we must parse the textures needed for this level, which have been added to properties
		
	for(XMLElement* e = pRoot->FirstChildElement(); e != NULL;	e = e->NextSiblingElement())
		{
			if(e->Value() == std::string("properties"))
			{
				for(XMLElement* f = e->FirstChildElement(); f != NULL; f = f->NextSiblingElement())
				{
					
					 parseTextures(f);
				}
			}
		}





	//parse any object layers
	for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e= e->NextSiblingElement())
	{
		if(e->Value() == std::string("objectgroup")  || e->Value() == std::string("layer"))
		{

			if(e->LastChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers(),pLevel);
				
			}
			else if(e->FirstChildElement()->Value() == std::string("data") || 
				(e->FirstChildElement()->NextSiblingElement() != 0 && 
				e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
			{
				
				parseTileLayer(e,pLevel->getLayers(), pLevel->getTilesets(),pLevel->getCollisionLayer());
			}
									
		}

	}

	return pLevel;

}


void LevelParser::parseTilesets(XMLElement* pTilesetRoot, std::vector<Tileset>* pTilests)
{
	std::string str;
	std::string xpath = "assets/";
	std::string imagesource = pTilesetRoot->FirstChildElement()->Attribute("source");
	str.append(xpath);
	str.append(imagesource);


	//First add the tileset to texture mangager
	ThetextureManager::Instance()->load(str,pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

	
	//create a tileset object
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->QueryIntAttribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->QueryIntAttribute("height",&tileset.height);
	pTilesetRoot->QueryIntAttribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->QueryIntAttribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->QueryIntAttribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->QueryIntAttribute("spacing", &tileset.spacing);
	pTilesetRoot->QueryIntAttribute("margin",&tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
	pTilests->push_back(tileset);
	
}

void LevelParser::parseTileLayer(XMLElement* pTileElement,std::vector<Layer*> *pLayers,
								 const std::vector<Tileset>*pTilesets, std::vector<TileLayer*> *pCollisonLayers)
{

	    TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width,m_height, *pTilesets);
		//TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	bool collidable = false;

	//tile data
	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	XMLElement* PDataNode;

	for(XMLElement* e= pTileElement->FirstChildElement(); e != NULL; e= e->NextSiblingElement())
	{
		if(e->Value() == std::string("properties"))
		{

			for(XMLElement* property = e->FirstChildElement(); property !=  NULL; property = property->NextSiblingElement())
			{
				if(property->Value() == std::string("property"))
				{
					if(property->Attribute("name") == std::string("collidable"))
					{

						collidable = true;
					}
				}
			}
		}


		if(e->Value() == std::string("data"))
		{
			PDataNode =e;

		}

	}

	for(XMLNode *e = PDataNode->FirstChild(); e != NULL; e= e->NextSibling())
	{
		XMLText* text = e->ToText();
		std::string t = text->Value();
		somestring = t;
		somestring.erase(std::remove(somestring.begin(),somestring.end(), '\n'), somestring.end());
		somestring.erase(std::remove_if(somestring.begin(), somestring.end(), ::isspace ), somestring.end() );
		decodedIDs = base64_decode(somestring);



	}



	//uncompress zlib compression
	uLongf sizeofids = m_width  * m_height * sizeof(int);
	std::vector<int> ids(m_width * m_height);
	uncompress((Bytef*)&ids[0], &sizeofids,(const Bytef*)decodedIDs.c_str(),decodedIDs.size());
	
	std::vector<int>layerRow(m_width);

	for(int j  =0; j < m_height; j++)
	{
		data.push_back(layerRow);

	}

	for(int rows =0; rows < m_height; rows++)
	{
		for(int cols =0; cols < m_width; cols++)
		{
			data[rows][cols] = ids[rows * m_width + cols];

		}

	}
	

	pTileLayer->setTileIDs(data);


	if(collidable)
	{
		//pCollisonLayers->push_back(pTileLayer);
		pCollisonLayers->push_back(pTileLayer);

	}



	pLayers->push_back(pTileLayer);

}

void LevelParser::parseTextures(XMLElement* pTextureRoot)
{

	ThetextureManager::Instance()->load(pTextureRoot->Attribute("value"),
		pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(XMLElement* pObjectElement,  std::vector<Layer*>*pLayers, Level* pLevel)
{
	//create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();



	for(XMLElement* e = pObjectElement->LastChildElement();e != NULL; e= e->NextSiblingElement())
	{
		
		if(e->Value() == std::string("object"))
		{
			int x,y, width, height, numFrames, callbackID, animSpeed;
			std::string type;
			std::string textureID;
			
			type = e->Attribute("type");
			
			//get the intial node valeus type , x and y
			e->QueryIntAttribute("x", &x);
			e->QueryIntAttribute("y",&y);
			GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute
				("type"));

			

			//get the property values 
			
			XMLNode *ancestor = e->Parent();
			
			XMLElement *firstchild = ancestor->FirstChildElement();
		
			for(XMLElement* properties =  firstchild; properties != NULL;
				properties = properties->NextSiblingElement())
			{

				if(properties->Value() == std::string("properties"))
				{
					for(XMLElement* property =properties->FirstChildElement(); property != NULL; property =property->NextSiblingElement())

					{
						
						if(property->Value() == std::string("property"))
						{
							if(property->Attribute("name") == std::string("numFrames"))
							{
								property->QueryIntAttribute("value", &numFrames);

							}
							else if(property->Attribute("name") == std::string("textureHeight"))
							{
								property->QueryIntAttribute("value", &height);
							}
							else if(property->Attribute("name")== std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if(property->Attribute("name")== std::string("textureWidth"))
							{
								property->QueryIntAttribute("value", &width);
							}
							else if(property->Attribute("name") == std::string("callbackID"))
							{

								property->QueryIntAttribute("value", &callbackID);									
							}
							else if(property->Attribute("name") == std::string("animSpeed"))
							{
								property->QueryIntAttribute("value", &animSpeed);

							}

						}

					}
					

				}


			}
			pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x,y, width,height,textureID,
				numFrames,callbackID, animSpeed)));
			pGameObject->setCollisionLayers(pLevel->getCollisionLayer());
			if(type == "Player")
			{
				pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));

			}


			pObjectLayer->getGameObject()->push_back(pGameObject);

		}
		
	}

	pLayers->push_back(pObjectLayer);
}



