#include "dependencies.h"

//Vector used to store created employees
std::vector<Employee> employeeList;

//hard coded adminstrator object can be used to login to the system
Admin admin = Admin("admin" , "admin");
//Active Employee used as a placeholder initially until someone logs on and then overwrites them. Variable used to diplay employee name as prompt.
Employee active = Employee("placeholder" , "placeholder");

//Inventory and Report objects used to call their methods
Inventory inventory = Inventory();
Report report = Report();

//checks if inventory was already loaded from file
bool wasLoaded = false;
//tracks if the logged in user is typof Admin
bool isAdmin = false;
//tracks if there is a currently logged in user is used in the logout function
bool isLoggedIn = false;

//variables used to store the first occurence of an item type in a product array
//they are used for easy indexing to return user selected product
bool firstBook = false;
bool firstCd = false;
bool firstDvd = false;
bool firstMagazine = false;

int beginBook = -1;
int beginCd = -1;
int beginDvd = -1;
int beginMagazine = -1;


//function displays the press Enter to continue prompt for the user on the console
//This is done as some data immiediatly dissapears when the options return
// I considered doing a delay with usleep() howwever this turned out to work better
void pressEnter(){
    std::cout << "Press Enter to Continue";
    std::cin.ignore(1000 , '\n');
    std::cin.ignore(1000 , '\n');
}

//function that prompts the user to select an integer between 1-4 based on the desired
//derived class product
int returnItemType(){
    std::cout << "Select Item Type:" <<std::endl;
    std::cout << "[1] Book" <<std::endl;
    std::cout << "[2] CD:" <<std::endl;
    std::cout << "[3] DVD:" <<std::endl;
    std::cout << "[4] Magazine:" <<std::endl;
    
    int userSelection = 0;
    //input handling loop until correct input is given
    while(true){
        std::cout << ">> ";
        std::cin >> userSelection;
        //catches type mismatches
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            std::cout << "Invalid Input" <<std::endl;
            continue;
        }
        //catches out of bounds
        else if(userSelection > 4 || userSelection < 1){
            std::cout << "Invalid Input" <<std::endl;
            continue;
        }
        else{
            break;
        }
    }
    //returns the selection
    return userSelection;
}

//similarly to above the function will return a quantity between 1 - 999
//based on user selection
int returnQuantity(){
    int selection;
    std::cout << "Enter Quantity: ";
    while(true){
        std::cout << ">> ";
        std::cin >> selection;
        if(std::cin.fail()){
            std::cin.clear();
            //ignores 1000 characters effectively clearing the line
            std::cin.ignore(1000 , '\n');
            std::cout << "Invalid Input" <<std::endl;
            continue;
        }
        //makes sure quantity is not negative
        else if(selection > 999 || selection < 1){
            std::cout << "Invalid Input" <<std::endl;
            continue;
        }
        else{
            break;
        }
    }
    return selection;
}

