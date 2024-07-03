#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Product class
class Product{
public:
    string name;
    double price;

    Product(string n, double p) : name(n), price(p) {}
};

// Abstract class(Transaction)
class Transaction{
protected:
    vector<pair<Product, int>>items;

public:
    // Function to add items
    void addItem(Product product,int quantity)
    {
        items.push_back(make_pair(product, quantity));
    }

    // Function to calculate total price of transaction
    double calculateTotal()
    {
        double total=0;
        for(const auto& item : items) {
            total+=item.first.price*item.second;
        }
        return total;
    }

    // Function to get items...
    vector<pair<Product,int>>getItems()
    {
        return items;
    }
};

// Class for cart,inherits from Transaction
class Cart : public Transaction {
public:
    //display cart
    void displayCart()
    {
        if(items.empty())
        {
            cout<<"-------------Your Cart is empty!!!------------\n";
            return;
        }
        for(const auto& item : items)
        {
            cout<<item.second<<" x "<<item.first.name<<" - Rs."<<(item.first.price * item.second)<<"\n";
        }
        cout<<"-----------------------------------------\n";
        cout<<"Total: Rs."<<calculateTotal()<<endl;
    }
};

//class for bills, inherits from Transaction
class BillPrinter : public Transaction{
private:
    string customerName;
    string phoneNumber;
    string upiid;
    int upin;
    string cno;
    string edate;
    int cvv;
    char paymentMethod;

   

public:
    // Constructor overloading
    BillPrinter(string name, string phone) : customerName(name), phoneNumber(phone) {}

    BillPrinter(string id, int upno) : upiid(id), upin(upno) {}

    BillPrinter(string no, string ed, int cv) : cno(no), edate(ed), cvv(cv) {}

    // Function to set payment method
    void setPaymentMethod(char method)
    {
        paymentMethod=method;
    }
    // Function to set items in the bill
    void setItems(vector<pair<Product, int>> items)
    {
        this->items=items;
    }

    // Function to print bill
    void printBill()
    {
        cout<<"Customer Name: "<<customerName<<endl;
        cout<<"Phone Number: "<<phoneNumber<<endl;
        if (paymentMethod=='U')
        {
            char ch;
            cout<<"******UPI TRANSACTION*****"<<endl;
            cout<<"Do you authorize this transaction(Y/N):";
            cin>>ch;
            if (ch=='Y')
                cout<<"Verification Successful";
            else
                cout<<"Please Verify again";
        }

        else if(paymentMethod=='R')
        {
            int cho;
            cout<<"Directing to Payments gateway"<<endl;
            cout<<"Which payments option do you want to use:"<<endl;
            cout<<"1.Axis Bank     2.Indian Bank      3.SBI"<<endl;
            cout<<"Enter your bank option:";
            cin>>cho;
            if(cho==1)
            {
                char c;
                cout<<"Welcome to Axis Bank Portal"<<endl;
                cout<<"Do you authorize this transaction (Y/N):";
                cin>>c;
                if(c=='Y')
                {
                    cout<<"Thanks for using our Portal \n Your transaction was a success";
                }
                else
                {
                    cout<<"Error during transaction";
                    exit(0);
                }
            }
            else if(cho==2)
            {
                char c;
                cout<<"Welcome to Indian Bank Portal"<<endl;
                cout<<"Do you authorize this transaction (Y/N):";
                cin>>c;
                if(c == 'Y')
                {
                    cout<<"Thanks for using our Portal \n Your transaction was a success";
                }
                else
                {
                    cout<<"Error during transaction";
                    exit(0);
                }
            }

            else if(cho==3)
            {
                char c;
                cout<<"Welcome to SBI Portal"<<endl;
                cout<<"Do you authorize this transaction (Y/N):";
                cin>>c;
                if(c == 'Y')
                {
                    cout<<"Thanks for using our Portal \n Your transaction was a success";
                }
                else
                {
                    cout<<"Error during transaction";
                    exit(0);
                }
            }

            else
            {
                cout<<"OOPS Invalid choice";
                exit(0);
            }
        }
        cout << "-----------------------------------------\n";
        cout << "Products:\n";
        for (const auto& item : items)
        {
            cout<<item.second<<" x "<<item.first.name<<" - Rs."<<item.first.price*item.second<<endl;
        }
        cout<<"-----------------------------------------\n";
        cout<<"Total: Rs."<<calculateTotal()<<endl;
        cout<<"Your order received within next five working days!!"<<endl;
        cout<<"**********THANKS FOR SHOPPING WITH US**********"<<endl;
    }
};

