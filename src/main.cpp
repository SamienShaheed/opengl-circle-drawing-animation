#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

// Global window parameters
int WINDOW_WIDTH = 1560;
int WINDOW_HEIGHT = 840;
std::string WINDOW_TITLE = "Circle Drawing Animation";

void myInit (void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glOrtho(-780, 780, -420, 420, -1, 1);
}

void drawCircle(float center_x, float center_y, float radius, int num_segments) {
    float angle_step = 3.1415926 * 2 / float(num_segments);
    float tangent_length = tanf(angle_step);
    float radius_correction = cosf(angle_step);

    float current_x = radius;
    float current_y = 0;
    
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    for (int segment = 0; segment < num_segments; segment++)
    {
        glVertex2f(current_x + center_x, current_y + center_y);

        float tangent_x = -current_y;
        float tangent_y = current_x;

        current_x += tangent_x * tangent_length;
        current_y += tangent_y * tangent_length;

        current_x *= radius_correction;
        current_y *= radius_correction;
    }
    glEnd();
}

// Simple function to draw a digit using points/lines
void drawDigit(int digit, float x, float y, float size) {
    glLineWidth(3);
    glColor3f(1.0, 1.0, 1.0);
    
    // Define 7-segment display style for digits 0-9
    // Each segment is defined by start and end points
    bool segments[10][7] = {
        {1,1,1,1,1,1,0}, // 0
        {0,1,1,0,0,0,0}, // 1
        {1,1,0,1,1,0,1}, // 2
        {1,1,1,1,0,0,1}, // 3
        {0,1,1,0,0,1,1}, // 4
        {1,0,1,1,0,1,1}, // 5
        {1,0,1,1,1,1,1}, // 6
        {1,1,1,0,0,0,0}, // 7
        {1,1,1,1,1,1,1}, // 8
        {1,1,1,1,0,1,1}  // 9
    };
    
    if (digit < 0 || digit > 9) return;
    
    glBegin(GL_LINES);
    
    // Top horizontal
    if (segments[digit][0]) {
        glVertex2f(x, y + size);
        glVertex2f(x + size, y + size);
    }
    // Top right vertical
    if (segments[digit][1]) {
        glVertex2f(x + size, y + size);
        glVertex2f(x + size, y + size/2);
    }
    // Bottom right vertical
    if (segments[digit][2]) {
        glVertex2f(x + size, y + size/2);
        glVertex2f(x + size, y);
    }
    // Bottom horizontal
    if (segments[digit][3]) {
        glVertex2f(x, y);
        glVertex2f(x + size, y);
    }
    // Bottom left vertical
    if (segments[digit][4]) {
        glVertex2f(x, y);
        glVertex2f(x, y + size/2);
    }
    // Top left vertical
    if (segments[digit][5]) {
        glVertex2f(x, y + size/2);
        glVertex2f(x, y + size);
    }
    // Middle horizontal
    if (segments[digit][6]) {
        glVertex2f(x, y + size/2);
        glVertex2f(x + size, y + size/2);
    }
    
    glEnd();
}

void drawNumber(int number, float x, float y, float size) {
    std::string numStr = std::to_string(number);
    float offset = 0;
    
    for (char c : numStr) {
        int digit = c - '0';
        drawDigit(digit, x + offset, y, size);
        offset += size * 1.5; // Space between digits
    }
}

int main() {
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL); // generate window pointer
    glfwMakeContextCurrent(window);
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    myInit();
    
    int starting_segment = -1; // start by drawing a triangle
    int end_segment = 100;
    int segment_to_draw = starting_segment;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // clear drawing first
        drawCircle(0.0f, 0.0f, 200.0f, segment_to_draw); // then draw the shape
        drawNumber(segment_to_draw, 600, 350, 30); // x, y, size
        
        if (segment_to_draw < end_segment) { // keep increasing until it reaches 100
            segment_to_draw += 1; // move to next polygon
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(350)); // add delay in ms
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}