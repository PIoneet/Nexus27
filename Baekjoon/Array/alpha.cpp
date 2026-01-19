#include <iostream>
#include <string>

using namespace std;

int main() {

    const int ALPHABET_COUNT = 26;
    struct letter{
        int count = 0;
    };

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string letters; // cin으로 받을 문자열
    char S[100];
    letter arr[ALPHABET_COUNT];
    cin >> letters;

    for(int index = 0; index < letters.length(); index++) {
        for(int i = 0; i < ALPHABET_COUNT; i++) {
            if(letters[index] == alphabet[i]) {
                arr[i].count++;
                break;
            }
        }    
    }
    for(int i = 0; i < ALPHABET_COUNT; i++) {
       cout << arr[i].count << " ";
    }
    return 0;
}