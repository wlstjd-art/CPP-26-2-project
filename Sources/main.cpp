#include <iostream>
#include <conio.h>  //키보드 인풋 함수!
#include <windows.h>    //슬립펑션! 추가하고싶은루프안에 sleep을넣어서 적당한속도로!
#include <ctime>    
#include <vector>   
using namespace std;

const int W = 45; //가로길이
const int H = 25; //세로길이

struct Vector2{
    int x;
    int y;
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

class fruit{
private:
    Vector2 fruitPos;
public:
    fruit(){
        fruitPos = {-1, -1}; 
    }
    void spawnFruit(snake& snake1, fruit& fruit1, const vector<Vector2>& walls){
        bool isCollision;
        do{ 
            isCollision = false;

            fruitPos.x = (rand() % (W-2)) + 1;      
            fruitPos.y = (rand() % (H-2)) + 1;   

            if(fruitPos.x == snake1.getheadPos().x && fruitPos.y == snake1.getheadPos().y){             //생성된 과일위치랑 현재머리위치검사
                isCollision = true; 
            }
            if(fruitPos.x == fruit1.fruitPos.x && fruitPos.y == fruit1.fruitPos.y){         //생성된 과일위치랑 원래있던 과일 위치검사
                isCollision = true;
            }          
            for(int i = 0; i < snake1.getbodyLength(); i++){
                if(fruitPos.x == snake1.getBody(i).x && fruitPos.y == snake1.getBody(i).y)      //생성된 과일위치랑 몸통들위치검사
                    isCollision = true;     
            }
            for(auto& w : walls){           //생성된 과일위치랑 벽 위치 비교,
                if(w.x == fruitPos.x && w.y == fruitPos.y){
                    isCollision = true;
                }
            }
        }while(isCollision);
    }
    Vector2 getfruitPos(){ return fruitPos; }

};

class gamemanager{
private:
    bool isalive;
    int score;
    vector<Vector2> pendingwalls;
    vector<Vector2> walls;
    int speed;
    time_t lastEatTime;
public:
    gamemanager(){
        isalive = true;
        score = 0;
        speed = 100;
        lastEatTime = time(NULL);
    }
    void drawBoard(snake& snake1,fruit& fruit1, fruit& fruit2){   
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
            else if(x == fruit1.getfruitPos().x && y == fruit1.getfruitPos().y){
                cout << 'F';
            }
            else if(x == fruit2.getfruitPos().x && y == fruit2.getfruitPos().y){
                cout << 'F';
            }
            else if(isWallAt(x,y)){     
                cout << '#';        
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
        // cout << "예약된 벽 개수 : " << pendingwalls.size() << endl;
        cout << "속도 : " << speed << endl;
        // cout << "마지막먹은시간 " << lastEatTime << endl;
        int remain = 5 - (time(NULL) - lastEatTime);
        if(remain > 0 && speed != 0)  cout << remain << " 초 안에 안먹으면 빨라집니다!!" << endl;
        else if(remain <= 0) {  //
            if(speed == 0){
                cout << "랜덤으로 벽이 생성됩니다!";
            }
            else if(speed > 0) cout << "가속중";
        }
    }
    int getscore(){ return score; }
    bool getisalive(){ return isalive; }
    void scoreplusplus(){ score++; }
    void setisalive(bool a){ this->isalive = a; }
    void gameover(snake& snake1){
        if(snake1.selfcollision()){
            isalive = false;
        }
        for(auto& w : walls){
            if(w.x == snake1.getheadPos().x &&
               w.y == snake1.getheadPos().y){
                isalive = false;
            }
        }
    }
    void addpendingwall(const Vector2& fruitpos){     // 9-2주차 벡터써보기!
        pendingwalls.push_back(fruitpos); //push_back으로
    }
    void addWall(snake& snake1){
        Vector2 head = snake1.getheadPos();

        for(int i = (int)pendingwalls.size() - 1; i >= 0; i--){
            
            bool isSnakeOnit = false;
            Vector2 a = pendingwalls[i];

            if(a.x == head.x && a.y == head.y){
                isSnakeOnit = true;
            }

            for(int j = 0; j < snake1.getbodyLength(); j++){
                if(snake1.getBody(j).x == a.x && snake1.getBody(j).y == a.y){
                    isSnakeOnit = true;
                    break;
                }
            }
            if(!isSnakeOnit){
                walls.push_back(a);
                pendingwalls.erase(pendingwalls.begin() + i);   //week9 erase_vector.cpp
            }
        }
    }
    bool isWallAt(int x, int y){
        for(int i = 0; i < walls.size(); i++){
            if(walls[i].x == x && walls[i].y == y){
                return true;
            }
        }
        return false;
    }
    void checkEatFruit(snake& mysnake, fruit& eatenFruit, fruit& otherFruit){   //eatenfruit함수화!
        //머리랑 과일이랑 닿았나?
        if(mysnake.getheadPos().x == eatenFruit.getfruitPos().x && 
           mysnake.getheadPos().y == eatenFruit.getfruitPos().y){ 
            lastEatTime = time(NULL);
            scoreplusplus();                           //점수올리기
            mysnake.bodyplusplus();                    //몸통 늘리기
            addpendingwall(eatenFruit.getfruitPos());  //벽 세울자리예약!
            eatenFruit.spawnFruit(mysnake,otherFruit,walls); //이과일만 스폰!
        }
    }
    vector<Vector2> getWalls(){
        return walls;
    }
    int getSpeed(){ return speed; }
    void updateSpeed(){
        if(time(NULL) - lastEatTime >= 5 && speed > 0){ speed -= 2; }
    }
};

int main()
{       
    srand(time(NULL)); 

    snake mysnake;
    fruit myfruit;
    fruit myfruit2;
    gamemanager mygame;

    myfruit.spawnFruit(mysnake,myfruit2,mygame.getWalls());
    myfruit2.spawnFruit(mysnake,myfruit,mygame.getWalls());
    
    while(mygame.getisalive()){
        
        system("cls");      //콘솔 클리어
        mygame.drawBoard(mysnake,myfruit,myfruit2);
        
        if(_kbhit()){   //사용자입력받기
            mysnake.changedir(_getch());
        }
        mysnake.move();
        mygame.addWall(mysnake);

        mygame.checkEatFruit(mysnake,myfruit,myfruit2); 
        mygame.checkEatFruit(mysnake,myfruit2,myfruit); 

        if(mysnake.getheadPos().x == 0 || mysnake.getheadPos().x == W-1 
        || mysnake.getheadPos().y == 0 || mysnake.getheadPos().y == H-1) //벽만나면죽음!!
            mygame.setisalive(false);
        
        mygame.updateSpeed();
        mygame.gameover(mysnake);
        Sleep(mygame.getSpeed());     
    }
        
}