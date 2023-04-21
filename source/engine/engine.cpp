// Header
#include <engine/engine.h>

// Variables
SDL_Renderer* Engine::renderer;
Vector2 Engine::mousePos;
bool Engine::clicking;

// Constructor
Engine::Engine(){
  // Init SDL2
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  // Create a window
  window = SDL_CreateWindow("Minesweeper",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCR_WIDTH, SCR_HEIGHT,
    SDL_WINDOW_SHOWN);
  if(window == NULL){
    throw("Failed to create an SDL window.\n");
  }

  // Create a renderer
  Engine::renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if(Engine::renderer == NULL){
    throw("Failed to create an SDL renderer.\n");
  }

  // Staring SDL2 subsystems
  IMG_Init(IMG_INIT_PNG);

  // We're running!
  running = true;
  clicking  = false;
}

// Functions
void Engine::Update(){
  // Getting events
  SDL_Event event;

  // Window position
  int wx, wy;
  SDL_GetWindowPosition(window, &wx, &wy);

  // Polling
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      running = false;
      break;
    case SDL_MOUSEMOTION:
      Engine::mousePos = Vector2(event.motion.x - wx, event.motion.y - wy);
      break;
    case SDL_MOUSEBUTTONDOWN:
      clicking = true;
      break;
    case SDL_MOUSEBUTTONUP:
      clicking = false;
      break;
    }
  }
}

void Engine::Clear(){
  SDL_SetRenderDrawColor(Engine::renderer, 0,0,0, 1);
  SDL_RenderClear(Engine::renderer);
}
void Engine::Display(){
  SDL_RenderPresent(Engine::renderer);
}

void Engine::Delete(){
  SDL_DestroyRenderer(Engine::renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}