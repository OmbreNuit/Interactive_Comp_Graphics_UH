/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * Install Make, GCC, OpenGL and freeglut.             *
 * To compile your program, run "make" in the          *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp, link   *
 * to your OpenGL libs, build and run the executable   *
 * as you normally would.                              *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double xRot = 0;
double yRot = 0;
int curProblem = 3; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
    // TODO: Your code here!

    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(i * 45, 0, 0, 1);
        if (i % 2 == 0) {
            glTranslatef(0, -1, 0);  
        }else {
            glTranslatef(0, -0.75, 0);
        }
        glutSolidTeapot(.1);
        glPopMatrix();
    }
}

void problem2() {
    // TODO: Your code here!
    int steps = 15;
    float height = 0.1;
    float baseSize = 3;
    float decrease = 0.2;
    
    for (int i = 0; i < steps; i++) {
        glPushMatrix();
        float currSize = baseSize - (i * decrease); // the pyramid is built bottom-up
        glTranslatef(0, i * height, 0);
        if (currSize < 0.1) {
            currSize = 0.1; //for when currSize is negative
        }
        glScalef(currSize, height, currSize);
        glutSolidCube(1);
        glPopMatrix();
    }
}

void problem3() {
    // TODO: Your code here!
    int rows = 6;
    float vertSpace = 0.3;
    float horSpace = 0.3;
    for (int i = 0; i < rows; i++) {
        int numPots = i + 1;
        float xStart = -((numPots - 1) * horSpace) / 2;
        for (int j = 0; j < numPots; j++) {
            glPushMatrix();
            glTranslatef(xStart + j * horSpace, -0.5 + i * vertSpace , 0);
            glutSolidTeapot(.1);
            glPopMatrix();   
        }
    }
}


void problem4() {
    // TODO: Your code here!
    // 3D Christmas Tree
    glDisable(GL_LIGHTING);
    
    glPushMatrix();
        
    // tree trunk
    glBegin(GL_QUADS);

    glColor3f(0.6, 0.3, 0);//Brown color
    // positive z (front side)
    glVertex3f(-0.1, -0.5, 0.1); //bottom left
    glVertex3f(0.1, -0.5, 0.1);  //bottom right
    glVertex3f(0.1, 0, 0.1); //top right
    glVertex3f(-0.1, 0, 0.1); //top left
    // negative z (behind)
    glVertex3f(-0.1, -0.5, -0.1);  
    glVertex3f(0.1, -0.5, -0.1);   
    glVertex3f(0.1, 0, -0.1);    
    glVertex3f(-0.1, 0, -0.1);  
    //negative x (left side)
    glVertex3f(-0.1, -0.5, -0.1);  
    glVertex3f(-0.1, -0.5, 0.1);   
    glVertex3f(-0.1, 0, 0.1);    
    glVertex3f(-0.1, 0, -0.1);   
    // positive x (right side)
    glVertex3f(0.1, -0.5, -0.1); 
    glVertex3f(0.1, -0.5, 0.1);   
    glVertex3f(0.1, 0, 0.1);    
    glVertex3f(0.1, 0, -0.1);   
    glEnd();

    // Nested glPushMatrix for tree layers
    glPushMatrix();
    glTranslatef(0, 0, 0); 

    // Bottom tree layer
    glBegin(GL_TRIANGLES);

    glColor3f(0, 0.5, 0); // dark green color
    //positive yz (front)
    glVertex3f(0, 0.8, 0); // Top vertex
    glVertex3f(-0.6, 0, 0.6);  // bottom left
    glVertex3f(0.6, 0, 0.6);  // bottom right
    //positve y negative z (behind)
    glVertex3f(0, 0.8, 0);
    glVertex3f(0.6, 0, -0.6);
    glVertex3f(-0.6, 0, -0.6);
    //positive yx (right side)
    glVertex3f(0, 0.8, 0);  
    glVertex3f(0.6, 0, 0.6);  
    glVertex3f(0.6, 0, -0.6);  
    //positve y negative x (left side)
    glVertex3f(0, 0.8, 0);
    glVertex3f(-0.6, 0, -0.6);
    glVertex3f(-0.6, 0, 0.6);
    glEnd();

    // Middle tree layer 
    glBegin(GL_TRIANGLES);

    glColor3f(0, 0.7, 0);  //medium green color
    //positive yz (front)
    glVertex3f(0, 1.0, 0);
    glVertex3f(-0.45, 0.3, 0.45); 
    glVertex3f(0.45, 0.3, 0.45);   
    //positve y negative z (behind)
    glVertex3f(0, 1.0f, 0);  
    glVertex3f(0.45, 0.3, -0.45);  
    glVertex3f(-0.45, 0.3, -0.45);
    //positive yx (right side)
    glVertex3f(0, 1.0, 0);  
    glVertex3f(0.45, 0.3, 0.45);   
    glVertex3f(0.45, 0.3, -0.45);  
    //positve y negative x (left side)
    glVertex3f(0, 1.0, 0); 
    glVertex3f(-0.45, 0.3, -0.45); 
    glVertex3f(-0.45, 0.3, 0.45);  
    glEnd();

    // Top tree layer
    glBegin(GL_TRIANGLES);
    
    glColor3f(0, 0.9, 0); //light green color
    //positive yz (front)
    glVertex3f(0, 1.2, 0);   
    glVertex3f(-0.3, 0.6, 0.3); 
    glVertex3f(0.3, 0.6, 0.3);   
    //positve y negative z (behind)
    glVertex3f(0, 1.2, 0);   
    glVertex3f(0.3, 0.6, -0.3);  
    glVertex3f(-0.3, 0.6, -0.3); 
    //positive yx (right side)
    glVertex3f(0, 1.2, 0);  
    glVertex3f(0.3, 0.6, 0.3);   
    glVertex3f(0.3, 0.6, -0.3); 
    //positve y negative x (left side)
    glVertex3f(0, 1.2, 0);   
    glVertex3f(-0.3, 0.6, -0.3); 
    glVertex3f(-0.3, 0.6, 0.3);  
    glEnd();

    // Star on top of tree
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 0.0);  // Yellow star
    glVertex3f(0, 1.4, 0.0);  
    glVertex3f(-0.1, 1.2, 0.1); 
    glVertex3f(0.1, 1.2, 0.1);
    //positve y negative z (behind)
    glVertex3f(0, 1.4, 0.0);
    glVertex3f(-0.1, 1.2, -0.1);
    glVertex3f(0.1, 1.2, -0.1);
    //positive yx (right side)
    glVertex3f(0, 1.4, 0.0);
    glVertex3f(0.1, 1.2, 0.1);
    glVertex3f(0.1, 1.2, -0.1);
    //positve y negative x (left side)
    glVertex3f(0, 1.4, 0.0);
    glVertex3f(-0.1, 1.2, 0.1);
    glVertex3f(-0.1, 1.2, -0.1);
    glEnd();

    glPopMatrix();  // for tree
    glPopMatrix();  // for trunk 

    glEnable(GL_LIGHTING);
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
    glEnd(/*GL_LINES*/);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    if (curProblem == 1) problem1();
    if (curProblem == 2) problem2();
    if (curProblem == 3) problem3();
    if (curProblem == 4) problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
    if (leftDown) {
        xRot += (y - lastPos[1]) * .1;
        yRot += (x - lastPos[0]) * .1;
    }
    if (rightDown) {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
    }


    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    curProblem = key - '0';
    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("HW2");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
