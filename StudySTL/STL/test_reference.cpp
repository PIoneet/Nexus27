#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono;
using std::ios;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void passValue(vector<vector<int>> v)
{
    int temp = v[0][0];
}

void passReference(vector<vector<int>>& v)
{
    int temp = v[0][0];
}

//
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> numbers(5000, vector<int>(5000, 1));
    //참조 전달 속도
    auto start1 = high_resolution_clock::now();

    passReference(numbers);
}