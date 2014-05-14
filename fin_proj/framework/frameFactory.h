#include <string>
#include <vector>
#include <map>
#include "frame.h"
#include "gamedata.h"

class FrameFactory {
public:
  static FrameFactory& getInstance();
  ~FrameFactory();
  Frame* getFrame(const std::string&);
  Frame* getScaledFrame(const std::string&,float);
  std::vector<Frame *> getMultiFrame(const std::string&);
  std::vector<Frame *> getTwoWayMultiFrameLeft(const std::string&);
  std::vector<Frame *> getTwoWayMultiFrameRight(const std::string&);

private:
  Gamedata* gdata;
  std::map<std::string, SDL_Surface*> surfaces;
  std::map<std::string, Frame*> frames;
  std::map<std::string,std::vector<Frame *> > mulFrames;
  std::map<std::string,std::vector<Frame *> > twoWayMultiFramesLeft;
  std::map<std::string,std::vector<Frame *> > twoWayMultiFramesRight;
  std::vector<Frame *> scaledFrames;
  std::map<std::string,SDL_Surface*> surfacesRoto;
  string surface_roto;
  std::map<std::string,SDL_Surface*> surfacesRoto1;
  string surface_roto1;

  
  FrameFactory() : 
    gdata( Gamedata::getInstance() ), surfaces(), frames(), mulFrames(), twoWayMultiFramesLeft(),twoWayMultiFramesRight(),scaledFrames(),surfacesRoto(),surface_roto(),surfacesRoto1(),surface_roto1()
  {}
  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
};
