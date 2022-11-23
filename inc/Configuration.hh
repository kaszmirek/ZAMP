#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include <cstring>

using namespace std;

class Configuration {
  private:
    Set4LibInterfaces * _Set4LibInterfaces_ptr;
    Set_MobileObjs obj_list;
  public:
    Configuration(Set4LibInterfaces * set_lib);
    void add_lib(const string &lib_name);
    Set_MobileObjs & get_obj_list();
    void add_obj(const string &obj_name, std::istream& IStrm, int size);
};


#endif
