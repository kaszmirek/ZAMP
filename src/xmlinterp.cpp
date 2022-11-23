#include <xercesc/util/PlatformUtils.hpp>
#include "xmlinterp.hh"
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>

#include <iostream>
#include <dlfcn.h>
#include <cassert>


using namespace xercesc;


using namespace std;


/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration * rConfig)
{
  try {
          XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
          char* message = XMLString::transcode(toCatch.getMessage());
          cerr << "Error during initialization! :\n";
          cerr << "Exception message is: \n"
                << message << "\n";
          XMLString::release(&message);
          return 1;
  }

  SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

  pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  pParser->setFeature(XMLUni::fgXercesDynamic, false);
  pParser->setFeature(XMLUni::fgXercesSchema, true);
  pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

  pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

  DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
  pParser->setContentHandler(pHandler);
  pParser->setErrorHandler(pHandler);

  try {
    
    if (!pParser->loadGrammar("config/config.xsd",
                            xercesc::Grammar::SchemaGrammarType,true)) {
      cerr << "!!! Plik config/config.xsd, '" << endl
          << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
          << endl;
      return false;
    }
    cout << "READFILE :: Pomyślne wczytano opis gramatyki config.xsd" << endl;
    pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
    pParser->parse(sFileName);
  }
  catch (const XMLException& Exception) {
          char* sMessage = XMLString::transcode(Exception.getMessage());
          cerr << "Informacja o wyjatku: \n"
                << "   " << sMessage << "\n";
          XMLString::release(&sMessage);
          return false;
  }
  catch (const SAXParseException& Exception) {
          char* sMessage = XMLString::transcode(Exception.getMessage());
          char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

          cerr << "Blad! " << endl
                << "    Plik:  " << sSystemId << endl
                << "   Linia: " << Exception.getLineNumber() << endl
                << " Kolumna: " << Exception.getColumnNumber() << endl
                << " Informacja: " << sMessage 
                << endl;

          XMLString::release(&sMessage);
          XMLString::release(&sSystemId);
          return false;
  }
  catch (...) {
          cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
          return false;
  }

  cout << "READFILE ::  Finished XML reading" << endl;
  delete pParser;
  delete pHandler;
  return true;
}


/*!
 * Konstruktor klasy. Inicjalizuje handler dla struktury konfiguracyjnej
 */
XMLInterp4Config::XMLInterp4Config(Configuration * rConfig)
{
  _configuration_ptr = rConfig;
}


/*!
 * Metoda wywoływana jest bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::startDocument()
{
  cout << "*** Rozpoczecie przetwarzania dokumentu XML." << endl;
}


/*!
 * Metoda wywoływana jest bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::endDocument()
{
  cout << "=== Koniec przetwarzania dokumentu XML." << endl;
}





/*!
 * Analizuje atrybuty elementu XML \p "Lib" i odpowiednio je interpretuje.
 * \param[in] rAttrs - atrybuty elementu XML \p "Lib".
 */
void XMLInterp4Config::ProcessLibAttrs(const xercesc::Attributes  &rAttrs)
{
  if (rAttrs.getLength() != 1) {
      cerr << "Zla ilosc atrybutow dla \"Lib\"" << endl;
      exit(1);
  }

  char* sParamName = xercesc::XMLString::transcode(rAttrs.getQName(0));

  if (strcmp(sParamName,"Name")) {
      cerr << "Zla nazwa atrybutu dla Lib" << endl;
      exit(1);
  }         

  XMLSize_t  Size = 0;
  char* sLibName = xercesc::XMLString::transcode(rAttrs.getValue(Size));

  cout << "  Nazwa biblioteki: " << sLibName << endl;

  _configuration_ptr->add_lib(sLibName);

  xercesc::XMLString::release(&sParamName);
  xercesc::XMLString::release(&sLibName);
}


/*!
 * Analizuje atrybuty. Sprawdza czy ich nazwy są poprawne. Jeśli tak,
 * to pobiera wartości atrybutów (w postaci napisów) i przekazuje ...
 * \param[in] rAttrs - atrybuty elementu XML \p "Cube".
 */
