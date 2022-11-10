#pragma once

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "FileReader.hh"
#include "Interp4Command.hh"
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

class ProgramInterpreter
{
private:
    Scene _Scn;
    Set4LibInterfaces _LibMan;
    std::vector<Interp4Command *> _Cmds;

public:
    ProgramInterpreter() {}
    ~ProgramInterpreter() {}

    void loadLibs()
    {
        _LibMan.addLib("Move", "libInterp4Move.so");
        _LibMan.addLib("Pause", "libInterp4Pause.so");
        _LibMan.addLib("Rotate", "libInterp4Rotate.so");
        _LibMan.addLib("Set", "libInterp4Set.so");
    }

    void printLibs()
    {
        cout << "Zaladowane wtyczki: " << endl;
        for (auto &lib : _LibMan)
        {
            lib.second->getCmd()->PrintSyntax();
        }
    }

    void parseInput(string cmdFile)
    {
        std::stringstream cmdStream(processCmdFile(cmdFile));

        while (!cmdStream.eof())
        {
            string name;
            cmdStream >> name;
            if (name.length() > 0)
            {
                _Cmds.push_back(_LibMan[name]->getCmd());
                _Cmds.back()->ReadParams(cmdStream);
            }
        }
    }

    void printCommands()
    {
        cout << "Odczytane komendy: " << endl;
        for (Interp4Command *cmd : _Cmds)
        {
            cmd->PrintCmd();
        }
    }
};