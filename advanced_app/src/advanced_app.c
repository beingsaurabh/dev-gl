// advanced_app.c: A basic rotating triangle with colors using OpenGL, GLFW, and GLEW.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

// Vertex Shader source
const char* vertex_shader_src = "#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition;\n"
"layout(location = 1) in vec3 vertexColor;\n"
"out vec3 fragColor;\n"
"uniform float angle;\n"
"void main() {\n"
"    float theta = radians(angle);\n"
"    float cosTheta = cos(theta);\n"
"    float sinTheta = sin(theta);\n"
"    mat3 rotation = mat3(\n"
"        cosTheta, -sinTheta, 0.0,\n"
"        sinTheta, cosTheta,  0.0,\n"
"        0.0,      0.0,       1.0\n"
"    );\n"
"    gl_Position = vec4(rotation * vertexPosition, 1.0);\n"
"    fragColor = vertexColor;\n"
"}\n";

// Fragment Shader source
const char* fragment_shader_src = "#version 330 core\n"
"in vec3 fragColor;\n"
"out vec4 color;\n"
"void main() {\n"
"    color = vec4(fragColor, 1.0);\n"
"}\n";

// Function to compile shaders
GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error compiling shader: %s\n", infoLog);
    }
    return shader;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(640, 480, "Rotating Triangle", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    // Define the triangle vertices and colors
    GLfloat vertices[] = {
        // Positions         // Colors
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Top vertex (Red)
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom-left vertex (Green)
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // Bottom-right vertex (Blue)
    };

    // Create and bind a Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind a Vertex Buffer Object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Compile and link the shaders
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_src);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_src);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("Error linking shader program: %s\n", infoLog);
    }

    // Clean up shaders as they are no longer needed after linking
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Set the polygon mode to fill (you can change it to GL_LINE for a wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Use the shader program
    glUseProgram(shader_program);

    // Get the location of the "angle" uniform in the vertex shader
    GLint angle_location = glGetUniformLocation(shader_program, "angle");

    // Main loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Update the angle for rotation
        angle += 1.0f;
        if (angle >= 360.0f) {
            angle = 0.0f;
        }

        // Pass the angle to the vertex shader
        glUniform1f(angle_location, angle);

        // Draw the triangle
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
