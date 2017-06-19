#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <GLFW/glfw3.h>

double deltaTime, currentFrame, lastFrame,
       yScroll;
int width, height;
bool clicked, space_pressed, a_pressed, d_pressed,
     paused, scroll_top, scroll_bot;

typedef struct t_v2{
  float x, y;
}v2;

typedef struct t_v3{
  float x, y, z;
}v3;

typedef struct t_v4{
  float x, y, z, w;
}v4;

typedef struct t_color4 {
  float r, g, b, a;
}color4;

typedef struct t_vertArray {
  v2 *verts;
  int vertCount;
}vertArray;

// function prototypes
float fLerp(float a, float b, float t);
v2 v2Lerp(v2 a, v2 b, float t);
v3 v3Lerp(v3 a, v3 b, float t);
float getMin(float a, float b);
float getMax(float a, float b);
float getDist(v2 a, v2 b);
float dotProduct2D(v2 a, v2 b);
float crossProduct2D(v2 a, v2 b);
void makeVertex2D(vertArray *vertices, GLFWwindow *window);
void pauseAndStart(float sweepLine, GLFWwindow *window);
void scrollSweep(float *sweepLine, GLFWwindow *window);
void scrollTop(GLFWwindow *window);
void scrollBot(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float beachLineFunc(float x, v2 site, float sweepLine);
v2 beachLineIntersection(v2 siteA, v2 siteB, float sweepLine);
void drawBeachLine(float sweepLine, vertArray vertex);
