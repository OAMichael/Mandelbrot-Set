#include "../Headers/Fractal.hpp"

namespace MSet {

	Fractal::Fractal(const char* name_) : name{name_} {};

	void Fractal::show() {
		
	    glutInitWindowPosition(400, 50);
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