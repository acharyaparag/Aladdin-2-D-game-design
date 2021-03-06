#include "gamedata.h"
#include "twowayMultisprite.h"
#include "shootingSprite.h"
#include "collisionStrategy.h"

class Player {
public:
  Player();
  virtual ~Player();

  virtual void update(Uint32 ticks);
  virtual void draw() const { aladdin->draw(); }
  const Drawable* getSprite() const { return aladdin; }

  void stop();
  void right();
  void left();
  void up();
  void down();

  void shoot();
  virtual bool collidedWith(const Drawable*) const;
  virtual bool collideSelf(const Drawable*) const;

private:
  CollisionStrategy* strategy;
  const Gamedata* gdata;
  bool keyPressed;
  int worldWidth;
  int worldHeight;
  Vector2f aladdinInitialVelocity;
  float aladdinWidth;
  float aladdinHeight;
  SDL_Surface *aladdinSurface;
  std::vector<Frame*> aladdinFrames;
  std::vector<Frame*> aladdinFramesLeft;
  ShootingSprite* aladdin;
  void makeAladdin();
  Player(const Player&);
  Player& operator=(const Player&);
};

