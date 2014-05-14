#include "shootingSprite.h"
#include "gamedata.h"
extern int flag;

ShootingSprite::ShootingSprite(const std::string& name,std::vector<Frame*>& fmsLeft,std::vector<Frame*>& fmsRight) :
  TwowayMultiframeSprite("aladdin", fmsLeft, fmsRight),
  bulletName( Gamedata::getInstance()->getXmlStr(name+"Bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance()->getXmlInt(bulletName+"SpeedX") )
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  TwowayMultiframeSprite(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
{ }

ShootingSprite& ShootingSprite::operator=(const ShootingSprite& rhs) {
  setName( rhs.getName() );
  setPosition( rhs.getPosition() );
  setVelocity( rhs.getVelocity() );
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = Gamedata::getInstance()->getXmlInt("worldWidth");
  worldHeight = Gamedata::getInstance()->getXmlInt("worldHeight");
  return *this;
}

void ShootingSprite::shoot() { 
  float x = X()+frameWidth;
  float y = Y()+frameHeight/2;

   if ( flag == 1)
  {
     x = X()-frameWidth/2;
   }

  bullets.shoot( Vector2f(x, y), 
   // Vector2f(minSpeed+velocityX(), velocityY()));
 Vector2f(minSpeed+velocityX(), 0));
}

bool ShootingSprite::collidedWith(const Drawable* obj) const {
  return bullets.collidedWith( obj );
}


void ShootingSprite::draw() const { 
  TwowayMultiframeSprite::draw();
  bullets.draw();
}

void ShootingSprite::update(Uint32 ticks) { 
  TwowayMultiframeSprite::update(ticks);
  bullets.update(ticks);

}

