#include "hitbox.h"
#include "Vector2D.h"

Hitbox::Hitbox()
{




}


double Hitbox::distanceSquared(int x1, int y1, int x2, int y2)
{
//To improve optimization the actual distance is not calculated because calculating the square root is a relatively expensive operation.	
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	

	return  deltaX * deltaX + deltaY * deltaY;

}

bool Hitbox::check_hitbox_collison(Circle& a, SDL_Rect& b)

{

	//closet point on the collision box
	int cX, cY;
	//int halfPointX = b.w/2;
		//find closet x offset
	//if the circle's center is to the left the box. the x position of the closest point on the left side of the box.
	if(a.x < b.x )
		{
			cX = b.x;

		}
		//if the circle center is on the right of the box, the x position of the closest point is on the right side of the box.
	else if(a.x > b.x + b.w)
		{

			cX = b.x + b.w;


		}
		//if the circle center is inside of the box, the x position of the closest point is the same as the x position of the circle.
		else
		{
			cX = a.x;

		}

	//find closest y offset
	//int halfPointY = b.h/2;
	if( a.y < b.y -b.h)
		{
			cY = b.y-b.h;
		}
		else if(a.y > b.y )
		{
			cY = b.y;

		}
		else
		{

			cY = a.y;
		}

		double testsquare = distanceSquared(a.x, a.y, cX, cY);
		double radiusCircle = a.r* a.r;
		//if the closest point is inside the circle
		if(distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
		{
			//This box and the circle have collided
			return true;

		}


		//IF the shapes have not collided
		return false;

}





bool  Hitbox::check_hitbox_collison( Circle& a, Circle& b ) 
{ 
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r; 
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;
	//If the distance between the centers of the circles is less than the sum of their radii 
	double testsquare = distanceSquared(a.x, a.y, b.x, b.y);
		
	if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) ) 
	{ 
		//The circles have collided 
		return true; 
	} 
	//If not 
	return false;
}

bool Hitbox::intersects(Circle& circle, SDL_Rect& rect)
{
	Vector2D circleDistance;
	circleDistance.setX(abs(circle.x - rect.x));
	circleDistance.setY(abs(circle.y - rect.y));

	if (circleDistance.getX() > (rect.w/2 + circle.r)) { return false; }
	if (circleDistance.getY() > (rect.h/2 + circle.r)) { return false; }

	if (circleDistance.getX() <= (rect.w/2)) { return true; } 
	if (circleDistance.getY()<= (rect.h/2)) { return true; }

	int cornerDistanceSq = sqrt(circleDistance.getX() - rect.w/2) +
		sqrt(circleDistance.getY() - rect.h/2);

    return (cornerDistanceSq <= (sqrt(circle.r)));

}
