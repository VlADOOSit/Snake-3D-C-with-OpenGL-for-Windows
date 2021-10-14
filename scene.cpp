#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <ctime>
#include "scene.h"
#include <stdio.h>
#include "snake.h"
#include "food.h"
#include "board.h"
#include <gl/glut.h>

Scene::Scene()
{
	width = 1200;
	height = 800;

	sceneX = NULL;
	sceneY = NULL;
	Xalpha = NULL;
	Yalpha = NULL;
	Zalpha = NULL;
	distZ = NULL;
	time = 0;
	score = 20;
	level = 4;
	button = NULL;
	mouseX = NULL;
	mouseY = NULL;
	Ypov = NULL;

	start = true;
	finish = false;
	res = false;
}

Snake snake[401];
Food food;
Board board;

void Scene::initialize()
{
	
	sceneX = 4.2f;
	sceneY = 21.0f;
	Xalpha = 10.0f;
	Yalpha = -70.0f;
	Zalpha = 10.0f;
	distZ = -8.4f;
	time = 0;
	score = 20;
	mouseX = 0.0f;
	mouseY = 0.0f;
	Ypov = 0.0f;

	snake[0].setX(0.0f);
	snake[0].setY(0.0f);
	snake[0].setSize(2);
	snake[0].setDir(GLUT_KEY_RIGHT);
	food.setX(14);
	food.setY(0);

	start = false;
	finish = false;
	res = false;
}

void Scene::drawString(void* font, const char* text, float x, float y)
{
	if (!text)
	{
		return;
	}
	glRasterPos2f(x, y);
	while (*text)
	{
		glutBitmapCharacter(font, *text);
		text++;
	}
}

int CountLinesInFile(char* filename)
{
	std::ifstream F(filename, std::ios::in);

	if (!F)
	{
		return -1;
	}

	int count = 0;
	char buffer[1000];

	while (!F.eof())
	{
		count++;
		F.getline(buffer, 1000);
	}
	F.close();
	return count;
}


int GetStringsFromFileC(char* filename, char*** _lines = nullptr)
{
	char** lines;
	int n = CountLinesInFile(filename);

	std::ifstream F(filename);

	if (!F) return -1;
	lines = new char* [n];

	int len;
	char buffer[1000];

	for (int i = 0; i < n; i++)
	{
		F.getline(buffer, 1000);
		for (len = 0; buffer[len] != '\0'; len++);
		lines[i] = new char[len + 1];
		for (int j = 0; j < len; j++)
		{
			lines[i][j] = buffer[j];
		}
		lines[i][len] = '\0'; 
	}
	F.close();

	*_lines = lines;
	return n;
}

