#include <iostream>
#include <cmath>
#include "bullet.h"
#include "collisionStrategy.h"

extern int flag;

bool Bullet::collidedWith(const Sprite* obj) const {
  return Sprite::collidedWith(obj);
}

void Bullet::update(Uint32 ticks) { 

 Vector2f pos = getPosition();
  Sprite::update(ticks);

 if (name == "apple" and flag == 1)
  {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  velocityX(-abs(velocityX()));
   }
 else if (name == "knife" or name == "knife1")
  {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  velocityX(-abs(velocityX()));
   }
    distance += ( hypot(X()-pos[0], Y()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
} 
