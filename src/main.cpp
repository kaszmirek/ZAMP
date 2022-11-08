#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "preprocessor.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

int main(int argc, char **argv)
{
  string cmd = processCmdFile(argv[1]);
  cout << cmd;

  Set4LibInterfaces plugin;

  plugin["Move"] = new LibInterface("libInterp4Move.so", RTLD_LAZY);
  plugin["Pause"] = new LibInterface("libInterp4Pause.so", RTLD_LAZY);
  plugin["Rotate"] = new LibInterface("libInterp4Rotate.so", RTLD_LAZY);
  plugin["Set"] = new LibInterface("libInterp4Set.so", RTLD_LAZY);

  for (auto &plug : plugin)
  {
    cout << plug.second->getCmdName() << endl;
    plug.second->getCmd()->PrintSyntax();
    plug.second->getCmd()->PrintCmd();
  }
}