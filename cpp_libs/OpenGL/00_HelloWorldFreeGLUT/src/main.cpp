#include <iostream>

#include <GL/gl.h>
#include <GL/freeglut.h>

void drawScene();

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(400,200);
    int windowId = glutCreateWindow("OpenGL - FreeGLUT");
    glutDisplayFunc(drawScene);
    glutMainLoop();
    return 0;
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    const float size = 0.5f;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-size, -size, 0.0f);
    glVertex3f(size, -size, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glEnd();

    glutSwapBuffers();
}