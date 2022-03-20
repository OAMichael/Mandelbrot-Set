#include "../Headers/Fractal.hpp"

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    MSet::Fractal Frac{"Mandelbrot's Set"};
    Frac.show();

    return 0;
}