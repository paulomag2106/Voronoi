#include "functions.h"

#define MAX_VERTS 50

int main() {

  // create vertex array
  v2 vertices[MAX_VERTS];
  for(int i = 0; i < MAX_VERTS;i++) {
    vertices[i] = (v2){(rand() % 460) + 10, (rand() % 460) + 10};
  }

  // create sweepLine
  v2 sweepLine[2] = {{0, 0},
                     {480, 0}};

  // Initialize the library
  if(!glfwInit())
    return -1;

  // Create a windowed mode window and its OpenGL context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  GLFWwindow* window = glfwCreateWindow(480, 480, "Voronoi Diagram", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Clear color4
  glClearColor(0.2, 0.2, 0.2, 1);

  // Application loop while window is OpenGL
  while(!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {

    // update delta time
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    printf("%.2lf\n", 1.0/deltaTime);

    // Create Camera Matrix
    glfwGetFramebufferSize(window, &width, &height);
    sweepLine[1].x = width;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width/2, height/2, 0, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);

    // draw vertices
    glColor3f(1, 1, 1);
    glPointSize(4);
    glBegin(GL_POINTS);
    for(int i = 0; i < MAX_VERTS;i++) {
      glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();

    // draw sweepLine
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);

    glVertex2f(sweepLine[0].x, sweepLine[0].y);
    glVertex2f(sweepLine[1].x, sweepLine[1].y);

    glEnd();

    // draw beach line between sweep line and vertices
    for(int i = 0; i < MAX_VERTS;i++) {
      drawBeachLine(sweepLine, vertices[i]);
    }

    sweepLine[0].y = sweepLine[0].y >= 480 ? 0 : sweepLine[0].y + 1;
    sweepLine[1].y = sweepLine[0].y;

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();

  }

  glfwTerminate();
  return 0;
}
