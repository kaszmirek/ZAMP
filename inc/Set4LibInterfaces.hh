#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <map>
#include <memory>
#include "LibInterface.hh"

class Set4LibInterfaces : public std::map<std::string, std::shared_ptr<LibInterface>>
{
private:
    /* data */
public:
    Set4LibInterfaces(/* args */) {}
    ~Set4LibInterfaces() {}
    void addLib(std::string name, std::string file)
    {
        insert(std::pair<std::string, std::shared_ptr<LibInterface>>(name, std::make_shared<LibInterface>(file.c_str())));
    }
};

#endif
