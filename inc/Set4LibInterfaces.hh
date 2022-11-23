#ifndef SET4LIBINTERF_HH
#define SET4LIBINTERF_HH

#include <memory>
#include "LibInterface.hh"

using namespace std;

typedef map<string, shared_ptr<LibInterface>> LibInterfMap;
class Set4LibInterfaces{
    private:
        LibInterfMap lib_map;

    public:
        Set4LibInterfaces();
        ~Set4LibInterfaces();
        void add_lib(string path);
        LibInterfMap::iterator not_exist();
        shared_ptr<LibInterface> find(string name);
};

#endif