// Define once
#ifndef H_NAVBAR
#define H_NAVBAR

// Includes
/// Externals
#include <engine/externals.h>
/// Engine
#include <engine/engine.h>
/// Game
#include <game/tilemap.h>

// Classes
class Navbar{
private:
  // Variables
  Tilemap* tilemap;

  // Functions
  void _drawBackground();
  void _drawFlagCounter();
  void _drawFace();
  void _drawTime();

public:
  // Variables

  // Constructor
  Navbar(Tilemap* tilemap);

  // Functions
  void Update();
  void Draw();
};

// End definition
#endif