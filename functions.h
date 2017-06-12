#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <GLFW/glfw3.h>

double deltaTime, currentFrame, lastFrame;
int width, height;

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

typedef struct t_queue_v2{
  v2 value;
  struct t_queue_v2 *next;
}queue_v2;

// function prototypes
float fLerp(float a, float b, float t);
v2 v2Lerp(v2 a, v2 b, float t);
v3 v3Lerp(v3 a, v3 b, float t);
float getMin(float a, float b);
float getMax(float a, float b);
float getDist(v2 a, v2 b);
float dotProduct2D(v2 a, v2 b);
float crossProduct2D(v2 a, v2 b);
void makeVertex2D(queue_v2 *queue, GLFWwindow* window);
void drawBeachLine(v2 *sweepLine, v2 vertex);
