#include <iostream>
using namespace std;

const int W = 30; //판 가로길이
const int H = 15; //세로길이

int headX = W/2, headY = H/2;  //머리 위치선언!


void drawBoard()
{   
    for(int y = 0; y < H; y++){
        for(int x = 0; x < W; x++){
            if(y == 0){  //첫번째 라인일떈
                cout << '#';
            }
            else if(y == H-1){ //마지막라인일떈?
                cout << '#';
            }
            else if(x == headX && y == headY){
                cout << '@';    //뱀의 머리 그리기!
            }
            else{   //나머지라인일땐 j가 0일떄랑 j의끝에서만 출력한다!
                if(x == 0)  cout << '#';    //j가 0일때
                else if(x == W-1)   cout << '#';    //끝일때
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