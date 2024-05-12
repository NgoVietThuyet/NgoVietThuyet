
#ifndef DRAW_H
#define DRAW_H
void drawRect(Rect name,int color) {
    SDL_Rect square = { name.x*20, name.y*20, name.Size - 1 , name.Size - 1 };
    if( color == RED )
    {
        SDL_SetRenderDrawColor(renderer, 232,43, 43, 255);
    }
    else if( color == GREEN)
    SDL_SetRenderDrawColor(renderer, 0,255,0, 255);
    if( color == YELLOW)
    SDL_SetRenderDrawColor(renderer, 255,255,0, 255);
    SDL_RenderFillRect(renderer, &square);
}
// Hàm vẽ hình tròn
void ve_hinh_tron(SDL_Renderer* renderer, int ban_kinh, Rect name) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu trắng
    for (int i = 0; i <= ban_kinh * 2; ++i) {
        for (int j = 0; j <= ban_kinh * 2; ++j) {
            int dx = ban_kinh - i;
            int dy = ban_kinh - j;
            if (dx*dx + dy*dy <= ban_kinh * ban_kinh) {
                SDL_RenderDrawPoint(renderer, 10*(name.x + dx), 10*(name.y + dy));
            }
        }
    }
}
#endif // DRAW_H

