#include <iostream>
#include <vector>
#include <windows.h>

#include "game_ui.h"
#include "game_map.h"
#include "character.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "triangle_buffer.h"

using namespace std;
GameState gameState = READY; //전역 변수로 설정
GameMap globalMap;
vector<GameCharacter> player(3, GameCharacter(&globalMap));
GameCharacter* currentPlayer = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //여러 창을 사용하는 경우 창을 구분하기 위해 주소를 인자로 받음.
{
    (void)window;
    glViewport(0, 0, width, height);
}

int main() {
    // 한글 출력을 위한 콘솔 코드페이지 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);



    //위 코드로 player 내부에 단일 객체 3개 만들고 생성자로 초기화까지.
    int choice = 0;
    while (gameState != EXIT) {
        if (gameState == READY) {
            choice = start_game_ui();
            
            switch(choice){
                case 1: 
                   currentPlayer = new_game(player);
                    break;
                case 2:
                    load_game();
                    break;
                case 3:
                    help();
                    break;
                case 4:
                    exit_game();
                    gameState = EXIT;
                    break;
            }
        }
        else if (gameState == INTRO) {
            system("cls"); // 화면 지우기
            game_intro();

            while(gameState == INTRO) {
                game_play(*currentPlayer); // 객체가 필요하니까 *주소값
            }

        }
    }

    cout << "Press Enter to exit...";
    cin.ignore(); // 입력 버퍼 비우기
    cin.get();    // 사용자 입력 대기
    

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

    // 삼각형 버퍼 준비 예시
    unsigned int VAO, VBO;
    setupTriangleBuffers(VAO, VBO);

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

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