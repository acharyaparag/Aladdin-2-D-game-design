#include <iostream>
#include <cmath>
#include "ioManager.h"
#include "bullets.h"

Bullets::~Bullets() {
  SDL_FreeSurface( bulletSurface );
  delete bulletFrame;
  delete strategy;
}

Bullets::Bullets(const std::string& n) :
  name(n),
  strategy( new MidPointCollisionStrategy ),
  bulletSurface(IOManager::getInstance().loadAndSet(
    Gamedata::getInstance()->getXmlStr(name+"File"), true)
  ),
  bulletFrame( 
    new Frame(bulletSurface, bulletSurface->w, bulletSurface->h, 0, 0) 
  ),
  frameInterval(Gamedata::getInstance()->getXmlInt(name+"BulletInterval")),
  timeSinceLastFrame( 0 ),
  bulletList(),
  freeList()
{ }

Bullets::Bullets(const Bullets& b) :
  name(b.name),
  strategy(b.strategy),
  bulletSurface(b.bulletSurface),
  bulletFrame(b.bulletFrame), 
  frameInterval(b.frameInterval),
  timeSinceLastFrame( b.timeSinceLastFrame ),
  bulletList(b.bulletList), 
  freeList(b.freeList)
{ }

bool Bullets::collidedWith(const Drawable* obj) const {
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    if ( strategy->execute(*ptr, *obj) ) {
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
      return true;
    }
    ++ptr;
  }
  return false;
}

void Bullets::shoot(const Vector2f& position, const Vector2f& velocity) {
	if (timeSinceLastFrame > frameInterval) {
    // If no bullets in pool, make one:
    if ( freeList.empty() ) {
      Bullet b(position, velocity,name, bulletFrame);
      bulletList.push_back( b );
    }
    else {
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setVelocity(velocity);
      b.setPosition(position);
      bulletList.push_back( b );
    }
		timeSinceLastFrame = 0;
	}
}

void Bullets::draw() const { 

  std::list<Bullet>::const_iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->draw();
    ++ptr;
  }
}

void Bullets::update(Uint32 ticks) { 
	timeSinceLastFrame += ticks;
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {  // Check to see if we should free a Bullet
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
    }   
    else ++ptr;
  }
}
