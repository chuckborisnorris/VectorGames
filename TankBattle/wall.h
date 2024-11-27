#include <math.h>
#define PI 3.14159265

class Wall {
public:
	int width, height;
	float x, y;
	void setValues (float, float, int, int);
	void drawWall();
};

void Wall::setValues(float _x, float _y, int _width, int _height) {
	x = _x;
	y = _y;
	width = _width;
	height = _height;
};