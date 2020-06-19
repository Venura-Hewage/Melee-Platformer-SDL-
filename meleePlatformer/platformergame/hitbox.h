#ifndef _hitbox_
#define _hitbox_
#include<string>
#include <vector> 
#include <cmath>
#include "circle.h"
#include <SDL.h>


class Hitbox
{

public:

	Hitbox();

double distanceSquared(int x1, int y1, int x2, int y2);

bool check_hitbox_collison(Circle& a, SDL_Rect& b);

bool  check_hitbox_collison( Circle& a, Circle& b );

bool intersects(Circle& a, SDL_Rect& b);



private:

};





#endif