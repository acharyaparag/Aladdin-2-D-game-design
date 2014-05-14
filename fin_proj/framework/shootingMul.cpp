#include "shootingMul.h"
#include "gamedata.h"

ShootingMul::ShootingMul(const std::string& name) :
  MultiframeSprite(name),
  bulletName( Gamedata::getInstance()->getXmlStr(name+"Bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance()->getXmlInt(bulletName+"SpeedX") )
{ }

ShootingMul::ShootingMul(const ShootingMul& s) :
  MultiframeSprite(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
{ }

ShootingMul& ShootingMul::operator=(const ShootingMul& rhs) {
  setName( rhs.getName() );
  setPosition( rhs.getPosition() );
  setVelocity( rhs.getVelocity() );
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = Gamedata::getInstance()->getXmlInt("worldWidth");
  worldHeight = Gamedata::getInstance()->getXmlInt("worldHeight");
  return *this;
}

void ShootingMul::shoot() { 
  float x = X()-frameWidth/2;
  float y = Y()+frameHeight/2;

  bullets.shoot( Vector2f(x, y), 
    Vector2f(minSpeed+velocityX(), velocityY()));
}

bool ShootingMul::collidedWith(const Drawable* obj) const {
  return bullets.collidedWith( obj );
}

void ShootingMul::draw() const { 
 MultiframeSprite::draw(); 
 bullets.draw();
}

void ShootingMul::update(Uint32 ticks) { 
  MultiframeSprite::update(ticks);
  bullets.update(ticks);
}

