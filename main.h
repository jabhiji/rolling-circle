#ifndef MAIN_H
#define MAIN_H

// OpenGL specific headers

#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>       // for using gluLookAt( ... )

// include files

#include <iostream>
#include <cmath>

// function prototypes

extern void drawCircle(GLFWwindow *window, bool clearWindow,
                       float x_min, float x_max,
                       float y_min, float y_max,
                       float *vertices, int NUM_VERTICES,
                       float move_x, float move_y, float theta, bool drawPoints);

void createVertexArray(const int N, const float R, float* vertices, bool white);

#endif
