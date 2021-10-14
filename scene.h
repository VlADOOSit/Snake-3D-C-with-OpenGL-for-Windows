#ifndef scene_h
#define scene_h

class Scene
{
private:
	int width;
	int height;

	float sceneX;
	float sceneY;
	float Xalpha;
	float Yalpha;
	float Zalpha;
	float distZ;
	int level;
	int time;
	int score;

	int button;
	float mouseX, mouseY;
	float Ypov;


	bool start, finish, res;

public:
	Scene();
	void initialize();
	void gameOver();
	void paint();
	void moveCamera(unsigned char key, int a, int b);
	void drawString(void* font, const char* text, float x, float y);
	void moveSnake();
	void motion(int x, int y);
	void mouse(int button, int state, int x, int y);
	void key(int key, int a, int b);
	void sizeWindow(int w, int h);
	void eat();
	void foodSpawn();
	void Timer(int value);
};


#endif // !scene_h
