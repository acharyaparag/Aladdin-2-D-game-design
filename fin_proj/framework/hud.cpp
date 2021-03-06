
#include "hud.h"
#include "gamedata.h"

Hud::Hud(unsigned x1,unsigned y1,unsigned x2,unsigned y2):
 X1(x1),
 X2(x2),
 Y1(y1),
 Y2(y2),
 io( IOManager::getInstance()),
 screen(io.getScreen()),
 RED(SDL_MapRGB(screen->format, 0xff, 0, 0)),
 clock( Clock::getInstance()),
 gdata( Gamedata::getInstance())

  { 
     draw();
  }

void Hud::draw() const {

     Draw_AALine(screen, X1,Y1, X2,Y1, RED);
     Draw_AALine(screen, X1,Y1, X1,Y2, RED);
     Draw_AALine(screen, X1,Y2, X2,Y2, RED);
     Draw_AALine(screen, X2,Y1, X2,Y2, RED);
     
     io.printMessageValueAt("FPS: ", clock.getFps(), X1+5, Y1+5);
     io.printMessageAt(gdata->getXmlStr("infoRight"),X1+5,Y1+20);
     io.printMessageAt(gdata->getXmlStr("infoLeft"),X1+5,Y1+40);
  
}




