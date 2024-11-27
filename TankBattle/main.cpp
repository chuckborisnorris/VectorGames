#define GREEN 96

#include "DrawingFunctions.h"
#include <list>
#include <sstream>
#include <stdlib.h>
#include <SFML/Audio.hpp>

//g++ -pthread -o asteroids-laser main.cpp HeliosDac.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -std=c++17 -lusb-1.0 -lsfml-audio -lsfml-system

Ship p1, p2;
Wall w1, w2;
Cannon c1, c2;

int main(void)
{
	GLFWwindow* window;
	
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winW, winH, "Tank Battle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, winW, winH); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winW, winH, 0, -10, 10);

	//Back to the modelview so we can draw stuff 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	
	//----Local vars------
	int state;
	
	//---"Simple" Audio Setup---	
	sf::Sound sound;
	sf::SoundBuffer Fire; Fire.loadFromFile("sfx/fire.wav");
	sf::SoundBuffer bangLarge; bangLarge.loadFromFile("sfx/bangLarge.wav");
	
	//-------------------------------------------------
	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {	
		glClear(GL_COLOR_BUFFER_BIT);
		
		//-------------Frame Info---------------
		glPointSize(1.0f);		
		SetHeliosColour(1,1,1);
		
		//drawBox();
		
		w1.setValues(55, 30, 50, 20); 
		w2.setValues(45, 70, 50, 20);  
		w1.drawWall();
		w2.drawWall();
		
		
		//----Setup Keyboard callback-----
		if (!p1.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_ENTER);
			if (state == GLFW_PRESS){ 
				p1.setValues(true, 4, 15, 15, 270); 
				p2.setValues(true, 4, 85, 85, 90);  
			}
		}
		
		if (!p2.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_SPACE);
			if (state == GLFW_PRESS){ 
				p1.setValues(true, 4, 15, 15, 270); 
				p2.setValues(true, 4, 85, 85, 90); 
			}
		}
		
		if (p1.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_LEFT);
			if (state == GLFW_PRESS){
				p1.turn(-2.0f);
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.isFiring = true;
					p1.c.b.setValues(p1.x, p1.y, p1.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_RIGHT);
			if (state == GLFW_PRESS){
				p1.turn(2.0f);
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.isFiring = true;
					p1.c.b.setValues(p1.x, p1.y, p1.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_N);
			if (state == GLFW_PRESS){
				p1.c.turn(-2.0f);
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.c.b.setValues(p1.x, p1.y, p1.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_M);
			if (state == GLFW_PRESS){
				p1.c.turn(2.0f);
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.c.b.setValues(p1.x, p1.y, p1.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_UP);
			if (state == GLFW_PRESS){
				p1.speed = p1.speed+2;
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.isFiring = true;
					p1.c.b.setValues(p1.x, p1.y, p1.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
			if (state == GLFW_PRESS && !p1.isFiring){
				p1.isFiring = true;
				p1.c.b.setValues(p1.x, p1.y, p1.c.rot+6);	
				if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
			}
		}
		
		//P2 controls 
		if (p2.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_A);
			if (state == GLFW_PRESS){
				p2.turn(-2.0f);
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.isFiring = true;
					p2.c.b.setValues(p2.x, p2.y, p2.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_D);
			if (state == GLFW_PRESS){
				p2.turn(2.0f);
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.isFiring = true;
					p2.c.b.setValues(p2.x, p2.y, p2.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_Z);
			if (state == GLFW_PRESS){
				p2.c.turn(-2.0f);
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.c.b.setValues(p2.x, p2.y, p2.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_X);
			if (state == GLFW_PRESS){
				p2.c.turn(2.0f);
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.c.b.setValues(p2.x, p2.y, p2.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_W);
			if (state == GLFW_PRESS){
				p2.speed = p2.speed+2;
				p2.rot = p2.rot;
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.isFiring = true;
					p2.c.b.setValues(p2.x, p2.y, p2.c.rot+6);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
			if (state == GLFW_PRESS && !p2.isFiring){
				p2.isFiring = true;
				p2.c.b.setValues(p2.x, p2.y, p2.c.rot+6);	
				if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
			}
		}
		
		//----Draw Player 1------	
		SetHeliosColour(0,1,0);
		if (p1.isAlive) {	
			drawLives(34, 6, p1.lives);
			if(p1.isFiring) {
				if (p1.c.b.move()) {
					if ((abs(p1.c.b.x - w1.x) < w1.width/2 && 
						abs(p1.c.b.y - w1.y) < w1.height/2) ||
						(abs(p1.c.b.x - w2.x) < w2.width/2 && 
						abs(p1.c.b.y - w2.y) < w2.height/2)){
						p1.isFiring = false;
					}
					else {
					p1.c.b.drawBullet();
					}
				} else {
					p1.isFiring = false;
				}
			}
			
			//Mate! can you even collide?!
			#define HALF_TANK	5			
			//Wall 1 (top)
			if (abs(p1.x - w1.x) <= w1.width/2 +HALF_TANK &&
			   abs(p1.y - w1.y) <= w1.height/2 +HALF_TANK) {
				if (p1.x - w1.x < 0 && abs(p1.y - w1.y) <= w1.height/2) {
					p1.x = w1.x - w1.width/2 -HALF_TANK;
				}
				else if (p1.x - w1.x > 0 && abs(p1.y - w1.y) <= w1.height/2) {
					p1.x = w1.x + w1.width/2 +HALF_TANK;
				}
				else if (p1.y - w1.y < 0 && abs(p1.x - w1.x) <= w1.width/2) {
					p1.y = w1.y - w1.height/2 -HALF_TANK;
				}
				else if (p1.y - w1.y > 0 && abs(p1.x - w1.x) <= w1.width/2) {
					p1.y = w1.y + w1.height/2 +HALF_TANK;
				}
			}
			//Wall 2 (bottom)
			if (abs(p1.x - w2.x) <= w2.width/2 +HALF_TANK &&
			   abs(p1.y - w2.y) <= w2.height/2 +HALF_TANK) {
				if (p1.x - w2.x < 0 && abs(p1.y - w2.y) <= w2.height/2) {
					p1.x = w2.x - w2.width/2 -HALF_TANK;
				}
				else if (p1.x - w2.x > 0 && abs(p1.y - w2.y) <= w2.height/2) {
					p1.x = w2.x + w2.width/2 +HALF_TANK;
				}
				else if (p1.y - w2.y < 0 && abs(p1.x - w2.x) <= w2.width/2) {
					p1.y = w2.y - w2.height/2 -HALF_TANK;
				}
				else if (p1.y - w2.y > 0 && abs(p1.x - w2.x) <= w2.width/2) {
					p1.y = w2.y + w2.height/2 +HALF_TANK;
				}
			}
			if (p1.iFrames > 0) {
				SetHeliosColour(1,1,0);
				p1.iFrames--;
			}
			p1.move();
			p1.drawShip();
		}
		if (p1.lives <= 0) { p1.isAlive = false; }
		
		//----Draw Player 2------	
		SetHeliosColour(0,0,1);	
		if (p2.isAlive) {	
			drawLives(92, 94, p2.lives);
			if(p2.isFiring) {
				if (p2.c.b.move()) {
					if ((abs(p2.c.b.x - w1.x) < w1.width/2 && 
						abs(p2.c.b.y - w1.y) < w1.height/2) ||
						(abs(p2.c.b.x - w2.x) < w2.width/2 && 
						abs(p2.c.b.y - w2.y) < w2.height/2)){
						p2.isFiring = false;
					}
					else {
					p2.c.b.drawBullet();
					}
				} else {
					p2.isFiring = false;
				}
			}
			
			//Wall 1 (top)
			if (abs(p2.x - w1.x) <= w1.width/2 +HALF_TANK &&
			   abs(p2.y - w1.y) <= w1.height/2 +HALF_TANK) {
				if (p2.x - w1.x < 0 && abs(p2.y - w1.y) <= w1.height/2) {
					p2.x = w1.x - w1.width/2 -HALF_TANK;
				}
				else if (p2.x - w1.x > 0 && abs(p2.y - w1.y) <= w1.height/2) {
					p2.x = w1.x + w1.width/2 +HALF_TANK;
				}
				else if (p2.y - w1.y < 0 && abs(p2.x - w1.x) <= w1.width/2) {
					p2.y = w1.y - w1.height/2 -HALF_TANK;
				}
				else if (p2.y - w1.y > 0 && abs(p2.x - w1.x) <= w1.width/2) {
					p2.y = w1.y + w1.height/2 +HALF_TANK;
				}
			}
			//Wall 2 (bottom)
			if (abs(p2.x - w2.x) <= w2.width/2 +HALF_TANK &&
			   abs(p2.y - w2.y) <= w2.height/2 +HALF_TANK) {
				if (p2.x - w2.x < 0 && abs(p2.y - w2.y) <= w2.height/2) {
					p2.x = w2.x - w2.width/2 -HALF_TANK;
				}
				else if (p2.x - w2.x > 0 && abs(p2.y - w2.y) <= w2.height/2) {
					p2.x = w2.x + w2.width/2 +HALF_TANK;
				}
				else if (p2.y - w2.y < 0 && abs(p2.x - w2.x) <= w2.width/2) {
					p2.y = w2.y - w2.height/2 -HALF_TANK;
				}
				else if (p2.y - w2.y > 0 && abs(p2.x - w2.x) <= w2.width/2) {
					p2.y = w2.y + w2.height/2 +HALF_TANK;
				}
			}
			if (p2.iFrames > 0) {
				SetHeliosColour(1,0,1);
				p2.iFrames--;
			}
			p2.move();
			p2.drawShip();
		}
		if (p2.lives <= 0) { p2.isAlive = false; }
		if (p1.lives <= 0 && p2.lives <= 0) { level = 0; }
		
		//--------PvP-----------
		if (p1.isAlive && p2.isAlive) {
			int dx1 = abs(p1.x - p2.c.b.x);
			int dy1 = abs(p1.y - p2.c.b.y);
			int dist1 = sqrt(dx1*dx1+dy1*dy1);
			if (dist1 < 3 && p1.iFrames <= 0) {
				sound.stop();
				sound.setBuffer(bangLarge);
				sound.play();
				p1.lives--;
				p1.iFrames = 100;
			}
		
			int dx2 = abs(p2.x - p1.c.b.x);
			int dy2 = abs(p2.y - p1.c.b.y);
			int dist2 = sqrt(dx2*dx2+dy2*dy2);
			if (dist2 < 3 && p2.iFrames <= 0) {
				sound.stop();
				sound.setBuffer(bangLarge);
				sound.play();
				p2.lives--;
				p2.iFrames = 100;
			}
		}
		
		//---Cleanup---
		glfwSwapBuffers(window);
		glfwPollEvents();
		WriteHeliosFrame();
		
	}
	CloseHeliosDAC() ;
    glfwTerminate();
    return 0;
}

