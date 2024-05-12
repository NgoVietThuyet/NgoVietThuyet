#ifndef LEVEL_H
#define LEVEL_H
bool level()
{
    SDL_RenderClear(renderer);
    fileImage = "image//imageLevel.png";
    SDL_Texture* standly = loadTexture(fileImage);
    SDL_RenderCopy(renderer, standly, NULL, NULL);
     font = TTF_OpenFont("font ttf//VNI-Hobo.ttf",40);
    Text("EASY" , 250, 160);
    Text("MEDIUM ",225, 270);
    Text("HARD ", 250, 380);
    Text("OK", 250, 500);
    SDL_Event event;

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                    {
                    case SDLK_BACKSPACE:
                        running = false;
                        break;
                    }
            }
            if( event.type == SDL_QUIT)
            {

                quit = false;
                return false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                   if(event.button.x >= 250 and event.button.x <= 350 and event.button.y >= 160 and event.button.y <= 200)
                {
                    Sound("sound//pressSound.Mp3");
                    speed = 100;
                    TextWhite("EASY" , 250, 160);
                    Text("MEDIUM ",225, 270);
                    Text("HARD ", 250, 380);
                }
                 if(event.button.x >= 225 and event.button.x <= 420 and event.button.y >= 270 and event.button.y <= 310)
                {
                    Sound("sound//pressSound.Mp3");
                    speed = 80;
                    Text("EASY" , 250, 160);
                    TextWhite("MEDIUM ",225, 270);
                    Text("HARD ", 250, 380);
                }
                 if(event.button.x >= 250 and event.button.x <= 350 and event.button.y >= 380 and event.button.y <= 420)
                {
                    Sound("sound//pressSound.Mp3");
                    speed = 50;
                    Text("EASY" , 250, 160);
                    Text("MEDIUM ",225, 270);
                    TextWhite("HARD ", 250, 380);
                }
                 if(event.button.x >= 250 and event.button.x <= 300 and event.button.y >= 500 and event.button.y <= 540)
                 {
                    Sound("sound//pressSound.Mp3");
                    running = false;
                 }

            }
        else if( event.type == SDL_MOUSEMOTION)
        {
            cout<<event.motion.x<<" "<<event.motion.y<<endl;
        }
        }
        //SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }
    return true;

}
#endif // LEVEL_H
