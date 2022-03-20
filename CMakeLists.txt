cmake_minimum_required(VERSION 3.11)

project(Mandelbrot_Set LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)  

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(SOURCE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/Headers)
set(LIBS glut GL)


add_executable(Main.exe ${SOURCE_EXE}/Shader.cpp ${SOURCE_EXE}/Iterations.cpp ${SOURCE_EXE}/Fractal.cpp ${SOURCE_EXE}/Main.cpp)


add_compile_options(
    -Werror

    -O3

    -Wall 
    -Wextra 
     
    -Wnarrowing 
    -Wconversion 
    -Wwrite-strings 
    -Wcast-qual 
    -Wundef    
    -Wreturn-type
)

add_definitions(-DGL_GLEXT_PROTOTYPES)

target_include_directories(Main.exe PUBLIC ${SOURCE_LIB})
target_link_libraries(Main.exe ${LIBS})