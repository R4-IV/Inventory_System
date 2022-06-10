#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "employee.cpp"
#include "product.cpp"
#include "inventory.cpp"
#include "report.cpp"
#include "dependencies.h"

//testing employee admin constructor
TEST_CASE("Testing Admin Constructor"){
    Admin adminstrator  = Admin("John" , "JS05");
    REQUIRE(adminstrator.getUsername().compare("John") == 0);
    REQUIRE(adminstrator.verifyPassword("JS05"));
}
//testing inventory class methods
TEST_CASE("Inventory Class tests"){
    Inventory inventory = Inventory();
    std::shared_ptr<Product> test (new Book("10001" , "Harry Potter" , 19.99 ,50 , "JK ROWLING" ));
    std::vector<std::string> result = inventory.sellItem(test , 30);
    REQUIRE(test->getStock() == 20);
    inventory.sellItem(test , 30);
    REQUIRE(test->getStock() != 0);
    std::shared_ptr<Product> test2 (new CD("20001" , "PlaceHolder" , 19.99 ,90 , "PlaceHolder" ));
    inventory.addInventory(test2 , 50);
    REQUIRE(test2->getStock() == 140);
    inventory.correctInventory(test2 , 10);
    REQUIRE(test2->getStock() == 10);
    REQUIRE(result[0].at(0) - '0' == 1);
}
//testing adminstrator creation of new employee
TEST_CASE("Testing Creation of New Employee"){
    Admin adminstrator  = Admin("John" , "JS05");
    Employee employee = adminstrator.createEmployee("Jane" , "JD07");
    REQUIRE(employee.verifyUsername("Jane"));
    REQUIRE(employee.verifyPassword("JD07"));
}


            


                                       










































