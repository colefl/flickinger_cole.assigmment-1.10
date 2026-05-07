#include "circle.h"
#include <glad/glad.h>
#include <math.h>
#include <vector>

Circle::Circle(float cx, float cy, float radius, int segments, float mass)
    : x(cx), y(cy), radius(radius), vx(0.0f), vy(0.0f), mass(mass) {

    std::vector<float> vertices;

    // Center point
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    vertices.push_back(0.0f);

    //Outer ring points
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        vertices.push_back(radius * cos(angle)); //X
        vertices.push_back(radius * sin(angle)); //Y
        vertices.push_back(0.0f); //Z
    }

    vertex_count = segments + 2; // center + ring + closing point

    //mass = 1.0f; //For some debug

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    //So it reads through each of the vertex attributes with an offset of 0 from location 0 which I 
    //have to distnguish in this linked txt file for some reason in order to allow my code to have 
    //lots of shader options like color and verticies and such
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0); //Allows it at location 0
}

void Circle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertex_count);
}

//Getting things to move on the screen
void Circle::update(float dt, float ax, float ay) {
    //const float gravity = -50.0f; // world units/sec for more debug
    vy += ay * dt;
    vx += ax * dt;
    x  += vx * dt;
    y  += vy * dt;
    //return x;

    //Makes the balls bounce on the edges
    if (y - radius < 0.0f)          { y = radius;       vy = -vy * 0.8f; }
    if (y + radius > 480.0f)        { y = 480.0f-radius; vy = -vy * 0.8f; }
    if (x - radius < 0.0f)          { x = radius;       vx = -vx * 0.8f; }
    if (x + radius > 640.0f)        { x = 640.0f-radius; vx = -vx * 0.8f; }
}

Circle::~Circle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}