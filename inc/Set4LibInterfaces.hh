#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <map>
#include <memory>
#include "LibInterface.hh"

class Set4LibInterfaces : public std::map<std::string, LibInterface *>
{
private:
    /* data */
public:
    Set4LibInterfaces(/* args */);
    ~Set4LibInterfaces();
};

Set4LibInterfaces::Set4LibInterfaces(/* args */)
{
}

Set4LibInterfaces::~Set4LibInterfaces()
{
}

#endif
