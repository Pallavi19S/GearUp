#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "flag.h"

int r, g, b;
//Game Speed
int FPS = 20;
//Game Track
int start = 0;
int gv = 0;
int level = 0;
//Track Score
int score = 0;
//Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;
//For Card Left / RIGHT
int lrIndex = 0;
//Car Coming
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;
//For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

GLfloat rx = 0, gx = 0, bx;

char s[30];
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void tree(int x, int y) {
    int newx = x;
    int newy = y;
    //Tree Left
            //Bottom
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11, newy + 55);
    glVertex2f(newx + 12, newy + 55 - 10);
    glVertex2f(newx + 10, newy + 55 - 10);
    glEnd();
    //Up
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11, newy + 55 + 3);
    glVertex2f(newx + 12 + 3, newy + 55 - 3);
    glVertex2f(newx + 10 - 3, newy + 55 - 3);
    glEnd();
}

void startGame() {
    //Road
    glColor3f(0.456, 0.456, 0.456);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();
    //Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(23, 100);
    glVertex2f(23, 0);
    glEnd();
    //Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(77, 0);
    glVertex2f(77, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();
    //Road Middel Border
      //TOP
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivTop + 80);
    glVertex2f(48, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 80);
    glEnd();
    roadDivTop--;
    if (roadDivTop < -100) {
        roadDivTop = 20;
        score++;
    }
    //Midle
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();
    roadDivMdl--;
    if (roadDivMdl < -60) {
        roadDivMdl = 60;
        score++;
    }
    //Bottom
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm + 0);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 0);
    glEnd();
    roadDivBtm--;
    if (roadDivBtm < -20) {
        roadDivBtm = 100;
        score++;
    }
    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(80, 88);
    glVertex2f(100, 88);
    glVertex2f(100, 99);
    glVertex2f(80, 99);
    glEnd();
    //Print Score
    char buffer[50];
    sprintf_s(buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95, (void*)font1, buffer);
    //Speed Print
    char buffer1[50];
    sprintf_s(buffer1, "SPEED:%dKm/h", FPS);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 4, (void*)font1, buffer1);
    //level Print
    if (score % 10 == 0) {
        int last = score / 10;
        if (last != level) {
            level = score / 10;
            FPS = FPS + 1;
        }
    }
    char level_buffer[50];
    sprintf_s(level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 6, (void*)font3, level_buffer);
    //Increse Speed With level
    //MAIN car
        //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26.7 - 1.35, 8.4);
    glVertex2f(lrIndex + 26.7 - 1.35, 10.4);
    glVertex2f(lrIndex + 29.3 + 1.35, 10.4);
    glVertex2f(lrIndex + 29.3 + 1.35, 8.4);
    glEnd();
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26.7 - 1.5, 4.6);
    glVertex2f(lrIndex + 26.7 - 1.5, 6.6);
    glVertex2f(lrIndex + 29.3 + 1.5, 6.6);
    glVertex2f(lrIndex + 29.3 + 1.5, 4.6);
    glEnd();
    //Car Body
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26, 4);
    glVertex2f(lrIndex + 26, 11);
    if (r == 1)
        glColor3f(1, 0, 0);
    else if (g == 1)
        glColor3f(0, 1, 0);
    else if (b == 1)
        glColor3f(0, 0, 1);
    else
        glColor3f(0.969, 0.745, 0.969);
    glVertex2f(lrIndex + 27.5, 13);
    glVertex2f(lrIndex + 28.5, 13);
    glVertex2f(lrIndex + 30, 11);
    glVertex2f(lrIndex + 30, 4);
    /*glVertex2f(lrIndex + 21, 2);
    glVertex2f(lrIndex + 23,5);
    glVertex2f(lrIndex + 31, 2);
    glVertex2f(lrIndex + 33, 5);*/
   
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 27.2, 13);
    glVertex2f(lrIndex + 28.6, 13);
    glVertex2f(lrIndex + 28.6, 13.5);
    glVertex2f(lrIndex + 27.2, 13.5);
    glEnd();


    /*connector
    glPushMatrix();
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 27, 4);
    glVertex2f(lrIndex + 27.5, 4);
    glVertex2f(lrIndex + 27.5, 3);
    glVertex2f(lrIndex + 27, 3);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 28.5, 4);
    glVertex2f(lrIndex + 29, 4);
    glVertex2f(lrIndex + 29, 3);
    glVertex2f(lrIndex + 28.5, 3);
    glEnd();
    //air shield
    //glPopMatrix();
    //glColor3f(0.022, 0.0235, 0.022);
    //glBegin(GL_POLYGON);
    //glVertex2f(lrIndex + 25.5, 3.7);
    //glVertex2f(lrIndex + 30.5, 3.7);
    //glVertex2f(lrIndex + 31.4, 2.3);
    //glVertex2f(lrIndex + 24.6, 2.3);
    //glEnd();*/

    //Opposite car 1
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 1, car1 + 100 - 4.5);
    glVertex2f(lrIndex1 + 26 - 1, car1 + 100 - 6.7);
    glVertex2f(lrIndex1 + 30 + 1, car1 + 100 - 6.7);
    glVertex2f(lrIndex1 + 30 + 1, car1 + 100 - 4.5);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 1, car1 + 100.2);
    glVertex2f(lrIndex1 + 26 - 1, car1 + 100 - 2.7);
    glVertex2f(lrIndex1 + 30 + 1, car1 + 100 - 2.7);
    glVertex2f(lrIndex1 + 30 + 1, car1 + 100.2);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26, car1 + 100);
    glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
    glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 30, car1 + 100);
    glEnd();
    //body
    glColor3f(0.439, 0.035, 0.035);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lrIndex1 + 26, car1 + 100);
    glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
    glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 30, car1 + 100);
    glEnd();
    //star and pentagon
    glColor3f(0.086, 0.086, 0.671);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 27, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 26.5, car1 + 100 - 5);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 29.5, car1 + 100 - 5);
    glVertex2f(lrIndex1 + 29, car1 + 100 - 2);
    glEnd();
    glColor3f(0.634, 0.634, 0.634);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lrIndex1 + 27, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 26.5, car1 + 100 - 5);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 29.5, car1 + 100 - 5);
    glVertex2f(lrIndex1 + 29, car1 + 100 - 2);
    glEnd();
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 4 + 0.46);
    glVertex2f(lrIndex1 + 27, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 27 + 0.3, car1 + 100 - 4 - 0.36);
    glVertex2f(lrIndex1 + 26.5, car1 + 100 - 5);
    glVertex2f(lrIndex1 + 27 + 0.5, car1 + 100 - 5.2);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 28 + 0.29, car1 + 100 - 5.2);
    glVertex2f(lrIndex1 + 29.5, car1 + 100 - 5);
    glVertex2f(lrIndex1 + 28 + 0.49, car1 + 100 - 4 - 0.36);
    glVertex2f(lrIndex1 + 29, car1 + 100 - 2);
    glEnd();
    car1--;
    if (car1 < -100) {
        car1 = 0;
        lrIndex1 = lrIndex;
    }
    //KIll check car1
    if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10)) {
        start = 0;
        gv = 1;
    }
    //Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26.1 - 1.5, car2 + 98.3 - 4);
    glVertex2f(lrIndex2 + 26.1 - 1.5, car2 + 98.3 - 6.5);
    glVertex2f(lrIndex2 + 30 + 1.5, car2 + 98.3 - 6.5);
    glVertex2f(lrIndex2 + 30 + 1.5, car2 + 98.3 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 1.75, car2 + 99.35 + 2);
    glVertex2f(lrIndex2 + 26 - 1.75, car2 + 99.35 - 1);
    glVertex2f(lrIndex2 + 30 + 1.75, car2 + 99.35 - 1);
    glVertex2f(lrIndex2 + 30 + 1.75, car2 + 99.35 + 2);
    glEnd();
    glColor3f(0.656, 0.656, 0.656);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 25.5, car2 + 103);
    glVertex2f(lrIndex2 + 25.5, car2 + 100 - 8);
    glVertex2f(lrIndex2 + 30.5, car2 + 100 - 8);
    glVertex2f(lrIndex2 + 30.5, car2 + 103);
    glEnd();
    glColor3f(0.256, 0.256, 0.256);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lrIndex2 + 25.5, car2 + 103);
    glVertex2f(lrIndex2 + 25.5, car2 + 100 - 8);
    glVertex2f(lrIndex2 + 30.5, car2 + 100 - 8);
    glVertex2f(lrIndex2 + 30.5, car2 + 103);
    glEnd();
    glColor3f(0.456, 0.456, 0.456);
    glBegin(GL_LINES);
    glVertex2f(lrIndex2 + 25.5 + 1.5, car2 + 103 - 2);
    glVertex2f(lrIndex2 + 25.5 + 1.5, car2 + 100 - 6.5);
    glVertex2f(lrIndex2 + 25.5 + 2.5, car2 + 103 - 2);
    glVertex2f(lrIndex2 + 25.5 + 2.5, car2 + 100 - 6.5);
    glVertex2f(lrIndex2 + 25.5 + 3.5, car2 + 103 - 2);
    glVertex2f(lrIndex2 + 25.5 + 3.5, car2 + 100 - 6.5);
    glEnd();

    glColor3f(0.522, 0.275, 0.153);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26.1, car2 + 92);
    glVertex2f(lrIndex2 + 26.1, car2 + 92 - 3);
    glVertex2f(lrIndex2 + 29.7, car2 + 92 - 3);
    glVertex2f(lrIndex2 + 29.7, car2 + 92);
    glEnd();
    glColor3f(0.222, 0.175, 0.153);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lrIndex2 + 26.1, car2 + 92);
    glVertex2f(lrIndex2 + 26.1, car2 + 92 - 3);
    glVertex2f(lrIndex2 + 29.7, car2 + 92 - 3);
    glVertex2f(lrIndex2 + 29.7, car2 + 92);
    glEnd();

    car2--;
    if (car2 < -100) {
        car2 = 0;
        lrIndex2 = lrIndex;
    }
    //KIll check car2
    if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10)) {
        start = 0;
        gv = 1;
    }
    //Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 1, car3 + 100 - 4.5);
    glVertex2f(lrIndex3 + 26 - 1, car3 + 100 - 6.7);
    glVertex2f(lrIndex3 + 30 + 1, car3 + 100 - 6.7);
    glVertex2f(lrIndex3 + 30 + 1, car3 + 100 - 4.5);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 1, car3 + 100.1);
    glVertex2f(lrIndex3 + 26 - 1, car3 + 100 - 2.7);
    glVertex2f(lrIndex3 + 30 + 1, car3 + 100 - 2.7);
    glVertex2f(lrIndex3 + 30 + 1, car3 + 100.1);
    glEnd();
    //body 
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 30, car3 + 100);
    glEnd();
    glColor3f(0.561, 0.188, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 30, car3 + 100);
    glEnd();
    //pentagon star
    glColor3f(0.031, 0.349, 0.031);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 27, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 26.5, car3 + 100 - 5);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 29.5, car3 + 100 - 5);
    glVertex2f(lrIndex3 + 29, car3 + 100 - 2);
    glEnd();
    glColor3f(0.634, 0.634, 0.634);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lrIndex3 + 27, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 26.5, car3 + 100 - 5);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 29.5, car3 + 100 - 5);
    glVertex2f(lrIndex3 + 29, car3 + 100 - 2);
    glEnd();
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 4 + 0.46);
    glVertex2f(lrIndex3 + 27, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 27 + 0.3, car3 + 100 - 4 - 0.36);
    glVertex2f(lrIndex3 + 26.5, car3 + 100 - 5);
    glVertex2f(lrIndex3 + 27 + 0.5, car3 + 100 - 5.2);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 28 + 0.29, car3 + 100 - 5.2);
    glVertex2f(lrIndex3 + 29.5, car3 + 100 - 5);
    glVertex2f(lrIndex3 + 28 + 0.49, car3 + 100 - 4 - 0.36);
    glVertex2f(lrIndex3 + 29, car3 + 100 - 2);
    glEnd();
    car3--;
    if (car3 < -100) {
        car3 = 0;
        lrIndex3 = lrIndex;
    }
    //KIll check car3
    if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10)) {
        start = 0;
        gv = 1;
    }
}

