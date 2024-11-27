#define GREEN 96

#include "DrawingFunctions.h"
#include <list>
#include <sstream>
#include <SFML/Audio.hpp>

Paddle p1, p2;
Ball b1;

// g++ -pthread -o pong-laser  main.cpp HeliosDac.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -std=c++17 -lusb-1.0 -lsfml-audio -lsfml-system

int main(void)
{
	GLFWwindow* window;
	
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winW, winH, "Pong", NULL, NULL);
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
	
	//---"Simple" Audio Setup---
	
	sf::Sound sound;
	sf::SoundBuffer Beat1; Beat1.loadFromFile("sfx/beat1.wav");
	sf::SoundBuffer Beat2; Beat2.loadFromFile("sfx/beat2.wav");
	sf::SoundBuffer bangLarge; bangLarge.loadFromFile("sfx/bangLarge.wav");
	
	//----Local vars------
	int state;
	
	
	//-------------------------------------------------
	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {	
		glClear(GL_COLOR_BUFFER_BIT);
		
		//-------------Frame Info---------------
		glPointSize(1.0f);
		
		
		//----Setup Keyboard callback-----
		state = glfwGetKey(window, GLFW_KEY_ENTER);
		if (state == GLFW_PRESS) { 
			p1.setAlive(1); 
			p2.setAlive(W_WIDTH); 
		}
		state = glfwGetKey(window, GLFW_KEY_SPACE);
		if (state == GLFW_PRESS) { 
			p1.setAlive(0); 
			p2.setAlive(W_WIDTH); 
		}
		if (p1.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_UP);
			if (state == GLFW_PRESS){
				p1.speed = -1;
			}
			state = glfwGetKey(window, GLFW_KEY_DOWN);
			if (state == GLFW_PRESS){
				p1.speed = 1;
			}
		}
		
		if (p2.isAlive) {
			state = glfwGetKey(window, GLFW_KEY_W);
			if (state == GLFW_PRESS){
				p2.speed = -1;
			}
			state = glfwGetKey(window, GLFW_KEY_S);
			if (state == GLFW_PRESS){
				p2.speed = 1;
			}
		}
		
		//----Draw Scores------	
		SetHeliosColour(1,1,1);
		drawScore(70, 4, p2.score, 5);
		drawScore(54,4,b1.level, 3);
		drawScore(30, 4, p1.score, 5);
		//drawBox();
		
		//----Draw Player 1------
		if (p1.isAlive) {	
			p1.move();
			p1.draw();
		}		
		//----Draw Ball-----
		if (p1.isAlive && p2.isAlive) {	
			int scored = b1.move();
			b1.draw();
			switch (scored) {
				case 1:
					p1.score++;
					sound.setBuffer(bangLarge);
					sound.play();
					break;
				case 2:
					p2.score++;
					sound.setBuffer(bangLarge);
					sound.play();
					break;
				default:
					break;
			}
		}		
		//----Draw Player 2------	
		if (p2.isAlive) {	
			p2.move();
			p2.draw();
		}
		
		//---Player 1----
		float dx = abs(b1.getX() - p1.x);
		float dy = abs(b1.getY() - p1.y);
		float dist = sqrt(dx*dx+dy*dy);
		if (dist < PLAYERSCALAR/2 && p1.iFrames <= 0) {
			b1.changeDir();
			p1.iFrames = 50;
			sound.setBuffer(Beat1);
			sound.play();
		}
		if (p1.iFrames > 0) {
			p1.iFrames--;
		}
				
		//---Player 2----
		dx = abs(b1.getX() - p2.x);
		dy = abs(b1.getY() - p2.y);
		dist = sqrt(dx*dx+dy*dy);
		if (dist < PLAYERSCALAR/2 && p2.iFrames <= 0) {
			b1.changeDir();
			p2.iFrames = 50;
			sound.setBuffer(Beat2);
			sound.play();
		}
		if (p2.iFrames > 0) {
			p2.iFrames--;
		}
		
		//--- End Condition-----
		if (p2.score == 15) { p1.isAlive = false; }
		if (p1.score == 15) { p2.isAlive = false; }

		
		//---Cleanup---
		glfwSwapBuffers(window);
		glfwPollEvents();
		WriteHeliosFrame();
		
	}
	CloseHeliosDAC() ;
    glfwTerminate();
    return 0;
}

