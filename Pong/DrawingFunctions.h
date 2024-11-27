#define W_WIDTH 100
#define W_HEIGHT 100
#define SCALAR 5
#define TEXTSCALAR 5
#define PLAYERSCALAR 12

#include <cstring>
#include <iostream>
#include <string>
#include <bits/stdc++.h> 

#include "paddle.h"
#include "ball.h"
#include "HeliosDacFunctions.h"

int winW = W_WIDTH*SCALAR;
int winH = W_HEIGHT*SCALAR;


void drawScore(int _x, int _y, int score, int size)
{
int x = _x*SCALAR;
int y = _y*SCALAR;

std::string tmp = std::to_string(score);
reverse(tmp.begin(),tmp.end());
char const *c = tmp.c_str();
	
for (int i = 6; i > -1; i--) {
	glPushMatrix();
	
    HeliosTranslate(float(x-6*i*5), y, 0); 
	HeliosScale(size,-size,0);
	HeliosRotate(0);
	
    glBegin(GL_LINE_STRIP);
    switch ( c[i] ) {
		case '5': 
		WriteHeliosBlank(-2, -4); 
		WriteHeliosPoint(-2, -4);   
		WriteHeliosPoint(2, -4); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(-2, 4);  
		WriteHeliosPoint(2, 4);	
		break;
		
		case '0': 
		WriteHeliosBlank(-2, -4); 
		WriteHeliosPoint(-2, -4);   
		WriteHeliosPoint(-2, 4); 
		WriteHeliosPoint(2, 4);  
		WriteHeliosPoint(2, -4);
		WriteHeliosPoint(-2, -4);
		WriteHeliosBlank(-2, 4);
		WriteHeliosBlank(-2, -4);	
		break;
		
		case '1': 
		WriteHeliosBlank(0, -4);
		WriteHeliosPoint(0, -4);   
		WriteHeliosPoint(0, 4); 
		break;
		
		case '2': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(-2, -4); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(2, 4);  
		WriteHeliosPoint(-2, 4); 		
		break;
		
		case '3': 
		WriteHeliosBlank(-2, -4); 
		WriteHeliosPoint(-2, -4);   
		WriteHeliosPoint(2, -4); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(2, 4);  
		WriteHeliosPoint(-2, 4); 	
		break;
		
		case '4': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(-2, 4); 	
		break;
		
		case '6': 
		WriteHeliosBlank(2, 4); 
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-2, 4);   
		WriteHeliosPoint(-2, -4); 
		WriteHeliosPoint(2, -4); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(-2, 0);	
		break;
		
		case '7': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-2, 4); 
		break;
		
		case '8': 
		WriteHeliosBlank(-2, -4); 
		WriteHeliosPoint(-2, -4);   
		WriteHeliosPoint(-2, 4); 
		WriteHeliosPoint(2, 4);  
		WriteHeliosPoint(2, -4);  
		WriteHeliosPoint(-2, -4);  
		WriteHeliosPoint(-2, 0);  
		WriteHeliosPoint(2, 0);  
		break;
		
		case '9': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-2, 4); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(2, 0); 
		break;
		
		default: 		
		break;
	}
	glEnd();
	glPopMatrix();
}
}

void drawBox() {
	glPushMatrix();
	
    HeliosTranslate(0, 0, 0); 
	HeliosScale(1, 1, 0);
	HeliosRotate(0);
	
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(0 ,0 ); 
		WriteHeliosPoint(0 ,0 );
		WriteHeliosPoint(0 ,winH);   
		WriteHeliosPoint(winW ,winH); 
		WriteHeliosPoint(winW ,0 ); 
		WriteHeliosPoint(0 ,0 );
	glEnd();
	glPopMatrix();
}

void Paddle::draw()
{
float real_x = x*SCALAR;
float real_y = y*SCALAR;
	glPushMatrix();
	
    HeliosTranslate(real_x, real_y, 0); 
	HeliosScale(PLAYERSCALAR, PLAYERSCALAR, 0);
	HeliosRotate(0);
	
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(0 , 2 ); 
		WriteHeliosPoint(0 , 2 );   
		WriteHeliosPoint(0 , -2 ); 
		WriteHeliosPoint(0 , 2 ); 
	glEnd();
	glPopMatrix();

}

void Ball::draw()
{
float real_x = x*SCALAR;
float real_y = y*SCALAR;
	glPushMatrix();
	
    HeliosTranslate(real_x, real_y, 0); 
	HeliosScale(PLAYERSCALAR/3, PLAYERSCALAR/3, 0);
	HeliosRotate(rot);
	
    glBegin(GL_LINE_STRIP);
	
	WriteHeliosBlank(3, 3 ); 
	WriteHeliosPoint(3, 3 );
	WriteHeliosPoint(3 ,-3 );
	WriteHeliosPoint(-3 , -3 );
	WriteHeliosPoint(-3 , 3 );
	WriteHeliosPoint(3 , 3 );
	WriteHeliosBlank(3, 3 );
	
	glEnd();
	glPopMatrix();

}

int Ball::move() {
	rot++;
	int signX = -2*int(std::signbit(dir_x))+1;
	int signY = -2*int(std::signbit(dir_y))+1;
	x += (dir_x + signX*level)/(3*PLAYERSCALAR); //add speed for level
	y += (dir_y + signY*level)/(3*PLAYERSCALAR);

	
	// ---out of bounds ---
	if (y < 0)  {
		y = 1;
		bounceY();
	}
	if (y > W_HEIGHT) {
		y = W_HEIGHT-1;
		bounceY();
	}
	
	// ---out of bounds ---
	if (x <= 0) {
		reset();
		return 2;
	}
	else if (x >= W_WIDTH) {
		reset();
		return 1;
	}
	else {
		return 0;	
	}
};
