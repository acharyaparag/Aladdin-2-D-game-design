#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include<list>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "sprite.h"
#include "world.h"
#include "viewport.h"
#include "multisprite.h"
#include "twowayMultisprite.h"
#include "player.h"
#include "scaledSprite.h"
#include "random.h"
#include "shootingSprite.h"
#include "explodingSprite.h"
#include "shootSprite.h"
#include "shootingMul.h"
#include "health.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
	
  void initOrbVector();

private:
  const bool env;
  const Gamedata* gdata;
  IOManager& io;
  bool printMessage;
  Clock& clock;

  SDL_Surface *screen;
  World worldBack;
  Viewport& viewport;	

  Player player;
  
  int currentOrb;	
  unsigned int orbNo;
  std::vector<Drawable*> sprites;  
  unsigned int spriteNo;
  std::vector<ScaledSprite*> genieScale;
  const unsigned TICK_INTERVAL;
  unsigned nextTime;
 
  void draw() const;
  Manager(const Manager&);
  Manager& operator=(const Manager&); 
  void makeJasmine();
  void update(Uint32);
  int timeLeft();
  void makeGenieScale();
  bool checkNumber(const std::string&) const;

  std::list<Drawable*> orbs;
  std::list<ExplodingSprite*> explodingOrbs;
  int collisionCount; 
  int guardFlag;
  int guard1Flag;

  Health bar;
  };
