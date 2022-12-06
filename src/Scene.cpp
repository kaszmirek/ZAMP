#include "Scene.hh"

/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 */
Scene::Scene(Set_MobileObjs &obj_list, int socket): obj_list(obj_list), GuardedSocket::GuardedSocket(socket) {
  Set_MobileObjs::iterator it;
  for (it = obj_list.begin(); it != obj_list.end(); it++)
  {
    cerr << "  " << it->first << endl;
  }
}

/*!
 * Destruktor klasy.
 */
Scene::~Scene(){

}

/*!
 * Metoda klasy pozwalająca na znalezienie wybranego obiektu na scenie
 */
Object_ptr Scene::FindMobileObj(string name){
  auto it = this->obj_list.find(name);  /*! Iterator elementu std::map<string, shared_ptr<MobileObj>>  */
  if (it == obj_list.end()) 
  {
    return nullptr;
  }
  else
  {
    return (it->second);
  }
}

/*!
 * Metoda klasy pozwalająca na dodanie obiektu do sceny
 */
void Scene::AddMobileObj(string name){
    Object_ptr obj_ptr = make_shared<MobileObj>();  
    this->obj_list.insert({name, obj_ptr});
}