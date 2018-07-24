project (First CXX)

set(SOURCES main.cpp)

# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# find_package(GLEW REQUIRED)

add_executable(First ${SOURCES})
# target_compile_features(First PRIVATE cxx_std_11)
target_link_libraries(First PRIVATE RadeonRays)
# if (APPLE OR UNIX)
# target_link_libraries(First PRIVATE OpenGL::GL GLUT::GLUT GLEW::GLEW)
# elseif (WIN32)
# target_include_directories(First
# PRIVATE ${GLUT_INCLUDES}
# PRIVATE ${GLEW_INCLUDES}
# )
# target_link_libraries(First PRIVATE OpenGL::GL ${GLUT_LIBS} ${GLEW_LIBS})
# endif (APPLE OR UNIX)
