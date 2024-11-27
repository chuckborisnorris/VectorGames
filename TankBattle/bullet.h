#include <math.h>
//#define PI 3.14159265

class Bullet {
public:
	double x, y, rot, xinc, yinc, speed;
	void setValues (double, double, double);
	void drawBullet();
	bool move ();
	Bullet();
};

void Bullet::setValues(double _x, double _y, double _rot) {
	x =_x;
	y = _y;
	rot = _rot;
	speed = 30;
};

bool Bullet::move() {
	xinc = speed * sin(rot * M_PI/180);
	yinc = speed * cos(rot * M_PI/180);
	
	x -= xinc/15;
	y += yinc/15;
	
	if (x < 0) 			return false;
	else if (x > 100) 	return false;
	else if (y < 0) 	return false;
	else if (y > 100) 	return false;
	else 				return true;
};

Bullet::Bullet() {}