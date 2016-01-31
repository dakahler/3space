// 3-Space Emulation Engine
// Author: Dave Kahler

// Feature List:
//   Keyboard-based Transformations
//   Texture Mapping Support
//   .PLG File Type Object Importer

#define PI  3.1415926535897932

#include <iostream>
#include "glut.h"
#include <math.h>
#include "roomimp.cpp"
#include "isInside.cpp"
#include <stdlib.h>
#include <conio.h>
#include "png/glpng.h"    // Free Internet Library .PNG Texture Loader

double x,y,z,yr,xr;
int x_pp,y_pp;
int tex1,tex2,tex3;

// Degree Sin
double dsin(int angle)
{
	return(sin(angle*(PI/180)));
}

// Degree Cos
double dcos(int angle)
{
	return(cos(angle*(PI/180)));
}

// Initialize Parameters
void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,800/600,1,1000);
	glClearColor(255,255,255,0);
	glEnable(GL_DEPTH_TEST);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glEnable(GL_TEXTURE_2D);


	// Call .PNG loading function pngBind to create texture objects
	tex1=pngBind("squares.png",0,PNG_SOLID,NULL,GL_REPEAT,GL_LINEAR,GL_LINEAR);
	tex2=pngBind("sky.png",0,PNG_SOLID,NULL,GL_REPEAT,GL_NEAREST,GL_NEAREST);
	tex3=pngBind("bump6.png",0,PNG_SOLID,NULL,GL_REPEAT,GL_NEAREST,GL_NEAREST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Redraw Display
void display(void)
{
	int j=0;

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xr,1,0,0);
	glRotatef(yr,0,1,0);
	glTranslatef(x,y,z);
	glBindTexture(GL_TEXTURE_2D,tex1);

	// Traverse Polygon Linked List
	PolyDef *travpoly=new PolyDef;
	travpoly=first->next;
	while (travpoly!=NULL) {
		j=0;
		glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3f(travpoly->x,travpoly->y,travpoly->z);
		travpoly=travpoly->next;
		glTexCoord2f(2,0);
		glVertex3f(travpoly->x,travpoly->y,travpoly->z);
		travpoly=travpoly->next;
		glTexCoord2f(2,1);
		glVertex3f(travpoly->x,travpoly->y,travpoly->z);
		travpoly=travpoly->next;
		glTexCoord2f(0,1);
		glVertex3f(travpoly->x,travpoly->y,travpoly->z);
		travpoly=travpoly->next;

		glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
}

// Respond to keyboard input
void keyboard(unsigned char keypress,int w,int h)
{
	int coll;
	double xt,zt;

	if (keypress=='w') {
		xt=x+((dcos(yr+90)));
		zt=z+((dsin(yr+90)));
		coll=1;
		if (coll==1) {
			x=xt;
			z=zt;
		}
	}
	if (keypress=='s') {
		xt=x+dcos(yr-90);
		zt=z+dsin(yr-90);
		coll=1;
		if (coll==1) {
			x=xt;
			z=zt;
		}
	}
	if (keypress=='a') {
		xt=x+dcos(yr);
		zt=z+dsin(yr);
		coll=1;
		if (coll==1) {
			x=xt;
			z=zt;
		}
	}
	if (keypress=='d') {
		xt=x+dcos(yr+180);
		zt=z+dsin(yr+180);
		coll=1;
		if (coll==1) {
			x=xt;
			z=zt;
		}
	}
	if (keypress=='z')
		y++;
	if (keypress=='x')
		y--;
	if (keypress=='.')
		yr++;
	if (keypress==',')
		yr--;
	if (keypress=='k')
		xr+=1;

	glutPostRedisplay();
}

// Respond to mouse movement
void mouse(int x_m,int y_m)
{	
	int x_temp=x_m,y_temp=y_m;
	if (x_m>x_pp || (x_pp==799 && x_m==799)) {
		while (x_m>x_pp) {
			x_m--;
			yr+=.2;
			glutPostRedisplay();
		}
		if (x_m==799 && x_pp==799) {
			x_m--;
			yr+=.2;
			glutPostRedisplay();
		}
	}
	if (x_m<x_pp || (x_pp==0 && x_m==0)) {
		while (x_m<x_pp) {
			x_m++;
			yr-=.2;
			glutPostRedisplay();
		}
		if (x_m==0 && x_pp==0) {
			x_m++;
			yr-=.2;
			glutPostRedisplay();
		}
	}
	if (y_m>y_pp) {
		while (y_m>y_pp) {
			y_m--;
			xr-=.2;
			glutPostRedisplay();
		}
	}
	if (y_m<y_pp) {
		while (y_m<y_pp) {
			y_m++;
			xr+=.2;
			glutPostRedisplay();
		}
	}
	x_pp=x_temp;
	y_pp=y_temp;
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

	importRoom("realmap.dk3");        // Load Map
	glutInitWindowSize(800,600);
	glutInitWindowPosition(1,1);
	glutCreateWindow("3-Space Emulator");
	glutSetCursor(GLUT_CURSOR_NONE);
	init();
	//glutFullScreen();
	glutPassiveMotionFunc(mouse);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}