void Scene::paint()
{
	char text[128];
	if (!start)
	{
		sprintf(text, " Time: %d sec.   Score: %d   F1, F2, F3, F4 - Restart game  (+,-)  - Zoom   Mouse - Rotate scene   Esc - Exit  ", time, score);

	}
	glClearColor(0.3f, 0.7f, 0.4f, 0.0f);

	float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float pos[] = { 5.0f, 25.0f, 20.0f, 1.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0.0f, 0.0f, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/////

	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f); 
	if (start)
	{
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Press    F1    to    start    easy    mode", -0.3, 0.4);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Press    F2    to    start    normal    mode", -0.3, 0.1);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Press    F3    to    start    hard    mode", -0.3, -0.2);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Press    F4    to    start    vary hard    mode", -0.3, -0.5);
		res = true;
	}
	if (finish && !start && !res)
	{
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "You lose!!   F1,F2,F3,F4 - chose mode and restart,  F5 - show results ", -0.6, 0.4);

	}

	if (res && !start)
	{
		int count;
		char** lines = nullptr;
		count = GetStringsFromFileC((char*)"result.txt", &lines);
		
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "F1, F2, F3, F4, -  restart game, ESC - Exit", -0.8, 0.9);
		if (count == 2)
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 2], -0.3, 0.4);
		}
		else if (count == 3)
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 2], -0.3, 0.4);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 3], -0.3, 0.1);
		}
		else if (count == 4)
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 2], -0.3, 0.4);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 3], -0.3, 0.1);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 4], -0.3, -0.2);
		}
		else if (count == 5)
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 2], -0.3, 0.4);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 3], -0.3, 0.1);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 4], -0.3, -0.2);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 5], -0.3, -0.5);
		}
		else if (count >= 6)
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 2], -0.3, 0.4);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 3], -0.3, 0.1);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 4], -0.3, -0.2);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 5], -0.3, -0.5);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, lines[count - 6], -0.3, -0.8);
		}
		if (lines != nullptr)
		{
			for (int i = 0; i < count; i++)
			{
				delete lines[i];
			}	
		}
		if (lines != nullptr)
		{
			delete[] lines;
		}
	}

	if (!res)
	{
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -0.8f, 0.9f);
	}
	
	glPopMatrix();

	////
	gluPerspective(60, (float)width / (float)height, 2.0f, 80.0f);


	glRotatef(Yalpha, 1.0f, 0.0f, 0.0f);
	
	glRotatef(Xalpha, 0.0f, 0.0f, 1.0f);

	glTranslatef(sceneX, sceneY, distZ);

	glRotatef(Ypov, 1.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	////////////////////////////////////

	glRotatef(-Zalpha, 0.0f, 0.0f, 1.0f);

	board.draw();

	for (int i = 0; i < snake[0].getSize(); i++)
	{
		if (i == 0)
		{
			glColor3f(0.5f, 1.0f, 0.0f);
			snake[i].draw();

		}
		else
		{
			glColor3f(1.0f, 0.1f, 0.0f);
			snake[i].draw();
		}
	}
	food.draw();
	////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);

	glFlush();
	glutSwapBuffers();
}
std::ofstream out;

void Scene::gameOver()
{
	time_t now;
	struct tm nowLocal;
	now = std::time(NULL);
	nowLocal = *localtime(&now);

	for (int i = 1; i < snake[0].getSize(); i++)
	{
		if (snake[0].getX() == snake[i].getX() && snake[0].getY() == snake[i].getY())
		{
			finish = true;
		}
		if (snake[0].getX() > 18.0f || snake[0].getY() > 18.0f || snake[0].getX() < -20.0f || snake[0].getY() < -20.0f)
		{
			finish = true;
		}
	}
	if (finish && !start)
	{
		out.open("result.txt", std::ios::app);
		out << "Score = " << score << ", " << "Time = " << time << " s " << "  ////  " << nowLocal.tm_mday << "." << nowLocal.tm_mon+1 << "." << nowLocal.tm_year+1900 << " ----- " << nowLocal.tm_hour << ":" << nowLocal.tm_min << ":" << nowLocal.tm_sec <<  std::endl;
		out.close();
	}

}


void Scene::moveCamera(unsigned char key, int a, int b)
{
	switch (key)
	{
	case '+':
		if (!res && !start)
		{
			if (sceneY > 9.0f)
			{
				distZ += 0.4f;
				sceneY -= 1.0f;
				sceneX -= 0.2f;
			}
			break;
		}
	case '=':
		if (!res && !start)
		{
			if (sceneY > 9.0f)
			{
				distZ += 0.4f;
				sceneY -= 1.0f;
				sceneX -= 0.2f;
			}
			break;
		}
	case '-':
		if (!res && !start)
		{
			if (sceneY < 60.0f)
			{
				distZ -= 0.4f;
				sceneY += 1.0f;
				sceneX += 0.2f;
			}
			break;
		}
	}
}

unsigned char dir = snake[0].getDir();

