#ifndef SCENE_HH
#define SCENE_HH

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene ...
 */

#include "MobileObj.hh"
#include <string>
#include <memory>
#include <map>
#include "AccessControl.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>


using namespace std;

typedef map<string, shared_ptr<MobileObj>> Set_MobileObjs;
typedef shared_ptr<MobileObj> Object_ptr;

/*!
 * \brief Modeluje wyświetlaną scenę, na której umieszczane będą obiekty
 *
 *  Klasa modeluje ...
 */
class Scene:  public AccessControl {
 private:
 public:
   Set_MobileObjs &obj_list;
 
   Scene(Set_MobileObjs &obj_list);
   ~Scene();

 /*!
 * Metoda klasy pozwalająca na znalezienie wybranego obiektu na scenie
 * \param sName -- nazwa wyszukiwanego obiektu
 */
    Object_ptr FindMobileObj(string name);
/*!
 * Metoda klasy pozwalająca na dodanie obiektu do sceny
 * \param pMobObj -- wskaznik na obiekt do dodania do klasy
 */
    void AddMobileObj(string name);
    Set_MobileObjs & GetMobileObj(){return obj_list;};
 };

#endif