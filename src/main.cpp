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

  LibInterface moveiface("libInterp4Move.so",RTLD_LAZY);
  LibInterface pauseiface("libInterp4Pause.so", RTLD_LAZY);

  cout << moveiface.getCmdName() << endl;
  moveiface.getCmd()->PrintSyntax();
  moveiface.getCmd()->PrintCmd();


  cout << pauseiface.getCmdName() << endl;
  pauseiface.getCmd()->PrintSyntax();
  pauseiface.getCmd()->PrintCmd();

}