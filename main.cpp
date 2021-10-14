#include <gl/glut.h>
#include "scene.h"

Scene scene;

void display()
{
	scene.paint();
}

void moveCamera(unsigned char key, int a, int b)
{
	scene.moveCamera(key, a, b);
	if (key == 27)
	{
		exit(0);
	}
}

void mouse(int button, int state, int x, int y)
{
	scene.mouse(button, state, x, y);
}

void motion(int x, int y)
{
	scene.motion(x, y);
}

void moveSnake(int key, int a, int b)
{
	scene.key(key, a, b);
}

void Timer(int value)
{
	scene.Timer(value);
	glutPostRedisplay();
	glutTimerFunc(30, Timer, 0);
}

void Reshape(int w, int h)
{
	scene.sizeWindow(w, h);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Snake");

	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(display);
	glutTimerFunc(30, Timer, 0);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(moveCamera);
	
	glutSpecialFunc(moveSnake);
	

	glutMainLoop();
	return 0;
}