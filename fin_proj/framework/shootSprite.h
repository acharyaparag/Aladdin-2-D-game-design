#include <string>
#include <iostream>
#include "sprite.h"
#include "bullets.h"

class ShootSprite : public Sprite {
public:
  ShootSprite(const std::string& n, const Frame*);
  ShootSprite(const ShootSprite& s);
  ShootSprite& operator=(const ShootSprite&);

  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
  virtual bool collidedWith(const Sprite*) const;

private:
  std::string bulletName;
  Bullets bullets;
  float minSpeed;
};
