#include "LibInterface.hh"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

LibInterface::LibInterface(const char* libName, int mode)
{
  _LibHandler = dlopen(libName, mode);
  if(!_LibHandler)
  {
    cerr << "!!! Brak biblioteki: "<< libName << endl;
    exit(1);
  }
  
  void *pFun = dlsym(_LibHandler, "CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    exit(1);
  }

  _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
  _pCmd = _pCreateCmd();
  _CmdName = _pCmd->GetCmdName();
}

LibInterface::~LibInterface()
{
  delete _pCmd;
  dlclose(_LibHandler);
}

std::string LibInterface::getCmdName()
{
  return _CmdName;
}

Interp4Command * LibInterface::getCmd()
{
  return _pCmd;
}
