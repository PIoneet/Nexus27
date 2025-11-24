#define TINYOBJLOADER_IMPLEMENTATION 
#include <iostream>
#include <fstream>
#include "game_ui.h"
#include "game_types.h"
#include "character.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "triangle_buffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tiny_obj_loader.h"

using namespace std;
GameState gameState = READY;
GameScore gameScore = DRAW;
GameMap globalMap;
vector<GameCharacter> player{ GameCharacter(&globalMap), GameCharacter(&globalMap) };
int id = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //여러 창을 사용하는 경우 창을 구분하기 위해 주소를 인자로 받음.
{
    (void)window;
    glViewport(0, 0, width, height);
}



int main() {
    // 한글 출력을 위한 콘솔 코드페이지 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<float> vertices; //VBO에 바인당할 정점 버퍼
    vector<unsigned int> indices; //EBO에 바인딩할 인덱스 버퍼
    vector<unsigned int> material;
    std::string inputfile = "./vertex/FinalBaseMesh.obj"; // 경로 저장
    tinyobj::ObjReaderConfig reader_config; 
    reader_config.mtl_search_path = "./vertex/FinalBaseMesh.mtl";

    tinyobj::ObjReader reader; // 파싱하면 이 클래스 내부에 파싱된 데이터가 들어감.

    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error(); //파싱 실패
        }
        exit(1);
    }

    auto& attrib = reader.GetAttrib(); //attrib 멤버 변수값 가져오기
    auto& shapes = reader.GetShapes(); //face 면 정보 저장
    //auto& materials = reader.GetMaterials(); // 재질 텍스쳐 좌표같은거

    // 모델 -> 삼각형 면들 수 -> 면의 꼭짓점 -> 정점 좌표, 노멀 좌표, 텍스쳐 좌표
    for (size_t s = 0; s < shapes.size(); s++) { // 각 모델을 돌아본다.
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]); //면의 꼭짓점 개수

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
            // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v]; // ex) 1//2면 정점 인덱스 0이랑 노멀 인덱스 1를 구조체에 저장
                indices.push_back(idx.vertex_index);
                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
                
                vertices.push_back(vx);
                vertices.push_back(vy);
                vertices.push_back(vz);

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];

                    vertices.push_back(nx);
                    vertices.push_back(ny);
                    vertices.push_back(nz);
                }
                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) { //index == -1이라 코드 넘어감
                    tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];

                    vertices.push_back(tx);
                    vertices.push_back(ty);
                }
            }
            index_offset += fv; //v는 항상 0,1,2,3인데 다음 면으로 넘어가야 되니까
        material.push_back(shapes[s].mesh.material_ids[f]); //.mtl 파일 위에서부터 순서대로 0,1,2...로 저장
        //각 face의 재질 인덱스를 따로 배열에 저장해 프래그먼트 셰이더에 전달.
        }
    }


    //게임 UI
    while (gameState != EXIT) {
        if (gameState == READY) {
            new_game(player);
        }
        else if (gameState == INTRO) {
            system("cls");
            while(gameState == INTRO) {
                game_play(player);
            }

        }
    }
    cout << "게임을 종료합니다. 감사합니다!" << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    
    

    
    
    //openGL 실습 시작 부분
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(1200, 1000, "Combat", NULL, NULL);

    if (window == NULL) // 포인터는 NULL이 들어갈 수 있어서 체크하는거임.
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }

    glfwMakeContextCurrent(window); // 랜더링(화면에 그리기)을 할 윈도우를 지정하는 작업

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // 셰이더 프로그램 생성 및 초기화
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shaderProgram; //gpu에서 최종으로 실행하는 링크된 오픈 gl 객체

    std::ifstream vShaderFile("src\\vertex_shader.glsl");
    if (!vShaderFile.is_open()) {
        std::cout << "vertex_shader.glsl 파일을 열 수 없습니다.`" << std::endl;
        return -1;
    }
    std::string vShaderCode((std::istreambuf_iterator<char>(vShaderFile)), std::istreambuf_iterator<char>());
    const char* vShaderSource = vShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vShaderSource, NULL); //GPU에 소스코드 전달
    glCompileShader(vertexShader); // GPU에 컴파일 명령 전달


    std::ifstream fShaderFile("src\\fragment_shader.glsl");
    std::string fShaderCode((std::istreambuf_iterator<char>(fShaderFile)), std::istreambuf_iterator<char>());
    const char* fShaderSource = fShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); //현재 사용할 셰이더 프로그램을 GPU에 활성화(바인딩)

    GLint success; // openGL에서만 사용하는 정수형 타입이다.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader Program Link Error:\n" << infoLog << std::endl;
    }


    unsigned int VAO, VBO, EBO;
    setupTriangleBuffers(vertices, indices, VAO, VBO, EBO);
    

    glm::mat4 model = glm::mat4(1.0f); // 아래 코드의 순서로 이동을 먼저할지 회전을 먼저할지 결정 가능
    model = glm::translate(model, glm::vec3(1.0f, 2.0f, 0.0f)); // 이동 
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // 회전
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f)); // 스케일

    glm::vec3 eye = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 target = glm::vec3(1.0f, 2.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(eye, target, up); //알아서 u,v,n 계산해줌.

    float fovy = 45.0f;
    float aspect = 1200.0f / 1000.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    glm::mat4 projection = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); 
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glViewport(0, 0, 1200, 1000);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //만약 윈도우 창이 여러개 있을시 한개를 지정해서 콜백함수를 호출할 수 있음.

    while(!glfwWindowShouldClose(window)) 
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();

    
    return 0;
}
