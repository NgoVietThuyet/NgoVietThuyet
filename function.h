#ifndef  FUNCTION_H_
#define FUNCTION _H_
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>
#include <iomanip>
using namespace std;
//  các tham số của chương trình
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int step = 1;
const int snake_height = 20;
const int RED = 0;
const int GREEN = 1;
const int YELLOW = 2;
int COUNTER = 1;
int score = 20;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font;
bool quit = true;
char direction = 'r';
SDL_Event e;
int counter = 0;
int counter_time = 0;
int Time = 0;
int stepX = 0, stepY = 0;
int speed = 100;
string fileImage;
//...............................
bool first =false; // kiểm tra là lần chạy đầu tiên
int IntFirst = 0;
struct Rect{
    int x,y;
    int Size;
};
vector<Rect>snake;
Rect smallball;
Rect bigball;

bool initSDL();

SDL_Texture* loadTexture( std::string& path);
SDL_Texture* loadGameOver(const std::string& path);
void StandlyScreen();
bool IsAte(Rect smallball);   // kiểm tra rắn đã ăn vật phẩm chưa
void CreateSnake(); // tạo con rắn ban đầu
Rect PosBall(int counter); // vẽ quả bóng
void closeSDL();  // đóng chương trinh
void drawRect(Rect name, int color); // vẽ các hình vuông
void drawEveryThing();   // vẽ mọi thứ
bool keyboard(bool& running);  // Xử lý sự kiện trên hàng đợi
void Step();     // bước di chuyển
bool die_yourseft();   // khi chết
void handleRun(); // xử lí di chuyển
void SCORE();     // tính điểm
void come_back();// xử lí khi snake ra khỏi khung hình
// đưa ra các dòng chữ trên màn hình
void Text(const string path, int x,int y);
void TextWhite(const string path, int x,int y);
void Sound(string path);  // chèn âm thanh
bool level();
bool Direction ();
bool play();
void handleWhenDie();
int Score = 0;

#endif
