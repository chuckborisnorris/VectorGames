#include "bullet.h"
#include <math.h>
//#define PI 3.14159265

class Cannon {
public:
	double rot;
	void turn(double);
	Bullet b;
	Cannon();
};

void Cannon::turn(double add) {
	rot += add;
	if (rot > 360) {
	rot -= 360;	
	}
	if (rot < 0) {
	rot += 360;	
	}
}


Cannon::Cannon() {
	rot = 0;
}
