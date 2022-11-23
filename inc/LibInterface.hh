#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <map>
#include <string>
#include "Interp4Command.hh"
#include <dlfcn.h>
#include <iostream>

using namespace std;

class LibInterface{
    private:
        void* handler;
        
    public:
        string name;
        LibInterface(string path);
        ~LibInterface();
        bool init();
        bool load(string path);

        Interp4Command * (*CreateCmd)(void);
};

#endif