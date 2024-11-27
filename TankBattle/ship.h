#include <math.h>
#include "cannon.h"

class Ship {
public:
	bool isAlive, isFiring;
	int lives, iFrames;
	double x, y, rot, xinc, yinc, speed;
	void setValues (bool, int, double , double , double );
	void drawShip();
	void move ();
	void turn(double);
	Cannon c;
	Ship();
};

void Ship::setValues(bool _isAlive, int _lives, double _x, double _y, double _rot) {
	isAlive = _isAlive;
	lives = _lives;
	x = _x;
	y = _y;
	rot = _rot;
	c.rot = _rot;
};

void Ship::move() {
	xinc = speed * sin(rot * M_PI/180);
	yinc = speed * cos(rot * M_PI/180);
	x -= xinc/20;
	y += yinc/20;
	
	if (x < 5) x = 5;
	if (x > 95) x = 95;	
	
	if (y < 5) y = 5;
	if (y > 95) y = 95;	
	
	if (speed > 0) speed = speed - speed/2;
};

void Ship::turn(double add) {
	rot += add;
	if (rot > 360) {
	rot -= 360;	
	}
	if (rot < 0) {
	rot += 360;	
	}
}

Ship::Ship() {
	isAlive = false;
	isFiring = false;
	lives = 0;
	iFrames = 0;
	x = 50;
	y = 50;
	rot = 180;
	xinc = 0;
	yinc = 0;
	speed = 0;
}
