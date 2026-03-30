#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// [] 조회나 수정을 위한 것이다. 
// 값 할당은 push_back()을 해야 자동으로 capacity도 늘려준다.
//resize()는 size와 capacity를 둘다 늘려준다.
//그니까 resize()로 초기화가 됐으면 []로 수정가능.
//근데 초기화 안된 상태에서 접근하는거면 []안된다는 애기


//결국 push_back()을 capacity가 여유 있을떄 쓰는게 가장 좋다.

int main(){
    vector<int> board;
    board.reserve(100); //size = 0, capacity = 100;
    //초기화는 안된 상태라서 []는 쓰지 않는게 좋음.

    board.push_back(24);
    cout << board[0] << endl;
}