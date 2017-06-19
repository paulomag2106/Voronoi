#include "functions.h"

int main() {
  width = 960;
  height = 540;

  clicked = false;
  space_pressed = false;
  a_pressed = false;
  d_pressed = false;
  paused = true;
  scroll_top = false;
  scroll_bot = false;

  // Initialize the library
  if(!glfwInit())
    return -1;

  // Create a windowed mode window and its OpenGL context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  GLFWwindow* window = glfwCreateWindow(width, height, "Voronoi Diagram", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  // Set window aspect ratio
  glfwSetWindowAspectRatio(window, 16, 9);

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Clear color4
  glClearColor(0.2, 0.2, 0.2, 1);

  // create vertex array
  vertArray vertices;
  vertices.vertCount = 0;
  vertices.verts = NULL;

  // create sweepLine
  float sweepLine = 0;

  // Application loop while window is OpenGL
  while(!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    // printf("%d, %d\n", width, height);

    // update delta time
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    // printf("%.2lf\n", 1.0/deltaTime);

    // Create Camera Matrix
    glfwGetFramebufferSize(window, &width, &height);

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

    for(int i = 0; i < vertices.vertCount;i++) {
      glVertex2f(vertices.verts[i].x, vertices.verts[i].y);
    }

    glEnd();

    // draw sweepLine
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);

    glVertex2f(0, sweepLine);
    glVertex2f(width, sweepLine);

    glEnd();

    // draw beach line between sweep line and vertices
    drawBeachLine(sweepLine, vertices);

    if(yScroll < 0) yScroll = 0;

    if(!paused) {
      sweepLine = sweepLine >= height/2 ? 0 : sweepLine + 1;
    } else if (!scroll_top && !scroll_bot){
      scrollSweep(&sweepLine, window);
    }

    if(paused) {
      scrollTop(window);
      scrollBot(window);

      if(scroll_top) {
        sweepLine = fLerp(sweepLine, 0, 0.1);
      } else if(scroll_bot) {
        sweepLine = fLerp(sweepLine, height/2, 0.1);
      }

      if(fabs(sweepLine - 0) <= 0.1) {
        scroll_top = false;
      }
      if(fabs(sweepLine - height/2) <= 0.1){
        scroll_bot = false;
      }
    }

    yScroll = sweepLine;

    makeVertex2D(&vertices, window);
    pauseAndStart(sweepLine, window);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();

  }

  free(vertices.verts);

  glfwTerminate();
  return 0;
}
