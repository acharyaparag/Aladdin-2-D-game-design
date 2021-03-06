#include <string>
#include <iostream>
#include "multisprite.h"
#include "bullets.h"

class ShootingMul : public MultiframeSprite{
public:
  ShootingMul(const std::string& n);
  ShootingMul(const ShootingMul& s);
  ShootingMul& operator=(const ShootingMul&);

  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
  virtual bool collidedWith(const Drawable*) const;

private:
  std::string bulletName;
  Bullets bullets;
  float minSpeed;
};