void Scene::moveSnake()
{
	if (finish)
	{
		return;
	}

	for (int i = snake[0].getSize(); i > 0; i--)
	{
		snake[i].setX(snake[i - 1].getX());
		snake[i].setY(snake[i - 1].getY());
	}
	switch (dir)
	{
	case GLUT_KEY_UP :
		snake[0].setY(snake[0].getY() + 2.0f);
		break;
	case GLUT_KEY_DOWN:
		snake[0].setY(snake[0].getY() - 2.0f);
		break;
	case GLUT_KEY_LEFT:
		snake[0].setX(snake[0].getX() - 2.0f);
		break;
	case GLUT_KEY_RIGHT:
		snake[0].setX(snake[0].getX() + 2.0f);
		break;
	}
	gameOver();
}


void Scene::key(int key, int a, int b)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if ((snake[0].getDir() != GLUT_KEY_DOWN) && (snake[0].getCheck()))
		{
			snake[0].setDir(GLUT_KEY_UP);
		}
		snake[0].setCheck(false);
		break;
	case GLUT_KEY_DOWN:
		if ((snake[0].getDir() != GLUT_KEY_UP) && (snake[0].getCheck()))
		{
			snake[0].setDir(GLUT_KEY_DOWN);
		}
		snake[0].setCheck(false);
		break;
	case GLUT_KEY_LEFT:
		if ((snake[0].getDir() != GLUT_KEY_RIGHT) && (snake[0].getCheck()))
		{
			snake[0].setDir(GLUT_KEY_LEFT);
		}
		snake[0].setCheck(false);
		break;
	case GLUT_KEY_RIGHT:
		if ((snake[0].getDir() != GLUT_KEY_LEFT) && (snake[0].getCheck()))
		{
			snake[0].setDir(GLUT_KEY_RIGHT);
		}
		snake[0].setCheck(false);
		break;
	case GLUT_KEY_F1:
		level = 6;
		initialize();
		break;
	case GLUT_KEY_F2:
		level = 4;
		initialize();
		break;
	case GLUT_KEY_F3:
		level = 3;
		initialize();
		break;
	case GLUT_KEY_F4:
		level = 2;
		initialize();
		break;
	case GLUT_KEY_F5:
		res = true;
		sceneX = NULL;
		sceneY = NULL;
		Xalpha = NULL;
		Yalpha = NULL;
		Zalpha = NULL;
		distZ = NULL;
		break;
	}
}

void Scene::mouse(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	if ((state == GLUT_UP))
	{
		this->button = -1;
		return;
	}
	this->button = button;
	
}

void Scene::motion(int x, int y)
{
	switch (button)
	{
	case 0:
		if (!res)
		{
			Ypov += y - mouseY;
			Zalpha -= x - mouseX;
			mouseX = x;
			mouseY = y;
			break;
		}
	}
}

void Scene::eat()
{
	if ((snake[0].getX() == food.getX() && snake[0].getY() == food.getY())|| (snake[1].getX() == food.getX() && snake[1].getY() == food.getY()))
	{
		snake[0].SizeChange();
		score += 10;
		foodSpawn();
	}
}

void Scene::sizeWindow(int w, int h)
{
	width = w;
	if (h == 0)
		h = 1;
	height = h;
}

void Scene::foodSpawn()
{
	food.setX(((-20 / 2) + rand() % ((18 - (-20) + 2) / 2)) * 2);
	food.setY(((-20 / 2) + rand() % ((18 - (-20) + 2) / 2)) * 2);
	for (int i = 0; i < snake[0].getSize(); i++)
	{
		if (food.getX() == snake[i].getX() && food.getY() == snake[i].getY())
		{
			foodSpawn();
		}
	}
}

int tick = 0;
int tick_time = 0;

void Scene::Timer(int value)
{
	tick++;
	if (tick >= level)
	{
		tick = 0;
		snake[0].setCheck(true);
		dir = snake[0].getDir();
		moveSnake();
		eat();
	}
	tick_time++;
	if (tick_time >= 40)
	{
		if (!finish)
		{
			time++;
		}
		tick_time = 0;
	}
}