#ifndef shape_h
#define shape_h

class Shape
{
protected:
	float x;
	float y;
public:
	Shape();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	virtual void draw() = 0;
};

#endif