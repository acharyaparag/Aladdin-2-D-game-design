#include "vector2f.h"
#include "aaline.h"
#include "ioManager.h"
#include "clock.h"
#include "viewport.h"

class Hud {
public:
    Hud(unsigned x1,unsigned y1,unsigned x2,unsigned y2);
    void draw() const; 

private:
    unsigned X1;
    unsigned X2;
    unsigned Y1;
    unsigned Y2;
    const IOManager& io;
    SDL_Surface *screen;
    const Uint32 RED;
    Clock& clock;
    const Gamedata* gdata;
  
};


    

