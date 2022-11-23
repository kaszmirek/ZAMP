
#include "xmlinterp.hh"

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Configuration.hh"
#include "InterpProgram.hh"
#include "Sender.hh"

using namespace std;


/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}



/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] rSender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}



int main()
{
  Set4LibInterfaces lib_set;
  Configuration config(&lib_set);

  cout << "Port: " << PORT << endl;
  int Socket4Sending;   

  if (!OpenConnection(Socket4Sending)) return 1;
  
  if (!ReadFile("config/config.xml", &config)) return 1;

  Set_MobileObjs obj_list = config.get_obj_list(); // odczytanie listy obiektow
  cout << "Stworzono program\n";
  InterpProgram program(obj_list, Socket4Sending);

  Sender   ClientSender(Socket4Sending, program.GetScenePtr());
  //  thread   Thread4Sending(Fun_Sender, Socket4Sending, &ClientSender);

  thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
  const char *sConfigCmds = "Clear\n";
  cout << "Clear\n" << endl; 
  Send(Socket4Sending,sConfigCmds); 
  program.SendScene();


  int return_val =0;
  if (true == program.exec_program("commands", lib_set))
  {
    cerr << "Program wykonal sie prawidlowo" << endl;
    return_val =  0;
  }
  else
  {
    cerr << "BLAD KRYTYCZNY!" << endl;
    return_val = 1;
  }

  cout << "Close\n" << endl; 
  sConfigCmds = "Close\n";
  Send(Socket4Sending,sConfigCmds);
  ClientSender.CancelCountinueLooping();
  Thread4Sending.join();
  close(Socket4Sending);

  return return_val;
}
