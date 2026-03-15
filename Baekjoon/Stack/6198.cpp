#include <iostream>
#include <stack>


using std::ios;
using std::cin;
using std::cout;
using std::endl;
using std::stack;
// 10 3 7 4 12 2 -> 5 출력
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    stack<int> t;
    int N;
    int input;
    long long total{0};
    cin >> N;
    for(int i = 0; i<N; i++)
    {   
        cin >> input;
        if(t.empty())
        {
            t.push(input);
            continue;
        }
    

        while(!t.empty() && t.top() <= input)
        {
            t.pop();
        }


        if(t.empty())
        {
            t.push(input);
        }
        else if(t.top() > input)
        {
            total = total + t.size(); //스택의 크기의 개수만큼 볼 수 있다는거
            t.push(input);
            //이거 지나면 3, 10 쌓임.
        }
    }

    cout << total << '\n';

}