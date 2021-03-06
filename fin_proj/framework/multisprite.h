#ifndef MULTISPRITE__H
#define MULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>

#include "drawable.h"

class CollisionStrategy;
class MultiframeSprite : public Drawable {
public:
  MultiframeSprite(const std::string& n, const std::vector<Frame*>& fms);
  MultiframeSprite(const std::string& n); 
  MultiframeSprite(const MultiframeSprite& s);
  virtual ~MultiframeSprite();
  virtual const Frame* getFrame() const { return frames[currentFrame]; }
  unsigned getCurrentFrame() const { return currentFrame;}

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  unsigned getPixel(Uint32, Uint32) const;
  virtual bool collidedWith(const MultiframeSprite*) const;
  MultiframeSprite& operator=(const MultiframeSprite&);

private:
  const std::vector<Frame *> frames;
protected:
  CollisionStrategy* strategy;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  void advanceFrame(Uint32 ticks);
};
#endif
