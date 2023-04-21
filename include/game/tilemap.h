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

// Classes
class Tilemap{
private:
  // Variables
  std::vector<int> grid_bomb;
  std::vector<int> grid_show;

  // Functions

public:
  // Variables

  // Constructors
  Tilemap();

  // Functions
  void Update();
  void Draw();
};

// End definiton
#endif