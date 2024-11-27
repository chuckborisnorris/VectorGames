
class Paddle {
public:
	bool isAlive, isPower;
	int score;
	float x, y, speed, iFrames;
	void setAlive (float);
	void draw();
	void move ();
	Paddle();
};

void Paddle::setAlive(float _x) {
	x = _x;	
	isAlive = true;
	score = 0;
}

void Paddle::move() {
	y += speed;
	
	if (y < 2) y = 2;
	if (y > 98) y = 98;	
	if (speed != 0) speed = speed - speed/2;
	
};

Paddle::Paddle() {
	isAlive = false;
	isPower = false;
	score = 0;
	iFrames = 0;
	x = 0;
	y = 50;
	speed = 0;
}
