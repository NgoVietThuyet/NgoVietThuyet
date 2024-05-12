#ifndef PLAY_H
#define PLAY_H

bool play()
{

     fileImage = "image//BackGround.png";
    SDL_Texture* background = loadTexture(fileImage);
    if (background == nullptr) {
        std::cerr << "Failed to load background image!" << std::endl;
        closeSDL();

    }
    CreateSnake();
    Rect smallball;
    bool running = true;


    while (running)
    {
       //if(Mix_Playing(-1) != 0) Mix_PlayChannel(-1,sound,0);
        if( keyboard(running) == false)
            return false;
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
            break;
         //   return 0;
        }

      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, background, NULL, NULL);
      drawEveryThing();
      SDL_RenderPresent(renderer);

    }
    return true;
   //SDL_DestroyTexture(background);
}
bool keyboard(bool& running)
{
       while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = false;
               return false;
            }
            // xử lí di chuyển
            else

            if (e.type == SDL_KEYDOWN)
        {
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
                case SDLK_BACKSPACE :
                    {
                        running = false;
                    }

                    break;
            }
        }
        }
        return true;
}
#endif // PLAY_H
