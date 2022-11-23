#include "LibInterface.hh"

LibInterface::LibInterface(string path){
    LibInterface::load(path);
    LibInterface::init();
}

LibInterface::~LibInterface(){
    dlclose(this->handler);
}

bool LibInterface::init(){
    void * new_cmd = dlsym(this->handler, "CreateCmd");
    if (new_cmd == nullptr){
        cerr << "Nie udalo się utworzyć komendy CreateCmd " << endl;
        return false;
    }
    CreateCmd = reinterpret_cast<Interp4Command* (*)(void)>(new_cmd);
    Interp4Command* interpreted_cmd = CreateCmd();
    this->name = interpreted_cmd->GetCmdName();
    delete interpreted_cmd;
    return true;
}

bool LibInterface::load(string path){
    this->handler = dlopen(path.c_str(), RTLD_LAZY);
    if (this->handler==nullptr) {
        cerr << "!!! Brak biblioteki " << path << endl;
        return false;
    }else{
        cout << "Załadowano biblioteke " << path << endl;
        return true;
    }
}