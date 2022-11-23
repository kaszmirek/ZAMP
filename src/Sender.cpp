
#include "Sender.hh"




int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);
  //cout<< "Debug przed wysłaniem! \n";
  //cout << sMesg;

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}



Sender::Sender(int Socket, Scene *pScn): _Socket(Socket), _pScn(pScn) {}

/*!
* \brief Sprawdza, czy pętla wątku może być wykonywana.
* 
* Sprawdza, czy pętla wątku może być wykonywana.
* \retval true - pętla wątku może być nadal wykonywana.
* \retval false - w przypadku przeciwnym.
*/
bool Sender::ShouldCountinueLooping() const { return _ContinueLooping; }
  
/*!
* \brief Powoduje przerwanie działania pętli wątku.
*
* Powoduje przerwanie działania pętli wątku.
* \warning Reakcja na tę operację nie będize natychmiastowa.
*/  
void Sender::CancelCountinueLooping() { _ContinueLooping = false; }

  
/*!
* \brief Ta metoda jest de facto treścią wątku komunikacyjnego
*
* Przegląda scenę i tworzy odpowiednie polecenia, a następnie
* wysyła je do serwera.
* \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
*                     wysyłane są polecenia.
*/
void Sender::Watching_and_Sending() {
  while (ShouldCountinueLooping()) {
    if (!this->_pScn->IsChanged())  { usleep(10000); continue; }
    this->_pScn->LockAccess();
    
    //------- Przeglądanie tej kolekcji to uproszczony przykład
    string message;
    for (const pair<string, shared_ptr<MobileObj>> &rObj : this->_pScn->obj_list) {
                                  // Ta instrukcja to tylko uproszczony przykład
      rObj.second->GetStateDesc(&message);
      message = "UpdateObj "+message;
      Send(_Socket,message.c_str()); // Tu musi zostać wywołanie odpowiedniej
                                        // metody/funkcji gerującej polecenia dla serwera.
    };
    
    this->_pScn->CancelChange();
    this->_pScn->UnlockAccess();
  }
}



