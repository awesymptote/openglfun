// ConsoleApplication1.cpp : Defines the entry point for the console application.
// CSE470 Project #0, by Kyle St. Leger-Barter


	
/* basics 
 * 
 * A basic, first OpenGL program.
 * 
 * This program illustrates how you open an window, specify its position and size,
 * and draw something in the window.
 *
 * Also illustrated: the state-machine operation of OGL. Notice that if you resize
 * the window, the box becomes blue -- the last color specified! This isn't the right
 * idea! Where should you put the color of the box?
 *
 * When you resize the window so it is not square, the box changes shape. This might
 * not be desired -- we will look into fixing this later. (Keep in mind, this has
 * something to do with the aspect ratio.)
 *
 * Try changing the size of gluOrtho2D -- see in code below -- and you'll see how the
 * relative size of the box changes within the window.
 *
 *
 * Dianne Hansford, August 2004
 * Modified by Ross Maciejewski August 2011
 */


#include <stdio.h>


/* Include the GLUT library. This file (glut.h) contains gl.h and glu.h */
/* See how this is "glut.h" as opposed to <glut.h> - this is due to the fact that you need
   glut in your local directory. */
#include "glut.h"


/* 
 * The rountine display() gets called each time the window is redrawn.
 */

int curWidth = 700;
int curHeight = 700;

float paddleYPos = 0;
float paddleXPos = 0;



void drawRect()
{
	//glPushMatrix();
	glScalef(0.5,0.5,0);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2f(-0.7,-0.5);
		glVertex2f(0.7,-0.5);
		glVertex2f(0.7,0.5);
		glVertex2f(-0.7,0.5);
	glEnd();


	//glPopMatrix();
}

void display()
{
	/* clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT);

	/* draw a filled polygon */
	// I added different color3f calls at each vertex to create a gradient across the polygon that persists if you resize the window9
	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	//if (paddleXPos >= -1 && paddleXPos <= 1)
	//{
	glLoadIdentity();
	glPushMatrix();
	glTranslatef((float)(paddleXPos), (float)(paddleYPos), 0);
		//drawRect();
	//}
	

	
	//glPopMatrix();
	glBegin(GL_POLYGON);
		glColor3f(0.0,1.0,0.0);
		glVertex2f(-0.5, -0.1);
		//glColor3f(1.0,0.0,0.0);
		glVertex2f( 0.5, -0.1);
		//glColor3f(0.0,0.0,1.0);
		glVertex2f( 0.5,  0.1);
		//glColor3f(0.123,0.54,0.97);
		glVertex2f(-0.5,  0.1);
	glEnd();
	glPopMatrix();
	
	/* draw a fancy line -- red to blue variation in color */
	/* variation is created with linear interpolation */


	/* ready to draw now! forces buffered OGL commands to execute */
	glutSwapBuffers();
}


/* Initialize states -- called before */

void init()
{
	/* set background clear color to white */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	/* set color to GREEN!*/
	//glColor3f(0.0, 1.0, 0.0);

	/* identify the projection matrix that we would like to alter */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* the window will correspond to these world coorinates */
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	

	/* identify the modeling and viewing matrix that can be modified from here on */
	/* we leave the routine in this mode in case we want to move the object around */
	/* or specify the camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*void drawRect(int width, int height, bool fill)
{
	glBegin(GL_QUADS);
		glVertex2d(-1.0,-1.0);
		gl

}*/


void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-(width/2.0),(width/2.0),-(height/2.0),(height/2.0));
	glMatrixMode(GL_MODELVIEW);

}

void skey(int key, int x, int y)
{
	switch (key)
	{

	case GLUT_KEY_LEFT:
		if (paddleXPos > -1.0)
			paddleXPos -= .05;
		break;

	case GLUT_KEY_RIGHT:
		if(paddleXPos < 1.0)
			paddleXPos += .05;
		break;

	default:
		break;
	}
	
	
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'q':	
		exit(0);
		break;

	default:
		break;

	}

	glutPostRedisplay();
}



/* The main program */

int main(int argc, char** argv)
{

	/* create a window, position it, and name it */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(curWidth, curHeight);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("basics");

	/* create a callback routine for (re-)display */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(skey);
	/* init some states */
	init();

	

	/* entering the event loop */
	glutMainLoop();

	/* code here will not be executed */
}


