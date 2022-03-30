#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include "Shader.hpp"

// All needed defines
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE  32
#define MAX_PIXEL_NUM 1800 * 1600 * 8


namespace MSet {

    static int init_wWidth =  500;
    static int init_wHeight = 500;
    static int num_of_pixels = init_wWidth * init_wHeight;
    static int curr_wWidth =  init_wWidth;
    static int curr_wHeight = init_wHeight;
    static bool FullScreen_Flag = false;


    static GLfloat  Scale = 1;
    static GLfloat  hShift = 0.5;
    static GLfloat  vShift = 0;

    static GLfloat x_range[2] = {-1, 1};
    static GLfloat x_inc = 0.01;
    static GLfloat y_range[2] = {-1, 1};
    static GLfloat y_inc = 0.01;


    static unsigned int VBO, VAO;

    static float Vertices[MAX_PIXEL_NUM];

    static bool Frame_Flag = true;

    static Shader shader{"../Shaders/Shader.vs", "../Shaders/Shader.fs"};

    void initGL();

    void Keyboard(unsigned char Typped, int x, int y);

    void SpecKeyboard(int key, int x, int y);

    void Mouse(int Button, int State, int x, int y);

    void reset(void);

    void display(void);

    void Timer(int);

}   // namespace MSet
