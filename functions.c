#include "functions.h"

float fLerp(float a, float b, float t) {
  return t <= 0 ? a : t >= 1 ? b : (1-t) * a + t * b;
}

v2 v2Lerp(v2 a, v2 b, float t) {
  return t <= 0 ? a : t >= 1 ? b : (v2){(1-t) * a.x + t * b.x,
                                        (1-t) * a.y + t * b.y};
}

v3 v3Lerp(v3 a, v3 b, float t) {
  return t <= 0 ? a : t >= 1 ? b : (v3){(1-t) * a.x + t * b.x,
                                        (1-t) * a.y + t * b.y,
                                        (1-t) * a.z + t * b.z};
}

float getMin(float a, float b) {
  return a < b ? a : b;
}

float getMax(float a, float b) {
  return a > b ? a : b;
}

float getDist(v2 a, v2 b) {
  float result = sqrt(((a.x-b.x)*(a.x-b.x)) + ((a.y-b.y)*(a.y-b.y)));
  printf("%f\n", result);
  return result;
}

float dotProduct2D(v2 a, v2 b) {
  return a.x * b.x + a.y * b.y;
}

// simplified 2d cross product
float crossProduct2D(v2 a, v2 b) {
  return fabsf(a.x * b.y - a.y * b.x);
}

void makeVertex2D(queue_v2 *queue, GLFWwindow* window) {

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS) {
    printf("%lf, %lf\n", xpos, ypos);
    queue->next = malloc(sizeof(queue_v2));
    queue->next->value = (v2){xpos, ypos};
  }
}

void drawBeachLine(v2 *sweepLine, v2 vertex) {

  if(sweepLine[0].y == vertex.y) {

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(vertex.x, 0);
    glVertex2f(vertex.x, vertex.y);
    glEnd();
  } else if(sweepLine[0].y > vertex.y) {
    // draw arch parabola of beach line
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < width;i+=5) {
      float x = i;
      // From DeBerg's "Algorithms and Applications"
      float y = (1.f/(2.f*(vertex.y - sweepLine[0].y)))*((x*x) - (2*(vertex.x)*x) + (vertex.x*vertex.x) +
                 (vertex.y*vertex.y) - (sweepLine[0].y*sweepLine[0].y));
      glVertex2f(x, y);
    }
    glEnd();
  }
}
