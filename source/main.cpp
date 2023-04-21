// Includes
/// External
#include <engine/externals.h>
/// Engine
#include <engine/engine.h>
/// Game
#include <game/tilemap.h>

// Entry Point
int main(int argc, char* argv[]){
  // Creating an engine
  Engine engine = Engine();
  Tilemap tilemap = Tilemap();

  // Game loop
  while(engine.running){
    // Update
    engine.Update();

    // Clear
    engine.Clear();

    // Game code..
    tilemap.Update();

    // Render code..
    tilemap.Draw();

    // Displaying
    engine.Display();
  }

  // Cleanup
  engine.Delete();
  
  // Quit app
  return 0;
}