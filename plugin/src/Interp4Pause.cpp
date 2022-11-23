#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause(): _Pause_time_ms(0)
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Pause_time_ms << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Pause::ExecCmd( MobileObj  *pMobObj,  int  Socket, AccessControl * mutex ) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  PrintCmd();

  mutex->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                            // modyfikacje na obiekcie.
  usleep(_Pause_time_ms *1000);
  mutex->MarkChange();
  mutex->UnlockAccess();
  return true;
}


/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Pause_time_ms;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause czas_pauzy_ms[ms]" << endl;
}
