project (Triangle CXX)

set(SOURCES main.cpp
	    hello.cpp
    $<TARGET_OBJECTS:TutorialTools>)
    
message($<TARGET_OBJECTS:TutorialTools>)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Triangle ${SOURCES})
target_compile_features(Triangle PRIVATE cxx_std_11)
target_link_libraries(Triangle PRIVATE RadeonRays)
if (APPLE OR UNIX)
    target_link_libraries(Triangle PRIVATE OpenGL::GL GLUT::GLUT GLEW::GLEW)
elseif (WIN32)
    target_include_directories(Triangle 
        PRIVATE ${GLUT_INCLUDES} 
        PRIVATE ${GLEW_INCLUDES} 
        )
    target_link_libraries(Triangle PRIVATE OpenGL::GL ${GLUT_LIBS} ${GLEW_LIBS})
endif (APPLE OR UNIX)
