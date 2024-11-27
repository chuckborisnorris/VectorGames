#include <math.h>

class Asteroid {
public:
	bool isVis;
	float x, y, scale, rot, dir_x, dir_y;
	int score;
	bool split(), getIsVis();
	void drawAsteroid();
	void move ();
	float getX(), getY(), getScale(), getDirX(), getDirY();
	int getScore();
	Asteroid();
	Asteroid(float, float, float, float, float);
	bool operator <(const Asteroid & ast) const {
        return sqrt(y*y + x*x) < sqrt(ast.y*ast.y + ast.x*ast.x) ;
    }
};



bool Asteroid::split() {
	scale = scale / 2;
	score = score * 2;
	if (scale >= SHIPSCALAR/2) { 
		rot = rand() % 359;
		float dir_temp = dir_x;
		dir_x = dir_y;
		dir_y = -dir_temp;
		return true;
	} else {
		isVis = false;
		return false;
	}
};



float Asteroid::getX() 		{ return x; }
float Asteroid::getY() 		{ return y; }
float Asteroid::getDirX() 	{ return dir_x; }
float Asteroid::getDirY() 	{ return dir_y; }
float Asteroid::getScale() 	{ return scale; }
bool Asteroid::getIsVis() 	{ return isVis; }
int Asteroid::getScore() 	{ return score; }

Asteroid::Asteroid(float _x, 
					float _y, 
					float _scale, 
					float _dir_x, 
					float _dir_y) {
	x = _x;
	y = _y;
	scale = _scale;
	rot = rand() % 359;
	dir_x = _dir_x;
	dir_y = _dir_y;
	isVis = true;
	score = 25;
}

Asteroid::Asteroid() {}