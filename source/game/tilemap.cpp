// Header
#include <game/tilemap.h>

// Constructors
Tilemap::Tilemap(){
  _init();
}

// Functions
/// Private
void Tilemap::_init(){
  // Reset all of our grids
  grid_bomb.clear();
  grid_flag.clear();
  grid_show.clear();

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
  savedClick = 0;
  didClick = true;
  cascading = false;
  win = true;
}
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
  // Result
  int result = 0;

  // Finding surrounding tiles
  for(int y = -1; y < 2; y++){
    for(int x = -1; x < 2; x++){
      // Out of bounds?
      if(tilePos.x + x < 0
      || tilePos.x + x >= GRID_W
      || tilePos.y + y < 0
      || tilePos.y + y >= GRID_H){
        continue;
      }

      // Otherwise good to go!
      result += grid_bomb[(y+tilePos.y)*GRID_H+(x+tilePos.x)];
    }
  }

  // Return result
  return result;
}
void Tilemap::revealTiles(Vector2 mousePos){
  // What's the mouse position
  int _gridPos = mousePos.y*GRID_H+mousePos.x;
  printf("Grid Position: %i\n", _gridPos);  // Debug

  // Was it a flag?
  if(grid_flag[_gridPos]) {return;}

  // Setting the grid position to VISIBLE
  grid_show[_gridPos] = 1;

  // Rippling
  cascading = true;
  while(cascading){
    spawnCascade(mousePos);
  }

  // Clicked on a bomb?
  // TODO: Add game over functionality
  if(grid_bomb[_gridPos]){
    win = false;
    playing = false;
  }
}
void Tilemap::spawnCascade(Vector2 position){
  // For clicking on a tile with a bomb next to it, 
  // it gets annoying when it clears everything
  // when you're trying to click on a tile right next
  // to the bomb.
  if(getSurrounding(position) != 0){
    cascading = false;
    return;
  }

  // Checking if there is a bomb near the current tile
  // And duplication
  for(int y = -1; y < 2; y++){
    for(int x = -1; x < 2; x++){
      // Checking for failure cases
      if(x == 0 && y == 0){
        // Center
        continue;
      }
      if(x + position.x < 0 || x + position.x > GRID_W
      || y + position.y < 0 || y + position.y > GRID_H){
        // Out of bounds
        continue;
      }

      // Diagonal
      if(x == -1 && y == -1
      && x == -1 && y == +1
      && x == +1 && y == +1
      && x == +1 && y == -1){
        continue;
      }

      // Flag near?
      if(grid_flag[(position.y+y)*GRID_W+(position.x+x)]){
        continue;
      }

      // Bombs near?
      if(getSurrounding(position + Vector2(x,y)) != 0){
        grid_show[(position.y+y)*GRID_W+(position.x+x)] = 1;
        continue;
      }

      // Duplication
      if(!grid_show[(position.y+y)*GRID_W+(position.x+x)]
      && !grid_bomb[(position.y+y)*GRID_W+(position.x+x)]){
        grid_show[(position.y+y)*GRID_W+(position.x+x)] = 1;
        spawnCascade(Vector2(position.x + x, position.y + y));
      }
    }
  }

  // Checking for a failure
  for(int y = -1; y < 2; y++){
    for(int x = -1; x < 2; x++){
      // Checking for failure cases
      if(x == 0 && y == 0){
        // Center
        continue;
      }
      if(x + position.x < 0 || x + position.x > GRID_W
      || y + position.y < 0 || y + position.y > GRID_H){
        // Out of bounds
        continue;
      }

      // Checking if there is a space that needs to be filled
      if(!grid_show[(position.y+y)*GRID_W+(position.x+x)]
      && !grid_bomb[(position.y+y)*GRID_W+(position.x+x)]){
        return;
      }
    }
  }

  // Failing
  cascading = false;
}
void Tilemap::_leftClick(){
  // Convert mouse position into local grid position
    Vector2 _mGridPos = Vector2(
    floor(Engine::mousePos.x / (SCR_WIDTH / GRID_W)),
    floor(
      (Engine::mousePos.y + SCR_H_BUFFER) / ((SCR_HEIGHT - SCR_H_BUFFER) / GRID_H)) 
      - ((SCR_H_BUFFER / ((SCR_HEIGHT - SCR_H_BUFFER) / GRID_H)) + 2)
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
void Tilemap::_rightClick(){
  // Convert mouse position into local grid position
  Vector2 _mGridPos = Vector2(
    floor(Engine::mousePos.x / (SCR_WIDTH / GRID_W)),
    floor(
      (Engine::mousePos.y + SCR_H_BUFFER) / ((SCR_HEIGHT - SCR_H_BUFFER) / GRID_H)) 
      - ((SCR_H_BUFFER / ((SCR_HEIGHT - SCR_H_BUFFER) / GRID_H)) + 2)
  );
  int _gridPos = _mGridPos.y*GRID_H+_mGridPos.x;

  // Are we clicking on an existing tile?
  if(grid_show[_gridPos]) {return;}

  // Do we want to add or remove?
  if(grid_flag[_gridPos]){
    // Remove
    flags++;
    grid_flag[_gridPos] = 0;
  }
  else{
    // Add
    if(flags <= 0) {return;}
    flags--;
    grid_flag[_gridPos] = 1;
  }
}
void Tilemap::clickDetection(){
  // Are we even playing?
  if(!playing) {return;}

  // Left clicking
  if(!didClick
  && Engine::clicking == 1){
    // One click at a time!
    savedClick = 1;
    didClick = true;
  }
  // Right clicking
  else if(!didClick
  && Engine::clicking == 2){
    // One click at a time!
    savedClick = 2;
    didClick = true;

    // Right click
    _rightClick();
  }
  // Allow new click (LEFT)
  else if(didClick
  && savedClick == 1
  && Engine::clicking == 0){
    // Allow new click
    didClick = false;

    // Left click
    _leftClick();
    
    savedClick = 0;
  }
  else if(didClick
  && Engine::clicking == 0){
    didClick = false;
    savedClick = 0;
  }
}

/// Public
void Tilemap::Update(){
  // Click detection
  clickDetection();
}
void Tilemap::Draw(){
  // Getting sizes
  int tileWidth = (int)(SCR_WIDTH / GRID_W);
  int tileHeight = (int)((SCR_HEIGHT - SCR_H_BUFFER) / GRID_H);

  // Going through all tiles
  for(int y = 0; y < GRID_H; y++){
    for(int x = 0; x < GRID_W; x++){
      // Global Tile
      SDL_Rect rect;

      rect.x = x * tileWidth;
      rect.y = (y * tileHeight) + SCR_H_BUFFER;

      rect.w = tileWidth;
      rect.h = tileHeight;

      // Frame
      SDL_Rect frame_rect;
      frame_rect.w = 16;
      frame_rect.h = 16;
      
      int frame = 0;

      // Shown tile, not a bomb
      if(!playing
      && grid_bomb[y*GRID_H+x]){
        frame = 2;
      }
      else if(grid_show[y*GRID_W+x]
      && !grid_bomb[y*GRID_H+x]){
        frame = 0;
      }
      else if(grid_flag[y*GRID_H+x]){
        frame = 1;
      }
      else{
        frame = 3;
      }

      // Setting frame rect
      switch(frame){
      case 0:
        switch(getSurrounding(Vector2(x,y))){
        case 0:
          frame_rect.x = 3;
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
        default:
          printf("Something went very wrong while checking for SURROUNDING.\n");
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
      default:
        printf("TILESET RENDERING ERROR.\n");
        break;
      }

      // Multiplying
      frame_rect.x *= 16;
      frame_rect.y *= 16;

      // Drawing
      SDL_SetRenderDrawColor(Engine::renderer, 255, 255,255, 1);
      SDL_RenderFillRect(Engine::renderer, &rect);

      SDL_RenderCopy(Engine::renderer, texture, &frame_rect, &rect);
    }
  }

  // DEBUG
}

void Tilemap::Reset(){
  // Resetting the game! (VERY DIFFICULT)
  printf("Reset.\n");

  // Reset!
  _init();
}