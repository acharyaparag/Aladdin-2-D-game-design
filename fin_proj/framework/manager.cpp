#include <cmath>
#include <algorithm>
#include "manager.h"
#include "frameFactory.h"
#include "changeSprite.h"
#include "hud.h"
#include "vecSort.h"
#include "sound.h"
  SDL_Event event;
    SDLSound sound;

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.

  for (unsigned i = 0 ; i< sprites.size() ; i++)
     {  
       delete sprites[i];
     }

  for (unsigned i = 0 ; i< genieScale.size() ; i++)
     {  
       delete genieScale[i];
     }

  std::list<ExplodingSprite*>::iterator expIt=explodingOrbs.begin();
  while ( expIt != explodingOrbs.end() ) {
    delete *expIt;
    ++expIt;
  }
  std::list<Drawable*>::iterator it=orbs.begin();
  while ( it != orbs.end() ) {
    delete *it;
    ++it;
  }

  delete Gamedata::getInstance();

}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  printMessage(false),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  worldBack(FrameFactory::getInstance().getFrame("back")),
  viewport(Viewport::getInstance()),
  player(),
  currentOrb(0),
  orbNo(gdata->getXmlInt("noOfGenie")),
  sprites(),
  spriteNo(gdata->getXmlInt("noOfSprite")),
  genieScale(),
  TICK_INTERVAL( 1*1000/gdata->getXmlInt("fps") ),
  nextTime(0),
  orbs(),
  explodingOrbs(),
  collisionCount(0),
  guardFlag(0) ,
  guard1Flag(0),
  bar() 
  {

   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }


  sprites.reserve(spriteNo);
  viewport.setObjectToTrack(player.getSprite());
  makeJasmine();
  makeGenieScale();
  atexit(SDL_Quit);
  orbs.push_back(new ShootingMul("guard"));
  orbs.push_back(new ShootingMul("guard1"));
  orbs.push_back(new MultiframeSprite("carpet")); 
  }


void Manager::makeJasmine() {
  sprites.push_back( new TwowayMultiframeSprite("jasmine"));
  currentOrb = sprites.size()-1;
  viewport.setObjectToTrack(sprites[currentOrb]);
  sprites.push_back( new MultiframeSprite("peddler"));
}
 
 
void Manager::makeGenieScale() {

  float up =  gdata->getXmlFloat("upperScale");
  float low =  gdata->getXmlFloat("lowerScale");
  unsigned numberOfGenieScale = gdata->getXmlInt("noOfGenie");
  genieScale.reserve( numberOfGenieScale );
  for (unsigned i = 0; i < numberOfGenieScale; ++i) {
    double scale = static_cast<double>(getRandFloat(low,up));
    genieScale.push_back(new ScaledSprite("genie", scale) );
  }
  sort(genieScale.begin(), genieScale.end(),Less());
   
}


void Manager::draw() const
{
 worldBack.draw();
 viewport.draw();
 io.printMessageCenteredAt(gdata->getXmlStr("captionTitle1"),gdata->getXmlInt("captionY1"));
 if (printMessage) 
{
      Hud(gdata->getXmlInt("hudSrcX1"),gdata->getXmlInt("hudSrcY1"),gdata->getXmlInt("hudSrcX2"),gdata->getXmlInt("hudSrcY2"));
}

 
 for( unsigned i = 0;i<sprites.size();i++)
    {
     sprites[i]->draw();
    }
 player.draw();
 
 for (unsigned i = 0; i < genieScale.size(); ++i) 
    {
    genieScale[i]->draw();
    }  

    std::list<ExplodingSprite*>::const_iterator expIt=explodingOrbs.begin();
  while ( expIt != explodingOrbs.end() ) {
    (*expIt)->draw();
    ++expIt;
  }
  std::list<Drawable*>::const_iterator it = orbs.begin();
  while ( it != orbs.end() ) {
    (*it)->draw();
    ++it;
  }
  bar.draw();

}

void Manager::update(Uint32 ticks)
{
 worldBack.update();
 for (unsigned i = 0 ; i< sprites.size();i++)
     {
       sprites[i]->update(ticks);
     }

 player.update(ticks);
 for (unsigned i = 0; i < genieScale.size(); ++i) 
  {
    genieScale[i]->update(ticks);
  }

std::list<ExplodingSprite*>::iterator expIt=explodingOrbs.begin();
  while ( expIt != explodingOrbs.end() ) {
    (*expIt)->update(ticks);
    ++expIt;
  }
  std::list<Drawable*>::iterator it = orbs.begin();
  while ( it != orbs.end() ) {
    ShootingMul* sprite = dynamic_cast<ShootingMul*>(*it);
    if (sprite && sprite->getCurrentFrame() == (unsigned)gdata->getXmlInt("guardFrame") && guardFlag == 0)
        {
      
          guardFlag = 1;
          sprite->update(ticks);
          sprite->shoot();
         }
    else if (sprite && sprite->getCurrentFrame() == (unsigned)gdata->getXmlInt("guard1Frame") && guard1Flag == 0)
        {
      
          guard1Flag = 1;
          sprite->update(ticks);
          sprite->shoot();
         }
    else 
         {
          (*it)->update(ticks);
         }
   if ( player.collideSelf(*it) ) {
      bar.update(ticks);
    }

   if ( player.collidedWith(*it) ) {
      explodingOrbs.push_back(new ExplodingSprite(*it));
      delete *it;
      it = orbs.erase(it);
      ++collisionCount;
    }
    else ++it;

  }
    
  viewport.update();
}

 
void Manager::play() {
 
  SDL_Event event;
  bool done = false;
  bool keyCatch = false;
  SDLSound sound;
  std::string msg("Type your selection <return>: ");
  while ( ! done ) {

      draw();
      SDL_Flip(screen);
      ++clock; 
      Uint32 ticks = clock.getElapsedTicks();
      if ( guardFlag == 1 or guard1Flag == 1) 
         {
          sound[1];
         }
      guardFlag = 0;
      guard1Flag = 0;
      update(ticks);
      if (nextTime > SDL_GetTicks()) 
      SDL_Delay(nextTime - SDL_GetTicks());
      nextTime = SDL_GetTicks() +  TICK_INTERVAL;
       
    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) { keyCatch = false; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_t      :{
          if (!keyCatch)
           {
             keyCatch = true;
              if (viewport.getObjectToTrack()->getName() == "aladdin")
                 {
                     currentOrb = (currentOrb + 1) % sprites.size(); 
                     viewport.setObjectToTrack(sprites[currentOrb]);
                 }
              else
                 {
                
                  viewport.setObjectToTrack(player.getSprite());
                 }   
               }
           break;
                          } 
        case SDLK_p      : {
          if (!keyCatch) 
          {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
                           }

        case SDLK_F1     :{
          if(!keyCatch)
          {
            keyCatch = true;             
            printMessage = !printMessage;           
          }
          break;
                          }

         case SDLK_SPACE     :{
          if(!keyCatch)
          {
             keyCatch = true;
             player.shoot();
             io.clearString();
             io.buildString(event);
             sound[0];
          }
                break;
                               }  
 
        default          : break;
      }
    }
     if (keystate[SDLK_LEFT])
       {
         player.left();
       }
     if (keystate[SDLK_RIGHT]) 
       {
      player.right();
       }
     if (keystate[SDLK_UP]) 
       {
    //  keyCatch = true;
      player.up();
       }

  }
}
