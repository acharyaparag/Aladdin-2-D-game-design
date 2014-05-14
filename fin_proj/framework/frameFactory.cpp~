#include "frameFactory.h"
#include "ioManager.h"
#include "vector2f.h"
#include "SDL/SDL_rotozoom.h"


FrameFactory::~FrameFactory() {
  std::cout << "The FrameFactory is down sizing!" << std::endl;
  std::map<std::string, SDL_Surface*>::iterator itSurf = surfaces.begin();
  while ( itSurf != surfaces.end() ) {
    SDL_FreeSurface( itSurf->second );
    ++itSurf;
  }
  
std::map<std::string, SDL_Surface*>::iterator itSurfRoto = surfacesRoto.begin();
  while ( itSurfRoto != surfacesRoto.end() ) {
    SDL_FreeSurface( itSurfRoto->second );
    ++itSurfRoto;
  }

std::map<std::string, SDL_Surface*>::iterator itSurfRoto1 = surfacesRoto1.begin();
  while ( itSurfRoto1 != surfacesRoto1.end() ) {
    SDL_FreeSurface( itSurfRoto1->second );
    ++itSurfRoto1;
  }

  std::map<std::string, Frame*>::iterator itFrame = frames.begin();
  while ( itFrame != frames.end() ) {
    delete itFrame->second;
    ++itFrame;
  }

  std::map<std::string, std::vector<Frame*> >::iterator iterateMulFrame = mulFrames.begin();
  while ( iterateMulFrame != mulFrames.end() ) {
    std::vector <Frame *>::iterator it; 
    for(it= iterateMulFrame->second.begin();it<iterateMulFrame->second.end();it++)
       { delete  *it;
        } 
    iterateMulFrame->second.clear();
    ++iterateMulFrame;
  }

  std::map<std::string, std::vector<Frame*> >::iterator iterateTwoWayFrameLeft = twoWayMultiFramesLeft.begin();
   while ( iterateTwoWayFrameLeft != twoWayMultiFramesLeft.end() ) {
    std::vector <Frame *>::iterator it; 
    for(it= iterateTwoWayFrameLeft->second.begin();it<iterateTwoWayFrameLeft->second.end();it++)
        {
        delete *it;
        }
   iterateTwoWayFrameLeft->second.clear();
   ++iterateTwoWayFrameLeft;
  }

   std::map<std::string, std::vector<Frame*> >::iterator iterateTwoWayFrameRight = twoWayMultiFramesRight.begin();
   while ( iterateTwoWayFrameRight != twoWayMultiFramesRight.end() ) {
    std::vector <Frame *>::iterator it; 
    for(it= iterateTwoWayFrameRight->second.begin();it<iterateTwoWayFrameRight->second.end();it++)
        {
        delete *it;
        }
   iterateTwoWayFrameRight->second.clear();
   ++iterateTwoWayFrameRight;
  }

  for (unsigned i = 0 ; i< scaledFrames.size() ; i++)
     {  
       delete scaledFrames[i];
     }

}

FrameFactory& FrameFactory::getInstance() {
  static FrameFactory factory;
  return factory;
}

Frame* FrameFactory::getFrame(const std::string& name) {
  std::map<std::string, Frame*>::const_iterator pos = frames.find(name); 
  if ( pos == frames.end() ) {
    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr(name+"File"),
          gdata->getXmlBool(name+"Transparency"));
    surfaces[name] = surface;
    Frame * const frame =new Frame(surface,
                gdata->getXmlInt(name+"Width"), 
                gdata->getXmlInt(name+"Height"),
                gdata->getXmlInt(name+"SrcX"), 
                gdata->getXmlInt(name+"SrcY")); 
    frames[name] = frame;
    return frame;
  }
  else {
    return pos->second;
  }
}


