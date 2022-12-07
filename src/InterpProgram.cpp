#include "InterpProgram.hh"
#include <vector>
#include <list>
#include <thread>

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
    this->scene = new Scene(obj_list, socket);
}

InterpProgram::~InterpProgram(){
    if (nullptr != this->scene)
    {
        delete scene;
    }
}

void Fun4Thread_ExecCmd(Interp4Command *CmdInterp, MobileObj *pMObj, int socket, GuardedSocket *pAccCtrl)
{
  CmdInterp->ExecCmd(pMObj,socket, pAccCtrl); 
}

bool InterpProgram::exec_program(const std::string filename, Set4LibInterfaces &lib_set){
    istringstream iss;
    this->exec_preprocessor(filename, iss);
    string cmd_name;
    string object_name;
    int parallel_exec_flag=0;
    std::shared_ptr<Interp4Command>               PInterp;
    std::vector<std::shared_ptr<Interp4Command>>  Tab4Interps;
    std::list<std::thread>                      Tab4Threads;

    Tab4Interps.reserve(10);  //Tab4Threads.reserve(10);

    while (iss >> cmd_name)
    {
        if(cmd_name == "Begin_Parallel_Actions"){
            parallel_exec_flag=1;
            cout << "DEBUG: begin parallel action"<<endl;
        }else if(cmd_name == "End_Parallel_Actions"){
            parallel_exec_flag=0;
            cout << "DEBUG: end parallel action"<<endl;
            for (std::thread &Th : Tab4Threads) Th.join();
        }else{
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
            if(parallel_exec_flag==1){
                PInterp = std::shared_ptr<Interp4Command>(cmd);
                Tab4Interps.push_back(PInterp);
                Tab4Threads.push_back(std::thread(Fun4Thread_ExecCmd,PInterp.get(),object.get(),_Socket,scene));  
            }else{
                cmd->ExecCmd(object.get(), _Socket, scene); // wykonaj operację
            }
   
        }
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
}