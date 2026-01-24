#include <iostream>
#include <string>
using namespace std;


class UserDeck{
private:
    struct Node{
        int data;
        Node* next; //back 쪽을 가리킴.
        Node* prev; //front 쪽을 가리킴.
        Node(int val): data(val), next(nullptr), prev(nullptr) {}
    };
    Node* front_node;
    Node* back_node;
    int count;
public:
    UserDeck(): front_node(nullptr), back_node(nullptr), count(0) {}
    ~UserDeck(){
        while(!empty()){
            pop_front();
        }
    }
    void push_front(int val){
        Node* new_node = new Node(val);
        if(count == 0){
            front_node = new_node;
            back_node = new_node;
        }else{
            new_node->next = front_node;
            front_node->prev = new_node; //기존 노드의 앞에 새 노드 연결
            front_node = new_node;
        }
        count++;
    }
    
    void push_back(int val){
        Node* new_node = new Node(val);
        if(count == 0){
            front_node = new_node;
            back_node = new_node;
        }else{
            new_node->prev = back_node;
            back_node->next = new_node;
            back_node = new_node;
        }
        count++;
    }

    int pop_front(){
        if(empty()) return -1;
        Node* temp = front_node;
        front_node = front_node->next;
        int ret = temp->data;
        delete temp;
        count--;
        return ret;
    }

    int pop_back(){
        if(empty()) return -1;
        Node* temp = back_node;
        back_node = back_node->prev;
        int ret = temp->data;
        delete temp;
        count--;
        return ret;
    }   
    
    int size(){
        return count;
    }

    int empty(){
        return count == 0 ? 1 : 0;
    }

    int front(){
        if(empty()) return -1;
        return front_node-> data;
    }

    int back(){
        if(empty()) return -1;
        return back_node-> data;
    }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    UserDeck D;
    int input_count;
    cin >> input_count;
    for(int i = 0; i < input_count; i++){
        string command;
        cin >> command;
        if(command == "push_front"){
            int val;
            cin >> val;
            D.push_front(val);
        } else if(command == "push_back"){
            int val;
            cin >> val;
            D.push_back(val);  
        } else if(command == "pop_front"){
            cout << D.pop_front() << "\n";
        } else if(command == "pop_back"){
            cout << D.pop_back() << "\n";
        } else if(command == "size"){
            cout << D.size() << "\n";
        } else if(command == "empty"){
            cout << D.empty() << "\n";
        } else if(command == "front"){
            cout << D.front() << "\n";
        } else if(command == "back"){
            cout << D.back() << "\n";
        }
    }

    return 0;
}