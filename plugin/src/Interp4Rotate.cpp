#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
    Interp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
    return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _angle(0)
{
}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
    /*
     *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
     */
    cout << GetCmdName() << " " << _angle << endl;
}

/*!
 *
 */
const char *Interp4Rotate::GetCmdName() const
{
    return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(MobileObj *pMobObj, int Socket) const
{
    /*
     *  Tu trzeba napisać odpowiedni kod.
     */
    return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
    /*
     *  Tu trzeba napisać odpowiedni kod.
     */
    return true;
}

/*!
 *
 */
Interp4Command *Interp4Rotate::CreateCmd()
{
    return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
    cout << "   Rotate  NazwaObiektu  Obrot[rad]" << endl;
}
