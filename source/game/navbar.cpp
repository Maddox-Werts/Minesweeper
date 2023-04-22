// Header
#include <game/navbar.h>

// Constructor
Navbar::Navbar(Tilemap* tilemap){
  // Setting variables
  this->tilemap = tilemap;
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

}
void Navbar::_drawFace(){

}
void Navbar::_drawTime(){
  
}
/// Public
void Navbar::Update(){

}
void Navbar::Draw(){
  // Drawing stuff in order
  /// Background
  _drawBackground();

  /// Flags counter

  /// Smiley face

  /// Time
}