#define W_WIDTH 100
#define W_HEIGHT 100
#define SCALAR 5
#define TEXTSCALAR 2
#define SHIPSCALAR 2

#include <cstring>
#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include "asteroid.h"
#include "ship.h"
#include "HeliosDacFunctions.h"

int winW = W_WIDTH*SCALAR;
int winH = W_HEIGHT*SCALAR;
int level = 0;

void drawLives(int _x, int _y, int lives)
{
int x = _x*SCALAR;
int y = _y*SCALAR;

glPushMatrix();
	
    HeliosTranslate(x, y, 0); 
	HeliosScale(TEXTSCALAR,-TEXTSCALAR,0);
	HeliosRotate(0);
	
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(2, -4); 	
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-20*lives, 4); 
		WriteHeliosPoint(-20*lives, -4); 
		WriteHeliosPoint(2, -4); 
//		WriteHeliosBlank(2, -4);
	glEnd();
glPopMatrix();

}

void drawScore(int _x, int _y, int score)
{
int x = _x*SCALAR;
int y = _y*SCALAR;

std::string tmp = std::to_string(score);
reverse(tmp.begin(),tmp.end());
char const *c = tmp.c_str();
	
for (int i = 6; i > -1; i--) {
	glPushMatrix();
	
    HeliosTranslate(float(x-6*i*TEXTSCALAR), y, 0); 
	HeliosScale(TEXTSCALAR,-TEXTSCALAR,0);
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
//		WriteHeliosBlank(2, 4);		
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
//		WriteHeliosBlank(-2, -4); 		
		break;
		
		case '1': 
		WriteHeliosBlank(0, -4);
		WriteHeliosPoint(0, -4);   
		WriteHeliosPoint(0, 4); 
//		WriteHeliosBlank(0, 4);
		break;
		
		case '2': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(-2, -4); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(2, 4);  
		WriteHeliosPoint(-2, 4); 
//		WriteHeliosBlank(-2, 4);		
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
//		WriteHeliosBlank(-2, 4);		
		break;
		
		case '4': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(-2, 4); 
//		WriteHeliosBlank(-2, 4);		
		break;
		
		case '6': 
		WriteHeliosBlank(2, 4); 
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-2, 4);   
		WriteHeliosPoint(-2, -4); 
		WriteHeliosPoint(2, -4); 
		WriteHeliosPoint(2, 0); 
		WriteHeliosPoint(-2, 0);
//		WriteHeliosBlank(-2, 0);		
		break;
		
		case '7': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-2, 4); 
//		WriteHeliosBlank(-2, 4);
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
//		WriteHeliosBlank(2, 0);
		break;
		
		case '9': 
		WriteHeliosBlank(2, -4); 
		WriteHeliosPoint(2, -4);   
		WriteHeliosPoint(2, 4); 
		WriteHeliosPoint(-2, 4); 
		WriteHeliosPoint(-2, 0); 
		WriteHeliosPoint(2, 0); 
//		WriteHeliosBlank(2, 0); 
		break;
		
		default: 
/* 		WriteHeliosBlank(-2*TEXTSCALAR + (x-6*i*TEXTSCALAR), -4*TEXTSCALAR + y); 
		WriteHeliosPoint(-2*TEXTSCALAR + (x-6*i*TEXTSCALAR), -4*TEXTSCALAR + y);   
		WriteHeliosPoint(-2*TEXTSCALAR + (x-6*i*TEXTSCALAR), 4*TEXTSCALAR + y); 
		WriteHeliosPoint(2*TEXTSCALAR + (x-6*i*TEXTSCALAR), 4*TEXTSCALAR + y);  
		WriteHeliosPoint(2*TEXTSCALAR + (x-6*i*TEXTSCALAR), -4*TEXTSCALAR + y);
		WriteHeliosPoint(-2*TEXTSCALAR + (x-6*i*TEXTSCALAR), -4*TEXTSCALAR + y);  */		
		break;
	}
	glEnd();
	glPopMatrix();
}
}



void Asteroid::drawAsteroid()
{
float real_x = x*SCALAR;
float real_y = y*SCALAR;
	glPushMatrix();
	
    HeliosTranslate(real_x, real_y, 0); 
	HeliosScale(scale*SHIPSCALAR, scale*SHIPSCALAR, 0);
	HeliosRotate(rot);
	
    glBegin(GL_LINE_STRIP);
	
	WriteHeliosBlank(0, 0 ); 
	WriteHeliosPoint(3, 3 );
	WriteHeliosPoint(3 ,-3 );
	WriteHeliosPoint(-3 , -3 );
	WriteHeliosPoint(-3 , 3 );
	WriteHeliosPoint(3 , 3 );
//	WriteHeliosBlank(3, 3 );
	
	glEnd();
	glPopMatrix();

}

void Ship::drawShip()
{
float real_x = x*SCALAR;
float real_y = y*SCALAR;
	glPushMatrix();
	
    HeliosTranslate(real_x, real_y, 0); 
	HeliosScale(SHIPSCALAR, SHIPSCALAR, 0);
	HeliosRotate(rot);
	
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(-2 , -4 ); 
		WriteHeliosPoint(-2 , -4 );   
		WriteHeliosPoint(0, 4 ); 
		WriteHeliosPoint(2 , -4 ); 
		WriteHeliosPoint(-2 , -4 );
///		WriteHeliosBlank(-2 , -4 ); 
	glEnd();
	glPopMatrix();

}

void Bullet::drawBullet()
{
float real_x = x*SCALAR;
float real_y = y*SCALAR;
	glPushMatrix();
	
    HeliosTranslate(real_x, real_y, 0); 
	HeliosScale(SHIPSCALAR, SHIPSCALAR, 0);
	HeliosRotate(0);
	
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(-2 , 0); 
		WriteHeliosPoint(-2 , 0);   
		WriteHeliosPoint(0, 2 ); 
		WriteHeliosPoint(2 , 0); 
		WriteHeliosPoint(0, -2 ); 
		WriteHeliosPoint(-2 , 0);
//		WriteHeliosBlank(-2 , 0); 
	glEnd();
	glPopMatrix();

}


void Asteroid::move() {
	rot++;
	x += (dir_x + level)/(5*SHIPSCALAR); //add speed for level
	y += (dir_y + level)/(5*SHIPSCALAR);
	
	if (x < 10) 	x += 80;
	if (x > 90) 	x -= 80;
	if (y < 10) 	y += 80;
	if (y > 90) 	y -= 80;
};

