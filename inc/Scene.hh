#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>

#include "MobileObj.hh"

class Scene
{
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;
};

#endif