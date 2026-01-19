#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {

    
        
        list<char> L;
        string str;
        int input_count;

    
        
        cin >> str;

        for(char c: str){
            L.push_back(c);       
        }
    
        auto curser = L.end();
    /*
    ++curser; // 실제 이동
    cout << *(next(curser)) << endl; 
    cout << *curser << endl; 
    ++curser;
    L.insert(curser, 'x'); 
    cout << *curser << endl; 
    curser = next(curser);
    cout << *curser << endl;
    L.erase(curser);
    */

        cin >> input_count;
        for(int i = 0; i < input_count; ++i){               
            char command;
            cin >> command;
            if(command == 'L'){
                if(curser != L.begin())
                    --curser;
            }
            if(command == 'D'){
                if(curser != L.end())
                    ++curser;
            }
            if(command == 'B'){
                if(curser != L.begin())
                    curser = L.erase(--curser);
            }
            if(command == 'P'){
                char add_char;
            cin >> add_char;
                L.insert(curser, add_char);
            }
        }
    

        for(char c: L){
            cout << c;
        }
        cout << endl;
        
    
    
    return 0;
}