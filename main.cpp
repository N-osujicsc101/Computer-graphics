//
//  main.cpp
//  newerOpengl
//
//  Created by Nneoma Osuji on 10/05/2024.
//

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

// Initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set the background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Reset the modelview matrix

    glTranslatef(0.0f, 0.0f, -7.0f); // Move the pyramid into the screen
    glRotatef(45.0f, 1.0f, 1.0f, 0.0f); // Rotate the pyramid

    // Begin drawing the pyramid
    glBegin(GL_TRIANGLES);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(0.0f, 1.0f, 0.0f); // Top
    glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom left
    glVertex3f(1.0f, -1.0f, 1.0f); // Bottom right

    // Right face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(0.0f, 1.0f, 0.0f); // Top
    glVertex3f(1.0f, -1.0f, 1.0f); // Bottom left
    glVertex3f(1.0f, -1.0f, -1.0f); // Bottom right

    // Back face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(0.0f, 1.0f, 0.0f); // Top
    glVertex3f(1.0f, -1.0f, -1.0f); // Bottom left
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom right

    // Left face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(0.0f, 1.0f, 0.0f); // Top
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom left
    glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom right

    glEnd(); // End of pyramid drawing

    // Draw the base of the pyramid
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f); // Grey
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glutSwapBuffers(); // Swap the front and back buffers (double buffering)
}

// Reshape callback function
void reshape(int w, int h) {
    if (h == 0) h = 1; // Prevent divide by zero
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h); // Set the viewport to cover the new window

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluPerspective(45.0, aspect, 1.0, 100.0); // Set up the perspective projection
    glMatrixMode(GL_MODELVIEW); // Select the modelview matrix
    glLoadIdentity(); // Reset the modelview matrix
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set up the display mode (double buffer, RGB color, depth buffer)
    glutInitWindowSize(800, 600); // Set the window size
    glutCreateWindow("OpenGL Pyramid"); // Create the window with a title

    init(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display callback function
    glutReshapeFunc(reshape); // Register the reshape callback function

    glutMainLoop(); // Enter the GLUT event loop

    return 0;
}

