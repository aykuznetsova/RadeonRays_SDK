cmake_minimum_required(VERSION 3.8)

project(Triangle CXX)

set(SOURCES main.cpp
    $<TARGET_OBJECTS:TutorialTools>)
    
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIR} )
MESSAGE("${OPENGL_INCLUDE_DIR}")
MESSAGE("${GLUT_INCLUDE_DIR}")

add_executable(Triangle ${SOURCES})
target_link_libraries(Triangle PRIVATE GTest RadeonRays Calc ${OPENGL_LIBRARY} ${GLUT_LIBRARY})
target_compile_features(Triangle PRIVATE cxx_std_11)
target_compile_definitions(Triangle PRIVATE USE_OPENCL=1)
target_include_directories(Triangle PRIVATE "${RadeonRaysSDK_SOURCE_DIR}")
