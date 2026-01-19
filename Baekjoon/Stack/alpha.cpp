#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Stack{
private:
    struct Node{ //Node(data)하면 생성자 발동
        int data;
        Node* next;
        Node(int data): data(data), next(nullptr) {}
    };
    Node* topNode;
    int count;

public:
    Stack(): topNode(nullptr), count(0) {} // 생성자임.
    
    ~Stack(){ //소멸자임. 
        while(!empty()){ // 혹시 모를 메모리 누수 제거
            pop();
        }
    }
    void push(int data){
        Node* newNode = new Node(data);
        newNode->next = topNode;// 새 노드가 또 오면 그걸 가리킴.
        topNode = newNode; //nullptr이던 topNode가 새 노드 가리킴.
        count++;
    }

    int pop(){
        if(empty()) return -1;
        Node* temp = topNode; //현재 가장 위의 주소값을 저장해둠. 삭제할려고
        topNode = topNode->next; //topNode -> next는 맨위에서 2번쨰꺼
        int poppedData = temp->data;
        delete temp; //이제 기존 topNode에 접근할 수단이 사라짐. 
        count--;
        return poppedData;
    }

    int size(){
        if(topNode == nullptr) return 0;
        return count;
    }

    int top(){
        if(empty()) return -1;
        return topNode->data;
    }
    int empty(){
        if(topNode == nullptr)
            return 1;
        else
            return 0;
    }
};
int main(){
    Stack S;
    
    int input_count;
    cin >> input_count;
    for(int i = 0; i < input_count; ++i){
        string command;
        cin >> command;
        if(command == "push"){
            int add_num;
            cin >> add_num;
            S.push(add_num);
        }
        if(command == "size"){
            cout << S.size() << endl;
        }
        if(command == "empty"){
            cout << S.empty() << endl;
        }
        if(command == "top"){
            cout << S.top() << endl;
        }
        if(command == "pop"){
            cout << S.pop() << endl;
        }
    }
    /*
    S.push(1);
    S.push(2);
    while(!S.empty()){
        cout << S.top() << endl;
        cout << S.pop() << endl;
        cout<< S.top() << endl;
    }
    */
    return 0;
}
