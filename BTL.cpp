/*#include <SDL.h>
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
int score = 20;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font;
bool quit = false;
char direction = 'r';
SDL_Event e;
int counter = 0;
int counter_time = 0;
int Time = 0;
int stepX = 0, stepY = 0;
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

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

bool IsAte(Rect smallball);   // kiểm tra rắn đã ăn vật phẩm chưa
void CreateSnake(); // tạo con rắn ban đầu
Rect PosBall(int counter); // vẽ quả bóng
void closeSDL();  // đóng chương trinh
void drawRect(Rect name, bool check); // vẽ các hình vuông
void drawEveryThing();   // vẽ mọi thứ
void keyboard();  // Xử lý sự kiện trên hàng đợi
void Step();     // bước di chuyển
bool die_yourseft();   // khi chết
void handleRun(); // xử lí di chuyển
void SCORE();     // tính điểm
void come_back();// xử lí khi snake ra khỏi khung hình
// đưa ra các dòng chữ trên màn hình
void Text(const string path, int x,int y);
void Sound(string path);  // chèn âm thanh
void handleWhenDie();
int Score = 0;



int main(int argc, char* args[])
{
    // Khởi tạo SDL
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }
    TTF_Init();
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL Mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;

    }
    font = TTF_OpenFont("SVN-Arial 3 bold.ttf",40);
    // Load background
    SDL_Texture* background = loadTexture("BachGround.png",renderer);
    if (background == nullptr) {
        std::cerr << "Failed to load background image!" << std::endl;
        closeSDL();
        return -1;
    }
    CreateSnake();
    Rect smallball;

    while (!quit)
    {
        //Sound("main sound.mp3");
        keyboard();
        Step();
        // tạo ra quả bóng đầu tiên
        if( IntFirst == 0 or first == true )
        {
             smallball = PosBall(counter);
             IntFirst = 1;
        }

       handleRun();
       SCORE();
        if( die_yourseft() == true )
        {
            handleWhenDie();

            return 0;
        }
       SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, background, NULL, NULL);
      drawEveryThing();
      SDL_RenderPresent(renderer);

    }
    // Giải phóng bộ nhớ và thoát
    SDL_DestroyTexture(background);
    closeSDL();
    return 0;
}




bool initSDL() {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo cửa sổ
    window = SDL_CreateWindow("Bai tap lon:                    GAME SNAKE", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_Image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
 {
    // Load ảnh từ đường dẫn
    //SDL_Surface* loadedSurface = IMG_Load("BachGround.png");
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Tạo texture từ surface
     newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }


    // Xóa surface không cần thiết
    SDL_FreeSurface(loadedSurface);


    return newTexture;
}

void drawRect(Rect name,bool check) {
    SDL_Rect square = { name.x*20, name.y*20, name.Size - 1 , name.Size - 1 };
    if( check == true)
    {
        SDL_SetRenderDrawColor(renderer,23,100,2,255);
    }
    else
    SDL_SetRenderDrawColor(renderer, 232,43, 43, 255);
    SDL_RenderFillRect(renderer, &square);
}
void CreateSnake()
{
    for(int i = 3; i >= 1;i--)
    {
        Rect body ;
        body.x = i;
        body.y =0;
        body.Size = 20;
        snake.push_back(body);

    }

}
Rect PosBall(int counter)
{
    srand(time(0));
    if( counter < 5 )
    {
        smallball.x = rand()%(SCREEN_WIDTH / 20);
        for(int i = 0; i < snake.size(); i++)
        {
            if( smallball.x == snake[i].x)
            {
                 smallball.x = rand()%(SCREEN_WIDTH / 20);
            }
        }

        smallball.y = rand()%(SCREEN_HEIGHT - 170)/20;
         for(int i = 0; i < snake.size(); i++)
        {
            if( smallball.y == snake[i].y)
            {
                 smallball.y = rand()%(SCREEN_HEIGHT-170)/ 20;
            }
        }
        smallball.Size = 20;
        return smallball;
    }

}
void keyboard()
{
       while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // xử lí di chuyển
            else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    if (direction != 'r') direction = 'l';
                    break;
                case SDLK_RIGHT:
                    if (direction != 'l') direction = 'r';
                    break;
                case SDLK_UP:
                    if (direction != 'd') direction = 'u';
                    break;
                case SDLK_DOWN:
                    if (direction != 'u') direction = 'd';
                    break;
            }
        }
        }
}
void Step()
{
    stepX = 0;
    stepY = 0;
    switch (direction) {
        case 'r':
            stepX = step;
            break;
        case 'l':
            stepX = -step;
            break;
        case 'u':
            stepY = -step;
            break;
        case 'd':
            stepY = step;
            break;
    }
}
bool IsAte(Rect ball)
{
    if( snake[0].x == ball.x and snake[0].y == ball.y)
       {

          return true;
       }
    return false;
}
bool die_yourseft()
{

    for(int i = 1; i < snake.size(); i++)
    {
        if(snake[0].x == snake[i].x and snake[0].y == snake[i].y)
            return true;
    }
    return false;
}
void come_back()
{
     for(int i = 0; i < snake.size(); i++)
     {
         if( snake[i].x < 0 or snake[i].x*20 + 20 > SCREEN_WIDTH)
         {

             if ( direction == 'r')
             snake[i].x = 0 - i;

             else snake[i].x = 29+ i;
         }
         if( snake[i].y < 0 or snake[i].y*20 + 20 > SCREEN_HEIGHT -150)
         {
             if( direction == 'd') snake[i].y = 0-i;
             else snake[i].y = (SCREEN_HEIGHT-150 - 20)/20  + i;
         }
     }
}
void handleRun()
{
     // xử lí cho snake di chuyển liên tục
        for (int i = snake.size() - 1; i >= 1; i--)
       {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;

       }
       // có thể điều chỉnh chế độ nhanh chậm tại đây
        SDL_Delay(100);


       snake[0].x += stepX;
       snake[0].y += stepY;
       come_back();
}
void SCORE()
{
      first = false;
     if( IsAte(smallball) == true )
        {
            first = true;
            Sound("eating sound.mp3");
            Rect add =snake[snake.size() - 1];
             snake.push_back(add);
             Score += score;

        }

}

void Text(const string path, int x, int y)
{
    SDL_Color textColor = {200,50,50}; // Màu chữ, ở đây là trắng

    SDL_Surface* surface = TTF_RenderText_Solid(font, path.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void handleWhenDie()
{



        Sound("game over.wav");
        SDL_Delay(200);
            SDL_Texture* gameover = loadTexture("GameOver.png",renderer);
            SDL_Event event;
             bool quit2 = false;

               SDL_RenderClear(renderer);
              SDL_RenderCopy(renderer, gameover, NULL, NULL);
            Text("SCORE : " + to_string(Score),180,300);
              Text("Time : " + to_string(Time),180,350);
            SDL_RenderPresent(renderer);
             while(!quit2)
             {
                   while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit2 = true;
            }
              }
             }
}
void drawEveryThing()
{
      counter_time ++;

        if( counter_time == 10)
        {
            Time++;

            counter_time = 0;
        }
      Text("TIME : " + to_string(Time),150,500);

      Text("SCORE : " + to_string(Score),150,450);
     for(int i = 0; i < snake.size(); i++)
     {



         if( i != 0)

         drawRect(snake[i],true);
         else
         {
            //  SDL_Texture* texture = loadTexture("headerSnake.png",renderer);

             //SDL_RenderCopy(renderer,texture, NULL,&character);
              drawRect(snake[i],false);

         }
     }
        drawRect(smallball,false);

}
void Sound(string path)
{


    // Load âm thanh từ tệp
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr) {
        std::cerr << "Failed to load sound! SDL_mixer Error: " << Mix_GetError() << std::endl;

    }
    // Phát âm thanh
    Mix_PlayChannel(-1, sound, 0);
    // Đợi cho đến khi âm thanh kết thúc
    //while (Mix_Playing(-1) != 0) {
       // SDL_Delay(100); // Delay để không chiếm quá nhiều tài nguyên CPU

   // }

    // Giải phóng bộ nhớ cho âm thanh
  //  Mix_FreeChunk(sound);

    // Đóng SDL Mixer
  //  Mix_CloseAudio();

}
void closeSDL() {
    // Hủy renderer
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    // Hủy cửa sổ
    SDL_DestroyWindow(window);
    window = nullptr;

    // Đóng SDL_Image
    IMG_Quit();

    // Đóng SDL
    SDL_Quit();
}
*/