int main()
{
    // User input for name,phone number and pin number 
    string name;
    string phoneNumber;
    double pin;
    cout << "          Welcome to EASY-PAY!         \n";
    cout << "Please enter your name: ";
    getline(cin, name);
    cout << "Please enter your phone number: ";
    cin>>phoneNumber;
    cout<<"Enter Your PIN CODE:";
    cin>>pin;
    if(100000>pin && pin>999999)
    {
        cout<<"Delivery is not available for the selected location\n";
        exit(0);
        
    }
    cout<<"Delivery is available for the selected location\n";


    //cart object
    Cart cart;

    //Using vector to list out available products
    vector<Product> availableProducts = {{"Milk      ", 35.00}, {"Bread      ", 20.00},{"Egg       ",6.000},{"Rice      ",70.00},
                                        {"Sugar     ",50.00},{"Salt      ",20.00},{"Pasta     ",25.00},{"Tea Powder",50.00},
                                        {"Detergent ",25.00},{"Ramen     ",60.00},{"Sunfeast  ",20.00},{"Dairy milk",120.0},
                                        {"Cookingoil",160.0},{"Fruit Jam ",75.00},{"Diapers   ",130.0},{"Toothpaste",35.00},
                                        {"Sanitizer ",80.00},{"Wheat    ",46.00},{"Flour     ",30.00},{"Stapler   ",25.00},
                                        {"Water can ",40.00},{"Pen Combo ",70.00},{"Candles   ",10.00},
                                        {"Notebooks ",35.00},{"ShoePolish",75.00},{"Ice cream(Vennela)",500.0}};

    // Displaying available products
    cout<<"Products available:\n";
    for (int i =0;i<availableProducts.size();++i) {
        cout<<i+1<<". "<<availableProducts[i].name<<" - Rs."<<availableProducts[i].price<<"\t\t";
        if(i==3||i==7||i==11||i==15||i==19||i==23)
        {
            cout<<"\n";
        }
    }

    // selecting items to purchase...
    int choice, quantity;
    do{
        cout<<"\n"<<"Enter the number corresponding to the product you want to buy (0 to finish): ";
        cin>>choice;
        if(choice!= 0)
        {
            cout<<"Enter quantity: ";
            cin>>quantity;
            cart.addItem(availableProducts[choice - 1], quantity);
            cout<<"Item added to cart.\n";
            cout<<"Products available:\n";
            for(int i=0;i<availableProducts.size();++i) 
            {
                cout<<i + 1<<". "<<availableProducts[i].name<<" - Rs."<<availableProducts[i].price<<"\t\t";
                if(i==3||i==7||i==11||i==15||i==19||i==23)
                {
                  cout<<"\n";
                }
            }

        }
    } while(choice != 0);

    //Used to display cart after selection of products
    cout<<"Your Cart:\n";
    cart.displayCart();

    //Choosing payment method(cash,card,UPI)
    char paymentMethod;
    cout<<"Choose payment method(U for UPI, C for cash, R for card): ";
    cin>>paymentMethod;

    //using billprinter class
    BillPrinter bill(name,phoneNumber);
    bill.setPaymentMethod(paymentMethod);
    // Declaring essentials...
    string idd, cno, edate;
    int cvv,cpin;
    
    //user input for id and pin if payment method is UPI
    if (paymentMethod=='U')
    {
        cout<<"Please Enter your upiid:";
        cin>>idd;
        cout<<"Validating ID...... \n Successfully validated\n";
        cout<<"Please Enter your UPI Pin: \n (Please make sure you are alone and confidential):";
        cin>>cpin;
        BillPrinter bill(idd,cpin);
    }
    //if the payment is by card
    else if(paymentMethod=='R')
    {
        cout<<"Please enter your card number:";
        cin>>cno;
        cout<<"Please enter expiry date:";
        cin>>edate;
        cout<<"Please enter CVV(secure):";
        cin>>cvv;
        BillPrinter bill(cno, edate, cvv);
    }
    else if(paymentMethod=='C')
    {
        cout<<"Please hand over the cash on delivery"<<endl;
    }
  
    else
    {
        cout<<"Invalid Choice \n Please try again";
        exit(0);
    }
    //items for billbill
    bill.setItems(cart.getItems());

    // Print bill
    cout << "Your Bill:\n";
    bill.printBill();

    return 0;
    
}
