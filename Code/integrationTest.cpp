
#include "stockManagement.h"
#include "product.cpp"
#include "inventory.cpp"
#include "employee.cpp"
#include <stdlib.h>
#include <vector>
#include "Report.cpp"


int main(){
    
       std::shared_ptr<Product> a  (new Book("100010" , "HP ST" , 19.99 , 10 , "JK ROWLING"));
       
       std::shared_ptr<Product> c  (new Book("100004" , "HP ST" , 19.99 , 10 , "JK ROWLING"));
       
       std::shared_ptr<Product> d  (new Book("100000" , "HP ST" , 19.99 , 10 , "JK ROWLING"));
       
       std::shared_ptr<Product> e  (new Book("100023" , "HP ST" , 19.99 , 10 , "JK ROWLING"));
       
       std::shared_ptr<Product> f  (new CD("204500" , "Imagine" , 3.50 , 19 , "John Lenon"));
       
       std::shared_ptr<Product> g  (new CD("208500" , "Thats Life" , 8.50 , 48 , "Frank Sinatra"));
       

    Inventory inventory = Inventory();

       inventory.addItem(a);
       inventory.addItem(c);
       inventory.addItem(d);
       inventory.addItem(e);
       inventory.addItem(c);
       inventory.addItem(f);
       inventory.addItem(g);
       
    
    
    Report report = Report();
    
    report.recordSale(inventory.sellItem(c , 7));
    report.recordSale(inventory.sellItem(c , 7));
    report.recordSale(inventory.sellItem(g , 24));
    report.recordSale(inventory.sellItem(d , 2));
    report.recordSale(inventory.sellItem(f , 19));
    
    report.printReport();
    
    inventory.saveInventory();
    
    
    std::vector<std::shared_ptr<Product>> b = inventory.returnProducts();
    return 0;
}

