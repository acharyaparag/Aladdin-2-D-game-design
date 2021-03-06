#include "player.h"
#include "ioManager.h"

extern int flag;

Player::~Player() {
  for (unsigned i = 0; i < aladdinFrames.size(); ++i) {
    delete aladdinFrames[i];
    delete aladdinFramesLeft[i];
  }
  SDL_FreeSurface(aladdinSurface);
  delete aladdin;
}

Player::Player() :
  strategy( new MidPointCollisionStrategy ),
  gdata( Gamedata::getInstance() ),
  keyPressed(false),
  worldWidth( gdata->getXmlInt("worldWidth") ), 
  worldHeight( gdata->getXmlInt("worldHeight") ), 
  aladdinInitialVelocity( Vector2f(gdata->getXmlInt("aladdinSpeedX"), 
                               gdata->getXmlInt("aladdinSpeedY") )
  ), 
  aladdinWidth( gdata->getXmlInt("aladdinWidth") ), 
  aladdinHeight( gdata->getXmlInt("aladdinHeight") ),
  aladdinSurface( 
    IOManager::getInstance().loadAndSet(gdata->getXmlStr("aladdinFile"), 
    gdata->getXmlBool("aladdinTransparency") )
  ),
  aladdinFrames(),
  aladdinFramesLeft(),
  aladdin( NULL )
{ 
  makeAladdin();
}

void Player::makeAladdin() {
  unsigned numberOfFrames = gdata->getXmlInt("aladdinFrames");
  Uint16 pwidth = gdata->getXmlInt("aladdinWidth");
  Uint16 pheight = gdata->getXmlInt("aladdinHeight");
  Uint16 srcRightX = gdata->getXmlInt("aladdinRightSrcX");
  Uint16 srcRightY = gdata->getXmlInt("aladdinRightSrcY");
  Uint16 srcLeftY = gdata->getXmlInt("aladdinLeftSrcY");
  Uint16 srcLeftX = gdata->getXmlInt("aladdinLeftSrcX");

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * pwidth + srcRightX;
    aladdinFrames.push_back( 
      new Frame(aladdinSurface, pwidth, pheight, frameX, srcRightY) );
  }

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * pwidth + srcLeftX;
    aladdinFramesLeft.push_back( 
      new Frame(aladdinSurface, pwidth, pheight, frameX, srcLeftY) );
  }
aladdin = new ShootingSprite("aladdin", aladdinFramesLeft, aladdinFrames);
}

void Player::update(Uint32 ticks) { 
  aladdin->update(ticks); 
  if (!keyPressed ) stop();
  keyPressed = false;
}

void Player::stop() { 
  aladdin->velocityX(0);  
  //aladdin->velocityY(0);  
}

void Player::right() { 
  flag = 0;
  keyPressed = true;
  if ( aladdin->X() < worldWidth-aladdinWidth) {
    aladdin->velocityX(aladdinInitialVelocity[0]);
  }
} 
void Player::left()  { 
  keyPressed = true;
  flag = 1;
  if ( aladdin->X() > 0) {
    aladdin->velocityX(-aladdinInitialVelocity[0]);
  }
} 
void Player::up()    { 
 //keyPressed = true;
  /*if ( aladdin->Y() < Gamedata::getInstance()->getXmlInt("aladdinMinY") ) {
    aladdin->velocityY( abs( aladdin->velocityY() ) );
  }
  else {
    aladdin->velocityY(-aladdinInitialVelocity[0]);

  }*/
  if(!aladdin->velocityY())
    aladdin->velocityY(-500);
    
} 
void Player::down()  { 
  /*keyPressed = true;
  if ( aladdin->Y() < worldHeight-aladdinHeight) {
    aladdin->velocityY(aladdinInitialVelocity[0]);
  }*/
}

void Player::shoot() { 
  aladdin->shoot();
}

bool Player::collidedWith(const Drawable* obj) const {
   return aladdin->collidedWith(obj);
}
 
bool Player::collideSelf(const Drawable* obj) const {
  const Drawable* aladdincoll = static_cast<Drawable*>(aladdin);
  return strategy->execute(*aladdincoll,*obj);
   }
