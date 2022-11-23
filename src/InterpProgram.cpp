#include "InterpProgram.hh"
#include "Sender.hh"



bool InterpProgram::exec_preprocessor(const std::string &name, std::istringstream &stream){
    bool result = false;
    string cmd = "cpp -P ";
    char buffer[LINE_SIZE];
    ostringstream output;

    FILE* pipe = popen((cmd + name).c_str(), "r");

    if (nullptr != pipe)
    {
        while (fgets(buffer, LINE_SIZE, pipe))
        {
        output << buffer;
        }

        stream.str(output.str());
        result = (pclose(pipe) == 0);
    }

    return result;
}

InterpProgram::InterpProgram(Set_MobileObjs &obj_list, int socket){
    this->_Socket = socket;
    this->scene = new Scene(obj_list);
}

InterpProgram::~InterpProgram(){
    if (nullptr != this->scene)
    {
        delete scene;
    }
}

bool InterpProgram::exec_program(const std::string filename, Set4LibInterfaces &lib_set){
    istringstream iss;
    this->exec_preprocessor(filename, iss);
    string cmd_name;
    string object_name;

    while (iss >> cmd_name)
    {
        

        shared_ptr<LibInterface> library = lib_set.find(cmd_name); // wyszukaj plugin

        if (nullptr == library)
        {
        cout << "Nie znaleziono komendy: " << cmd_name << endl;
        return false;
        }

        Interp4Command * cmd = library->CreateCmd(); // utworzenie interpreter
        if(cmd_name != "Pause"){
            iss >> object_name; // wczytaj nazwę obiektu
        }


        if(false == cmd->ReadParams(iss)) // odczyt parametrow
        {
        cout << "Błąd czytania parametrów" << endl;
        delete cmd;
        return false;
        }

        
        Object_ptr object = scene->FindMobileObj(object_name); // znajdź obiekt

        if (nullptr == object && cmd_name != "Pause")
        {
        cout << "Nie można znaleźć obiektu o nazwie: " << object_name << endl;
        delete cmd;
        return false;
        }

        cmd->ExecCmd(object.get(), 0, scene); // wykonaj operację
        delete cmd;
    }

    return true;
}

void InterpProgram::SendScene(){
    string message;
    for (const pair<string, shared_ptr<MobileObj>> &rObj : scene->obj_list) {
                                  // Ta instrukcja to tylko uproszczony przykład
      rObj.second->GetStateDesc(&message);
      message = "AddObj "+message;
      Send(_Socket,message.c_str()); // Tu musi zostać wywołanie odpowiedniej
                                        // metody/funkcji gerującej polecenia dla serwera.
    };
};