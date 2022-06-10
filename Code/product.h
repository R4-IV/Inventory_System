#ifndef product_H
#define product_H

class Product{
protected:
    //unique id for each product
    std::string ID;
    //name of the product e.g title
    std::string name;
    //price of the product
    double price;
    //amount of stock of the product
    int stock;
public:
    Product(std::string Oid , std::string Oname , double Oprice , int Ostock );
    std::string getName();
    int getStock();
    std::string getID();
    double getPrice();
    void setStock(int Ostock);
    void setPrice(double Oprice);
    virtual std::string getAuthor();
    virtual std::string getArtist();
    virtual std::string getDirector();
    virtual int getVolume();
    virtual int getIssue();
};

class Book : public Product{
private:
    std::string author;
public:
    Book(std::string Oid , std::string Oname , double Oprice , int Ostock , std::string Oauthor);
    std::string getAuthor();
};

class CD : public Product{
private:
    std::string artist;
public:
    CD(std::string Oid , std::string Oname , double Oprice , int Ostock , std::string Oartist);
    std::string getArtist();
};

class DVD : public Product{
private:
    std::string director;
public:
    DVD(std::string Oid , std::string Oname , double Oprice , int Ostock , std::string Odirector);
    std::string getDirector();
};

class Magazine : public Product{
private:
    int volume;
    int issue;
public:
    Magazine(std::string Oid , std::string Oname , double Oprice , int Ostock , int Ovolume , int Oissue);
    int getVolume();
    int getIssue();
};
#endif
