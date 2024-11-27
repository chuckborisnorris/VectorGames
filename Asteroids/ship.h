#include "bullet.h"
#include <math.h>
#define PI 3.14159265

class Ship {
public:
	bool isAlive, isFiring;
	int score, lives, iFrames;
	float x, y, rot, xinc, yinc, speed, trot;
	void setValues (bool, int, int, int, int);
	void drawShip();
	void move ();
	Bullet b;
	Ship();
};

void Ship::setValues(bool _isAlive, int _score, int _lives, int _x, int _y) {
	isAlive = _isAlive;
	score = _score;
	lives = _lives;
	x = _x;
	y = _y;
};

void Ship::move() {
	xinc = speed * sin(trot * PI/180);
	yinc = speed * cos(trot * PI/180);
	x -= xinc/20;
	y += yinc/20;
	
	if (x < 0) 		x += 100;
	if (x > 100) 	x -= 100;
	if (y < 0) 		y += 100;
	if (y > 100) 	y -= 100;
	
	if (speed > 0) speed = speed - 0.1f;
};

Ship::Ship() {
	isAlive = false;
	isFiring = false;
	score = 0;
	lives = 0;
	iFrames = 0;
	x = 50;
	y = 50;
	rot = 180;
	xinc = 0;
	yinc = 0;
	speed = 0;
	trot = rot;
}
