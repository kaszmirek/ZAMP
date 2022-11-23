#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include <cmath>
#include "AccessControl.hh"

using std::cout;
using std::endl;

const double PI  =3.141592653589793238463;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mS(0), _Distance_m(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " "  << _Speed_mS  <<" "<< _Distance_m << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket, AccessControl * mutex ) const
{
  double dist, pitch, yaw;
  int frame_number = 30*_Distance_m/abs(_Speed_mS);
  cout << pMobObj->GetName() << "   ";
  PrintCmd();
  if(_Speed_mS <0){
    dist = -1*_Distance_m;
  }else{
    dist = _Distance_m;
  }
  dist = dist/frame_number;
  for(int i=0; i<frame_number; ++i){
    mutex->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                              // modyfikacje na obiekcie.

    Vector3D pos = pMobObj->UsePosition_m();
    pitch = pMobObj->GetAng_Pitch_deg();
    yaw = pMobObj->GetAng_Yaw_deg();
    cout << "New pos " << pos << endl;
    pos[0] += dist * cos(pitch*PI/180) * cos(yaw*PI/180);
    pos[1] += dist * cos(pitch*PI/180) * sin(yaw*PI/180);
    pos[2] += -1*dist * sin(pitch*PI/180);
    pMobObj->SetPosition_m(pos);

    mutex->MarkChange();
    mutex->UnlockAccess();
    usleep(100000);
  };
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Speed_mS >> _Distance_m;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
