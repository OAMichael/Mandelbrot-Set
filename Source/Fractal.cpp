#include "../Headers/Fractal.hpp"

namespace MSet {

	Fractal::Fractal(const char* name_) : name{name_} {};

	// Drawing function for fractal
	void Fractal::show() {
		
	    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)  - init_wWidth)  / 2, 
                           	   (glutGet(GLUT_SCREEN_HEIGHT) - init_wHeight) / 2);
	    glutInitWindowSize(init_wWidth, init_wHeight);
	     
	    int win = glutCreateWindow(name);

	    initGL();
	    glutDisplayFunc(display);

	    glutKeyboardFunc(Keyboard);
	    glutSpecialFunc(SpecKeyboard);
	    glutMouseFunc(Mouse);

	    glutTimerFunc(1000, Timer, 0);
	    glutMainLoop();
	}
}