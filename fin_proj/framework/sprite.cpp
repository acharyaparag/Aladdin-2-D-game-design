#include <iostream>
#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "collisionStrategy.h"

Sprite::~Sprite() { delete strategy; } 

Sprite::Sprite(const std::string& name, const Frame* fm) :
  Drawable(name,
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f( (Gamedata::getInstance()->getXmlInt(name + "SpeedX"))?(rand()%Gamedata::getInstance()->getXmlInt(name+"SpeedX")):0,
                     (Gamedata::getInstance()->getXmlInt(name + "SpeedY"))?(rand()%Gamedata::getInstance()->getXmlInt(name+"SpeedY")):0)
  ), 
  frame(fm),
  strategy( new MidPointCollisionStrategy ),
  frameWidth(fm->getWidth()),
  frameHeight(fm->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite::Sprite(const Vector2f& pos, const Vector2f& vel, 
               const string& n, const Frame* fm) :
  Drawable(n, pos, vel),
  frame(fm),
  strategy( new MidPointCollisionStrategy ),
  frameWidth(fm->getWidth()),
  frameHeight(fm->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite::Sprite(const string& name):
  Drawable(name,
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"),
                    Gamedata::getInstance()->getXmlInt(name+"Y")),
           Vector2f( (Gamedata::getInstance()->getXmlInt(name + "SpeedX"))?(rand()%Gamedata::getInstance()->getXmlInt(name+"SpeedX")):0,
                     (Gamedata::getInstance()->getXmlInt(name + "SpeedY"))?(rand()%Gamedata::getInstance()->getXmlInt(name+"SpeedY")):0)
  ),
  frame(FrameFactory::getInstance().getFrame(name)),
  strategy( new MidPointCollisionStrategy ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  frame(s.frame),
  strategy( new MidPointCollisionStrategy ),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;
  strategy = new MidPointCollisionStrategy;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

bool Sprite::collidedWith(const Sprite* obj) const {
  return strategy->execute(*this, *obj);
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

unsigned Sprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}


int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  float height = static_cast<float>(frame->getHeight());
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > Gamedata::getInstance()->getXmlInt("worldHeight")-height) {
    velocityY( -abs( velocityY() ) );
  }

  float width = static_cast<float>(frame->getWidth());
  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth")-width) {
    velocityX( -abs( velocityX() ) );
  }
 
}
