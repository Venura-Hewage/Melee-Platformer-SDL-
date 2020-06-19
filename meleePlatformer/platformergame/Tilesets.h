#ifndef _Tilesets_
#define _Tilesets_
#include<string>

struct Tileset
	{
		int firstGridID;
		int tileWidth;
		int tileHeight;
		int spacing;
		int margin;
		int width;
		int height;
		int numColumns;
		std::string name;
	};

#endif