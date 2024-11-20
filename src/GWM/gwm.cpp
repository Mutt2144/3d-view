#include "gwm.hpp"

void GWM::init(int *pargc, char **argv, int w, int h, const char* title) {
    glutInit(pargc,  argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow(title);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, w / h, 0.01, 100);
    glMatrixMode(GL_MODELVIEW);

    //glutFullScreen();

    glEnable(GL_DEPTH_TEST);


    glutKeyboardFunc(handle_keyboard);
    glutKeyboardUpFunc(handle_keyboard_up);
    glutSpecialFunc(handle_special_keys);
    glutSpecialUpFunc(handle_special_keys_up);
    glutPassiveMotionFunc(handle_mouse_movement);
}