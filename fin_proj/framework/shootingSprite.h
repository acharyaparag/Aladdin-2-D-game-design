#ifndef SHOOTINGSPRITE__H
#define SHOOTINGSPRITE__H

#include <string>
#include <iostream>
#include "sprite.h"
#include "bullets.h"
#include <vector>
#include "twowayMultisprite.h"

class ShootingSprite : public TwowayMultiframeSprite {
public:
  ShootingSprite(const std::string& n,std::vector<Frame*>& fmsLeft,std::vector<Frame*>& fmsRight); 
  ShootingSprite(const ShootingSprite& s);
  ShootingSprite& operator=(const ShootingSprite&);

  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
  virtual bool collidedWith(const Drawable*) const;

private:
  std::string bulletName;
  Bullets bullets;
  float minSpeed;
};
#endif
