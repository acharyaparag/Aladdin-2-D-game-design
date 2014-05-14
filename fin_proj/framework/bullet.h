#ifndef BULLET__H
#define BULLET__H


#include <iostream>
#include "sprite.h"
#include "gamedata.h"
class Bullet : public Sprite {
public:
  explicit Bullet( const Vector2f& pos, const Vector2f vel,const string& name,  
                   const Frame* fm) :
    Sprite(pos, vel,name, fm), 
    distance(0), 
    maxDistance(Gamedata::getInstance()->getXmlInt(name+"Distance")), 
    tooFar(false),
    name(name),
    pos(pos) 
  { }
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
    bool collidedWith(const Sprite* obj) const;

private:
  float distance;
  float maxDistance;
  bool tooFar;
  const string& name;
  const Vector2f& pos;
};
#endif
