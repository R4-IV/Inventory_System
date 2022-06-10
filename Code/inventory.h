#ifndef inventory_H
#define inventory_H
class Inventory{
private:
    //using shared pointer vector to avoid Object slicing and heap management
    std::vector<std::shared_ptr<Product>> productList;
public:
    std::vector<std::string> sellItem(std::shared_ptr<Product> obj , int amount);
    void loadInventory();
    void saveInventory();
    void addInventory(std::shared_ptr<Product> obj, int amount);
    void correctInventory(std::shared_ptr<Product> obj, int amount);
    std::vector<std::shared_ptr<Product>> & returnProducts();
    void addItem(std::shared_ptr<Product> obj);
};
#endif
