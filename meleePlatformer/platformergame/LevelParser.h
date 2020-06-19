#ifndef _LevelParser_
#define _LevelParser_
#include "Level.h"
//#include "tinyxml2.h"
#include "StateParaser.h"
#include "TileLayer.h"


class LevelParser
{

public:
	LevelParser();
	Level* parseLevel(const char* levelFile);


private:
	
	void parseTilesets(XMLElement* pTilesetRoot, std::vector<Tileset>*pTileSets);

	void parseTileLayer(XMLElement* pTileElement, std::vector<Layer*> *pLayers, const
		std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

	void parseTileLayer(XMLElement* pTileElement, std::vector<Layer*> *pLayers, const
		std::vector<Tileset>* pTilesets, Level* vLevel);

	void parseTileLayer(XMLElement* pTileElement, std::vector<Layer*> *pLayers, const
		std::vector<Tileset>* pTilesets, Level* vLevel, std::vector<TileLayer*> *pCollisionLayers);




	void parseTextures(XMLElement* pTextureRoot);
	void parseObjectLayer(XMLElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);


	 int m_tileSize;
	 int m_width;
	 int m_height;
	 std::string somestring;


};

#endif






