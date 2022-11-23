#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _Axis('X'), _Angle_deg(0), _Angular_speed_degs(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Angle_deg  << " " << _Axis << " " << _Angular_speed_degs << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  int  Socket, AccessControl * mutex ) const
{
  double roll, pitch, yaw;
  int frame_number = 30*abs(_Angle_deg)/_Angular_speed_degs;
  double angle = _Angle_deg/frame_number; 
  cout << pMobObj->GetName() << "   ";
  PrintCmd();
  for(int i=0; i<frame_number; ++i){
    mutex->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                              // modyfikacje na obiekcie.
    
    switch(_Axis){
      case 'X':
        roll = pMobObj->GetAng_Roll_deg();
        pMobObj->SetAng_Roll_deg(roll+angle);
        break;
      case 'Y':
        pitch = pMobObj->GetAng_Pitch_deg();
        pMobObj->SetAng_Pitch_deg(pitch+angle);
        break;
      case 'Z':
        yaw = pMobObj->GetAng_Yaw_deg();
        pMobObj->SetAng_Yaw_deg(yaw+angle);
        break;
    }
    mutex->MarkChange();
    mutex->UnlockAccess();
    usleep(100000);
  };

  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Angular_speed_degs >> _Axis >> _Angle_deg;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Szybkość_kątowa[deg/s] nazwa_osi Kąt_obrotu[deg]" << endl;
}