//function that will return a ptr to Product object based on the user input
std::shared_ptr<Product> makeProduct(int ItemType){
    //variables that are required to create a Product object
    std::string name;
    std::string id;
    int inventory;
    double price;
    std::string optional;
    int vol;
    int issue;
    
    //captures user input for name with no error handling
    std::cout << "Enter the product name/title >> ";
    std::getline(std::cin , name);
    std::getline(std::cin , name);
    
    //captures user input for id error handling ensures all 5 characters are integers
    //between 0 - 9
    while(true){
        std::cout << "Please Enter a unique 5 digit ID >> ";
        std::cin >> id;
        
        bool allDigits = true;
        
        if(id.length() != 5){
            std::cout << "invalid length" <<std::endl;
            continue;
        }
        else{
            //compares to their ascii values
            for(int i = 0; i < id.length(); i++ ){
                if((int)id.at(i) < 48 || (int)id.at(i) > 57){
                    allDigits = false;
                    break;
                }
            }
            if(allDigits){
                break;
            }
            else{
                std::cout << "Invalid Input "<<std::endl;
                continue;
            }
        }
    }
    //uses standard function with error handling to set initial inventory
    inventory = returnQuantity();
    
    //captures double input with error handling, not to worried about decimal places as they are later trimmed
    while(true){
        std::cout << "Enter Item Price >> ";
        std::cin >> price;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            std::cout << "invalid Input" <<std::endl;
            continue;
        }
        else if(price < 0){
            std::cout <<"price can't be negative"<<std::endl;
            continue;
        }
        else{
            break;
        }
    }
    
    //if the item isn't a magazine it will have input for optional params
    if(ItemType != 4){
        std::cout << "Enter Optional param Author/Artist/Director >> ";
        std::getline(std::cin , optional);
        std::getline(std::cin , optional);
    }
    //if the item is a magazine we need to capture input for both issue and volumue integers();
    if(ItemType == 4){
        
        while(true){
            std::cout << "Enter Item Volume >> ";
            std::cin >> vol;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(1000 , '\n');
                std::cout << "invalid Input" <<std::endl;
                continue;
            }
            else if(vol < 0){
                std::cout <<"volume can't be negative"<<std::endl;
                continue;
            }
            else{
                break;
            }
        }
        while(true){
            std::cout << "Enter Item Issue >> ";
            std::cin >> issue;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(1000 , '\n');
                std::cout << "invalid Input" <<std::endl;
                continue;
            }
            else if(issue < 0){
                std::cout <<"issue can't be negative"<<std::endl;
                continue;
            }
            else{
                break;
            }
        }
    }
    //creates a string to append itemt ype specific ids to the product
    std::string itemSpecificID;
    
    switch(ItemType){
        case 1:{
            //creates object if selected type was book
            itemSpecificID = "1";
            itemSpecificID.append(id);
            std::shared_ptr<Product> ptr (new Book(itemSpecificID, name , price , inventory , optional));
            return ptr;
            break;
            
        }
        case 2:{
            //creates object if selected type was cd
            itemSpecificID = "2";
            itemSpecificID.append(id);
            std::shared_ptr<Product> ptr (new CD(itemSpecificID, name , price , inventory , optional));
            return ptr;
            break;
            
        }
        case 3:{
            //creates object if selected type was dvd
            itemSpecificID = "3";
            itemSpecificID.append(id);
            std::shared_ptr<Product> ptr (new DVD(itemSpecificID, name , price , inventory , optional));
            return ptr;
            break;
        }
        case 4:{
            //creates object if selected type was magazine
            itemSpecificID = "4";
            itemSpecificID.append(id);
            std::shared_ptr<Product> ptr (new Magazine(itemSpecificID, name , price , inventory , vol , issue));
            return ptr;
            break;
        }
    }
    //an unconditinal return will never trigger but keeps the compiler from throwing warnings
    return NULL;
}
//function that returns a pointer to a Product object the user has chosen
std::shared_ptr<Product> selectItem(int itemType , int option = 0){
    std::vector<std::shared_ptr<Product>> allItems = inventory.returnProducts();
    //this variable will give the index offset used to return the users selected Product
    int incrementer = 1;
    //loop through all the products in the allItems vector
    for(auto iter = allItems.begin(); iter != allItems.end(); ++iter){
        //first 4 if function used to set the origin index of their respective datatype
        if((*iter)->getID().at(0) - '0' == 1 && !firstBook){
            firstBook = true;
            beginBook = iter - allItems.begin();
        }
        if((*iter)->getID().at(0) - '0' == 2 && !firstCd){
            firstCd = true;
            beginCd = iter - allItems.begin();
        }
        if((*iter)->getID().at(0) - '0' == 3 && !firstDvd){
            firstDvd = true;
            beginDvd = iter - allItems.begin();
        }
        if((*iter)->getID().at(0) - '0' == 4 && !firstMagazine){
            firstMagazine = true;
            beginMagazine = iter - allItems.begin();
        }
        //next 4 ifs print members of a specified derived class order by id
        if((*iter)->getID().at(0) - '0' == 1 && 1 == itemType){
            std::cout << "[" << incrementer++ << "] "<< "ID: " << (*iter)->getID();
            std::cout << " Title: " << (*iter)->getName() << " Author: " << (*iter)->getAuthor() << " Price: " << std::fixed << std::setprecision(2) << (*iter)->getPrice() << " Qty Available: " << (*iter)->getStock() << std::endl;
        }
        if((*iter)->getID().at(0) - '0' == 2 && 2 == itemType){
            std::cout << "[" << incrementer++ << "] "<< "ID: " << (*iter)->getID();
            std::cout << " Title: " << (*iter)->getName() << " Artist: " << (*iter)->getArtist() << " Price: " << std::fixed << std::setprecision(2) << (*iter)->getPrice() << " Qty Available: " << (*iter)->getStock() << std::endl;
        }
        if((*iter)->getID().at(0) - '0' == 3 && 3 == itemType){
            std::cout << "[" << incrementer++ << "] "<< "ID: " << (*iter)->getID();
            std::cout << " Title: " << (*iter)->getName() << " Director: " << (*iter)->getDirector() << " Price: " << std::fixed << std::setprecision(2) << (*iter)->getPrice() << " Qty Available: " << (*iter)->getStock() << std::endl;
        }
        if((*iter)->getID().at(0) - '0' == 4 && 4 == itemType){
            std::cout << "[" << incrementer++ << "] "<< "ID: " << (*iter)->getID();
            std::cout << " Title: " << (*iter)->getName() << " Volume: " << (*iter)->getVolume() << " Issue " << (*iter)->getIssue()  << " Price: " << std::fixed << std::setprecision(2) << (*iter)->getPrice() << " Qty Available: " << (*iter)->getStock() << std::endl;
        }
    }
    std::cout<<std::endl;
    //if the incrementer did not increment then there are no products to choose from.
    //returns null which is handled in inventory functions such as sell item or add stock
    if(incrementer == 1){
        std::cout << "No items available" << std::endl;
        return NULL;
    }
    //optional argument used to exit function early used when the items need to be displayed an not returned
    if(option != 0){
        return NULL;
    }
    //handles user integer selection
    int selection;
    bool isInvalid = true;
    std::cout <<"Select an Item: " << std::endl;
    while(isInvalid){
        std::cout << ">> ";
        std::cin >> selection;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(256 , '\n');
            std::cout << "Invalid Input" <<std::endl;
            continue;
        }
        else if(selection > incrementer || selection < 1){
            std::cout << "Invalid Input" <<std::endl;
            continue;
        }
        else{
            break;
        }
    }
    //creates offset based on what type the object was
    int index;
    if(itemType == 1){
        index = selection - 1 + beginBook;
    }
    else if(itemType == 2){
        index = selection - 1 + beginCd;
    }
    else if(itemType == 3){
        index = selection - 1 + beginDvd;
    }
    else if(itemType == 4){
        index = selection - 1 + beginMagazine;
    }
    
    std::shared_ptr<Product> selected = allItems[index];
    return selected;
}

