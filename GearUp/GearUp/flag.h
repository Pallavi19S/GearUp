#pragma once
#include <GL/glut.h>
#include <GL/glu.h>
#include <Windows.h>
#include <math.h>

GLfloat xa = 2.5, ya = 3.5;
int yflag = 1, xflag = 1, aniflag = 1;
void Animate() {
	if (aniflag == 1) {
		if (ya > -6.5 && yflag == 1)
			ya = ya - 0.1;
		if (ya <= -6.5 && yflag == 1)
			yflag = 0;
		if (ya < 6.5 && yflag == 0)
			ya = ya + 0.1;
		if (ya >= 6.5 && yflag == 0)
			yflag = 1;

		if (xa > -4.5 && xflag == 1)
			xa = xa - 0.1;
		if (xa <= -4.5 && xflag == 1)
			xflag = 0;
		if (xa < 4.5 && xflag == 0)
			xa = xa + 0.1;
		if (xa >= 4.5 && xflag == 0)
			xflag = 1;
	}
	glutPostRedisplay();
}

void draw() {
	GLfloat x[4], y1[4], y2[4], y3[4];
	GLdouble xt[200], y1t[200], y2t[200], y3t[200], t;
	int i, c;
	x[0] = 45; x[1] = 50 + (xa); x[2] = 55 + (xa / 2); x[3] = 60 + (xa / 10);
	y1[0] = 60; y1[1] = 60 + ya; y1[2] = 60 - ya; y1[3] = 60 + (ya / 2);
	y2[0] = 50; y2[1] = 50 + ya; y2[2] = 50 - ya; y2[3] = 50 + (ya / 2);


	for (i = 0, t = 0, c = 0; t < 1; i++, t = t + 0.02) {
		xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
		y1t[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
		y2t[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];

		c++;
	}
	glColor3f(0.929, 0.761, 0.827);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < c; i++) {
		glVertex2d(xt[i], y1t[i]);
		glVertex2d(xt[i], y2t[i]);
	}
	glEnd();
	glColor3f(0.522, 0.118, 0.365);
	glRecti(45, 35, 44, 60);
	glColor3f(0.654, 0.654, 0.654);
	/*glRecti(40, 35, 50, 32);
	glRecti(35, 32, 55, 29);*/
	glFlush();
}