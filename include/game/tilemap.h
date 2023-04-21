// Define once
#ifndef H_TILEMAP
#define H_TILEMAP

// Includes
/// Externals
#include <engine/externals.h>
/// Engine
#include <engine/engine.h>

// Constants
#define GRID_W 10
#define GRID_H 10
#define GRID_B 10

// Classes
class Tilemap{
private:
  // Variables
  std::vector<int> grid_bomb;
  std::vector<int> grid_flag;
  std::vector<int> grid_show;

  SDL_Texture* texture;
  int flags;

  // Functions
  void createGrid(Vector2 mousePos);

  int getSurrounding(Vector2 tilePos);
  void revealTiles(Vector2 mousePos);

public:
  // Variables
  bool playing;

  // Constructors
  Tilemap();

  // Functions
  void Update();
  void Draw();
};

// End definiton
#endif