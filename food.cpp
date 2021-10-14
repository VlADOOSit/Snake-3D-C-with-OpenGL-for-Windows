#include "food.h"
#include <gl/glut.h>


void Food::draw()
{
	glColor3f(0, 1, 0);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);
	glBegin(GL_QUADS);
	// ����� �����
	glNormal3f(-1, 0, 0);
	glVertex3f((x - 1) / 2, (y - 1) / 2, 0);
	glVertex3f((x - 1) / 2, (y + 1) / 2, 0);
	glVertex3f((x - 1) / 2, (y + 1) / 2, 1);
	glVertex3f((x - 1) / 2, (y - 1) / 2, 1);
	// ������ �����
	glNormal3f(1, 0, 0);
	glVertex3f((x + 1) / 2, (y - 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y + 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y + 1) / 2, 1);
	glVertex3f((x + 1) / 2, (y - 1) / 2, 1);
	// ������ �����
	glNormal3f(0, 0, -1);
	glVertex3f((x - 1) / 2, (y - 1) / 2, 0);
	glVertex3f((x - 1) / 2, (y + 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y + 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y - 1) / 2, 0);
	// ������� �����
	glNormal3f(0, 0, 1);
	glVertex3f((x - 1) / 2, (y - 1) / 2, 1);
	glVertex3f((x - 1) / 2, (y + 1) / 2, 1);
	glVertex3f((x + 1) / 2, (y + 1) / 2, 1);
	glVertex3f((x + 1) / 2, (y - 1) / 2, 1);
	// ������ �����
	glNormal3f(0, -1, 0);
	glVertex3f((x - 1) / 2, (y + 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y + 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y + 1) / 2, 1);
	glVertex3f((x - 1) / 2, (y + 1) / 2, 1);
	// �������� �����
	glNormal3f(0, 1, 0);
	glVertex3f((x - 1) / 2, (y - 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y - 1) / 2, 0);
	glVertex3f((x + 1) / 2, (y - 1) / 2, 1);
	glVertex3f((x - 1) / 2, (y - 1) / 2, 1);
	glEnd();
}
