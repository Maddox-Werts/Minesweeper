// Header
#include <game/tilemap.h>

// Constructors
Tilemap::Tilemap(){
  // Adding all tiles to the map
  for(int y = 0; y < GRID_H; y++){
    for(int x = 0; x < GRID_W; x++){
      grid_bomb.push_back(0);
      grid_flag.push_back(0);
      grid_show.push_back(0);
    }
  }

  // Loading texture
  SDL_Surface* surf = IMG_Load("data/tileset.png");
  if(surf == NULL){
    printf("ERROR: %s\n", IMG_GetError());
    throw("Failed to load tiles.\n");
  }

  texture = SDL_CreateTextureFromSurface(Engine::renderer, surf);
  SDL_FreeSurface(surf);

  // Variables
  playing = true;
  flags = GRID_B;
}

// Functions
/// Private
void Tilemap::createGrid(Vector2 mousePos){
  for(int i = 0; i < GRID_B; i++){
    // Completly random number
    srand(time(NULL));

    // Placeholder position
    Vector2 _bombPos = Vector2(0,0);

    // Loop!
    while(true){
      _bombPos = Vector2(
        floor(rand() % GRID_W),
        floor(rand() % GRID_H)
      );

      if(!grid_bomb[_bombPos.y*GRID_H+_bombPos.x]
      && _bombPos.x != mousePos.x
      && _bombPos.y != mousePos.y){
        break;
      }
    }

    // Apply position
    grid_bomb[_bombPos.y*GRID_H+_bombPos.x] = 1;
  }
}
int Tilemap::getSurrounding(Vector2 tilePos){

}
void Tilemap::revealTiles(Vector2 mousePos){
  // What's the mouse position
  int _gridPos = ((int)(mousePos.y))*GRID_H+((int)(mousePos.x));

  // Flag present?
  if(grid_flag[_gridPos]) {return;}

  // Show the current tile
  grid_show[_gridPos] = 1;
}

/// Public
void Tilemap::Update(){
  // Clicking?
  if(!Engine::clicking) {return;}

  // Convert mouse position into local grid position
  Vector2 _mGridPos = Vector2(
    floor(Engine::mousePos.x / (SCR_WIDTH / GRID_W)),
    floor(Engine::mousePos.y / (SCR_HEIGHT / GRID_H))
  );

  // Do we need a new grid?
  int _totalBombs = 0;
  for(int i = 0; i < grid_bomb.size(); i++){
    _totalBombs += grid_bomb[i];
  }

  if(_totalBombs == 0){
    createGrid(_mGridPos);
  }

  // Reveal the tiles!
  revealTiles(_mGridPos);
}
void Tilemap::Draw(){
  // Getting sizes
  int tileWidth = (int)(SCR_WIDTH / GRID_W);
  int tileHeight = (int)(SCR_HEIGHT / GRID_H);

  // Going through all tiles
  for(int y = 0; y < GRID_H; y++){
    for(int x = 0; x < GRID_W; x++){
      // Global Tile
      SDL_Rect rect;

      rect.x = x * tileWidth;
      rect.y = y * tileHeight;

      rect.w = tileWidth;
      rect.h = tileHeight;

      // Frame
      SDL_Rect frame_rect;
      frame_rect.w = 16;
      frame_rect.h = 16;
      
      int frame = 0;

      // Shown tile, not a bomb
      if(grid_show[y*GRID_W+x]
      && !grid_bomb[y*GRID_H+x]){
        frame = 0;
      }
      else if(grid_flag[y*GRID_H+x]){
        frame = 1;
      }
      else if(!playing
      && grid_bomb[y*GRID_H+x]){
        frame = 2;
      }
      else{
        frame = 3;
      }

      // Setting frame rect
      switch(frame){
      case 0:
        switch(getSurrounding(Vector2(x,y))){
        case 0:
          frame_rect.x = 3 * 16;
          frame_rect.y = 0;
          break;
        case 1:
          frame_rect.x = 0;
          frame_rect.y = 1;
          break;
        case 2:
          frame_rect.x = 1;
          frame_rect.y = 1;
          break;
        case 3:
          frame_rect.x = 2;
          frame_rect.y = 1;
          break;
        case 4:
          frame_rect.x = 3;
          frame_rect.y = 1;
          break;
        case 5:
          frame_rect.x = 0;
          frame_rect.y = 2;
          break;
        case 6:
          frame_rect.x = 1;
          frame_rect.y = 2;
          break;
        case 7:
          frame_rect.x = 2;
          frame_rect.y = 2;
          break;
        case 8:
          frame_rect.x = 3;
          frame_rect.y = 2;
          break;
        }
        break;
      case 1:
        frame_rect.x = 1;
        frame_rect.y = 0;
        break;
      case 2:
        frame_rect.x = 2;
        frame_rect.y = 0;
        break;
      case 3:
        frame_rect.x = 0;
        frame_rect.y = 0;
        break;
      }

      // Drawing
      SDL_SetRenderDrawColor(Engine::renderer, 255, 255,255, 1);
      SDL_RenderFillRect(Engine::renderer, &rect);

      SDL_RenderCopy(Engine::renderer, texture, &frame_rect, &rect);
    }
  }
}