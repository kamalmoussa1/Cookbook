#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static GLFWwindow* window;

#include <glm/glm.hpp>
using namespace glm;

int main( void )
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
  glfwWindowHint(GLFW_SAMPLES, 4); //??
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //??
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
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

  glewExperimental = true; // Needed for core profile
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
  GLuint vertextArrayID;
  GLuint vertexShaderID;
  GLuint fragmentShaderID;
  GLuint programID;


  //------------------------------------------
  // Load shaders and create GLSL program
  //------------------------------------------

    const char* vertexShaderPath   = "../SimpleVertexShader.glsl";
    const char* fragmentShaderPath = "../SimpleFragmentShader.glsl";

    // create shaders
    vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
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

    GLint status      = GL_FALSE;
    int infoLogLength = 0;

    char const * vertexShaderPointer   = vertexShaderSource.c_str();
    char const * fragmentShaderPointer = fragmentShaderSource.c_str();

    glShaderSource(vertexShaderID, 1, &vertexShaderPointer, NULL);
    glCompileShader(vertexShaderID);

    // Check vertex shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
      fprintf(stderr, "ERROR: (in) Compiling ver shader\n");

      glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
      std::string compileLogInfo;
      glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &compileLogInfo[0]);

      printf("%s\n", &compileLogInfo[0]);
    }

    glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, NULL);
    glCompileShader(fragmentShaderID);

    // Check fragment shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS,  &status);
    if(status != GL_TRUE)
    {
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
    if(status != GL_TRUE)
    {
      fprintf(stderr, "ERROR: (in) Linking program\n");

      glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
      std::string linkLogInfo;
      glGetProgramInfoLog(programID, infoLogLength, NULL, &linkLogInfo[0]);

      fprintf(stdout, "%s\n", &linkLogInfo[0]);
    }


  //------------------------------------------
  //  DATA
  //------------------------------------------
  const int vertex_count = 6*2*3;

  static const GLfloat cubeBufferData[] = {
    -0.5f, -0.5f, -0.5f, // triangle 1 : begin
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f, // triangle 1 : end
    0.5f,  0.5f, -0.5f, // triangle 2 : begin
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f, // triangle 2 : end
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    0.5f, -0.5f,  0.5f
  };


  static const GLfloat colorBufferData[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
  };

  //------------------------------------------
  // MATRICIES:: MODEL->VIEW->PROJECTION
  //------------------------------------------

  glm::mat4 projMatrix  = glm::perspective(
                            glm::radians(45.0f),    // FoV
                            4.0f/3.0f,              // aspect ratio
                            0.1f,                   // near clipping
                            100.0f                  // far clipping
                            );


  glm::mat4 viewMatrix  = glm::lookAt(
                            glm::vec3(-3.0f, 0.0f, -2.0f),  // camera center
                            glm::vec3( 0.0f, 0.0f,  0.0f),    // camera target: look at origin
                            glm::vec3( 0.0f, 1.0f,  0.0f)     // upvector
                            );


  glm::mat4 modelMatrix = glm::mat4(1.0f); // identiy


  glm::mat4 MVPMatrix   = projMatrix * viewMatrix * modelMatrix;

  GLint MVP_ID = glGetUniformLocation(programID, "MVP");

  //------------------------------------------
  //  Create data buffers
  //------------------------------------------

  // vertx buffer
  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeBufferData), cubeBufferData, GL_STATIC_DRAW);

  // color buffer
  GLuint colorBufferID;
  glGenBuffers(1, &colorBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

  // gnerate and bind vertex array
  glGenVertexArrays(1, &vertextArrayID);
  glBindVertexArray(vertextArrayID);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE /*normalized?*/, 0, (void *) 0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

  glBindVertexArray(0);

  //------------------------------------------
  //  set rendering flags
  //------------------------------------------

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background

  // Enable depth test
  glEnable(GL_DEPTH_TEST);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // draw the visible sides only, please
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  //------------------------------------------
  //  start rendering
  //------------------------------------------
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    glBindVertexArray(vertextArrayID);

    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVPMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glBindVertexArray(0);
    glUseProgram(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  //------------------------------------------
  //  Clean up
  //------------------------------------------

  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  glDeleteBuffers(1, &vertexBufferID);
  glDeleteBuffers(1, &colorBufferID);

  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &vertextArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

