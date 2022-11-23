#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){
}

Set4LibInterfaces::~Set4LibInterfaces(){

}

/*!
 * \brief Zwraca koniec mapy
 */
LibInterfMap::iterator Set4LibInterfaces::not_exist() 
{
  return this->lib_map.end();
}

void Set4LibInterfaces::add_lib(string name){
    string path = "libs/" + name;
    std::shared_ptr<LibInterface> lib_ptr = make_shared<LibInterface>(path);
    this->lib_map.insert({lib_ptr->name, lib_ptr});
}

shared_ptr<LibInterface> Set4LibInterfaces::find(string name){
    
    auto it = this->lib_map.find(name); /*! Iterator elementu std::map<string, shared_ptr<LibInterface>>  */
    if (it == lib_map.end()) 
    {
        return nullptr;
    }
    else
    {
        return (it->second);
    }
}