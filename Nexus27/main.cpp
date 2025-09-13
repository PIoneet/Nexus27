#include <iostream>
#include <vector>
#include <windows.h>
#include "game_ui.h"
#include "game_map.h"
#include "character.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;
GameState gameState = READY; //전역 변수로 설정
GameMap globalMap;
vector<GameCharacter> player(3, GameCharacter(&globalMap));
GameCharacter* currentPlayer = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
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
    window = glfwCreateWindow(800, 600, "ZMMR", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();

    //cout << "Press Enter to exit...";
    //cin.ignore(); // 입력 버퍼 비우기
    //cin.get();    // 사용자 입력 대기
    return 0;
}