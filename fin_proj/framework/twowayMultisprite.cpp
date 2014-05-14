#include <iostream>
#include <cmath>
#include "twowayMultisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void TwowayMultiframeSprite::advanceFrame(Uint32 ticks) {
  float ms = 1000.0/frameInterval;
  dt += ticks;
  int df = dt / ms;
  dt -= df * ms;
  currentFrame = (currentFrame + df) % numberOfFrames;
}

TwowayMultiframeSprite::TwowayMultiframeSprite( const std::string& name, 
                  std::vector<Frame*> & fmsLeft,
                  std::vector<Frame*> & fmsRight) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance()->getXmlInt(name+"SpeedY"))
           ),
  framesLeft(fmsLeft),
  framesRight(fmsRight),
  frames(fmsRight),
  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance()->getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance()->getXmlInt(name+"FrameInterval") ),
  frameWidth(framesLeft[0]->getWidth()),
  frameHeight(framesLeft[0]->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  gravity(Gamedata::getInstance()->getXmlInt(name+"Gravity"))
{ }


TwowayMultiframeSprite::TwowayMultiframeSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance()->getXmlInt(name+"SpeedY"))
           ),
  framesLeft(FrameFactory::getInstance().getTwoWayMultiFrameLeft(name)),
  framesRight(FrameFactory::getInstance().getTwoWayMultiFrameRight(name)),
  frames(FrameFactory::getInstance().getTwoWayMultiFrameRight(name)),
  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance()->getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance()->getXmlInt(name+"FrameInterval") ),
  frameWidth(framesLeft[0]->getWidth()),
  frameHeight(framesLeft[0]->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  gravity(Gamedata::getInstance()->getXmlInt(name+"Gravity"))
{ }


TwowayMultiframeSprite::
TwowayMultiframeSprite(const TwowayMultiframeSprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()),
  framesLeft(s.framesLeft),
  framesRight(s.framesRight),
  frames(s.framesRight),
  dt(s.dt),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  gravity(s.gravity)
  { }

void TwowayMultiframeSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void TwowayMultiframeSprite::update(Uint32 ticks) { 
 
 if ( velocityX() != 0 ) {
  advanceFrame(ticks);
  }

  if (getGravity() > 0)
    {
      if (Y() < worldHeight-frameHeight || Y() > 0)
         velocityY( velocityY() + (getGravity() * static_cast<float>(ticks) * 0.1) );
    }	

  if ( Y() < 0) {
    if(getGravity() < 0) {
      velocityY( 0 );
      Y( 0 );
    } else {
      velocityY( abs( velocityY() ) );
    }
  }
  if ( Y() > worldHeight-frameHeight) {
    if(getGravity() > 0) {
      velocityY( 0 );
      Y(worldHeight - frameHeight);
    } else {
      velocityY( -abs( velocityY() ) );
    }
  }

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  

  if ( velocityX() < 0 ) frames = framesLeft;
  if ( velocityX() > 0 ) frames = framesRight;
}

unsigned TwowayMultiframeSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frames[currentFrame]->getSurface()->pixels);
  return pixels[ ( y * frames[currentFrame]->getWidth() ) + x ];
}
