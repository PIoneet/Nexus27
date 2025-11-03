#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>

using std::string;

// 타입 검사와 범위 검사를 한번에 하는 함수
int get_valid_input(int min, int max, const string& prompt);
void swap_int(int& a, int& b);

#endif // INPUT_UTILS_H
