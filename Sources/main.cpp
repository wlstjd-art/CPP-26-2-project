#include <iostream>
#include <conio.h>  //키보드 인풋 함수!
#include <windows.h>    //슬립펑션! 추가하고싶은루프안에 sleep을넣어서 적당한속도로!
#include <ctime>    
#include <vector>   
using namespace std;
struct Vector2{
    int x;
    int y;
};
const int W = 35; //가로길이
const int H = 25; //세로길이
int score = 0; 
Vector2 headPos{W/2, H/2};
Vector2 fruitPos{};
Vector2 body[100];
int bodyLength = 0;


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
            else if(x == headPos.x && y == headPos.y){
                cout << '@';    //뱀의 머리 그리기!
            }
            else if(x == fruitPos.x && y == fruitPos.y){
                cout << 'F';
            }
            else{   
                if(x == 0)  cout << '#';    //x가 0일때
                else if(x == W-1)   cout << '#';    //끝일때
                else if(x > 0 && x < W-1){  
                    bool isEmpty = true;    //버그해결방법은
                    for(int i = 0; i < bodyLength; i++){
                        if(body[i].x == x && body[i].y == y){
                            cout << 'o';
                            isEmpty = false;
                        }
                    }
                    if(isEmpty)
                        cout << ' '; //디폴트 빈칸들
                }    
            }
        }
        cout << endl;
    }
    cout << "점수 : " << score << endl;
}
void spawnFruit(){
    bool isCollision;
    do{ 
        isCollision = false;

        fruitPos.x = (rand() % (W-2)) + 1;      
        fruitPos.y = (rand() % (H-2)) + 1;   

        if(fruitPos.x == headPos.x && fruitPos.y == headPos.y){
            isCollision = true;
        }
        for(int i = 0; i < bodyLength; i++){
            if(fruitPos.x == body[i].x && fruitPos.y == body[i].y)  
                isCollision = true;
        }
    }while(isCollision);
}



int main()
{       
    srand(time(NULL));  
    
    
    char dir = 'd';  //처음은 오른쪽출발!
    bool isAlive = true;
    spawnFruit();
    
    while(isAlive){
        
        system("cls");      //콘솔 클리어
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
        for(int i = bodyLength - 1; i >= 1; i--){       //
            body[i] = body[i-1];                        //
        }                                               //
        if(bodyLength > 0)  body[0] = headPos;          //

        switch(dir){ //머리좌표변경!
            case 'w':
                headPos.y --;
                break;
            case 's':
                headPos.y ++;
                break;
            case 'a':
                headPos.x --;
                break;
            case 'd':
                headPos.x ++;
                break;
            default:
                break;
        }
        cout << "(" << headPos.x << ", " << headPos.y << ")";
            for(int i = 0; i < bodyLength ; i++){
                cout << "(" << body[i].x << ", " << body[i].y << ")";
            }
        if(headPos.x == fruitPos.x && headPos.y == fruitPos.y){ 
            score++;
            bodyLength++;
            spawnFruit();
        } 

        if(headPos.x == 0 || headPos.x == W-1 
        || headPos.y == 0 || headPos.y == H-1) //벽만나면죽음!!
            isAlive = false;
        
        Sleep(100);     
    }
        
}