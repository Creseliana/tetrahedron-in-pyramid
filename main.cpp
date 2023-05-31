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
    // Initialize the GLUT library
    glutInit(&argc, argv);
    // Initialize display modes for window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Set window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // Create window with given name
    glutCreateWindow("Tetrahedron in pentagonal pyramid");
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Set display callback for the window
    glutDisplayFunc(display);
    // Set global idle callback
    glutIdleFunc(display);
    // Set view limits
    glOrtho(-50, 50, -50, 50, -50, 50);
    // Enter main event processing loop
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Put current matrix in stack, apply rotations,
    // draw tetrahedron with applied rotations
    // and remove this matrix from stack
    glPushMatrix();
    glRotatef(30, 1, 0, 0);
    glRotatef(0, 0, 0, 1);
    glRotatef(rotationAngle, 0, 1, 0);
    drawTetrahedron();
    glPopMatrix();

    // Put current matrix in stack, apply rotations,
    // draw pentagonal pyramid with applied rotations
    // and remove this matrix from stack
    glPushMatrix();
    glRotatef(30, 1, 0, 0);
    glRotatef(0, 0, 0, 1);
    glRotatef(rotationAngle, 0, -1, 0);
    drawPentagonalPyramid();
    glPopMatrix();

    // Flush and swap current buffer
    glutSwapBuffers();

    // Update rotation angle
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
    // Pyramid height (y coord). To achieve given height half size up
    // and half size down relative to the zero coord
    int up = size / 2;
    int down = size / 2 * -1;
    // Calculate angle size in radians by angle number
    double angleRadian = 360.0 / angleNumber * M_PI / 180.0;
    // Array for base coords
    double base[angleNumber][3];
    double angle = 0.0;
    // Fill array with calculated coords
    for (int i = 0; i < angleNumber; ++i) {
        base[i][0] = radius * cos(angle);
        base[i][1] = down;
        base[i][2] = radius * sin(angle);
        angle += angleRadian;
    }
    // For each pair of coords create triangle primitive with a common vertex
    // in the center of the base up the Y axis by half of the size
    for (int f = angleNumber - 1, s = 0, c = 0; s < angleNumber; ++f, ++s, ++c) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3fv(colored == 1 ? colors[c] : baseColor);
        glVertex3dv(base[f]);
        glVertex3dv(base[s]);
        glVertex3d(0, up, 0);
        glEnd();
        if (f == angleNumber - 1) {
            f = -1;
        }
    }
}