#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <complex>
#include <iostream>
#include <functional>

#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE  32

namespace MSet {

    int init_wWidth =  600;
    int init_wHeight = 600;
    int curr_wWidth =  init_wWidth;
    int curr_wHeight = init_wHeight;

    GLdouble Scale = 1;
    GLfloat  hShift = 0.5;
    GLfloat  vShift = 0;
    GLfloat  Degree = 2;
    auto iter_max = 50;

    GLdouble x_range[2] = {-1.5, 0.5};
    GLdouble x_inc = 0.01;
    GLdouble y_range[2] = {-1, 1};
    GLdouble y_inc = 0.01;


    unsigned int VBO, VAO;
    float Vertices[] = {
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    auto func = [] (std::complex<double>z, std::complex<double> c) -> std::complex<double> { return pow(z, Degree) + c; };
    int Escape(std::complex<double>& c, const int& iter_max, const std::function<std::complex<double>(std::complex<double>,
               std::complex<double>)>& func);
    bool Frame_Flag = true;

    unsigned int shaderProgram{0};
    const char* VertexShaderSource ="#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "layout (location = 1) in vec3 aColor;\n"
                                    "out vec3 ourColor;\n"
                                    "uniform mat4 transform;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = transform * vec4(aPos, 1.0);\n"
                                    "   ourColor = aColor;\n"
                                    "}\n\0";

    const char* FragmentShaderSource =  "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "in vec3 ourColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   FragColor = vec4(ourColor, 1.0f);\n"
                                        "}\n\0";


    void initGL() {

        // vertex shader
        unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
        glCompileShader(VertexShader);

        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // fragment shader
        unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
        glCompileShader(FragmentShader);

        // check for shader compile errors
        glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, VertexShader);
        glAttachShader(shaderProgram, FragmentShader);
        glLinkProgram(shaderProgram);

        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(VertexShader);
        glDeleteShader(FragmentShader);



        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //glUseProgram(shaderProgram);
 
    } 

    void Keyboard(unsigned char Typped, int x, int y) {
        Frame_Flag = true;
        switch(Typped) {
            case 'q':
            case KEY_ESCAPE:        exit(0);

            case KEY_SPACE:         iter_max += 10;
                                    iter_max %= 50;
                                    ++iter_max;      break;

            case KEY_ENTER:         hShift = 0.5;
                                    vShift = 0;
                                    Scale = 1;
                                    iter_max = 50;   break;

            case 'a':               Degree -= 0.1;   break;

            case 'd':               Degree += 0.1;   break;

            case 'w':               Degree += 1.0;   break;

            case 's':               Degree -= 1.0;   break;
        }

        return;
    }

    void SpecKeyboard(int key, int x, int y) {
        Frame_Flag = true;
        switch(key)
        {
            case GLUT_KEY_UP:       vShift -= 0.1;   break;

            case GLUT_KEY_DOWN:     vShift += 0.1;   break;

            case GLUT_KEY_LEFT:     hShift += 0.1;   break;

            case GLUT_KEY_RIGHT:    hShift -= 0.1;   break;
        }

        return;
    }

    void Mouse(int Button, int State, int x, int y) {
        Frame_Flag = true;
        switch(Button)
        {
            case 3:     Scale *= 1.1;   break; 
            
            case 4:     Scale /= 1.1;   break;
        }

        return;
    }

    void display(void) {

        if(Frame_Flag == true) {

            curr_wWidth  = glutGet(GLUT_WINDOW_WIDTH);
            curr_wHeight = glutGet(GLUT_WINDOW_HEIGHT);

            std::cout << "Drawing" << std::endl;
            Frame_Flag = false;
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1, 1, 1, 1); 
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glPushMatrix();

            glTranslatef(hShift, vShift, 0);
            glScalef(Scale, Scale, Scale);

            x_range[0] = (-1 - hShift) / Scale;
            x_range[1] = ( 1 - hShift) / Scale;
            x_inc = 2 / Scale / curr_wWidth;

            std::cout << x_range[0] << ' ' << x_range[1] << std::endl;

            y_range[0] = (-1 - vShift) / Scale;
            y_range[1] = ( 1 - vShift) / Scale;
            y_inc = 2 / Scale / curr_wHeight;

            glBegin(GL_POINTS);

                for(double i = x_range[0]; i < x_range[1]; i += x_inc)
                    for(double j = y_range[0]; j < y_range[1]; j += y_inc) {
                        std::complex<double> c{i, j};
                        int iters = Escape(c, iter_max, func);

                        GLdouble t = static_cast<GLdouble>(iters) / static_cast<GLdouble>(iter_max);  
                        glColor3f(9 * (1-t) * t*t*t, 15 * (1-t)*(1-t) * t*t, 8.5 * (1-t)*(1-t)*(1-t) * t);
                        glVertex2f(i, j);
                    }
            glEnd();

            glPopMatrix();

            glutSwapBuffers();
        }
/*       else {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0, 0, 0, 1); 
            
            //glMatrixMode(GL_PROJECTION);
            //glLoadIdentity();

            //glPushMatrix();
            // create transformations
            glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            transform = glm::translate(transform, glm::vec3(hShift, vShift, 0.0f));
            transform = glm::scale(transform, glm::vec3(Scale, Scale, 1));

            glUseProgram(shaderProgram);
            unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            //glPopMatrix();

            glutSwapBuffers();
        }
*/
    
        return;
    }

    void Timer(int) {
        glutPostRedisplay();
        glutTimerFunc(1000/20, Timer, 0);

        return;
    }

    void Reshape(int Width, int Height) {
        Frame_Flag = true;

        curr_wWidth  = Width;
        curr_wHeight = Height;

        double hScale = static_cast<double>(Height) / init_wHeight;
        double wScale = static_cast<double>(Width)  / init_wWidth;
        glOrtho(0, wScale, 0, hScale, -1, 1);

        return;
    }

    int Escape(std::complex<double>& c, const int& iter_max, const std::function<std::complex<double>(std::complex<double>,
        std::complex<double>)>& func) {
        std::complex<double> z{0};
        int iter = 0;
     
        while (abs(z) < 2.0 && iter < iter_max) {
            z = func(z, c);
            ++iter;
        }
     
        return iter;
    }

}