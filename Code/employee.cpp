#include "dependencies.h"


//constructor initialises the values in the employee class
Employee :: Employee(std::string usernm , std::string passwd){
    username = usernm;
    password = passwd;
}
//function returns true if the provided string matches the employee password
bool Employee :: verifyPassword(std::string passwd){
    if(passwd.compare(password) == 0){
        return true;
    }
    else{
        return false;
    }
}
//returns a string with a value of the Employee username
std::string Employee :: getUsername(){
    return username;
}
//function returns true if provided string matches the employee username
bool Employee :: verifyUsername(std::string usernm){
    if(usernm.compare(username) == 0){
        return true;
    }
    else{
        return false;
    }
}

//constructor implictly calls superclass constructor and passes arguments
Admin :: Admin(std::string a , std::string b) : Employee(a , b){}
    
//function that calls the employeee constructor with its member variables as arguments and
//returns an Employee Object
Employee Admin :: createEmployee(std::string usernm , std::string passwd){
    Employee employee =  Employee(usernm , passwd);
    return employee;
}

