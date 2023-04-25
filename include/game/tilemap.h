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

  int savedClick = 0;
  bool didClick;
  bool gameBegan;

  bool cascading;
  float timepassed;

  // Functions
  void _init();
  void createGrid(Vector2 mousePos);

  int getSurrounding(Vector2 tilePos);
  void revealTiles(Vector2 mousePos);
  void spawnCascade(Vector2 position);

  void _leftClick();
  void _rightClick();

  void winDetection();
  void clickDetection();

public:
  // Variables
  bool playing;
  bool win;
  int flags;
  int gameTime;

  // Constructors
  Tilemap();

  // Functions
  void Update();
  void Draw();

  void Reset();
};

// End definiton
#endif