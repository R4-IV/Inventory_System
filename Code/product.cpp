#include "dependencies.h"


    
//product constructor
Product :: Product(std::string Oid , std::string Oname , double Oprice , int Ostock ){
    ID = Oid;
    name = Oname;
    price = Oprice;
    stock = Ostock;
}
    
    
//returns the objects name
std::string Product :: getName(){
    return name;
}
//returns the objects ID
std::string Product :: getID(){
    return ID;
}
//returns the amount of stock of the object
int Product :: getStock(){
    return stock;
}
//returns the object price
double Product :: getPrice(){
    return price;
}
//sets the current object stock to the provided int
void Product :: setStock(int Ostock){
    stock = Ostock;
}
//sets current object price to the provided double
void Product:: setPrice(double Oprice){
    price = Oprice;
}
//virtual functions , Using a vector of pointers as storage for Product objects this eliminates object slicing however reduces the abillity to .access derived
//class methods hence virtual functions are used for later overriding.
std::string Product :: getAuthor(){
    return "";
        
}
std::string Product :: getDirector(){
    return "";
}
std::string Product :: getArtist(){
    return "";
}
int Product :: getVolume(){
    return 0;
}
int Product :: getIssue(){
    return 0;
}


Book :: Book(std::string Oid , std::string Oname , double Oprice , int Ostock , std::string Oauthor) : Product(Oid , Oname , Oprice , Ostock){
    author = Oauthor;
}
    //function returns the book objects author
std::string Book :: getAuthor(){
    return author;
}



CD :: CD(std::string Oid , std::string Oname , double Oprice , int Ostock , std::string Oartist) : Product(Oid , Oname , Oprice , Ostock){
    artist = Oartist;
}
    //overriden virtual method returns cd object artist
std::string CD :: getArtist(){
    return artist;
}




DVD :: DVD(std::string Oid , std::string Oname , double Oprice , int Ostock , std::string Odirector) : Product(Oid , Oname , Oprice , Ostock){
    director = Odirector;
}
    //returns director
std::string DVD :: getDirector(){
    return director;
}



Magazine :: Magazine(std::string Oid , std::string Oname , double Oprice , int Ostock , int Ovolume , int Oissue) : Product(Oid , Oname , Oprice , Ostock){
    volume = Ovolume;
    issue = Oissue;
}
    //function getters
int Magazine :: getVolume(){
    return volume;
}
    
int Magazine :: getIssue(){
    return issue;
}



