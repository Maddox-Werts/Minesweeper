// For windows
#define SDL_MAIN_HANDLED

// Includes
/// External
#include <engine/externals.h>
/// Engine
#include <engine/engine.h>
/// Game
#include <game/tilemap.h>
#include <game/navbar.h>

// Entry Point
int main(int argc, char* argv[]){
  // Creating an engine
  Engine engine = Engine();
  Tilemap tilemap = Tilemap();
  Navbar navbar = Navbar(&tilemap);

  // Game loop
  while(engine.running){
    // Update
    engine.Update();

    // Clear
    engine.Clear();

    // Game code..
    tilemap.Update();
    navbar.Update();

    // Render code..
    tilemap.Draw();
    navbar.Draw();

    // Displaying
    engine.Display();
  }

  // Cleanup
  engine.Delete();
  
  // Quit app
  return 0;
}