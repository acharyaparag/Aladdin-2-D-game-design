#include <iostream>
#include <cmath>
#include "changeSprite.h"
#include "gamedata.h"
#include <limits>
#include "frameFactory.h"
using std::cout; using std::endl;

ChangeSprite::ChangeSprite(const std::string& name, const Frame* fm) :
  Sprite(name, fm),
  frameWidth(fm->getWidth()),
  frameHeight(fm->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  acceleration( getVelocity().normalize() * Gamedata::getInstance()->getXmlInt("mulFactor") ),
  withVelocity(1.0)
{ }

ChangeSprite::ChangeSprite(const string& name):
  Sprite(name),
  frameWidth(FrameFactory::getInstance().getFrame(name)->getWidth()),
  frameHeight(FrameFactory::getInstance().getFrame(name)->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  acceleration( getVelocity().normalize() * Gamedata::getInstance()->getXmlInt("mulFactor")),
  withVelocity(1.0)
{ }


ChangeSprite::ChangeSprite(const ChangeSprite& s) :
  Sprite(s),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  acceleration(s.acceleration),
  withVelocity(s.withVelocity)
{ }

ChangeSprite& ChangeSprite::operator=(const ChangeSprite& rhs) {
  setName( rhs.getName() );
  setPosition( rhs.getPosition() );
  setVelocity( rhs.getVelocity() );
  setFrame( rhs.getFrame() );
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = Gamedata::getInstance()->getXmlInt("worldWidth");
  worldHeight = Gamedata::getInstance()->getXmlInt("worldHeight");
  acceleration= rhs.acceleration;
  withVelocity = rhs.withVelocity;
  return *this;
}

void ChangeSprite::update(Uint32 ticks) { 

  Sprite::update(ticks);
  
  // Dr. Levine Approach:
  // And now we will do the 1/2 gt^2 part:
  float time = static_cast<float>(ticks) * 0.001;
  //update the position based on acceleration 
  setPosition(getPosition() + 0.5*time*time*acceleration);
 
  //decide if we bounced
  if ( Y() < 0) {
    acceleration[1] = withVelocity * abs( acceleration[1] ) ;
  }
  if ( Y() > worldHeight-frameHeight ) {
    acceleration[1] = withVelocity * -abs( acceleration[1] ) ;
  }
  if ( X() < 0) {
    acceleration[0] = withVelocity * abs( acceleration[0] ) ;
  }
  if ( X() > worldWidth-frameWidth ) {
    acceleration[0] = withVelocity * -abs( acceleration[0] ) ;
  } 

  //update the velocity based on acceleration
  setVelocity(getVelocity() + time*acceleration );

  //slow down or speed up
  if ( getVelocity().magnitude() > Gamedata::getInstance()->getXmlInt("upperLimit") ||
       getVelocity().magnitude() < Gamedata::getInstance()->getXmlInt("lowerLimit")) {
    acceleration = -1.0 * acceleration;
    withVelocity = -1.0 * withVelocity;
  }
}

