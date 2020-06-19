#ifndef _Level_
#define _Level_
#include <string>
#include<vector>
#include "Layer.h"
#include "Player.h"
//#include "LevelParser.h"
#include "TileLayer.h"
//class TileLayer;
#include "Tilesets.h"



class Level
{
public:
	
	~Level() {}


	void update();
	void render();

	

	std::vector<Tileset>* getTilesets()
	{
		return &m_tilesets;

	}

	std::vector<Layer*>* getLayers()
	{
		return &m_layers;
	}

	std::vector<TileLayer*> * getCollisionLayer()
	{
		return  &m_collisonLayers;
	}

	const std::vector<TileLayer*>& getCollidableLayers() { return m_collisonLayers; }


	Player* getPlayer() { return m_pPlayer;}
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer;}
	


private:
	Player* m_pPlayer;
	

	
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	std::vector<TileLayer*> m_collisonLayers;
	Level();
	friend class LevelParser;
	
};

#endif
