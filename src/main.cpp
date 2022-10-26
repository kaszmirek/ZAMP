#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "preprocessor.hh"
#include "LibInterface.hh"

using namespace std;


int main(int argc, char** argv)
{
  string cmd = processCmdFile(argv[1]);
  cout << cmd;

  LibInterface iface("libInterp4Move.so",RTLD_LAZY);

  cout << iface.getCmdName() << endl;
  iface.getCmd()->PrintSyntax();
  iface.getCmd()->PrintCmd();

}