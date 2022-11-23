#ifndef INTERPPROGRAM_HH
#define INTERPPROGRAM_HH

#include <sstream>
#include "Configuration.hh"
#include "Sender.hh"

#define LINE_SIZE 500

class InterpProgram{
    private:
        Scene * scene;
        bool exec_preprocessor(const std::string &name, std::istringstream &stream);
        /*!
        * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
        */
        int _Socket = 0;
    public:
        InterpProgram(Set_MobileObjs &obj_list, int socket);
        ~InterpProgram();
        bool exec_program(const std::string filename, Set4LibInterfaces &lib_set);
        Scene * GetScenePtr(){return scene;};
        void SendScene();

};

#endif