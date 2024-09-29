#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Vertex data for a triangle
GLfloat triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,  // Bottom left
     0.5f, -0.5f, 0.0f,  // Bottom right
     0.0f,  0.5f, 0.0f   // Top
};

GLfloat color[] = { 1.0f, 0.0f, 0.0f }; // Initial color: Red
GLfloat position[] = { 0.0f, 0.0f }; // Initial position

// Function to handle key input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                position[1] += 0.1f; // Move up
                break;
            case GLFW_KEY_DOWN:
                position[1] -= 0.1f; // Move down
                break;
            case GLFW_KEY_LEFT:
                position[0] -= 0.1f; // Move left
                break;
            case GLFW_KEY_RIGHT:
                position[0] += 0.1f; // Move right
                break;
            case GLFW_KEY_R:
                color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; // Red
                break;
            case GLFW_KEY_G:
                color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f; // Green
                break;
            case GLFW_KEY_B:
                color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f; // Blue
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE); // Exit
                break;
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Keyboard Interaction, Press R, G, B Use Left, Right, Up, Down arrow", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    // Set key callback
    glfwSetKeyCallback(window, keyCallback);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the color based on input
        glColor3f(color[0], color[1], color[2]);

        // Set the model view matrix for translation
        glPushMatrix();
        glTranslatef(position[0], position[1], 0.0f);

        // Draw the triangle
        glBegin(GL_TRIANGLES);
            glVertex2f(triangleVertices[0], triangleVertices[1]);
            glVertex2f(triangleVertices[3], triangleVertices[4]);
            glVertex2f(triangleVertices[6], triangleVertices[7]);
        glEnd();

        glPopMatrix();

        // Poll events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
