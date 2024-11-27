#include <math.h>

class Ball {
public:
	bool isVis;
	float x, y, rot, dir_x, dir_y, level;
	float maxLevel = 16;
	bool getIsVis();
	void draw(), changeDir(), bounceY(), reset();
	int move ();
	float getX(), getY(), getDirX(), getDirY();
	Ball();
	bool operator <(const Ball & ball) const {
        return sqrt(y*y + x*x) < sqrt(ball.y*ball.y + ball.x*ball.x) ;
    }
};

float Ball::getX() 		{ return x; }
float Ball::getY() 		{ return y; }
float Ball::getDirX() 	{ return dir_x; }
float Ball::getDirY() 	{ return dir_y; }
bool Ball::getIsVis() 	{ return isVis; }

Ball::Ball() {
	x = 50;
	y = 50;
	rot = rand() % 359;
	dir_x = 10-(rand()%20);
	dir_y = 5-(rand()%10);
	isVis = true;
}

void Ball::reset() {
	x = 50;
	y = 50;
	level = 0;
	dir_x = -dir_x;
}

void Ball::changeDir() {
	level++;
	if (level > maxLevel) {
		maxLevel = level;
		std::cout << maxLevel << std::endl;
	}

	dir_x = -dir_x;
	dir_y += 5-(rand()%10);
}

void Ball::bounceY() {
	dir_y = -dir_y;
}