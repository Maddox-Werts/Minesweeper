// Header
#include <game/navbar.h>

// Constructor
Navbar::Navbar(Tilemap* tilemap){
  // Setting variables
  this->tilemap = tilemap;
  didClick = false;

  // Getting texture
  SDL_Surface* surf = IMG_Load("data/glyph.png");
  if(surf == NULL){
    throw("Failed to load Glyph surface.\n");
  }

  texture = SDL_CreateTextureFromSurface(Engine::renderer, surf);
  SDL_FreeSurface(surf);
}

// Functions
/// Private
void Navbar::_drawBackground(){
  // Making a rect for the top
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = SCR_WIDTH;
  rect.h = SCR_H_BUFFER;

  // Color
  SDL_SetRenderDrawColor(Engine::renderer, 190,190,190, 1);
  SDL_RenderFillRect(Engine::renderer, &rect);
}
void Navbar::_drawFlagCounter(){
  if(tilemap->flags < 10){
    // Positional rect
    SDL_Rect rect;
    rect.x = SCR_WIDTH / 10;
    rect.y = 0;
    rect.w = 50; rect.h = 50;

    // Frame
    SDL_Rect frame;
    frame.x = 0; frame.y = 0;
    frame.w = 16; frame.h = 16;

    // What number?
    switch(tilemap->flags){
    case 0:
      frame.x = 0;
      frame.y = 0;
      break;
    case 1:
      frame.x = 1;
      frame.y = 0;
      break;
    case 2:
      frame.x = 2;
      frame.y = 0;
      break;
    case 3:
      frame.x = 3;
      frame.y = 0;
      break;
    case 4:
      frame.x = 4;
      frame.y = 0;
      break;
    case 5:
      frame.x = 0;
      frame.y = 1;
      break;
    case 6:
      frame.x = 1;
      frame.y = 1;
      break;
    case 7:
      frame.x = 2;
      frame.y = 1;
      break;
    case 8:
      frame.x = 3;
      frame.y = 1;
      break;
    case 9:
      frame.x = 4;
      frame.y = 1;
      break;
    }

    // Scaling to size
    frame.x *= 16;
    frame.y *= 16;

    // Drawing
    SDL_SetRenderDrawColor(Engine::renderer, 255,255,255, 1);
    SDL_RenderCopy(Engine::renderer, texture, &frame, &rect);
  }
  else{
    // Positional rect
    SDL_Rect rect;
    rect.x = SCR_WIDTH / 10;
    rect.y = 0;
    rect.w = 50; rect.h = 50;

    // Frame
    SDL_Rect frame;
    frame.x = 0; frame.y = 0;
    frame.w = 16; frame.h = 16;

    Vector2 fPos = _getNumber(tilemap->flags%10);
    frame.x = fPos.x;
    frame.y = fPos.y;

    // Drawing
    SDL_SetRenderDrawColor(Engine::renderer, 255,255,255, 1);
    SDL_RenderCopy(Engine::renderer, texture, &frame, &rect);

    // The second one
    rect.x -= 50;

    fPos = _getNumber((tilemap->flags / 10)%10);
    frame.x = fPos.x;
    frame.y = fPos.y;

    // Drawing
    SDL_SetRenderDrawColor(Engine::renderer, 255,255,255, 1);
    SDL_RenderCopy(Engine::renderer, texture, &frame, &rect);
  }
}
void Navbar::_drawFace(){
  // Shapes
  SDL_Rect rect;
  SDL_Rect frame;

  rect.x = (SCR_WIDTH / 2) - (25);
  rect.y = 0;
  rect.w = 50; rect.h = 50;

  frame.w = 16;
  frame.h = 16;

  // This face is gonna be weird to draw..
  if(Engine::clicking){
    // Anxious face
    frame.x = 1;
    frame.y = 2;
  }
  else if(!tilemap->playing && !tilemap->win){
    // Sad face
    frame.x = 2;
    frame.y = 2;
  }
  else{
    // Happy face
    frame.x = 0;
    frame.y = 2;
  }

  // Scaling to size
  frame.x *= 16;
  frame.y *= 16;

  // Drawing
  SDL_SetRenderDrawColor(Engine::renderer, 255,255,255, 1);
  SDL_RenderCopy(Engine::renderer, texture, &frame, &rect);
}
void Navbar::_drawTime(){
  
}
Vector2 Navbar::_getNumber(int number){
  // Result
  Vector2 frame(0,0);

  // What number?
  switch(number){
  case 0:
    frame.x = 0;
    frame.y = 0;
    break;
  case 1:
    frame.x = 1;
    frame.y = 0;
    break;
  case 2:
    frame.x = 2;
    frame.y = 0;
    break;
  case 3:
    frame.x = 3;
    frame.y = 0;
    break;
  case 4:
    frame.x = 4;
    frame.y = 0;
    break;
  case 5:
    frame.x = 0;
    frame.y = 1;
    break;
  case 6:
    frame.x = 1;
    frame.y = 1;
    break;
  case 7:
    frame.x = 2;
    frame.y = 1;
    break;
  case 8:
    frame.x = 3;
    frame.y = 1;
    break;
  case 9:
    frame.x = 4;
    frame.y = 1;
    break;
  }

  // Scaling to size
  frame.x *= 16;
  frame.y *= 16;

  // Return result
  return frame;
}
/// Public
void Navbar::Update(){
  // Did we click on the face?
  if(Engine::clicking
  && !didClick){
    // Clicking!
    didClick = true;

    // Getting the mouse position
    Vector2 mPos = Engine::mousePos;

    // Constant
    const int mid_w = SCR_WIDTH / 2;

    // Face clicking?
    if(mPos.x >= mid_w - 50
    && mPos.x <= mid_w + 50
    && mPos.y <= SCR_H_BUFFER){
      // Restart game
      tilemap->Reset();
    }
  }
  if(!Engine::clicking){
    didClick = false;
  }
}
void Navbar::Draw(){
  // Drawing stuff in order
  /// Background
  _drawBackground();

  /// Flags counter
  _drawFlagCounter();

  /// Smiley face
  _drawFace();

  /// Time
  _drawTime();
}