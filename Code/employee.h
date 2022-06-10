#ifndef employee_H
#define employee_H
class Employee {
private:
    //employee members store variables
    std::string username;
    std::string password;
    
public:
    Employee(std::string usernm , std::string passwd);
    bool verifyPassword(std::string passwd);
    std::string getUsername();
    bool verifyUsername(std::string usernm);
};


class Admin : public Employee {
public:
    Admin(std::string a , std::string b);
    Employee createEmployee(std::string usernm , std::string passwd);
};
#endif
