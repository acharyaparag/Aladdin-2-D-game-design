#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Less{
public:
  bool operator() (ScaledSprite * left, ScaledSprite* right) const {
    return left->getScale() < right->getScale();
  }
};
