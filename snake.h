#ifndef snake_h
#define snake_h
#include "shape.h"
#include <gl/glut.h>

class Snake : public Shape
{
private:
	int size;
	bool check;
	int dir;
public:
	Snake() : Shape()
	{
		size = 2;
		check = false;
		dir = GLUT_KEY_RIGHT;
	}
	virtual void draw();
	int getDir();
	void SizeChange();
	float getSize();
	void setSize(int size);
	bool getCheck();
	void setCheck(bool check);
	void setDir(int dir);
};

#endif