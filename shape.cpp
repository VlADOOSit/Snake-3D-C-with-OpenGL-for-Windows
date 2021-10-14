#include "shape.h"

Shape::Shape()
{
	x = 0;
	y = 0;
}

float Shape::getX()
{
	return x;
}

float Shape::getY()
{
	return y;
}

void Shape::setX(float x)
{
	this->x = x;
}

void Shape::setY(float y)
{
	this->y = y;
}
