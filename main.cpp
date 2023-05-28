#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

static const float colors[3][3] = {
        {0.8f, 0.6f, 1.0f},
        {0.6f, 0.8f, 1.0f},
        {0.6f, 1.0f, 0.8f}
};

static const float baseColor[3] =
        {1.0f, 1.0f, 1.0f};

float rotationStep = 1, rotationAngle = 0;

void display();

void drawPentagonalPyramid();

void drawTetrahedron();

void drawPyramid(int angleNumber, double radius, int size, int colored);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Tetrahedron in pentagonal pyramid");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glOrtho(-50, 50, -50, 50, -50, 50);
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(30, 1, 0, 0);
    glRotatef(0, 0, 0, 1);
    glRotatef(rotationAngle, 0, 1, 0);
    drawTetrahedron();
    glPopMatrix();

    glPushMatrix();
    glRotatef(30, 1, 0, 0);
    glRotatef(0, 0, 0, 1);
    glRotatef(rotationAngle, 0, -1, 0);
    drawPentagonalPyramid();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();

    rotationAngle += rotationStep;
    if (rotationAngle >= 360) {
        rotationAngle = 0;
    }
}

void drawPentagonalPyramid() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawPyramid(5, 20.0, 40, 0);
}

void drawTetrahedron() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawPyramid(3, 6.0, 10, 1);
}

void drawPyramid(int angleNumber, double radius, int size, int colored) {
    int up = size / 2;
    int down = size / 2 * -1;
    double angleRadian = 360.0 / angleNumber * M_PI / 180.0;
    double base[angleNumber][3];
    double angle = 0.0;
    for (int i = 0; i < angleNumber; ++i) {
        base[i][0] = radius * cos(angle);
        base[i][1] = down;
        base[i][2] = radius * sin(angle);
        angle += angleRadian;
    }

    int start = 1;
    for (int f = 0, s = angleNumber - 1, c = 0; s < angleNumber; ++f, ++s, ++c) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3fv(colored == 1 ? colors[c] : baseColor);
        glVertex3dv(base[f]);
        glVertex3dv(base[s]);
        glVertex3d(0, up, 0);
        glEnd();
        if (start == 1) {
            start = 0;
            f = -1;
            s = 0;
        }
    }
}