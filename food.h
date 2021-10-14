#ifndef food_h
#define food_h
#include "shape.h"

class Food : public Shape
{

public:
	Food() : Shape() 
	{
		x = 14;
		y = 0;
	}
	virtual void draw();
};

#endif