#include "../Headers/Iterations.hpp"

using namespace MSet;

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(400, 50);
    glutInitWindowSize(init_wWidth, init_wHeight);
     
    int win = glutCreateWindow("Mandelbrot set");

    initGL();
    glutDisplayFunc(display);
    //glutReshapeFunc(Reshape);

    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecKeyboard);
    glutMouseFunc(Mouse);

    //glutFullScreen();
    glutTimerFunc(1000, Timer, 0);
    glutMainLoop();

    return 0;
}