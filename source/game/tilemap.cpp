// Header
#include <game/tilemap.h>

// Constructors
Tilemap::Tilemap(){
  // Adding all tiles to the map
  for(int y = 0; y < GRID_H; y++){
    for(int x = 0; x < GRID_W; x++){
      grid_bomb.push_back(0);
      grid_show.push_back(0);
    }
  }
}

// Functions
/// Private

/// Public
void Tilemap::Update(){

}
void Tilemap::Draw(){
  // Getting sizes
  int tileWidth = (int)(SCR_WIDTH / GRID_W);
  int tileHeight = (int)(SCR_HEIGHT / GRID_H);

  // Going through all tiles
  for(int y = 0; y < GRID_H; y++){
    for(int x = 0; x < GRID_W; x++){
      SDL_Rect rect;

      rect.x = x * tileWidth;
      rect.y = y * tileHeight;

      rect.w = tileWidth;
      rect.h = tileHeight;

      SDL_SetRenderDrawColor(Engine::renderer, x*25, 255,255, 1);
      SDL_RenderFillRect(Engine::renderer, &rect);
    }
  }
}