#include <iostream>
#include <conio.h>  //키보드 인풋 함수!
#include <windows.h>    //슬립펑션! 추가하고싶은루프안에 sleep을넣어서 적당한속도로!
#include <ctime>    
#include <vector>   
using namespace std;

const int W = 45; //가로길이
const int H = 25; //세로길이
const int FRUITCOUNT = 25; //과일갯수!

struct Vector2{
    int x;
    int y;
};

class fruit{
private:
    Vector2 fruitPos;
public:
    fruit(){
        fruitPos = {-1, -1}; 
    }
    Vector2 getfruitPos(){ return fruitPos; }
    void setfruitpos(int x, int y){ fruitPos.x = x; fruitPos.y = y; }
};

class snake{
private:
    Vector2 headPos;
    Vector2 body[100];
    int bodyLength;
    char dir;
    bool selfcol;
public:
    snake(){
        headPos = {W/2 , H/2};
        bodyLength = 0;
        dir = 'd';
        selfcol = false;
    }
    Vector2 getheadPos(){ return headPos; }
    Vector2 getBody(int i){ return body[i]; }
    int getbodyLength(){ return bodyLength; }
    void bodyplusplus(){ bodyLength++; }
    void changedir(char Tempdir){
        // char Tempdir = _getch();
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
    void move(){
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
    }

    bool selfcollision(){
        bool a = false;
        for(int i = 0; i < bodyLength; i++){
            if(headPos.x == body[i].x && headPos.y == body[i].y)
                a = true;
        }
        return a;
    }
};



class gamemanager{
private:
    bool isalive;
    int score;

public:
    gamemanager(){
        isalive = true;
        score = 0;
    }
    bool fruitspot(int x, int y, vector<fruit>& fruits){
        for(int i = 0; i < fruits.size(); i++){
            if(x == fruits[i].getfruitPos().x && y == fruits[i].getfruitPos().y)    return true;
        }
        return false;
    }
    void drawBoard(snake& snake1,vector<fruit>& fruits){   
        for(int y = 0; y < H; y++){
            for(int x = 0; x < W; x++){
                if(y == 0){  //첫번째 라인일떈
                    cout << '#';
                }
                else if(y == H-1){ //마지막라인일떈?
                    cout << '#';
                }
                else if(x == snake1.getheadPos().x && y == snake1.getheadPos().y){
                    cout << '@';    //뱀의 머리 그리기!
                }
                else if(fruitspot(x,y,fruits)){
                    cout << 'F';
                }
                else{   
                    if(x == 0)  cout << '#';    //x가 0일때
                    else if(x == W-1)   cout << '#';    //끝일때
                    else if(x > 0 && x < W-1){  
                        bool isEmpty = true;    //버그해결
                        for(int i = 0; i < snake1.getbodyLength(); i++){
                            if(snake1.getBody(i).x == x && snake1.getBody(i).y == y){
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
    int getscore(){ return score; }
    bool getisalive(){ return isalive; }
    void scoreplusplus(){ score++; }
    void setisalive(bool a){ this->isalive = a; }
    bool isoccupied(int x, int y, snake& snake1, vector<fruit>& fruits){
        //1.머리랑
        if(x == snake1.getheadPos().x && y == snake1.getheadPos().y){ return true; }
        //2.몸통이랑
        for(int i = 0; i < snake1.getbodyLength(); i++){
            if(snake1.getBody(i).x == x && snake1.getBody(i).y == y){ return true; }
        }
        //3.과일들
        for(int i = 0; i < fruits.size(); i++){
            if(fruits[i].getfruitPos().x == x && fruits[i].getfruitPos().y == y)
                return true;
        }
        return false;
    }   
    void spawnFruit(fruit& targetfruit, snake& snake1, vector<fruit>& fruits){
        int x, y;
        do{
            x = (rand() % (W-2)) + 1;      
            y = (rand() % (H-2)) + 1;   
            
        }while(isoccupied(x,y,snake1,fruits));
            targetfruit.setfruitpos(x,y);
    }
    void checkeat(snake& snake1, vector<fruit>& fruits){
        for(int i = 0; i < fruits.size(); i++){
            if(fruits[i].getfruitPos().x == snake1.getheadPos().x && fruits[i].getfruitPos().y == snake1.getheadPos().y){
                scoreplusplus();
                snake1.bodyplusplus();
                spawnFruit(fruits[i], snake1, fruits);
            }
        }
    }
    void gameover(snake& snake1){
        if(snake1.selfcollision()){
            isalive = false;
        }
    }

};

int main()
{       
    srand(time(NULL)); 
    
    snake mysnake;
    gamemanager mygame;
    vector<fruit> myfruits;
    for(int i = 0; i < FRUITCOUNT; i++){
        myfruits.push_back(fruit());
        mygame.spawnFruit(myfruits.back(), mysnake, myfruits);
    }

    
    while(mygame.getisalive()){
        
        system("cls");      //콘솔 클리어
        mygame.drawBoard(mysnake,myfruits);
        
        if(_kbhit()){   //사용자입력받기
            mysnake.changedir(_getch());
        }
        mysnake.move();
        mygame.checkeat(mysnake, myfruits);
        
        if(mysnake.getheadPos().x == 0 || mysnake.getheadPos().x == W-1 
        || mysnake.getheadPos().y == 0 || mysnake.getheadPos().y == H-1) //벽만나면죽음!!
            mygame.setisalive(false);
        
        mygame.gameover(mysnake);
            
        Sleep(100);     
    }
        
}