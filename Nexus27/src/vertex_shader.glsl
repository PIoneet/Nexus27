#version 330 core
layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aNormal; 
out vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); 
    //openGL 내장 변수임. 래스터화 단계의 입력값이다.
    vec3 transformedNormal = mat3(transpose(inverse(view * model))) * aNormal;
    //이동 변환 적용 안하기에 3차원 좌표계 사용
    vNormal = transformedNormal;
}