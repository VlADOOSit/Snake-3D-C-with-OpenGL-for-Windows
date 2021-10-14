#include "board.h"
#include <gl/glut.h>

void Board::draw()
{
	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = -10; i < 10; i++)
	{
		for (int j = -10; j < 10; j++)
		{
			glPushMatrix();
			if ((j + i) % 2 == 0)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				glMaterialf(GL_FRONT, GL_SHININESS, 64);
			}
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				glMaterialf(GL_FRONT, GL_SHININESS, 80);
			}


			glTranslatef(i * 1.0f, j * 1.0f, 0.0f);


			glBegin(GL_QUADS);
			// лева€ грань
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.4f);
			glVertex3f(-0.5f, 0.5f, -0.4f);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			// права€ грань
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -0.4f);
			glVertex3f(0.5f, 0.5f, -0.4f);
			glVertex3f(0.5f, 0.5f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.0f);
			// нижн€€ грань
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-0.5f, -0.5f, -0.4f);
			glVertex3f(-0.5f, 0.5f, -0.4f);
			glVertex3f(0.5f, 0.5f, -0.4f);
			glVertex3f(0.5f, -0.5f, -0.4f);
			// верхн€€ грань
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.0f);
			// задн€€ грань
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-0.5f, 0.5f, -0.4f);
			glVertex3f(0.5f, 0.5f, -0.4f);
			glVertex3f(0.5f, 0.5f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			// передн€€ грань
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.4f);
			glVertex3f(0.5f, -0.5f, -0.4f);
			glVertex3f(0.5f, -0.5f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glEnd();
			glPopMatrix();
		}
	}
}
