#include <iostream>
#include <string>

using namespace std;

int main(){
    const int NUM_COUNT = 10;  
    struct num{
        char name;
        int count = 0;
        num() : name('0'), count(0) {}
    };
    num numbers[NUM_COUNT];
    int arr[3];
    long input_result = 1;
    string input_string;

    for(int i = 0; i < 3; i++) {
        cin >> arr[i];
        input_result *= arr[i];
    }
    input_string = to_string(input_result);
    

    for(int i=0; i<input_string.length(); i++) {
        for(int j=0; j<NUM_COUNT; j++) {
            if(input_string[i] == (char)(numbers[j].name + j)) {
                numbers[j].count++; 
                break;
            }
        }
    }
    for(int i=0; i<NUM_COUNT; i++) {
        cout << numbers[i].count << endl;
    }


    return 0;
}