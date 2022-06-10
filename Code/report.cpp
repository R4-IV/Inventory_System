#include "dependencies.h"

//functions to fill the created vectors to their respective size
std::vector<double> Report :: makeSales(){
    std::vector<double> vec(5);
    std::fill(vec.begin() , vec.end() , 0);
    return vec;
}
    
std::vector<int> Report :: makeAmountSold(){
    std::vector<int> vec(4);
    std::fill(vec.begin() , vec.end() , 0);
    return vec;
}
    

//constructor
Report :: Report(){
    sales = makeSales();
    amountSold = makeAmountSold();
}
    
//function accepts a string vector of arguments and allocates them to the correct container
void Report :: recordSale(std::vector<std::string> args){
    //function sell item has a chance to return an empty vector this is here to catch that
    if(args.size() == 0){
        return;
    }
    //updates the current running total
    sales[0] += std::stod(args[1]);
        
    //cases based on the first number of the product id
    //allocated to the correct container based on item type
    switch(std::stoi(args[0])){
            //Book
        case 1:{
            sales[1] += std::stod(args[1]);
            amountSold[0] += std::stoi(args[2]);
            break;
        }
            //CD
        case 2:{
            sales[2] += std::stod(args[1]);
            amountSold[1] += std::stoi(args[2]);
            break;
        }
            //DVD
        case 3:{
            sales[3] += std::stod(args[1]);
            amountSold[2] += std::stoi(args[2]);
            break;
        }
            //Magazine
        case 4:{
            sales[4] += std::stod(args[1]);
            amountSold[3] += std::stoi(args[2]);
            break;
        }
    }
}
    
//function prints report to the console using values from member variable vectors
void Report :: printReport(){
    std::cout << "-----SALES REPORT-----" << std::endl;
    //std::fixed < std::setprecision used to get doubles to display to 2 decimal places
    //total sales
    std::cout << "Total Sales: £" << std::fixed << std::setprecision(2) << sales[0] << std::endl;
    std::cout <<std::endl;
    //sales by item type
    std::cout << "Sales by item type:" <<std::endl;
    std::cout <<std::endl;
    std::cout<<"Total Book Sales £" << std::fixed << std::setprecision(2) << sales[1] << std::endl;
    std::cout<<"Books Sold : " << amountSold[0] << std::endl;
    std::cout <<std::endl;
    std::cout<<"Total CD Sales £" << std::fixed << std::setprecision(2) << sales[2] << std::endl;
    std::cout<<"CDs Sold : " << amountSold[1] << std::endl;
    std::cout <<std::endl;
    std::cout<<"Total DVD Sales £" << std::fixed << std::setprecision(2) << sales[3] << std::endl;
    std::cout<<"Dvds Sold : " << amountSold[2] << std::endl;
    std::cout <<std::endl;
    std::cout<<"Total Magazine Sales £" <<std::fixed << std::setprecision(2) << sales[4] << std::endl;
    std::cout<<"Magazines Sold : " << amountSold[3] << std::endl;
}

