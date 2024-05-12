

#include "function.h"
#include "draw.h"
#include "level.h"
#include "Direction.h"
#include "play.h"
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

   StandlyScreen();


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
SDL_Texture* loadTexture(std::string& path) {
    // Load ảnh từ đường dẫn
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Tạo texture từ surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    // Xóa surface không cần thiết
    SDL_FreeSurface(loadedSurface);


    return texture;
}

void StandlyScreen()
{
    fileImage = "image//standlyImage.png";
    SDL_Texture* standly = loadTexture(fileImage);
    SDL_RenderCopy(renderer, standly, NULL, NULL);
    font = TTF_OpenFont("font ttf//VNI-Hobo.ttf",40);
    Text("LEVEL ", 100, 440);
    Text(" DIRECTION ",340, 440);
    font = TTF_OpenFont("font ttf//VNI-Butlong.ttf",100);
    Text("PLAY ", 120, 150);
    SDL_Event event;

    while (quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
               {
                   quit = false;
               }
            }else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.x >= 100 and event.button.x <= 230 and event.button.y >= 450 and event.button.y <= 500)
                {
                    Sound("sound//pressSound.mp3");
                    quit = level();
                }
                if ( event.button.x >=350 and event.button.x <= 570 and event.button.y >= 450 and event.button.y <= 500 )
                {
                    Sound("sound//pressSound.mp3");
                    quit = Direction();
                }
                if( event.button.x >= 180 and event.button.x <= 450 and event.button.y >= 240 and event.button.y <= 320)
                {
                     Sound("sound//pressSound.mp3");
                    quit = play();
                }
                SDL_RenderCopy(renderer, standly, NULL, NULL);
               font = TTF_OpenFont("font ttf//VNI-Hobo.ttf",40);
               Text("LEVEL ", 100, 440);
               Text(" DIRECTION ",340, 440);
               font = TTF_OpenFont("font ttf//VNI-Butlong.ttf",100);
               Text("PLAY ", 120, 150);
            }

        }
        //SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

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
           Sound("sound//eating sound.MP3");
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
       if( score % 200 == 0)
       {
           speed += 50;
       }
        SDL_Delay(speed);


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
            Rect add =snake[snake.size() - 1];
             snake.push_back(add);
             if( COUNTER % 6 ==0 )
             Score += 30;
             else if( COUNTER  % 9 == 0)
                Score += 40;
             else Score += 20;

             COUNTER ++;
        }
}

void Text(const string path, int x, int y)
{
    SDL_Color textColor = {200,100,100}; // Màu chữ, ở đây là trắng

    SDL_Surface* surface = TTF_RenderText_Solid(font, path.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void TextWhite(const string path, int x, int y)
{
    SDL_Color textColor = {0,0,0}; // Màu chữ, ở đây là trắng

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


        Sound("sound//game over.wav");
        fileImage = "GameOver.png";
        SDL_Texture* gameover = loadTexture(fileImage);
        SDL_Event event;
        bool quit2 = false;

        SDL_RenderClear(renderer);
        font = TTF_OpenFont("font ttf//VNI-Hobo.ttf",40);
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
    font = TTF_OpenFont("font arial//SVN-Arial 3 bold.ttf",40);
    Text("TIME : " + to_string(Time),150,500);

    Text("SCORE : " + to_string(Score),150,450);
    for(int i = 0; i < snake.size(); i++)
     {

         snake[i].Size = 20;
         if( i != 0)
         drawRect(snake[i],GREEN);
         else
         {
              drawRect(snake[i],RED);

         }
     }
     if( COUNTER % 6 == 0)
     {
         drawRect(smallball,GREEN);

     }
     else if( COUNTER % 9 == 0) drawRect(smallball, YELLOW) ;
     else drawRect(smallball,RED);

}
void Sound(string path)
{
    Mix_Music *backgroundMusic = Mix_LoadMUS(path.c_str());
    if (!backgroundMusic) {
        std::cerr << "Shound not file mixer SDL_Error: " << Mix_GetError() << std::endl;

    }
    // Phát âm thanh
    Mix_PlayMusic(backgroundMusic, 0); // -1: Lặp vô hạn, 0: Không lặp, số dương: số lần lặp

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