void drawCar() {
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2i(5, 10);
    glVertex2i(10, 10);
    glVertex2i(10, 10);
    glVertex2i(15, 15);
    glVertex2i(15, 15);
    glVertex2i(20, 15);
    glVertex2i(20, 15);
    glVertex2i(25, 15);
    glVertex2i(25, 15);
    glVertex2i(30, 10);
    glVertex2i(30, 10);
    glVertex2i(35, 10);
    glVertex2i(35, 10);
    glVertex2i(35, 5);
    glVertex2i(35, 5);
    glVertex2i(33, 5);
    glVertex2i(27, 5);
    glVertex2i(13, 5);
    glVertex2i(7, 5);
    glVertex2i(5, 5);
    glVertex2i(5, 5);
    glVertex2i(5, 10);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2i(12.5, 10.5);
    glVertex2i(15, 14);
    glVertex2i(25, 14);
    glVertex2i(28.5, 10.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2i(20.5, 14);
    glVertex2i(21.5, 14);
    glVertex2i(21.5, 10.5);
    glVertex2i(20.5, 10.5);
    glEnd();
    glPushMatrix();
    glTranslatef(10, 5, 0);
    glutSolidSphere(3, 25, 25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 5, 0);

    glutSolidSphere(3, 25, 25);
    glPopMatrix();
    glPopMatrix();
}
void placeCar(GLint tx, GLint ty) {
    glPushMatrix();
    glTranslatef(tx, ty, 0);
    glScalef(0.4, 0.4, 1);
    drawCar();
    glPopMatrix();
}

void drawcarLane(int y) {
    glColor3f(0.976, 0.667, 1);
    placeCar(0, 10 + y * 20);
    placeCar(28, 10 + y * 20);
    placeCar(53, 10 + y * 20);
    placeCar(78, 10 + y * 20);
    placeCar(10, 30 + y * 20);
    placeCar(40, 30 + y * 20);
    placeCar(70, 30 + y * 20);
}

void drawFlag(GLfloat x) {
    glPushMatrix();
    glScalef(0.5, 0.5, 1);
    glTranslatef(18 + x, 100, 0);
    draw();
    Animate();
    glPopMatrix();
}
void fristDesign() {
    drawcarLane(0);
    drawcarLane(4);
    placeCar(5, 50);
    placeCar(81, 50);
    placeCar(10, 70);
    placeCar(75, 70);
    //Text Information in Frist Page
    if (gv == 1) {
        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(42.5, 63 + 10, (void*)font1, "GAME OVER");
        r = g = b = 0;
        drawFlag(0);
        drawFlag(75);
        glColor3f(1,1,1);
        char buffer2[50];
        sprintf_s(buffer2, "Your Score is : %d", score);
        renderBitmapString(41.7, 62 - 4 + 10, (void*)font1, buffer2);
    }
    glColor3f(0.024, 0.839, 0.82);
    renderBitmapString(45.5, 80, (void*)font1, "Gear UP");
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(50, 50 + 1.5 + 10, (void*)font2, "Help:");
    renderBitmapString(50, 50 + 1.49 + 10, (void*)font2, "____");
    glColor3f(0.200, 1.000, 0.900);
    renderBitmapString(35, 48 + 10, (void*)font2, "Press SPACE to START New Game");
    renderBitmapString(45, 48 - 3 + 10, (void*)font2, "Press ESC to Exit");
    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(32.5, 49 - 6 + 10, (void*)font3, "Press UP Arrow Button to increase Speed");
    renderBitmapString(32.5, 49 - 8 + 10, (void*)font3, "Press DOWN Arrow Button to decrease Speed");
    renderBitmapString(32.5, 49 - 10 + 10, (void*)font3, "Press RIGHT Arrow Button to turn Right");
    renderBitmapString(32.5, 49 - 12 + 10, (void*)font3, "Press LEFT Arrow Button to turn Left");
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (start == 1) {
        // glClearColor(0.627, 0.322, 0.176,1);
        glClearColor(0.000, 0.392, 0.000, 1);
        startGame();
    }
    else {
        glClearColor(0, 0, 0, 1);
        // PlaySound(TEXT("first.mp3"), NULL, SND_FILENAME);
        fristDesign();
    }
    glFlush();
    glutSwapBuffers();
}
void spe_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN:
        if (FPS > (50 + (level * 2)))
            FPS = FPS - 2;
        break;
    case GLUT_KEY_UP:
        FPS = FPS + 2;
        break;
    case GLUT_KEY_LEFT:
        if (lrIndex >= 0) {
            lrIndex = lrIndex - (FPS / 10);
            if (lrIndex < 0) {
                lrIndex = -1;
            }
        }
        break;
    case GLUT_KEY_RIGHT:
        if (lrIndex <= 44) {
            lrIndex = lrIndex + (FPS / 10);
            if (lrIndex > 44) {
                lrIndex = 45;
            }
        }
        break;
    default:
        break;
    }
}
void processKeys(unsigned char key, int x, int y) {
    switch (key)
    {
    case ' ':
        if (start == 0) {
            start = 1;
            gv = 0;
            FPS = 50;
            roadDivTopMost = 0;
            roadDivTop = 0;
            roadDivMdl = 0;
            roadDivBtm = 0;
            lrIndex = 0;
            car1 = 0;
            lrIndex1 = 0;
            car2 = +35;
            lrIndex2 = 0;
            car3 = +70;
            lrIndex3 = 0;
            score = 0;
            level = 0;
        }
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

void colorMenu(int id) {
    if (id == 1) {
        r = 1;
        g = 0; b = 0;
    }
    else if (id == 2) {
        g = 1;
        r = 0; b = 0;
    }
    else if (id == 3)
    {
        b = 1;
        r = 0; g = 0;
    }

}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("gearUP");
    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);
    glutCreateMenu(colorMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    gluOrtho2D(0, 100, 0, 100);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}