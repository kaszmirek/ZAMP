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
Interp4Rotate::Interp4Rotate() : _ObjName(""), _RotSpeed(0), _Angle(0)
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

    cout << GetCmdName() << " " << _ObjName << " " << _RotSpeed << " " << _Angle << endl;
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

    return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
    Strm_CmdsList >> _ObjName;
    Strm_CmdsList >> _RotSpeed;
    Strm_CmdsList >> _Angle;
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
    cout << "   Rotate  NazwaObiektu  Szybkosc_katowa[rad/s] Kat_skretu[rad]" << endl;
}
