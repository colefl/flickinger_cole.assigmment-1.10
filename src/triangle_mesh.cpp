#include "triangle_mesh.h"
#include <vector>
#include <glad/glad.h>

TriangleMesh::TriangleMesh() {
    std::vector<float> positions = { //In openGl, a vertex is a collection of all of the attributes needed to draw a point
        -1.0f, -1.0f, 0.0f, //bottom left
         1.0f, -1.0f, 0.0f, //bottom right
        -1.0f,  1.0f, 0.0f, //top left
         1.0f,  1.0f, 0.0f  //top right
    };

    std::vector<int> colorIndicies = { //In openGl, a vertex is a collection of all of the attributes needed to draw a point
        0, 1, 2, 3
    };

    std::vector<int> elementIndicies = {
        0, 1, 2, 2, 1, 3
    };
    
    vertex_count = 6;

    glGenVertexArrays(1, &VAO); //VAO = Vertex Array Object
    glBindVertexArray(VAO);

    VBOs.resize(2); //Creates 2 unsigned integers

    glGenBuffers(2, VBOs.data()); //VBO: Vertex Buffer Object

    //position
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), 
            positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0); //This attribute has an offset of 0 when looking at the vertex
    glEnableVertexAttribArray(0);

    //color
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndicies.size() * sizeof(float), 
            colorIndicies.data(), GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, 4, (void*)0); //This attribute has an offset of 0 when looking at the vertex
    glEnableVertexAttribArray(1);

    //elements
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            elementIndicies.size() * sizeof(int), 
            elementIndicies.data(), GL_STATIC_DRAW);
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0); //Method goes mode, count of objects being drawn, type, and indicies
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &EBO);
}