#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(){

    class Stack{
    private:
        struct Node{
            int data;
            Node* next;
            Node(int val): data(val), next(nullptr) {}
        };
        Node* top_node;
        int count;
    public:
        Stack() {
            top_node = nullptr;
            count = 0;
        }
        ~Stack(){
            while(!empty()){
                pop();
            }
        }
        void push(int val){
            Node* new_node = new Node(val);
            new_node -> next = top_node;
            top_node = new_node;
            count++;
        }
        void pop(){
            if(empty()) return;
            Node* temp = top_node;
            top_node = top_node->next;
            delete temp;
            count--;
        }
        int top(){
            if(empty()) return -1;
            return top_node->data;
        }
        bool empty(){
            return top_node == nullptr;
        }
        int assemble(){
            int result = 0;
            Node* current = top_node;
            for(int i=0; i<count; i++){
                result += current->data;
                current = current->next;
            }
            return result;
        }
        int getCount(){
            return count;
        }
        

    };

    int input_count;
    cin >> input_count;
    Stack S;

    for(int i=0; i<input_count; i++){
        int add_value;
        cin >> add_value;

        if(add_value !=0){
            S.push(add_value);
        }
        else{
            if(S.empty()) continue;
            S.pop();
        }

    }
    cout << S.assemble() <<endl;
    
    
    return 0;
}