#include <iostream>
#include <conio.h>  //ai가알려준거...! 키보드 인풋 함수!
using namespace std;

const int W = 30; //판 가로길이
const int H = 15; //세로길이

int headX = W/2, headY = H/2;  //머리 위치선언!

bool isAlive = true;

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

    while(isAlive){
        
        system("cls");      //매
        drawBoard();
        switch (_getch())   //머리움직이기! //
        {
        case 'w':
            headY --;
            break;
        case 's':
            headY ++;
            break;
        case 'a':
            headX --;
            break;
        case 'd':
            headX ++;
            break;
        default:
            break;
        }
        if(headX == 0 || headX == W-1 
        || headY == 0 || headY == H-1) //벽만나면죽음!!
            isAlive = 0;
        

    }

    return 0;
}