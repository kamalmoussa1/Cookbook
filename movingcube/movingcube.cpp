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

#define WINDOW_WIDTH   1024
#define WINDOW_HIEGHT  768
#define WINDOW_X       400
#define WINDOW_Y       200
#define WINDOW_CEN_X   WINDOW_WIDTH/2
#define WINDOW_CEN_Y   WINDOW_HIEGHT/2

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

glm::vec3 cameraPostion = glm::vec3(  0.0f, 0.0f,   8.0f);
glm::vec3 cameraFront   = glm::vec3(  0.0f, 0.0f,  -1.0f);
glm::vec3 cameraUp      = glm::vec3(  0.0f, 1.0f,   0.0f);

float FOV     = glm::radians(45.0f);

int main( void )
{
  //------------------------------------------
  // Initialize GLFW and GL context
  //------------------------------------------

  if (glfwInit() != GLFW_TRUE) {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
    return -1;
  }

  // set window parameters
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HIEGHT, "Moving Cube", NULL, NULL);
  if( window == NULL )
  {
    fprintf(stderr,
            "Failed to open GLFW window.\n" );
    getchar();
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetWindowPos(window, WINDOW_X, WINDOW_Y);

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // Ensure we can capture the escape key being pressed
  //  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  // Hide the mouse and enable unlimited mouvement
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background

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

  const char *vertexShaderPath   = "../SimpleVertexShader.glsl";
  const char *fragmentShaderPath = "../SimpleFragmentShader.glsl";

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

  GLint status        = GL_FALSE;
  int   infoLogLength = 0;

  char const *vertexShaderPointer   = vertexShaderSource.c_str();
  char const *fragmentShaderPointer = fragmentShaderSource.c_str();

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
  const int vertex_count = 6 * 2 * 3;

  // clang-format off
  const GLfloat cubeBufferData[] = {
    -0.5f, -0.5f, -0.5f,    -0.5f, -0.5f,  0.5f,    -0.5f,  0.5f,  0.5f, // triangle 1 
     0.5f,  0.5f, -0.5f,    -0.5f, -0.5f, -0.5f,    -0.5f,  0.5f, -0.5f, // triangle 2
     0.5f, -0.5f,  0.5f,    -0.5f, -0.5f, -0.5f,     0.5f, -0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f,     0.5f, -0.5f, -0.5f,    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,    -0.5f,  0.5f,  0.5f,    -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,    -0.5f, -0.5f,  0.5f,    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,    -0.5f, -0.5f,  0.5f,     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,     0.5f, -0.5f, -0.5f,     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,     0.5f,  0.5f,  0.5f,     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,     0.5f,  0.5f, -0.5f,    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,    -0.5f,  0.5f, -0.5f,    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,    -0.5f,  0.5f,  0.5f,     0.5f, -0.5f,  0.5f,
  };

  const GLfloat colorBufferData[] = { 
    0.583f,  0.771f,  0.014f,    0.609f,  0.115f,  0.436f,    0.327f,  0.483f,  0.844f, // triangle 1
    0.822f,  0.569f,  0.201f,    0.435f,  0.602f,  0.223f,    0.310f,  0.747f,  0.185f, // triangle 2 
    0.597f,  0.770f,  0.761f,    0.559f,  0.436f,  0.730f,    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,    0.559f,  0.861f,  0.639f,    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,    0.771f,  0.328f,  0.970f,    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,    0.971f,  0.572f,  0.833f,    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,    0.945f,  0.719f,  0.592f,    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,    0.167f,  0.620f,  0.077f,    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,    0.714f,  0.505f,  0.345f,    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,    0.302f,  0.455f,  0.848f,    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,    0.053f,  0.959f,  0.120f,    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,    0.820f,  0.883f,  0.371f,    0.982f,  0.099f,  0.879f
  };
  // clang-format on

  //------------------------------------------
  // MATRICIES:: MODEL->VIEW->PROJECTION
  //------------------------------------------

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

  //------------------------------------------
  //  start rendering
  //------------------------------------------

  // Initial horizontal angle : toward -Z
  float horizontalAngle = 0.0f; //180?

  // Initial vertical angle : none
  float verticalAngle = 0.0f;

  float speed      = 2.0f; // 3 units / second
  float mouseSpeed = 0.05f;

  float a_ratio = 4.0f / 3.0f;
  float n_clip  = 0.1f;
  float f_clip  = 100.0f;

  float cameraSpeed = 2.5f;

  float lastXpos = WINDOW_WIDTH / 2;
  float lastYpos = WINDOW_HIEGHT / 2;

  glm::vec3 cameraRight = glm::cross(cameraFront, cameraUp);

  bool first = true;
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float  deltaTime   = float(currentTime - lastTime);

    lastTime = currentTime;

    double xpos;
    double ypos;

    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, WINDOW_CEN_X, WINDOW_CEN_Y);

    horizontalAngle += mouseSpeed * (float(xpos) - lastXpos);
    verticalAngle += mouseSpeed * (lastYpos - float(ypos));

    if (verticalAngle > 89.0f)
      verticalAngle =  89.0f;
    if(verticalAngle < 0.0f)
      verticalAngle = 0.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(verticalAngle)) * cos(glm::radians(horizontalAngle));
    front.y = sin(glm::radians(verticalAngle));
    front.z = cos(glm::radians(verticalAngle)) * sin(glm::radians(horizontalAngle));

    cameraFront = glm::normalize(front);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // reset camera postion
    {
      cameraPostion = glm::vec3(  0.0f, 0.0f,  8.0f);
      cameraFront   = glm::vec3(  0.0f, 0.0f,  -1.0f);
      cameraUp      = glm::vec3(  0.0f, 1.0f,  0.0f);
      cameraRight   = glm::cross(cameraFront, cameraUp);
      FOV           = glm::radians(45.0f);
    }

    cameraRight = glm::cross(cameraFront, cameraUp);

    //---------------------------------------------------------------------------------------
    cameraSpeed = 3.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      cameraPostion += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      cameraPostion -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      cameraPostion -= cameraRight* cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      cameraPostion += cameraRight * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) // zoom out
      FOV -= glm::radians(1.0f);
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) // zoom in
      FOV += glm::radians(1.0f);

    //---------------------------------------------------------------------------------------

    glm::mat4 projMatrix    = glm::perspective(FOV, a_ratio, n_clip, f_clip);
    glm::mat4 viewMatrix    = glm::lookAt(cameraPostion, cameraPostion + cameraFront, cameraUp);
    glm::mat4 modelMatrix   = glm::mat4(1.0f);

    //---------------------------------------------------------------------------------------

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE /*normalized?*/, 0, (void *) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //---------------------------------------------------------------------------------------

    glm::mat4 MVPMatrix = projMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVPMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.0f, 0.0f, 0.0f));
    MVPMatrix   = projMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVPMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.0f, 0.0f, 0.0f));
    MVPMatrix   = projMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVPMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

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

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  //  if (key == GLFW_KEY_W && action == GLFW_PRESS)'
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  if(FOV >= 1.0f && FOV <= 45.0f)
    FOV -= yoffset/10;
  if(FOV <= 1.0f)
    FOV = 1.0f;
  if(FOV >= 45.0f)
    FOV = 45.0f;
}
