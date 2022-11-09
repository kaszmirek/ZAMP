#pragma once

#include <string>
#include <dlfcn.h>

#include "Interp4Command.hh"

class LibInterface
{
private:
  void *_LibHandler;
  Interp4Command *(*_pCreateCmd)(void);

  std::string _CmdName;
  Interp4Command *_pCmd;

public:
  LibInterface(const char *libName, int mode = RTLD_LAZY);
  ~LibInterface();

  std::string getCmdName();
  Interp4Command *getCmd();
};