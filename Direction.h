#ifndef DIRECTION_H
#define DIRECTION_H
bool Direction()
{
    // push image include direction string

    SDL_RenderClear(renderer);
    fileImage = "image//Direction.png";
    SDL_Texture* standly = loadTexture(fileImage);
    SDL_RenderCopy(renderer, standly, NULL, NULL);
   // string rule = "- To move, the player presses the shortcut keys: “UP”, “DOWN”, “RIGHT”, “LEFT”";
   // TextWhite(rule,0,30);
    SDL_Event event;
    bool running = true;
    while( running)
    {
        while( SDL_PollEvent(&event) != 0)
        {
            if( event.type == SDL_QUIT)
            {

                quit =  false;
                return false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                    {
                    case SDLK_BACKSPACE:
                        running = false;
                        break;
                    }
            }
        }
        SDL_RenderPresent(renderer);
    }
    return true;


}
#endif // DIRECTION_H
