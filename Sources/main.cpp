#include <iostream>
using namespace std;

const int W = 30; //판 가로길이
const int H = 15; //세로길이

void drawBoard()
{   
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(i == 0){  //첫번째 라인일떈
                cout << '#';
            }
            else if(i == H-1){ //마지막라인일떈?
                cout << '#';
            }
            else{   //나머지라인일땐 j가 0일떄랑 j의끝에서만 출력한다!
                if(j == 0)  cout << '#';    //j가 0일때
                else if(j == W-1)   cout << '#';    //끝일때
                else    cout << ' '; //디폴트 빈칸들
            }
        }
        cout << endl;
    }

}


int main()
{
    drawBoard();

    return 0;
}