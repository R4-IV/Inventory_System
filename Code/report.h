#ifndef report_H
#define report_H
class Report{
private:
    //creates vectors to store sales data
    std::vector<double> sales;
    std::vector<int> amountSold;
    std::vector<double> makeSales();
    std::vector<int> makeAmountSold();
    
public:
    //constructor
    Report();
    void recordSale(std::vector<std::string> args);
    void printReport();
};
#endif
