#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

static GLFWwindow* window;

#include <glm/glm.hpp>
using namespace glm;

int main(void)
{
  //------------------------------------------
  // Initialize GLFW and GL context
  //------------------------------------------

  if(glfwInit() != GLFW_TRUE)
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
    return -1;
  }

  // set window parameters
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // fixed-size window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(500, 500, "Playground", NULL, NULL);
  if( window == NULL )
  {
    fprintf(stderr,
            "Failed to open GLFW window.\n" );
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

  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  //------------------------------------------
  // GL operations start
  //------------------------------------------

  glClearColor(0.5f, 0.0f, 0.8f, 0.0f);

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

  const char *vertexShaderPath = "../SimpleVertexShader.glsl";
  const char *fragmentShaderPath = "../SimpleFragmentShader.glsl";

  // create shaders
  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // read vertex shader source
  std::fstream vertexShaderHandle(vertexShaderPath);
  std::string  vertexShaderSource;
  if(vertexShaderHandle.is_open())
  {
    vertexShaderSource.append(std::istreambuf_iterator<char>(vertexShaderHandle),
                              std::istreambuf_iterator<char>() );
    vertexShaderHandle.close();
  }
  else
  {
    fprintf(stderr,"ERROR: Faild to read vertex shader: %s\n", vertexShaderPath);
    exit(EXIT_FAILURE);
  }

  // read vertex shader source
  std::fstream fragmentShaderHandle(fragmentShaderPath);
  std::string  fragmentShaderSource;
  if(fragmentShaderHandle.is_open())
  {
    fragmentShaderSource.append(std::istreambuf_iterator<char>(fragmentShaderHandle),
                                std::istreambuf_iterator<char>() );
    fragmentShaderHandle.close();
  }
  else
  {
    fprintf(stderr,"ERROR: Faild to read fragment shader: %s\n", fragmentShaderPath);
    exit(EXIT_FAILURE);
  }

  GLint status = GL_FALSE;

  const char *vertexShaderPointer = vertexShaderSource.c_str();
  const char *fragmentShaderPointer = fragmentShaderSource.c_str();

  glShaderSource(vertexShaderID, 1, &vertexShaderPointer, nullptr);
  glCompileShader(vertexShaderID);

  // Check vertex shader
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
  if(status != GL_TRUE)
  {
    GLint infoLogLength = 0;

    fprintf(stderr, "ERROR: (in) Compiling vertex shader\n");

    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> compileLogInfo(infoLogLength+1);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &compileLogInfo[0]);

    printf("%s\n", &compileLogInfo[0]);
  }

  glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, nullptr);
  glCompileShader(fragmentShaderID);

  // Check fragment shader
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS,  &status);
  if (status != GL_TRUE) {
    GLint infoLogLength = 0;

    fprintf(stderr, "ERROR: (in) Compiling fragment shader\n");

    std::string compileLogInfo;
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &compileLogInfo[0]);

    fprintf(stdout, "%s\n", &compileLogInfo[0]);
  }

  // Link program
  programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID); // link to the current context

  // Check program
  glGetProgramiv(programID, GL_COMPILE_STATUS,  &status);
  if (status != GL_TRUE) {
    GLint infoLogLength = 0;

    fprintf(stderr, "ERROR: (in) Linking program\n");

    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::string linkLogInfo;
    glGetProgramInfoLog(programID, infoLogLength, NULL, &linkLogInfo[0]);

    fprintf(stdout, "%s\n", &linkLogInfo[0]);
  }

  // cleaning
  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  //------------------------------------------
  //  DATA
  //------------------------------------------

  static const GLfloat cubeBufferData[] = {

    -0.5f, -0.5f, 0.0f, 1.0, 1.0, 1.0, 0.0, 1.0, // triangle 1 : begin
    -0.5f, +0.5f, 0.0f, 1.0, 1.0, 1.0, 0.0, 1.0, //
    +0.5f, +0.5f, 0.0f, 1.0, 1.0, 0.0, 1.0, 1.0, // triangle 1 : end

    +0.5f, +0.5f, 0.0f, 1.0, 1.0, 1.0, 0.0, 1.0, // triangle 2 : begin
    +0.5f, -0.5f, 0.0f, 1.0, 1.0, 1.0, 0.2, 1.0, //
    -0.5f, -0.5f, 0.0f, 1.0, 1.0, 0.0, 1.0, 1.0, // triangle 2 : end

  };

  //------------------------------------------
  //  Create data buffers
  //------------------------------------------

  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeBufferData), cubeBufferData, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //------------------------------------------
  //  set offset
  //------------------------------------------

  auto offsetLoc = glGetUniformLocation(programID, "offset");
  auto timeLoc = glGetUniformLocation(programID, "time");

  //------------------------------------------
  //  set rendering flags
  //------------------------------------------

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  auto last_time = glfwGetTime();

  //------------------------------------------
  //  start rendering
  //------------------------------------------
  do {
    float x_offset, y_offset, z_offset = 0.0;

    auto time = glfwGetTime();
    x_offset = cos(glfwGetTime() * 1) * 0.5f;
    y_offset = sin(glfwGetTime() * 1) * 0.5f;
    z_offset = sin(glfwGetTime() * 1) * 0.5f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    glUniform3f(offsetLoc, x_offset, y_offset, 0.0);
    glUniform1f(timeLoc, glfwGetTime() - last_time / 1000);
    last_time = glfwGetTime();

    //rebind the vertex array to the context
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

    glEnableVertexAttribArray(0); // for position attr
    glEnableVertexAttribArray(1); // for color attr

    // tell opengl how to interpret the data from the bound buffer
    glVertexAttribPointer(0,                    // index
                          4,                    // size
                          GL_FLOAT,             // type
                          GL_FALSE,             // normalized
                          8 * sizeof(GL_FLOAT), // stride
                          0);                   // offset

    // tell opengl how to interpret the data from the bound buffer
    glVertexAttribPointer(1,                                // index
                          4,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized
                          8 * sizeof(GL_FLOAT),             // stride
                          (void *) (4 * sizeof(GL_FLOAT))); // offset

    glDrawArrays(GL_TRIANGLES, 0, 6 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  //------------------------------------------
  //  Clean up
  //------------------------------------------

  glDeleteBuffers(1, &vertexBufferID);
  glDeleteVertexArrays(1, &vertextArrayID);

  glDeleteProgram(programID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

