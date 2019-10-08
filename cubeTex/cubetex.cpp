#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"

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

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);   // Dark blue background

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

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
  // MATRICIES:: MODEL->VIEW->PROJECTION
  //------------------------------------------

  glm::mat4 projMatrix  = glm::perspective(
                            glm::radians(45.0f),    // FoV
                            4.0f/3.0f,              // aspect ratio
                            0.1f,                   // near clipping
                            100.0f                  // far clipping
                            );


  glm::mat4 viewMatrix  = glm::lookAt(
                            glm::vec3(-3.0f, 0.0f, -4.0f),  // camera center
                            glm::vec3( 0.0f, 0.0f,  0.0f),    // camera target: look at origin
                            glm::vec3( 0.0f, 1.0f,  0.0f)     // upvector
                            );


  glm::mat4 modelMatrix = glm::mat4(1.0f); // identiy


  glm::mat4 MVPMatrix   = projMatrix * viewMatrix * modelMatrix;

  GLint MVP_ID = glGetUniformLocation(programID, "MVP");

  //------------------------------------------
  //  Load texture
  //------------------------------------------

  // Load the texture
  GLuint Texture = loadBMP_custom("../uvtemplate.bmp");
//    GLuint Texture = loadDDS("../uvtemplate.DDS ");

  // Get a handle for "textureSampler" uniform
  GLint TextureID  = glGetUniformLocation(programID, "textureSampler");

  //------------------------------------------
  //  DATA
  //------------------------------------------
  const int vertex_count = 6*2*3;

  static const GLfloat cubeBufferData[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };

  // Two UV coordinatesfor each vertex. They were created with Blender.
  static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
  };


  //------------------------------------------
  //  Create data buffers
  //------------------------------------------

  // vertx buffer
  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeBufferData), cubeBufferData, GL_STATIC_DRAW);

  GLuint uvbuffer;
  glGenBuffers(1, &uvbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);


  do
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVPMatrix[0][0]);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE /*normalized?*/, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );


  //------------------------------------------
  //  Clean up
  //------------------------------------------

  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  glDeleteBuffers(1,  &vertexBufferID);
  glDeleteBuffers(1,  &uvbuffer);
  glDeleteTextures(1, &Texture);

  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &vertextArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

