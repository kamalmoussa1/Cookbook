cmake_minimum_required (VERSION 3.0)

project(cubegrid)

find_package(OpenGL REQUIRED)
find_package(GLEW	REQUIRED)
find_package(glfw3	REQUIRED)
find_package(glm	REQUIRED)


set(ASSIMP_INCLUDE "../assimp/include")
set(ASSIMP_LIB		 "../assimp/lib")


include_directories( ${glfw3_DIR}
	                   ${GLEW_INCLUDE_DIRS}
										 ${ASSIMP_INCLUDE}
										 )
link_directories(${ASSIMP_LIB})

set(ALL_LIBS
        ${OPENGL_LIBRARY}
				${GLEW_LIBRARIES}
				glfw
				assimp)

set(SOURCES model.cpp
	          model.h	)

add_executable(${PROJECT_NAME} ${SOURCES} "stb_image.h" "cubegrid.cpp")

target_link_libraries(${PROJECT_NAME}
	                    ${ALL_LIBS})
