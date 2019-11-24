#pragma once
#include <GLAUX.h>
#include <glut.h>
#include <math.h>
#include <time.h>
void w2init();
void displayFcn();
void reshapeFcn(GLint newWidth, GLint newHeight);
void lineSegment_Circle_Line();
void wireQuadSurfs();
void winReshapeFcn(GLint newWidth, GLint newHeight);
void teapot();

void TeapotInit();
void Teapot();

void key(unsigned char k, int x, int y);
void redraw();
void updateView(int width, int height);
void Draw_Scene(float place[]);
void idle();
void reshape(GLint width, GLint height);