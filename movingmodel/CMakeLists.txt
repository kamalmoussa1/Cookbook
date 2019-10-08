cmake_minimum_required (VERSION 3.0)

project(movingmodel)

find_package(OpenGL REQUIRED)
find_package(GLEW	REQUIRED)
find_package(glfw3	REQUIRED)
find_package(glm	REQUIRED)

include_directories( ${glfw3_DIR}
	                   ${GLEW_INCLUDE_DIRS})

set(ALL_LIBS
        ${OPENGL_LIBRARY}
				${GLEW_LIBRARIES}
				glfw)

set(SOURCES objloader.hpp
	          objloader.cpp)

add_executable(${PROJECT_NAME} ${SOURCES}
"movingmodel.cpp")

target_link_libraries(${PROJECT_NAME}
	                    ${ALL_LIBS})
