// Define once
#ifndef H_ENGINE
#define H_ENGINE

// Includes
/// External
#include "externals.h"

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