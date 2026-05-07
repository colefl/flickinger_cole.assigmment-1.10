#pragma once
#include <vector>

class Circle {
public:
    Circle(float cx, float cy, float radius, int segments, float mass);
    void draw();
    void update(float dt, float ax, float ay); // change int time, change in x, change in y
    ~Circle();

    float x, y; //position (NDC space, -1 to 1)
    float vx, vy; //velocity
    float radius;
    float mass;

private:
    unsigned int VAO, VBO;
    int vertex_count;
};