//function that takes all 10 of the user available options and implemets them using existing functions and class methods.
void performAction(int selectedOption){
    
    switch(selectedOption){
            //sell item
        case 1:{
            int selection = returnQuantity();
            report.recordSale(inventory.sellItem(selectItem(returnItemType()) , selection));
            std::cout<<std::endl;
            
            break;
        }
        case 2:{
            //addStock
            int selection = returnQuantity();
            inventory.addInventory(selectItem(returnItemType()) , selection);
            std::cout<<std::endl;
            
            break;
        }
        case 3:{
            //overwrite Stock
            int selection = returnQuantity();
            inventory.correctInventory(selectItem(returnItemType()) , selection);
            std::cout<<std::endl;
            
            break;
        }
        case 4:{
            //create new item
            inventory.addItem(makeProduct(returnItemType()));
            break;
        }
        case 5:{
            //save inventory to file
            inventory.saveInventory();
            std::cout << "Inventory saved" << std::endl;
            pressEnter();
            std::cout << std::endl;
            
            
            break;
        }
        case 6:{
            //Load inventory from file
            if(wasLoaded){
                std::cout << "Inventory already Loaded in this session" << std::endl;
                std::cout<<std::endl;
            }
            else{
                inventory.loadInventory();
                std::cout << "Loaded succesfully" << std::endl;
                std::cout << std::endl;
                wasLoaded = true;
            }
            pressEnter();
            break;
        }
        case 7:{
            //print sales report
            report.printReport();
            std::cout<<std::endl;
            pressEnter();
            std::cout << std::endl;
            break;
        }
        case 8:{
            //list items of a selected item type
            selectItem(returnItemType() , 1);
            pressEnter();
            
            
            break;
        }
        case 9:{
            //Logs the user out by manipulating the bool values used in the main function
            isLoggedIn = false;
            isAdmin = false;
            std::cout<< "Logged out" <<std::endl;
            std::cout<<std::endl;
            break;
        }
            //creates a new user and adds them to the employee List
        case 10:
            std::string uname;
            std::string pass;
            std::string temp;
            
            std::cout <<"User Creation " << std::endl;
            std::cout << "Enter a username >> ";
            std::cin >> uname;
            std::getline(std::cin , temp);
            std::cout << "Enter a password >> ";
            std::cin >> pass;
            std::getline(std::cin , temp);
            employeeList.push_back(admin.createEmployee(uname , pass));
            std::cout << "Account created" << std::endl;
            std::cout<<std::endl;
    }
}