void XMLInterp4Config::ProcessCubeAttrs(const xercesc::Attributes  &rAttrs)
{
  XMLSize_t length = rAttrs.getLength();
  if (length < 1) {
    cerr << "Zla ilosc atrybutow dla \"Cube\"" << endl;
    exit(1);
  }

  char *sName, *sValue;
  string parameters;
  XMLSize_t  index = 0; 
  sName = xercesc::XMLString::transcode(rAttrs.getQName(index));
  if( strcmp(sName, "Name") != 0){
    cerr << "Pierwszy parametr powinien być nazwą obiektu! Odebrano :"<< sName << endl;
    exit(1);
  };
  sValue = xercesc::XMLString::transcode(rAttrs.getValue(index));
  string obj_name(sValue);

  for (XMLSize_t  index = 1; index < length ; index++){
    sName = xercesc::XMLString::transcode(rAttrs.getQName(index));
    sValue = xercesc::XMLString::transcode(rAttrs.getValue(index));

    parameters += sName;
    parameters += " ";
    parameters += sValue;
    parameters += " ";

    xercesc::XMLString::release(&sName);
    xercesc::XMLString::release(&sValue);
  }
  istringstream IStrm;
  IStrm.str(parameters);
  _configuration_ptr->add_obj(obj_name, IStrm, length-1);
 //-----------------------------------------------------------------------------
 // Przykład czytania wartości parametrów
 // Ten przykład jest zrobiony "na piechotę" wykorzystując osobne zmienne.
 // Skala powinna być wektorem. Czytanie powinno być rezlizowane z wykorzysaniem
 // wektorów, np.
 //
 //
 // istringstream IStrm;
 // IStrm.str(sValue_Scale);
 // Vector3D  Scale;
 //
 // IStrm >> Scale;
 //
//  istringstream   IStrm;
 
//  IStrm.str(sValue_Scale);
//  double  Sx,Sy,Sz;

//  IStrm >> Sx >> Sy >> Sz;
//  if (IStrm.fail()) {
//      cerr << " Blad!!!" << endl;
//  } else {
//      cout << " Czytanie wartosci OK!!!" << endl;
//      cout << "     " << Sx << "  " << Sy << "  " << Sz << endl;
//  }

 // Tu trzeba wstawić odpowiednio własny kod ...
}







/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] rElemName - nazwa elementu XML.
 * \param[in] rAttrs - atrybuty napotkanego elementu XML.
 */
void XMLInterp4Config::WhenStartElement( const std::string           &rElemName,
		                         const xercesc::Attributes   &rAttrs
                                       )
{
  if (rElemName == "Lib") {
    ProcessLibAttrs(rAttrs);   return;   
  }

  if (rElemName == "Cube") {
    ProcessCubeAttrs(rAttrs);  return;
  }
}




/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pURI - (Uniform Resource Identifier) jeżeli nie jest on wyspecyfikowany
 *                    poprzez użycie atrybutów \p xmlns (o ile jego użycie jest przewidziane w gramatyce,
 *                    w tym przykładzie nie jest to przewidziane), to będzie to napis pusty.
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] pQName - pełna kwalifikowana nazwa. To ma znaczenie, gdy użyta jest przestrzeń nazwa.
 *                      Wówczas poprzez ten parametr można otrzymać nazwę elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeśli przestrzeń nazw nie jest użyta (taka jak w tym
 *                      przykładzie), to \p pQName i \p pLocalName dostaczają identyczne napisy.
 *  \param[in] rAttrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLInterp4Config::startElement(  const   XMLCh* const            pURI,
                                      const   XMLCh* const            pLocalName,
                                      const   XMLCh* const            pQName,
				      const   xercesc::Attributes&    rAttrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  cout << "+++ Poczatek elementu: "<< sElemName << endl;

  WhenStartElement(sElemName, rAttrs);

  xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Lib Name="Rotate">
     </Lib>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika:
 * \verbatim</Lib>\endverbatim
 * Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pURI - (Uniform Resource Identifier) jeżeli nie jest on wyspecyfikowany
 *                    poprzez użycie atrybutów \p xmlns (o ile jego użycie jest przewidziane w gramatyce,
 *                    w tym przykładzie nie jest to przewidziane), to będzie to napis pusty.
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Lib".
 *  \param[in] pQName - pełna kwalifikowana nazwa. To ma znaczenie, gdy użyta jest przestrzeń nazwa.
 *                      Wówczas poprzez ten parametr można otrzymać nazwę elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeśli przestrzeń nazw nie jest użyta (taka jak w tym
 *                      przykładzie), to \p pQName i \p pLocalName dostaczają identyczne napisy.
 *                      
 */
void XMLInterp4Config::endElement(  const   XMLCh* const    pURI,
                                    const   XMLCh* const    pLocalName,
                                    const   XMLCh* const    pQName
                                 )
{
   char* sURI =  xercesc::XMLString::transcode(pURI);
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   char* sQName =  xercesc::XMLString::transcode(pQName);
   cout << "   URI: " << sURI << endl;
   cout << " QName: " << sQName << endl;
   cout << "----- Koniec elementu: "<< sElemName << endl;

   xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 * \param[in] rException - zawiera informacje dotyczące błędu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::fatalError(const xercesc::SAXParseException&  rException)
{
   char* sMessage = xercesc::XMLString::transcode(rException.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(rException.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << rException.getLineNumber() << endl
        << " Kolumna: " << rException.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] rException - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLInterp4Config::error(const xercesc::SAXParseException&  rException)
{
  cerr << "Blad ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}


/*!
 * Metoda wywołana jest w przypadku błędów, które nie są fatalne
 * i mogą być traktowane jako ostrzeżenia.
 * \param[in] rException - zawiera informacje dotyczące błędu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::warning(const xercesc::SAXParseException&  rException)  
{
  cerr << "Ostrzezenie ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}
