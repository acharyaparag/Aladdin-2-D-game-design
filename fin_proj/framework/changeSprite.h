#include <string>
#include <iostream>

#include "sprite.h"

class ChangeSprite : public Sprite {
public:
  ChangeSprite(const std::string& n, const Frame*);
  ChangeSprite(const std::string& n);
  ChangeSprite(const ChangeSprite& s);
  virtual ~ChangeSprite() { } 
  ChangeSprite& operator=(const ChangeSprite&);
  virtual void update(Uint32 ticks);

private:
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  Vector2f acceleration;
  float withVelocity;
};