int main(){
    
    //main command prompt loop
    while(true){
        if(!isLoggedIn){
            std::cout << "Welcome to SMS (Stock Management System):" << std::endl;
            std::cout << "Select an option to continue:" << std::endl;
            std::cout << "[1] Login" << std::endl;
            std::cout << "[2] Exit" << std::endl;
            int selection;
            std::cout << ">> ";
            std::cin >> selection;
            //error handling for login or exit choice
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(256 , '\n');
                std::cout << "Invalid input" <<std::endl;
                std::cout << std::endl;
                continue;
            }
            if(selection != 1 && selection != 2){
                std::cout << "Invalid input" <<std::endl;
                std::cout << std::endl;
                continue;
            }
            //allows the user to leave the program
            if(selection == 2){
                exit(0);
            }
            
            std::string username;
            std::string password;
            std::cout << "username >> ";
            std::cin >> username;
            std::cout << "password >> ";
            std::cin >> password;
            std::cout<<std::endl;
            std::cout << employeeList.size() <<std::endl;
            //username and password verification
            if(admin.verifyUsername(username) && admin.verifyPassword(password)){
                isAdmin = true;
                isLoggedIn = true;
                continue;
            }
            else{
                //checks if supplied details live in the employee list
                for(auto eIter = employeeList.begin() ; eIter != employeeList.end(); ++eIter){
                    if((*eIter).verifyUsername(username) && (*eIter).verifyPassword(password)){
                        isLoggedIn = true;
                        //active user has their name set as the prompt
                        active = *eIter;
                        continue;
                    }
                }
            }
            if(!isLoggedIn){
                std::cout << "Invalid Login details" << std::endl;
                continue;
            }
            //happens if user is logged in
        }
        else{
            //displays options available to the user
            std::cout << "-----OPTIONS-----" << std::endl;
            std::cout << "[1] Sell Product" << std::endl;
            std::cout << "[2] Add Stock To Product" << std::endl;
            std::cout << "[3] Correct Product Stock" << std::endl;
            std::cout << "[4] Add New Product" << std::endl;
            std::cout << "[5] Save Inventory To File" << std::endl;
            std::cout << "[6] Load Inventory From File" << std::endl;
            std::cout << "[7] View Sales Report" << std::endl;
            std::cout << "[8] List Products" << std::endl;
            std::cout << "[9] Logout" << std::endl;
            
            //additional option will only appear if the use is an Admin
            if(isAdmin){
                std::cout << "[10] Add Employee" << std::endl;
                std::cout<<std::endl;
                std::cout << "admin >> ";
            }
            else{
                //sets the prompt as the active employee username
                std::cout<<std::endl;
                std::cout << active.getUsername() << " >> ";
            }
            //error handling for the user to select an option
            int choice;
            std::cin >> choice;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(256 , '\n');
                std::cout << "Invalid input" <<std::endl;
                std::cout << std::endl;
                continue;
            }
            
            if(choice > 10 || choice < 1){
                std::cout << "Invalid input" <<std::endl;
                std::cout << std::endl;
                continue;
            }
            //option 10 will fail for the user but not for the admin meaning it cant be accessed by a regular employee even if its just invisible to them
            if(choice == 10 && isAdmin == false){
                std::cout << "Invalid input" <<std::endl;
                std::cout << std::endl;
                continue;
            }
            //calls function to carry out the selected option
            performAction(choice);
            continue;
        }
    }
    return 0;
}


