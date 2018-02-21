#include <iostream>
#include <string>
using namespace std;

class Investment
{
public:
    Investment(string name, int price);
    string name() const;
    int purchasePrice() const;
    virtual bool fungible() const;
    virtual string description() const = 0;
    virtual ~Investment();
    
private:
    string investmentName;
    int investmentPrice;
};

class Painting: public Investment
{
public:
    Painting(string name, int price);
    virtual string description() const;
    virtual ~Painting();
};

class Stock: public Investment
{
public:
    Stock(string name, int price, string description);
    virtual bool fungible() const;
    virtual string description() const;
    virtual ~Stock();
private:
    string tickerString;
};

class House: public Investment
{
public:
    House(string name, int price);
    virtual string description() const;
    virtual ~House();
};

Investment::Investment(string name, int price):
    investmentName(name), investmentPrice(price)
{}

string Investment::name() const
{
    return investmentName;
}

int Investment::purchasePrice() const
{
    return investmentPrice;
}

bool Investment::fungible() const
{
    return false;
}

Investment::~Investment()
{
}

Painting::Painting(string name, int price) : Investment(name, price)
{
}


string Painting::description() const
{
    return "painting";
}

Painting::~Painting()
{
    cout<<"Destroying "<<name()<<", a "<<description()<<endl;
}

Stock::Stock(string name, int price, string ticker) : Investment(name, price), tickerString(ticker)
{
}

bool Stock::fungible() const
{
    return true;
}

string Stock::description() const
{
    return "stock trading as " + tickerString;
}

Stock::~Stock()
{
    cout<<"Destroying "<<name()<<", a stock holding"<<endl;
}

House::House(string name, int price) : Investment(name, price)
{
}

string House::description() const
{
    return "house";
}

House::~House()
{
    cout<<"Destroying the "<<description()<<" "<<name()<<endl;
}

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

//int main()
//{
//    Investment* portfolio[4];
//    portfolio[0] = new Painting("Salvator Mundi", 450300000);
//    // Stock holdings have a name, value, and ticker symbol
//    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
//    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
//    portfolio[3] = new House("4 Privet Drive", 660000);
//
//    for (int k = 0; k < 4; k++)
//        display(portfolio[k]);
//
//    // Clean up the investments before exiting
//    cout << "Cleaning up" << endl;
//    for (int k = 0; k < 4; k++)
//        delete portfolio[k];
//}

