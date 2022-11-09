#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() : _x(0), _y(0)
{
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _x << " " << _y << endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName;
  Strm_CmdsList >> _x;
  Strm_CmdsList >> _y;
  Strm_CmdsList >> _RotZ;
  return true;
}

/*!
 *
 */
Interp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  Set X[mm] Y[mm] RotZ[rad]" << endl;
}
