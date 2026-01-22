#include <iostream>
#include <string>
#include <stack>
#include <memory>

// 2026 . 01. 20 시간 초과 되긴 했지만 접근과 구현자체는 훌룡했음
using namespace std;

class ControlStack{
private:
    struct Tower{
        int height;
        int name;
        int laser_receiver;
        Tower* next;
        Tower(int h): height(h), name(0), laser_receiver(0), next(nullptr) {}
    };
    Tower* right_tower;
    int tower_count;

public:
    ControlStack(): right_tower(nullptr), tower_count(0) {}
    ~ControlStack(){
        while (!empty()) {
            popTower();
        }
    }
    void pushTower(int height){
        Tower* new_tower = new Tower(height);
        new_tower->next = right_tower;
        right_tower = new_tower;
        tower_count++;
        new_tower->name = tower_count;
    }

    void popTower(){
        if(empty()) return;
        Tower* temp = right_tower;
        right_tower = right_tower->next;
        delete temp;
        tower_count--;
    }

    int getHeight(Tower* targetTower){
        if(targetTower == nullptr) return 0;
        return targetTower->height;
    }

    void sendLaser(){
        Tower* current = right_tower;
        Tower* target = current->next;

        for(int i=0; i<tower_count; i++){    

            if(target == nullptr) break;
             
            while(getHeight(target) < getHeight(current)){
                target = target->next;
                if(target == nullptr) break; //계속 다음 타워 이동 무한 루프 빠짐 이거 없으면
            }
            
            if(getHeight(target) != 0){
                current->laser_receiver = target->name;    
            }
            current = current->next;
            target = current->next;
        }

    }

    bool empty() {
        return right_tower == nullptr;
    }

    int getTowerCount() {
        return tower_count;
    }

    unique_ptr<int[]> getLaserReceiver(){
        Tower* current = right_tower;
        auto towers = make_unique<int[]>(tower_count);
        for(int i=tower_count-1; i>=0; i--){
            towers[i] = current->laser_receiver;
            current = current->next;
        }
        return towers;
    }
};



int main(){

    int input_count;
    cin >> input_count;
    ControlStack S;

    for(int i = 0; i<input_count; i++){
        int height;
        cin >> height;
        S.pushTower(height);
    }

    S.sendLaser();

    auto receivers = S.getLaserReceiver();


    for(int i=0; i<S.getTowerCount(); i++){
        cout << receivers[i] << " ";
    }

    return 0;
}