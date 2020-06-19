#include "TileLayer.h"
#include "Game.h"
#include "camera.h"



TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : m_tileSize(tileSize),
	m_tilesets(tilesets),m_position(0,0), m_velocity(0,0)
{
	int sumnumber = TheGame::Instance()->getGameHeight();
	m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize);
	m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
	m_mapWidth = TheGame::Instance()->getGameWidth();
	
}

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets) : m_tileSize(tileSize),
	m_tilesets(tilesets),m_position(0,0), m_velocity(0,0)
{

	int sumnumber = TheGame::Instance()->getGameHeight();
	m_numColumns = mapWidth ;
	m_numRows = mapHeight;
	//m_mapWidth = mapWidth;
	m_mapWidth = TheGame::Instance()->getGameWidth();
	

}





void TileLayer::update(Level* pLevel)
{
	//m_position += TheCamera::Instance()->getPosition();
//	m_position+= m_velocity;
//	m_velocity.setX(1);

	




}

void TileLayer::render()
{
	int x, y, x2, y2 =0;
	
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;
	
	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;

	for(int i=0; i < m_numRows; i++)
	{
		for(int j =0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i + y][j+x];
			
			if(id ==0)
			{
				continue;
			}

	//if outside the viewable area then  skip the tile
			Vector2D camerapos= TheCamera::Instance()->getPosition();
			int camerax = camerapos.getX();
			
		if(((j* m_tileSize)- x2) - camerax  < -m_tileSize
				|| ((j* m_tileSize) - x2) - camerax > TheGame::Instance()->getGameWidth())
			{

				continue;

			}

			// draw the tile into position while offsetting its x position by

		// subtracting the camera position
			Tileset tileset = getTilesetById(id);
			id--;
			ThetextureManager::Instance()->drawTile(tileset.name, tileset.margin,tileset.spacing,((j * m_tileSize) - x2)  -camerax,
				(i * m_tileSize) - y2, m_tileSize, m_tileSize,(id -(tileset.firstGridID -1)) / 
				tileset.numColumns, (id -(tileset.firstGridID -1)) % 
				tileset.numColumns, TheGame::Instance()->getRenderer());

		}

	}



}

Tileset TileLayer::getTilesetById(int tileID)
{
	for(int i=0; i < m_tilesets.size(); i++)
	{
		if(i+1 <= m_tilesets.size() -1)
		{
			if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i +1].firstGridID)
			{
				return m_tilesets[i];

			}
		}
		else
		{
			return m_tilesets[i];

		}


	}
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;

	

}