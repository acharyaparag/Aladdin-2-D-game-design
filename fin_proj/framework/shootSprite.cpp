#include "shootSprite.h"
#include "gamedata.h"

ShootSprite::ShootSprite(const std::string& name, const Frame* fm) :
  Sprite(name, fm),
  bulletName( Gamedata::getInstance()->getXmlStr(name+"Bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance()->getXmlInt(bulletName+"SpeedX") )
{ }

ShootSprite::ShootSprite(const ShootSprite& s) :
  Sprite(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
{ }

ShootSprite& ShootSprite::operator=(const ShootSprite& rhs) {
  setName( rhs.getName() );
  setPosition( rhs.getPosition() );
  setVelocity( rhs.getVelocity() );
  setFrame( rhs.getFrame() );
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = Gamedata::getInstance()->getXmlInt("worldWidth");
  worldHeight = Gamedata::getInstance()->getXmlInt("worldHeight");
  return *this;
}

void ShootSprite::shoot() { 
  float x = X()+frameWidth;
  float y = Y()+frameHeight/2;
  // I'm not adding minSpeed to y velocity:
 
    bullets.shoot( Vector2f(x, y), 
    Vector2f(minSpeed+velocityX(), velocityY()));
}

bool ShootSprite::collidedWith(const Sprite* obj) const {
  return bullets.collidedWith( obj );
}

void ShootSprite::draw() const { 
  Sprite::draw();
  bullets.draw();
}

void ShootSprite::update(Uint32 ticks) { 
  Sprite::update(ticks);
  bullets.update(ticks);
}

