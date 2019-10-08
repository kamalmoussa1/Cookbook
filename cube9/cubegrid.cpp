#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.h"

static GLFWwindow* window;

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

  Model model;

  std::vector<unsigned short> indices;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  const char *model_path = "../objects/cone.obj";

  bool result = model.load(model_path, indices, vertices, uvs, normals);
  std::cout << result << std::endl;

  //------------------------------------------
  //  DATA
  //------------------------------------------

  const int vertex_count = 6*2*3;

  static const GLfloat cubeBufferData[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,

    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
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

  static const GLfloat uvCoord[]    = {
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,


  };

  //------------------------------------------
  //  Create data buffers
  //------------------------------------------

  // vertx buffer
  GLuint veruvBufferID;
  glGenBuffers(1, &veruvBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, veruvBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeBufferData), cubeBufferData, GL_STATIC_DRAW);
  //  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

  // color buffer
  GLuint colorBufferID;
  glGenBuffers(1, &colorBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

  // tex buffer
  GLuint uvBufferID;
  glGenBuffers(1, &uvBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoord), uvCoord, GL_STATIC_DRAW);
  //  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

  //------------------------------------------
  // Load texture using stbi
  //------------------------------------------
  //  stbi_set_flip_vertically_on_load(true);

  int width;
  int height;
  int channel;

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  const char* texture_path = "../texture/awesomeface.png";

  unsigned char* data = stbi_load(texture_path, &width, &height, &channel, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D,               // target
                 0,                           // mipmap level
                 GL_RGB,                      // format
                 width,
                 height,
                 0,                           // always 0
                 GL_RGB,                      // source format
                 GL_UNSIGNED_BYTE,            // data type
                 data);
    glGenerateMipmap(GL_TEXTURE_2D); // generate mipmaps for our texture
  }
  else
    fprintf(stderr, "Faild to load texture: %s.\n", texture_path);

  stbi_image_free(data);

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
                            glm::vec3( 0.0f, 0.0f,  5.0f),  // camera center
                            glm::vec3( 0.0f, 0.0f,  0.0f),    // camera target: look at origin
                            glm::vec3( 0.0f, 1.0f,  0.0f)     // upvector
                            );



  GLint MVP_ID = glGetUniformLocation(programID, "MVP");


  //------------------------------------------
  //  start rendering
  //------------------------------------------
  int cube_count = 9;
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), // center

    glm::vec3( 2.0f,  0.0,   0.0f), // right

    glm::vec3( 0.0f,  2.0f,  0.0f), // up

    glm::vec3( -2.0f,  0.0f,  0.0f), // left
    glm::vec3( -2.0f,  0.0f,  0.0f), // lft

    glm::vec3( 0.0f,  -2.0f,  0.0f), // down
    glm::vec3( 0.0f,  -2.0f,  0.0f), // down

    glm::vec3( 2.0f,  0.0f,  0.0f), // right
    glm::vec3( 2.0f,  0.0f,  0.0f), // right

  };


  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // Dark blue background

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);


  glUseProgram(programID);
  glUniform1i(glGetUniformLocation(programID, "texSampler1"), 0); // set texture unit
  glUniform1i(glGetUniformLocation(programID, "texSampler2"), 1);

  do
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    glm::mat4 modelMatrix = glm::mat4(1.0f); // identiy

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, veruvBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE /*normalized?*/, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // draw 9 cubes
    //    for(int i = 0; i < cube_count; ++i)
    //    {
    //      modelMatrix = glm::translate(modelMatrix, cubePositions[i]);

    glm::mat4 MVPMatrix   = projMatrix * viewMatrix * modelMatrix;

    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVPMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

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

  glDeleteBuffers(1, &veruvBufferID);
  glDeleteBuffers(1, &colorBufferID);

  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &vertextArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

