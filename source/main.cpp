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
#include <game/message.h>

// Entry Point
int main(int argc, char* argv[]){
  // Creating an engine
  Engine engine = Engine();
  Tilemap tilemap = Tilemap();
  Navbar navbar = Navbar(&tilemap);

  // Messages
  Message gameOver("Game Over!");
  Message youWin("You Win!");

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
  
    /// Messages?
    if(!tilemap.playing){
      if(tilemap.win){
        youWin.Draw();
      }
      else{
        gameOver.Draw();
      }
    }

    // Displaying
    engine.Display();
  }

  // Cleanup
  engine.Delete();
  
  // Quit app
  return 0;
}