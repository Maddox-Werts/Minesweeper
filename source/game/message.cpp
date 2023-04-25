// Header
#include <game/message.h>

// Constructors
Message::Message(const char* msg){
    // Loading fonts
    TTF_Font* font = TTF_OpenFont("data/fonts/font.ttf", 64);
    if(font == NULL){
        throw("Failed to load font.\n");
    }

    // Surface to texture
    SDL_Surface* surf = TTF_RenderText_Blended(font, msg, {255,255,255});
    texture = SDL_CreateTextureFromSurface(Engine::renderer, surf);

    // Variables
    this->x = (SCR_WIDTH/2) - (surf->w / 2);
    this->y = (SCR_HEIGHT/2) - (surf->h / 2);
    this->w = surf->w;
    this->h = surf->h;

    // Cleanup
    SDL_FreeSurface(surf);
}

// Functions
void Message::Update(){

}
void Message::Draw(){
    SDL_SetRenderDrawColor(Engine::renderer, 255,255,255, 1);

    SDL_Rect rect;
    rect.x = x; rect.y = y;
    rect.w = w; rect.h = h;

    SDL_RenderCopy(Engine::renderer, texture, NULL, &rect);
}