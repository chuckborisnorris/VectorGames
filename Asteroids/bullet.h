#include <math.h>
#define PI 3.14159265

class Bullet {
public:
	float x, y, rot, xinc, yinc;
	void setValues (float, float, float);
	void drawBullet();
	bool move ();
	Bullet();
};

void Bullet::setValues(float _x, float _y, float _rot) {
	x =_x;
	y = _y;
	rot = _rot;
};

bool Bullet::move() {
	xinc = 30 * sin(rot * PI/180);
	yinc = 30 * cos(rot * PI/180);
	
	x -= xinc/20;
	y += yinc/20;
	
	if (x < 0) 			return false;
	else if (x > 100) 	return false;
	else if (y < 0) 	return false;
	else if (y > 100) 	return false;
	else 				return true;
};

Bullet::Bullet() {}