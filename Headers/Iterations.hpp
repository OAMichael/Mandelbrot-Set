#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include <functional>

#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE  32


namespace MSet {

    int init_wWidth =  500;
    int init_wHeight = 500;
    int num_of_pixels = init_wWidth * init_wHeight;
    int curr_wWidth =  init_wWidth;
    int curr_wHeight = init_wHeight;
    bool FullScreen_Flag = false;


    GLdouble Scale = 1;
    GLfloat  hShift = 0.5;
    GLfloat  vShift = 0;

    GLdouble x_range[2] = {-1.5, 0.5};
    GLdouble x_inc = 0.01;
    GLdouble y_range[2] = {-1, 1};
    GLdouble y_inc = 0.01;


    unsigned int VBO, VAO;

    float Vertices2[1800 * 1600 * 8];

    bool Frame_Flag = true;

    unsigned int shaderProgram{0};

    const char* VertexShaderSource =    "#version 330 core\n"
                                        "layout (location = 0) in vec2 vPosition;\n"
                                        "uniform mat4 transform;\n"
                                        "out vec4 MainColor;\n"

                                        "void main() {\n"
                                            "gl_Position = vec4(vPosition, 0.0, 1.0);\n"
                                            "vec2 p = gl_Position.xy;\n"
                                            "vec2 c = p;\n"
                                            "gl_Position = transform * vec4(vPosition, 0.0, 1.0);\n"


                                            //Set default color to HSV value for black
                                            "vec3 color = vec3(0.0, 0.0, 0.0);\n"


                                            "for(int i = 0; i < 100; i++) {\n"
                                                //Perform complex number arithmetic
                                                "p = vec2(p.x * p.x - p.y * p.y, 2.0 * p.x * p.y) + c;\n"
                                                
                                                "if (dot(p, p) > 4.0) {\n"
                                                    "float colorRegulator = float(i - 1) - log( (log(dot(p, p)) / log(2.0)) ) / log(2.0);\n"
                                                    
                                                    "color = vec3(0.95 + 0.012 * colorRegulator , 1.0, 0.2 + 0.4 * (1.0 + sin(0.3 * colorRegulator)));\n"
                                                   
                                                    "break;\n"
                                                "}\n"
                                            "}\n"
                                            "vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);\n"
                                            "vec3 m = abs(fract(color.xxx + K.xyz) * 6.0 - K.www);\n"
                                            "MainColor.rgb = color.z * mix(K.xxx, clamp(m - K.xxx, 0.0, 1.0), color.y);\n"
                                            "MainColor.a = 1;\n"
                                        "};\0";

    const char* FragmentShaderSource =  "#version 330 core\n"
                                        "in vec4 MainColor;\n"
                                        "out vec4 FragColor;\n"

                                        "void main() {\n"
                                            "FragColor = MainColor;\n"
                                        "}\0";

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
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_DYNAMIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram);
 
    } 

    void Keyboard(unsigned char Typped, int x, int y) {
        Frame_Flag = true;
        switch(Typped) {
            case 'q':
            case KEY_ESCAPE:        exit(0);

            case KEY_ENTER:         glutReshapeWindow(init_wWidth, init_wHeight);
                                    Frame_Flag = true;
                                    hShift = 0.5;
                                    vShift = 0;
                                    Scale = 1;      break;
        }

        return;
    }

    void SpecKeyboard(int key, int x, int y) {
        Frame_Flag = true;
        switch(key)
        {
            case GLUT_KEY_UP:       vShift -= 0.07 / Scale;   break;

            case GLUT_KEY_DOWN:     vShift += 0.07 / Scale;   break;

            case GLUT_KEY_LEFT:     hShift += 0.07 / Scale;   break;

            case GLUT_KEY_RIGHT:    hShift -= 0.07 / Scale;   break;

            case GLUT_KEY_F11:      FullScreen_Flag = !FullScreen_Flag;
                                    if(FullScreen_Flag)
                                        glutFullScreen();
                                    else {
                                        glutReshapeWindow(init_wWidth, init_wHeight);
                                        glutPositionWindow(400, 50);
                                    }                 
                                    break;
        }

        return;
    }

    void Mouse(int Button, int State, int x, int y) {
        Frame_Flag = true;
        switch(Button)
        {
            case 3:     Scale *= 1.02;   break; 
            
            case 4:     Scale /= 1.02;   break;
        }

        return;
    }

    void display(void) {
        int new_wWidth  = glutGet(GLUT_WINDOW_WIDTH);
        int new_wHeight = glutGet(GLUT_WINDOW_HEIGHT);

        if(curr_wWidth != new_wWidth || curr_wHeight != new_wHeight)
                Frame_Flag = true;

        //std::cout << "New Pixels: " << new_wWidth << "x" << new_wHeight << std::endl;

        if(Frame_Flag == true) {
            Frame_Flag = false;

            num_of_pixels = new_wWidth * new_wHeight;

            std::cout << "\nScale = " << Scale << std::endl; 
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1, 1, 1, 1); 

            x_range[0] = -1 / Scale * new_wWidth  / init_wWidth - hShift;
            x_range[1] =  1 / Scale * new_wWidth  / init_wWidth - hShift;

            y_range[0] = -1 / Scale * new_wHeight / init_wHeight - vShift;
            y_range[1] =  1 / Scale * new_wHeight / init_wHeight - vShift;

            // Initialize matrix to identity matrix first
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::scale(transform, glm::vec3(Scale / new_wWidth  * init_wWidth,
                                                        Scale / new_wHeight * init_wHeight, 1));
            transform = glm::translate(transform, glm::vec3(hShift, vShift, 0.0f));



            unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


            curr_wWidth  = new_wWidth;
            curr_wHeight = new_wHeight;
            x_inc = (x_range[1] - x_range[0]) / curr_wWidth  / 2;
            y_inc = (y_range[1] - y_range[0]) / curr_wHeight / 2;

            std::cout << "x: " << x_range[0] << " : " << x_range[1] << 
                   ". Points:" << (x_range[1] - x_range[0]) / x_inc << "; Pixels: " << curr_wWidth << std::endl;


            std::cout << "y: " << y_range[0] << " : " << y_range[1] << 
                   ". Points:" << (y_range[1] - y_range[0]) / y_inc << "; Pixels: " << curr_wHeight << std::endl;

            int k = 0;

            for(float i = x_range[0]; i < x_range[1]; i += x_inc)
                for(float j = y_range[0]; j < y_range[1]; j += y_inc) {

                    Vertices2[2 * k] = i;
                    Vertices2[2 * k + 1] = j;
                        ++k;
                }


            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_DYNAMIC_DRAW);

            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS, 0, num_of_pixels * 4);

            glutSwapBuffers();
        }

        return;
    }

    void Timer(int) {
        glutPostRedisplay();
        glutTimerFunc(1000/20, Timer, 0);

        return;
    }

    void Reshape(int Width, int Height) {
        Frame_Flag = true;

        double hScale = static_cast<double>(Height) / curr_wHeight;
        double wScale = static_cast<double>(Width)  / curr_wWidth;
        glOrtho(0, wScale, 0, hScale, -1, 1);

        return;
    }

}
