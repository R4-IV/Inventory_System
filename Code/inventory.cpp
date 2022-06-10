#include "dependencies.h"


    
//function to sell items
std::vector<std::string> Inventory :: sellItem(std::shared_ptr<Product> obj , int amount){
    //returns vector of arguments to record sale in report.cpp based on the input it recieves
    //it can return an empty vector of args;
    //happens when the user attempts to sell or add inventory to item types that have no memebrs
    //caught in report
    std::vector<std::string> returnVec;
    if(obj == NULL){
        return returnVec;
    }
    //if stock is too low will return an empty vector which is then caught in report
    if(obj->getStock() < amount ){
        std::cout << "Not enough stock" << std::endl;
        return returnVec;
    }
    else{
        //decrements the available stock
        int temp = obj->getStock();
        obj->setStock(temp - amount);
        double tempPrice = obj->getPrice() * amount;
        //returns the values required for salerecording as a string array
        int tempItemType = obj->getID().at(0) - '0';
        std::cout <<tempItemType << " itemtype in sale" << std::endl;
        returnVec.push_back(std::to_string(tempItemType));
        returnVec.push_back(std::to_string(tempPrice));
        returnVec.push_back(std::to_string(amount));
        return returnVec;
    }
}
    
//function that retrieves the contents of the inventory from a file and loads all the objects into the heap.
void Inventory :: loadInventory(){
    std::string currentLine;
    //selected file to read from
        std::ifstream inputFile("inventory.txt");
    //checks if input file is open
        if(inputFile.is_open()){
            //tokenises the supplied line from the file by using "!" as delimiter , previously used spaces however many products have multiword names hence splitting them.
        while(std::getline(inputFile,currentLine)){
            int tokStart = 0;
            int tokEnd = 0;
            std::vector<std::string> args;
            for(int i = 0; i < currentLine.length(); i++){
                //handles the last word in the line
                if(i == currentLine.length() -1){
                    args.push_back(currentLine.substr(tokStart , tokEnd - tokStart + 1));
                }
                if(currentLine.at(i) == '!'){
                    args.push_back(currentLine.substr(tokStart , tokEnd - tokStart));
                    tokStart = tokEnd + 1;
                }
                tokEnd++;
            }
            int tempItemType = args[0].at(0) - '0';
                
            //creates a derived class object based on the first number in its ID
            switch(tempItemType){
                case 1:{
                    std::shared_ptr<Product> product (new Book(args[0] , args[1] , std::stod(args[2]) , std::stoi(args[3]) , args[4]));
                    addItem(product);
                    break;
                }
                case 2:{
                    std::shared_ptr<Product> product (new CD(args[0] , args[1] , std::stod(args[2]) , std::stoi(args[3]) , args[4]));
                    addItem(product);
                    break;
                }
                case 3:{
                    std::shared_ptr<Product> product (new DVD(args[0] , args[1] , std::stod(args[2]) , std::stoi(args[3]) , args[4]));
                    addItem(product);
                    break;
                }
                case 4:{
                    std::shared_ptr<Product> product (new Magazine(args[0] , args[1] , std::stod(args[2]) , std::stoi(args[3]) , std::stoi(args[4]) , std::stoi(args[5])));
                    addItem(product);
                    break;
                }
            }
        }
            //closes inputStream this would have died when out of scope however its good practice to manually close it.
        inputFile.close();
    }
}
    
    //function used to save inventory to a data
    void Inventory :: saveInventory(){
        std::ofstream output("inventory.txt");
        //builds a string for each entry in the productList in a simillar style to json
        for(auto iter = productList.begin(); iter != productList.end(); ++iter){
            
            int tempItemType = (*iter)->getID().at(0) - '0';
            
            std::string jsonOBJ;
            jsonOBJ.append((*iter)->getID());
            jsonOBJ.append("!");
            jsonOBJ.append((*iter)->getName());
            jsonOBJ.append("!");
            jsonOBJ.append(std::to_string((*iter)->getPrice()));
            jsonOBJ.append("!");
            jsonOBJ.append(std::to_string((*iter)->getStock()));
            
            //custom derived class specific output is added here
            switch(tempItemType){
                case 1:{
                    jsonOBJ.append("!");
                    jsonOBJ.append((*iter)->getAuthor());
                    break;
                }
                case 2:{
                    jsonOBJ.append("!");
                    jsonOBJ.append((*iter)->getArtist());
                    break;
                }
                case 3:{
                    jsonOBJ.append("!");
                    jsonOBJ.append((*iter)->getDirector());
                    break;
                }
                case 4:{
                    jsonOBJ.append("!");
                    jsonOBJ.append(std::to_string((*iter)->getVolume()));
                    jsonOBJ.append("!");
                    jsonOBJ.append(std::to_string((*iter)->getIssue()));
                    break;
                }
            }
            //writes to the actual file and sets up each product as its own line
            output << jsonOBJ;
            output << std::endl;
        }
        //closing output stream
        output.close();
    }
    
    //function adds an amount of items to a product pointer
    void Inventory :: addInventory(std::shared_ptr<Product> obj, int amount){
        //can recieve a null value if the user is browsing products of a type that doesn't yet
        //exist
        if(obj == NULL){
            return;
        }
        int temp = obj->getStock();
        obj->setStock(temp + amount);
    }
    //Function that overwrites the stock number with input otherwise performs similarly to the function above
    void Inventory :: correctInventory(std::shared_ptr<Product> obj, int amount){
        if(obj == NULL){
            return;
        }
        obj->setStock(amount);
    }
    
    //returns the vector product list
    std::vector<std::shared_ptr<Product>> & Inventory ::  returnProducts(){
        return productList;
    }
    
    //function checks if item exists by comparing its id with existing ids in the product list
    //will not add the item if a duplicate is found
    void Inventory :: addItem(std::shared_ptr<Product> obj){
        //inserts subsequent products in ascending order based on their ids
        if(productList.size() == 0){
            productList.push_back(obj);
        }
        else{
            for(auto iter = productList.begin(); iter != productList.end(); ++iter){
                if(obj->getID().compare((*iter)->getID()) == 0){
                    return;
                }
            }
            for(auto iter = productList.begin(); iter != productList.end(); ++iter){
                if(iter == productList.end() - 1){
                    productList.push_back(obj);
                    return;
                }
                if(std::stoi(obj->getID()) < std::stoi((*iter)->getID())){
                    productList.insert(iter , obj);
                    return;
                }
            }
        }
            
    }

