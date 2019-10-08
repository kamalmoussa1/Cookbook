cmake_minimum_required (VERSION 3.0)

project(glPlayground)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(OpenGL REQUIRED)
find_package(GLEW	  REQUIRED)
find_package(glfw3	REQUIRED)
find_package(glm	  REQUIRED)

include_directories( ${glfw3_DIR}
	                   ${GLEW_INCLUDE_DIRS})

set(ALL_LIBS
        ${OPENGL_LIBRARY}
				${GLEW_LIBRARIES}
				glfw)

add_executable(${PROJECT_NAME} "triangle.cpp")

target_link_libraries(${PROJECT_NAME}
	                    ${ALL_LIBS})

