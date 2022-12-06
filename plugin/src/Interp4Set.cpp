#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include <cstring>

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _X_coord(0), _Y_coord(0), _OX_deg(0), _OY_deg(0), _OZ_deg(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " "  << _X_coord << " " << _Y_coord << " " << _OX_deg << " " << _OY_deg << " " << _OZ_deg << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket, GuardedSocket * mutex ) const
{
  {
    std::lock_guard<std::mutex>  Lock(mutex->UseGuard());// Zamykamy dostęp do sceny, gdy wykonujemy
    cout << pMobObj->GetName() << "   ";
    PrintCmd();
    Vector3D pos = pMobObj->UsePosition_m();
    pos[0]=_X_coord;
    pos[1]=_Y_coord;
    pos[2]=0;
    pMobObj->SetPosition_m(pos);
    pMobObj->SetAng_Roll_deg(_OX_deg);
    pMobObj->SetAng_Pitch_deg(_OY_deg);
    pMobObj->SetAng_Yaw_deg(_OZ_deg);

    std::string message;
    pMobObj->GetStateDesc(&message);
    message = "UpdateObj " + message;
    Send(mutex->GetSocket() , message.c_str()); 
  }
  usleep(30000);
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _X_coord >> _Y_coord >> _OX_deg >> _OY_deg >> _OZ_deg;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  wsp_x wsp_y kat_OX[deg] kat_OY[deg] kat_OZ[deg]" << endl;
}


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