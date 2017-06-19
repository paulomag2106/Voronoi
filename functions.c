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
  // printf("%f\n", result);
  return result;
}

float dotProduct2D(v2 a, v2 b) {
  return a.x * b.x + a.y * b.y;
}

// simplified 2d cross product
float crossProduct2D(v2 a, v2 b) {
  return fabsf(a.x * b.y - a.y * b.x);
}

void makeVertex2D(vertArray *vertices, GLFWwindow* window) {

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if(state == GLFW_PRESS && !clicked) {
    clicked = !clicked;
    vertices->vertCount++;
    vertices->verts = vertices->verts == NULL ? malloc(sizeof(v2)) : realloc(vertices->verts, sizeof(v2)*(vertices->vertCount));
    vertices->verts[vertices->vertCount-1] = (v2){xpos, ypos};
    // printf("vertex[%d](%lf, %lf)\n", vertices->vertCount, xpos, ypos);
  }
  else if(state == GLFW_RELEASE && clicked) {
    clicked = !clicked;
  }
}

void scrollSweep(float *sweepLine, GLFWwindow* window) {
  glfwSetScrollCallback(window, scroll_callback);
  *sweepLine = yScroll;
}

void scrollTop(GLFWwindow *window) {
  int state = glfwGetKey(window, GLFW_KEY_A);
  if(state == GLFW_PRESS && !a_pressed) {
    a_pressed = true;
    scroll_top = !scroll_bot;
  } else if(state == GLFW_RELEASE && a_pressed) {
    a_pressed = false;
  }
}

void scrollBot(GLFWwindow *window) {
  int state = glfwGetKey(window, GLFW_KEY_D);
  if(state == GLFW_PRESS && !d_pressed) {
    d_pressed = true;
    scroll_bot = !scroll_top;
  } else if(state == GLFW_RELEASE && d_pressed) {
    d_pressed = false;
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  yScroll += yoffset;
}

void pauseAndStart(float sweepLine, GLFWwindow* window) {

  int state = glfwGetKey(window, GLFW_KEY_SPACE);
  if(state == GLFW_PRESS && !space_pressed) {
    yScroll = sweepLine;
    space_pressed = true;
    paused = !paused;
  } else if(state == GLFW_RELEASE && space_pressed) {
    space_pressed = false;
  }
}

// From DeBerg's "Algorithms and Applications"
float beachLineFunc(float x, v2 site, float sweepLine) {
  return ((x*x) - (2*(site.x)*x) + (site.x*site.x) + (site.y*site.y) - (sweepLine*sweepLine)) /
                     (2.f*(site.y - sweepLine));
}

v2 beachLineIntersection(v2 siteA, v2 siteB, float sweepLine) {
  v2 *beachLineA = NULL;
  int pointCountA = 0;
  for(int i = 0; i < width; i+= 5) {
    beachLineA = beachLineA == NULL ? malloc(sizeof(v2)*(++pointCountA)) :
                                      realloc(beachLineA, sizeof(v2)*(++pointCountA));
    beachLineA[pointCountA-1] = (v2){i, beachLineFunc(i, siteA, sweepLine)};
  }

  v2 *beachLineB = NULL;
  int pointCountB = 0;
  for(int i = 0; i < width; i+= 5) {
    beachLineB = beachLineB == NULL ? malloc(sizeof(v2)*(++pointCountB)) :
                                      realloc(beachLineB, sizeof(v2)*(++pointCountB));
    beachLineB[pointCountB-1] = (v2){i, beachLineFunc(i, siteB, sweepLine)};
  }

  free(beachLineA);
  free(beachLineB);

  v2 result = {0, 0};
  return result;
}

void drawBeachLine(float sweepLine, vertArray vertices) {

  for(int j = 0; j < vertices.vertCount;j++) {
    if(fabs(sweepLine-vertices.verts[j].y) <= 0.1) {
      // printf("braca!\n");
      glColor3f(0, 1, 0);
      glBegin(GL_LINES);
      glVertex2f(vertices.verts[j].x, 0);
      glVertex2f(vertices.verts[j].x, vertices.verts[j].y);
      glEnd();
    } else if(sweepLine > vertices.verts[j].y) {

      // draw arch parabola of beach line
      glColor3f(0, 1, 0);
      glBegin(GL_LINE_STRIP);
      for(int i = 0; i < width;i+=1) {
        float x = i;
        // From DeBerg's "Algorithms and Applications"
        float y = beachLineFunc(x, vertices.verts[j], sweepLine);
        if(getDist((v2){x, y}, vertices.verts[j]) > getDist((v2){x, y}, vertices.verts[(j+1)% vertices.vertCount]))
          y = beachLineFunc(x, vertices.verts[(j+1)%vertices.vertCount], sweepLine);
        glVertex2f(x, y);
      }
      glEnd();
    }
  }
}
