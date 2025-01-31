#define GREEN 96

#include "DrawingFunctions.h"
#include <list>
#include <sstream>
#include <stdlib.h>
#include <SFML/Audio.hpp>

//g++ -pthread -o asteroids-laser main.cpp HeliosDac.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -std=c++17 -lusb-1.0 -lsfml-audio -lsfml-system

Ship p1;
Ship p2;
int numAsteroids = 3;

void nextLevel(std::list<Asteroid> &_asts) {
	for (int i = 0; i < numAsteroids; i++) {
		_asts.push_back(Asteroid((rand()%100),5,4,3-(rand()%6),3-(rand()%6)));
	}
	level++;
}

int main(void)
{
	GLFWwindow* window;
	
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winW, winH, "Asteroids", NULL, NULL);
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
	
	std::list<Asteroid> asts;
	nextLevel(asts);
	int state;
	
	//---"Simple" Audio Setup---
	
	sf::Sound sound;
	sf::SoundBuffer Fire; Fire.loadFromFile("sfx/fire.wav");
	sf::SoundBuffer Beat1; Beat1.loadFromFile("sfx/beat1.wav");
	sf::SoundBuffer Beat2; Beat2.loadFromFile("sfx/beat2.wav");
	sf::SoundBuffer bangSmall; bangSmall.loadFromFile("sfx/bangSmall.wav");
	sf::SoundBuffer bangMedium; bangMedium.loadFromFile("sfx/bangMedium.wav");
	sf::SoundBuffer bangLarge; bangLarge.loadFromFile("sfx/bangLarge.wav");
	
	//-------------------------------------------------
	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {	
		glClear(GL_COLOR_BUFFER_BIT);
		
		//-------------Frame Info---------------
		glPointSize(1.0f);
		//----Asteroids-----
		asts.sort();
		
		SetHeliosColour(1,1,1);
		
		std::list<Asteroid>::iterator it;
		bool visible = false;
		for (it = asts.begin(); it != asts.end(); ++it){
			if (it->getIsVis()) {
			visible = true;
			it->move();
			it->drawAsteroid();
			float astScale = it->getScale();
			
			//---Player 1 Interactions---
			float dx = abs(it->getX() - p1.x);
			float dy = abs(it->getY() - p1.y);
			float dist = sqrt(dx*dx+dy*dy);
			if (dist < astScale/2+1 && p1.iFrames <= 0) {
				sound.stop();
				sound.setBuffer(Beat1);
				sound.play();
				p1.lives--;
				p1.iFrames = 100;
			}
			if(p1.isFiring) {
				dx = abs(it->getX() - p1.b.x);
				dy = abs(it->getY() - p1.b.y);
				dist = sqrt(dx*dx+dy*dy);
				if (dist < astScale) {
					int s = it->getScale();
					if (s > 3) {
						p1.score += 25;
						sound.stop();
						sound.setBuffer(bangLarge);
						sound.play();
					} else if (s > 1) {
						p1.score += 50;
						sound.stop();
						sound.setBuffer(bangMedium);
						sound.play();
					} else {
						p1.score += 100;
						sound.stop();
						sound.setBuffer(bangSmall);
						sound.play();
					}
					if (it->split()) {
						asts.push_back(Asteroid(it->getX(),it->getY(),it->getScale(),-it->getDirX(),-it->getDirY()));
					}		
					p1.isFiring = false;
				}
			}
			
			//---Player 2 Interactions---
			dx = abs(it->getX() - p2.x);
			dy = abs(it->getY() - p2.y);
			dist = sqrt(dx*dx+dy*dy);
			if (dist < astScale/2+1 && p2.iFrames <= 0) {
				sound.stop();
				sound.setBuffer(Beat2);
				sound.play();
				p2.lives--;
				p2.iFrames = 100;
			}
			if(p2.isFiring) {
				dx = abs(it->getX() - p2.b.x);
				dy = abs(it->getY() - p2.b.y);
				dist = sqrt(dx*dx+dy*dy);
				if (dist < astScale) {
					int s = it->getScale();
					if (s > 3) {
						p2.score += 25;
						sound.stop();
						sound.setBuffer(bangLarge);
						sound.play();
					} else if (s > 1) {
						p2.score += 50;
						sound.stop();
						sound.setBuffer(bangMedium);
						sound.play();
					} else {
						p2.score += 100;
						sound.stop();
						sound.setBuffer(bangSmall);
						sound.play();
					}
					if (it->split()) {
						asts.push_back(Asteroid(it->getX(),it->getY(),it->getScale(),-it->getDirX(),-it->getDirY()));
					}		
					p2.isFiring = false;
				}
			}
			}
		}
		
		//----Setup Keyboard callback-----
		state = glfwGetKey(window, GLFW_KEY_ENTER);
		if (state == GLFW_PRESS){ p1.setValues(true, 0, 4, 45, 50); }
		if (p1.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_LEFT);
			if (state == GLFW_PRESS){
				p1.rot = p1.rot - 2.0f;
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.isFiring = true;
					p1.b.setValues(p1.x, p1.y, p1.rot);	
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_RIGHT);
			if (state == GLFW_PRESS){
				p1.rot = p1.rot + 2.0f;
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.isFiring = true;
					p1.b.setValues(p1.x, p1.y, p1.rot);
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_UP);
			if (state == GLFW_PRESS && p1.speed < 20){
				p1.speed++;
				p1.trot = p1.rot;
				state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (state == GLFW_PRESS && !p1.isFiring){
					p1.isFiring = true;
					p1.b.setValues(p1.x, p1.y, p1.rot);
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
			if (state == GLFW_PRESS && !p1.isFiring){
				p1.isFiring = true;
				p1.b.setValues(p1.x, p1.y, p1.rot);
				if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
			}
		}
		
		state = glfwGetKey(window, GLFW_KEY_SPACE);
		if (state == GLFW_PRESS){ p2.setValues(true, 0, 4, 55, 50); }
		if (p2.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_A);
			if (state == GLFW_PRESS){
				p2.rot = p2.rot - 2.0f;
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.isFiring = true;
					p2.b.setValues(p2.x, p2.y, p2.rot);
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_D);
			if (state == GLFW_PRESS){
				p2.rot = p2.rot + 2.0f;
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.isFiring = true;
					p2.b.setValues(p2.x, p2.y, p2.rot);
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_W);
			if (state == GLFW_PRESS && p2.speed < 20){
				p2.speed++;
				p2.trot = p2.rot;
				state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS && !p2.isFiring){
					p2.isFiring = true;
					p2.b.setValues(p2.x, p2.y, p2.rot);
					if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
				}
			}
			state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
			if (state == GLFW_PRESS && !p2.isFiring){
				p2.isFiring = true;
				p2.b.setValues(p2.x, p2.y, p2.rot);
				if (sound.getStatus() != sf::Sound::Playing) {
						sound.setBuffer(Fire);
						sound.play();
					}
			}
		}
		if (!visible) {
			asts.clear();
			nextLevel(asts);
		}
		
		//----Draw Player 1------	
		SetHeliosColour(0,1,0);
		if (!p1.isAlive) {
			drawScore(40, 6, p1.score);
		} 
		if (p1.isAlive) {	
			char score_buf[6];
			drawScore(40, 6, p1.score);
			drawLives(40, 12, p1.lives);
			if(p1.isFiring) {
				if (p1.b.move()) {
					p1.b.drawBullet();
				} else {
					p1.isFiring = false;
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
		if (!p2.isAlive) {
			drawScore(92, 6, p2.score);
		}		
		if (p2.isAlive) {	
			char score_buf[6];
			drawScore(92, 6, p2.score);
			drawLives(92, 12, p2.lives);
			if(p2.isFiring) {
				if (p2.b.move()) {
					p2.b.drawBullet();
				} else {
					p2.isFiring = false;
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
			int dx1 = abs(p1.x - p2.b.x);
			int dy1 = abs(p1.y - p2.b.y);
			int dist1 = sqrt(dx1*dx1+dy1*dy1);
			if (dist1 < 3 && p1.iFrames <= 0) {
				p1.lives--;
				p1.iFrames = 100;
			}
		
			int dx2 = abs(p2.x - p1.b.x);
			int dy2 = abs(p2.y - p1.b.y);
			int dist2 = sqrt(dx2*dx2+dy2*dy2);
			if (dist2 < 3 && p2.iFrames <= 0) {
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

