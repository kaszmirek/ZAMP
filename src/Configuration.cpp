#include "Configuration.hh"

Configuration::Configuration(Set4LibInterfaces * set_lib){
    _Set4LibInterfaces_ptr = set_lib;
}

void Configuration::add_lib(const string &lib_name){
    this->_Set4LibInterfaces_ptr->add_lib(lib_name);
}

Set_MobileObjs & Configuration::get_obj_list(){
    return this->obj_list; 
}

/*!
 * Metoda klasy pozwalająca na dodanie obiektu do listy
 */
void Configuration::add_obj(const string &obj_name, std::istream& IStrm, int size){
    string param_name;
    Vector3D param_values;
    Object_ptr obj_ptr = make_shared<MobileObj>();  
    obj_ptr->SetName(obj_name);
    cout << "   Name " << obj_name << endl;
    for(int i=0; i<size; i++){
        IStrm >> param_name;
        IStrm >> param_values[0] >> param_values[1] >> param_values[2];
        if (IStrm.fail()) {
            cerr << " Blad czytania parametrów!" << endl;
        }else{
            if( param_name=="Scale"){
                obj_ptr->SetScale(param_values);
            }else if(param_name.compare("Shift") == 0){
                obj_ptr->SetShift_m(param_values);
            }else if(param_name.compare("RGB") == 0){
                obj_ptr->SetRGB(param_values);
            }else if( param_name.compare("Trans_m") == 0){
                obj_ptr->SetPosition_m(param_values);
            }else if( param_name.compare("RotXYZ_deg") == 0){
                obj_ptr->SetAng_Roll_deg(param_values[0]);
                obj_ptr->SetAng_Pitch_deg(param_values[1]);
                obj_ptr->SetAng_Yaw_deg(param_values[2]);
            };
            cout<< "   " <<param_name<<" "<< param_values<<endl; 
        }
        
        
    }
    

    this->obj_list.insert({obj_name, obj_ptr});
}
