#include <iostream>
#include <string>

using namespace std;

class UserQueue{
private:
    struct Node{
        int data;
        Node* next;
        Node(int val): data(val), next(nullptr) {}
    };
    Node* first_node;
    int count;
public:
    UserQueue(): first_node(nullptr), count(0) {}
    ~UserQueue(){
        while(!empty()){
            pop();
        }
    }

    void push(int val){
        Node* new_node = new Node(val);
        if(first_node == nullptr){
            first_node = new_node;
        } else {
            Node* temp = first_node;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        count++;
    }

    int pop(){
        if(empty()) return -1;
        Node* temp = first_node;
        first_node = first_node->next;
        int ret = temp->data;
        delete temp;
        count--;
        return ret; 
    }

    int size(){
        return count;
    }

    int empty(){
        return count == 0 ? 1 : 0; //비어있을시 1 반환
    }

    int front(){
        if(empty()) return -1;
        return first_node-> data;
    }

    int back(){
        if(empty()) return -1;
        Node* temp = first_node;
        while(temp != nullptr && temp->next != nullptr){
            // nullptr로 이동하면 temp->data 접근 불가
            temp = temp->next;
        }
        return temp->data;
    }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    UserQueue Q;
    int input_count;
    cin >> input_count;

    for(int i=0; i<input_count; i++){
        string command;
        cin >> command;

        if(command == "push"){
            int value;
            cin >> value;
            Q.push(value);
        }
        else if(command == "pop"){
            cout << Q.pop() << "\n";
        }
        else if(command == "size"){
            cout << Q.size() << "\n";
        }
        else if(command == "empty"){
            cout << Q.empty() << "\n";
        }
        else if(command == "front"){
            cout << Q.front() << "\n";
        }
        else if(command == "back"){
            cout << Q.back() << "\n";
        }
    }

    return 0;
}