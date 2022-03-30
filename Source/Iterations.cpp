#include "../Headers/Iterations.hpp"

namespace MSet {
	
    // Initialization of GL
	void initGL() {

        shader.init();

        // Creating and binding vertex array
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Enabling shader
        shader.use(); 

    }

    // Reseting window options to default
    void reset(void) {
        glutReshapeWindow(init_wWidth, init_wHeight);
        glutPositionWindow((glutGet(GLUT_SCREEN_WIDTH)  - init_wWidth)  / 2, 
                           (glutGet(GLUT_SCREEN_HEIGHT) - init_wHeight) / 2);
                                    
        hShift = 0.5;
        vShift = 0;
        Scale = 1;
        x_range[0] = -1;
        x_range[1] = 1;
        y_range[0] = -1;
        y_range[1] = 1;

        Frame_Flag = true;
        
        return;
    }

    // Keyboard callback function
    void Keyboard(unsigned char Typped, int x, int y) {
        Frame_Flag = true;
        switch(Typped) {
            case 'q':
            case KEY_ESCAPE:        exit(0);

            case KEY_ENTER:         reset();    break;
        }

        return;
    }

    // Special keyboard callback function
    void SpecKeyboard(int key, int x, int y) {
        Frame_Flag = true;
        switch(key)
        {
            case GLUT_KEY_UP:       vShift -= 0.07 / Scale;   break;

            case GLUT_KEY_DOWN:     vShift += 0.07 / Scale;   break;

            case GLUT_KEY_LEFT:     hShift += 0.07 / Scale;   break;

            case GLUT_KEY_RIGHT:    hShift -= 0.07 / Scale;   break;

            // Switching to fullscreen and back again
            case GLUT_KEY_F11:      FullScreen_Flag = !FullScreen_Flag;
                                    if(FullScreen_Flag)
                                        glutFullScreen();
                                    else {
                                        glutReshapeWindow(init_wWidth, init_wHeight);
                                        glutPositionWindow((glutGet(GLUT_SCREEN_WIDTH)  - init_wWidth)  / 2, 
                                                           (glutGet(GLUT_SCREEN_HEIGHT) - init_wHeight) / 2);
                                    }                 
                                    break;
        }

        return;
    }

    // Mouse callback function
    void Mouse(int Button, int State, int x, int y) {
        Frame_Flag = true;
        switch(Button)
        {
            case 3:     if(Scale < 60000)
                            Scale *= 1.02;   break; 
            
            case 4:     if(Scale > 0.5)
                            Scale /= 1.02;   break;
        }

        return;
    }

    // Main displaying function
    void display(void) {
        int new_wWidth  = glutGet(GLUT_WINDOW_WIDTH);
        int new_wHeight = glutGet(GLUT_WINDOW_HEIGHT);

        if(curr_wWidth != new_wWidth || curr_wHeight != new_wHeight)
                Frame_Flag = true;


        if(Frame_Flag == true) {
            Frame_Flag = false;

            num_of_pixels = new_wWidth * new_wHeight;

            float new_hScale = static_cast<float>(new_wHeight) / init_wHeight;
            float new_wScale = static_cast<float>(new_wWidth) / init_wWidth;
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1, 1, 1, 1); 

            x_range[0] = -1 / Scale * new_wScale - hShift;
            x_range[1] =  1 / Scale * new_wScale - hShift;

            y_range[0] = -1 / Scale * new_hScale - vShift;
            y_range[1] =  1 / Scale * new_hScale - vShift;
            

            // Initialize matrix to identity matrix first
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::scale(transform, glm::vec3(Scale / new_wScale,
                                                        Scale / new_hScale, 1.0f));
            
            transform = glm::translate(transform, glm::vec3(hShift, vShift, 0.0f));

            // Proceed matrix transformation for shader
            shader.set_matrix(transform);

            curr_wWidth  = new_wWidth;
            curr_wHeight = new_wHeight;


            x_inc = (x_range[1] - x_range[0]) / curr_wWidth  / 2;
            y_inc = (y_range[1] - y_range[0]) / curr_wHeight / 2;

            int k = 0;

            for(float i = x_range[0]; i < x_range[1]; i += x_inc)
                for(float j = y_range[0]; j < y_range[1]; j += y_inc) {

                    Vertices[2 * k] = i;
                    Vertices[2 * k + 1] = j;
                        ++k;
                }


            // Drawing vertex array
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);

            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS, 0, num_of_pixels * 4);

            glutSwapBuffers();
        }

        return;
    }

    // Timer function
    void Timer(int) {
        glutPostRedisplay();
        glutTimerFunc(1000/20, Timer, 0);

        return;
    }
}  // namespace MSet