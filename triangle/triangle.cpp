#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

static GLFWwindow *window;

int main()
{
  //------------------------------------------
  // Initialize GLFW and GL context
  //------------------------------------------

  if (glfwInit() != GLFW_TRUE) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  // set window parameters
  glfwWindowHint(GLFW_SAMPLES, 4);          //??
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //??
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Playground", nullptr, nullptr);
  if (window == nullptr) {
    fprintf(stderr, "Failed to create GLFW window.\n");
    getchar();
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  // Ensure we can capture the escape key being pressed
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //------------------------------------------
  // Initialize GLEW
  //------------------------------------------

  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // device information
  fprintf(stdout, "Renderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stdout, "Vendor:   %s\n", glGetString(GL_VENDOR));
  fprintf(stdout, "Version:  %s\n", glGetString(GL_VERSION));

  //------------------------------------------
  // GL operations start
  //------------------------------------------

  // set background color
  glClearColor(0.0f, 0.5f, 0.4f, 0.0f);

  GLuint vertextArrayID;
  GLuint vertexShaderID;
  GLuint fragmentShaderID;
  GLuint programID;

  // gnerate and bind vertex array
  glGenVertexArrays(1, &vertextArrayID);
  glBindVertexArray(vertextArrayID);

  //------------------------------------------
  // Load shaders and create GLSL program
  //------------------------------------------

  const char *vertexShaderPath   = "../SimpleVertexShader.vertexshader";
  const char *fragmentShaderPath = "../SimpleFragmentShader.fragmentshader";

  // create shaders
  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // read vertex shader source
  std::fstream vertexShaderHandle(vertexShaderPath);
  std::string vertexShaderSource;
  if (vertexShaderHandle.is_open()) {
    vertexShaderSource.append(std::istreambuf_iterator<char>(vertexShaderHandle),
                              std::istreambuf_iterator<char>());
    vertexShaderHandle.close();
  } else {
    fprintf(stderr, "ERROR: Faild to read vertex shader: %s\n", vertexShaderPath);
    exit(EXIT_FAILURE);
  }

  // read vertex shader source
  std::fstream fragmentShaderHandle(fragmentShaderPath);
  std::string fragmentShaderSource;
  if (fragmentShaderHandle.is_open()) {
    fragmentShaderSource.append(std::istreambuf_iterator<char>(fragmentShaderHandle),
                                std::istreambuf_iterator<char>());
    fragmentShaderHandle.close();
  } else {
    fprintf(stderr, "ERROR: Faild to read fragment shader: %s\n", fragmentShaderPath);
    exit(EXIT_FAILURE);
  }

  GLint status = GL_FALSE;
  int infoLogLength = 0;

  char const *vertexShaderPointer = vertexShaderSource.c_str();
  char const *fragmentShaderPointer = fragmentShaderSource.c_str();

  glShaderSource(vertexShaderID, 1, &vertexShaderPointer, nullptr);
  glCompileShader(vertexShaderID);

  // Check vertex shader compilation
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    fprintf(stderr, "ERROR: (in) Compiling ver shader\n");

    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> compileLogInfo(infoLogLength + 1);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, &compileLogInfo[0]);

    printf("%s\n", &compileLogInfo[0]);
  }

  glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, nullptr);
  glCompileShader(fragmentShaderID);

  // Check fragment shader compilation
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    fprintf(stderr, "ERROR: (in) Compiling fragment shader\n");

    std::string compileLogInfo;
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr, &compileLogInfo[0]);

    fprintf(stdout, "%s\n", &compileLogInfo[0]);
  }

  // Link program to the current context
  programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  // Check program compilation
  glGetProgramiv(programID, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    fprintf(stderr, "ERROR: (in) Linking program\n");

    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::string linkLogInfo;
    glGetProgramInfoLog(programID, infoLogLength, nullptr, &linkLogInfo[0]);

    fprintf(stdout, "%s\n", &linkLogInfo[0]);
  }

  //------------------------------------------
  //  DATA
  //------------------------------------------

  int vertexCount = 9;
  static const GLfloat triangleBufferData[] = {
    -1.0f,
    -1.0f,
    0.0f, // left   vertex
    1.0f,
    -1.0f,
    0.0f, // right  vertex
    0.0f,
    1.0f,
    0.0f // middle vertex
  };

  //------------------------------------------
  //  Create data buffers
  //------------------------------------------

  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleBufferData), triangleBufferData, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glUseProgram(programID);

  //------------------------------------------
  //  start rendering
  //------------------------------------------
  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  //------------------------------------------
  //  Clean up
  //------------------------------------------

  glDisableVertexAttribArray(0);

  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  glDeleteBuffers(1, &vertexBufferID);
  glDeleteVertexArrays(1, &vertextArrayID);

  glDeleteProgram(programID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
