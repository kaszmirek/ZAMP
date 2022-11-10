#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>

#include "MobileObj.hh"

class Scene
{
private:
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;

public:
    std::shared_ptr<MobileObj> FindMobileObj(const char *sName)
    {
        return Set_MobileObjs[sName];
    }

    void AddMobileObj(std::shared_ptr<MobileObj> pMobObj)
    {
        Set_MobileObjs[pMobObj->GetName()] = pMobObj;
    }
};

#endif