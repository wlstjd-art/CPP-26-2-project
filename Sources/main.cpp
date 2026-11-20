#include <iostream>
#include <conio.h>  //키보드 인풋 함수!
#include <windows.h>    //슬립펑션! 추가하고싶은루프안에 sleep을넣어서 적당한속도로!
#include <ctime>    
#include <vector> 
using namespace std;

const int W = 25; //가로길이
const int H = 15; //세로길이

int headX = W/2, headY = H/2;  //머리 위치선언!
int fruitX , fruitY;
vector<int> fruit


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
            else if(x == fruitX && y == fruitY){
                
                cout << 'F';
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
    
    do{
    srand(time(NULL));
    fruitX = (rand() % (W-2)) + 1;
    fruitY = (rand() % (H-2)) + 1;
    }
    while(fruitX == headX);
    
    char dir = 'd';  //처음은 오른쪽출발!
    bool isAlive = true;

    while(isAlive){
        
        system("cls");      
        drawBoard();

        if(_kbhit()){
            char Tempdir = _getch();
            if(Tempdir == 'w'||Tempdir == 'a'||Tempdir == 's'||Tempdir == 'd'){   // w , a, s, d일떄만 키보드인풋 허용!
                if(Tempdir == 'w')   //그중에서도 움직일수있을경우만!
                    dir != 's' ? dir = Tempdir : dir = dir;
                if(Tempdir == 'a')   //그중에서도 움직일수있을경우만!
                    dir != 'd' ? dir = Tempdir : dir = dir;
                if(Tempdir == 's')   //그중에서도 움직일수있을경우만!
                    dir != 'w' ? dir = Tempdir : dir = dir;
                if(Tempdir == 'd')   //그중에서도 움직일수있을경우만!
                    dir != 'a' ? dir = Tempdir : dir = dir;
            }
        }


        switch (dir)   //머리움직이기! 
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
            isAlive = false;

        Sleep(55);     
    }
    return 0;
        
}