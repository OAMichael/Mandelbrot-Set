cmake_minimum_required(VERSION 3.8)

project (Mandelbrot_Set)  

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp)
set(SOURCE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/Headers)
set(LIBS glut GL)


add_executable(Main.exe)


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

target_sources(Main.exe PRIVATE ${SOURCE_EXE})
target_include_directories(Main.exe PRIVATE ${SOURCE_LIB})
target_link_libraries(Main.exe ${LIBS})