std::vector<Frame *> FrameFactory::getMultiFrame(const std::string& name) {

  std::map<std::string, std::vector<Frame *> >::const_iterator pos = mulFrames.find(name); 

  if ( pos == mulFrames.end() ) {

    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr(name+"File"),
          gdata->getXmlBool(name+"Transparency"));
    surfaces[name] = surface;
  
    std::vector<Frame *> multiFrames;
    unsigned num = gdata->getXmlInt(name+"Frames"); 
    Uint16 pwidth = gdata->getXmlInt(name+"Width");
    Uint16 pheight = gdata->getXmlInt(name+"Height");
    Uint16 srcX = gdata->getXmlInt(name+"SrcX");
    Uint16 srcY = gdata->getXmlInt(name+"SrcY");

    for (unsigned i = 0; i < num; i++)
        { 
         unsigned frameX = i*pwidth + srcX;
         multiFrames.push_back(new Frame(surface, pwidth, pheight, frameX, srcY) ); 
        }                          
 
    mulFrames[name] = multiFrames;
    return multiFrames;
  }
  else {
    return pos->second;
  }
}

std::vector<Frame *> FrameFactory::getTwoWayMultiFrameLeft(const std::string& name) {

 std::map<std::string, std::vector<Frame *> >::const_iterator pos = twoWayMultiFramesLeft.find(name); 

 if ( pos == twoWayMultiFramesLeft.end() ) {

    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr(name+"File"),
          gdata->getXmlBool(name+"Transparency"));
    surfaces[name] = surface;
  
    std::vector<Frame *> multiFramesLeft;
    unsigned num = gdata->getXmlInt(name+"Frames"); 
    Uint16 pwidth = gdata->getXmlInt(name+"Width");
    Uint16 pheight = gdata->getXmlInt(name+"Height");
    Uint16 srcLeftX = gdata->getXmlInt(name+"LeftSrcX");
    Uint16 srcLeftY = gdata->getXmlInt(name+"LeftSrcY");


    for (unsigned i = 0; i < num; ++i) 
    {
       unsigned frameX = i * pwidth + srcLeftX;
       multiFramesLeft.push_back( 
       new Frame(surface, pwidth, pheight, frameX, srcLeftY) );
    }
                         
 
    twoWayMultiFramesLeft[name] = multiFramesLeft;
    return multiFramesLeft;
  }
  else {
    return pos->second;
  }
}


std::vector<Frame *> FrameFactory::getTwoWayMultiFrameRight(const std::string& name) {

 std::map<std::string, std::vector<Frame *> >::const_iterator pos = twoWayMultiFramesRight.find(name); 

 if ( pos == twoWayMultiFramesRight.end() ) {

    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr(name+"File"),
          gdata->getXmlBool(name+"Transparency"));
    surfaces[name] = surface;
  
    std::vector<Frame *> multiFramesRight;
    unsigned num = gdata->getXmlInt(name+"Frames"); 
    Uint16 pwidth = gdata->getXmlInt(name+"Width");
    Uint16 pheight = gdata->getXmlInt(name+"Height");
    Uint16 srcRightX = gdata->getXmlInt(name+"RightSrcX");
    Uint16 srcRightY = gdata->getXmlInt(name+"RightSrcY");


    for (unsigned i = 0; i < num; ++i) 
    {
       unsigned frameX = i * pwidth + srcRightX;
       multiFramesRight.push_back( 
       new Frame(surface, pwidth, pheight, frameX, srcRightY) );
    }
                         
 
    twoWayMultiFramesRight[name] = multiFramesRight;
    return multiFramesRight;
  }
  else {
    return pos->second;
  }
}


Frame* FrameFactory::getScaledFrame(const std::string& name,float scale) {

    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr(name+"File"),
          gdata->getXmlBool(name+"Transparency"));

    surface_roto1 = surface_roto1+name;    
    surfacesRoto1[surface_roto1] = surface;

    SDL_Surface* const tmp = 
      rotozoomSurface(surface, 0, scale, SMOOTHING_ON);

    surface_roto = surface_roto+name;
     
    surfacesRoto[surface_roto] = tmp;

     Frame* const frame = new Frame(tmp, tmp->w, tmp->h,
                gdata->getXmlInt(name+"SrcX"), 
                gdata->getXmlInt(name+"SrcY"));

    scaledFrames.push_back(frame);
    return frame;

}




