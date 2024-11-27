#define W_WIDTH 100
#define W_HEIGHT 100
#define SCALAR 5.5
#define TEXTSCALAR 2
#define SHIPSCALAR 3

#include <cstring>
#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include "ship.h"
#include "wall.h"
#include "HeliosDacFunctions.h"

int winW = W_WIDTH*SCALAR;
int winH = W_HEIGHT*SCALAR;
int level = 0;

void drawBox() {
	glPushMatrix();	
	HeliosTranslate(50*SCALAR, 50*SCALAR, 0); 
	HeliosScale(SCALAR,-SCALAR,0);
	HeliosRotate(0);
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(-49, 49); 	
		WriteHeliosPoint(-49, 49);   
		WriteHeliosPoint(49, 49); 
		WriteHeliosPoint(49, -49); 
		WriteHeliosPoint(-49, -49); 
		WriteHeliosPoint(-49, 49); 
//		WriteHeliosBlank(2, -4);
	glEnd();
	glPopMatrix();
}

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

void Wall::drawWall()
{
float real_x = x*SCALAR;
float real_y = y*SCALAR;
	glPushMatrix();	
    HeliosTranslate(real_x, real_y, 0); 
	HeliosScale(SCALAR,-SCALAR,0);	
	HeliosRotate(0);
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(-(width/2) , -(height/2)); 
		WriteHeliosPoint(-(width/2) , -(height/2));
		WriteHeliosPoint(-(width/2) , (height/2)); 
		WriteHeliosPoint((width/2) , (height/2)); 
		WriteHeliosPoint((width/2) , -(height/2));
		WriteHeliosPoint(-(width/2) , -(height/2)); 
		/*WriteHeliosBlank(-(width/2-3) , -(height/2)); 
		WriteHeliosPoint(-(width/2-3) , -(height/2));
		WriteHeliosPoint(-(width/2) , -(height/2-3));  
		WriteHeliosPoint(-(width/2) , (height/2-3)); 
		WriteHeliosPoint(-(width/2-3) , (height/2)); 
		WriteHeliosPoint((width/2-3) , (height/2)); 
		WriteHeliosPoint((width/2) , (height/2-3)); 
		WriteHeliosPoint((width/2) , -(height/2-3));
		WriteHeliosPoint((width/2-3) , -(height/2));
		WriteHeliosPoint(-(width/2-3) , -(height/2));  */
//		WriteHeliosBlank(-2 , 0); 
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
		WriteHeliosBlank(-4 , 8 ); 
		WriteHeliosPoint(-4 , 8 );   
		WriteHeliosPoint(-4, 4 ); 
		WriteHeliosPoint(4 , 4 ); 
		WriteHeliosPoint(4 , 8 );
		WriteHeliosPoint(4 , -8 ); 
		WriteHeliosPoint(4 , -4 ); 
		WriteHeliosPoint(-4 , -4 );
		WriteHeliosPoint(-4 , -8 ); 
		WriteHeliosPoint(-4 , 8 ); 	
//		WriteHeliosBlank(-2 , 4 ); 
	glEnd();
	
	HeliosRotate(c.rot);
	
    glBegin(GL_LINE_STRIP);
		WriteHeliosBlank(-2 , 2 );  
		WriteHeliosPoint(-2, 2 ); 
		WriteHeliosPoint(-1, 2 ); 
		WriteHeliosPoint(-1, 10 ); 
		WriteHeliosPoint(1, 10 );
		WriteHeliosPoint(1, 2 );
		WriteHeliosPoint(2 , 2 ); 
		WriteHeliosPoint(2 , -2 ); 
		WriteHeliosPoint(-2 , -2 );	
		WriteHeliosPoint(-2, 2 ); 
//		WriteHeliosBlank(-2 , 4 ); 
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
	HeliosRotate(rot);	
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

