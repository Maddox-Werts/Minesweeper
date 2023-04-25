// Define once
#ifndef H_MESSAGE
#define H_MESSAGE

// Includes
/// Externals
#include <engine/externals.h>
/// Engine
#include <engine/engine.h>
/// Game
#include "tilemap.h"

// Classes
class Message{
private:
    // Variables
    SDL_Texture* texture;

    int x,y;
    int w,h;

public:
    // Variables

    // Constructors
    Message(const char* msg);

    // Functions
    void Update();
    void Draw();
};

// End definition
#endif