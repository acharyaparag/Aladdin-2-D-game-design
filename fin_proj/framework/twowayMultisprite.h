#ifndef TWOWAY_MULTISPRITE__H
#define TWOWAY_MULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>
#include "drawable.h"

class TwowayMultiframeSprite : public Drawable {
public:
  TwowayMultiframeSprite(const std::string& n, 
                   std::vector<Frame*>& fmsLeft,
                   std::vector<Frame*>& fmsRight);
  TwowayMultiframeSprite(const std::string& n);
  TwowayMultiframeSprite(const TwowayMultiframeSprite& s);

  virtual ~TwowayMultiframeSprite() { } 
  virtual const Frame* getFrame() const { return frames[currentFrame]; }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  unsigned getPixel(Uint32, Uint32) const;
  int getGravity() const { return gravity; }
  void setGravity(int grav) { gravity = grav; }


private:
  std::vector<Frame *> framesLeft;
  std::vector<Frame *> framesRight;
  std::vector<Frame *> frames;
  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  void advanceFrame(Uint32 ticks);
  TwowayMultiframeSprite& operator=(const TwowayMultiframeSprite&);
protected:
   int frameWidth;
   int frameHeight;
   int worldWidth;
   int worldHeight;
   int gravity;
 
};
#endif
