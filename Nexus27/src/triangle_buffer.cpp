#include <glad/glad.h>
#include "triangle_buffer.h"

void setupTriangleBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) {
    // 사각형을 두 개의 삼각형으로 그리는 예시 (정점 4개, 인덱스 6개)
    float vertices[] = {
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // 오른쪽 위
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // 오른쪽 아래
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // 왼쪽 아래
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // 왼쪽 위
    };
    unsigned int indices[] = {
        0, 1, 3,   // 첫 번째 삼각형
        1, 2, 3    // 두 번째 삼각형
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO); //VAO 바인딩 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
