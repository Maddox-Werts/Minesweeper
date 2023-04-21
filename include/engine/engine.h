// Define once
#ifndef H_ENGINE
#define H_ENGINE

// Includes
/// External
#include "externals.h"
/// Engine
#include "vectors.h"

// Constants
#define SCR_WIDTH 512
#define SCR_HEIGHT 512

// Classes
class Engine{
private:
  // Variables
  SDL_Window* window;

public:
  // Variables
  static SDL_Renderer* renderer;
  static Vector2 mousePos;
  static bool clicking;
  bool running;

  // Constructor
  Engine();

  // Functions
  void Update();

  void Clear();
  void Display();
  
  void Delete();
};

// End definition
#endif