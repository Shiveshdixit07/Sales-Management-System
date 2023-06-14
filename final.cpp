#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>

using namespace std;

class Customer
{
private:
    string name;
    string address;
    string phone_number;

protected:
    string password;

public:
    string username;
    Customer() {}
    Customer(string n, string a, string p, string username, string password)
    {
        name = n;
        address = a;
        phone_number = p;
        this->username = username;
        this->password = password;
    }

    Customer(string n, string a, string p)
    {
        name = n;
        address = a;
        phone_number = p;
    }

    string getName()
    {

        return name;
    }

    string getAddress()
    {

        return address;
    }

    string getPhoneNumber()
    {

        return phone_number;
    }
    int checkPassword(string password)
    {

        if (this->password == password)
        {

            return 1;
        }
        else
        {

            return 0;
        }
    }
};

class Product
{
private:
    string name;
    double price;
    int quantity;

public:
    Product() {}
    Product(string n, double p, int q)
    {
        name = n;
        price = p;
        quantity = q;
    }

    string getName()
    {
        return name;
    }

    double getPrice()
    {
        return price;
    }

    int getQuantity()
    {
        return quantity;
    }

    void updateQuantity(int q)
    {
        quantity += q;
    }
};
class Sale
{
private:
    Customer customer;
    Product product;
    int quantity;

public:
    Sale(Customer c, Product p, int q)
    {
        customer = c;
        product = p;
        quantity = q;
    }

    double getTotal()
    {
        return product.getPrice() * quantity;
    }

    Customer getCustomer()
    {
        return customer;
    }

    Product getProduct()
    {
        return product;
    }

    int getQuantity()
    {
        return quantity;
    }
};

vector<Customer> customers;
vector<Product> products;
vector<Sale> sales;

map<string, int> cart;

class shopingCart
{
private:
    Customer customer;
    int quantity;

public:
    shopingCart() {}
    shopingCart(Customer customer)
    {
        this->customer = customer;
    }

    void addToCart(Product product, int quantity)
    {

        this->quantity = quantity;
        cart[product.getName()] = quantity;
        cout << "Product successfully added!!" << endl;
    }
    void displayCart()
    {
        map<string, int>::iterator it = cart.begin();
        cout << "----------------------------------------" + customer.getName() + " 's Shoping Cart:" + "----------------------------------------" << endl;
        for (it; it != cart.end(); it++)
        {
            cout << "-----------------" + it->first + " : ";
            cout << it->second << endl;
        }
    }
    double totalBill()
    {
        double total;
        vector<Product>::iterator p = products.begin();
        map<string, int>::iterator it = cart.begin();

        for (it; it != cart.end(); it++)
        {
            for (p; p != products.end(); p++)
            {
                if (p->getName() == it->first)
                {
                    total += it->second * p->getPrice();
                }
            }
        }
        return total;
    }
};

class Payment
{
protected:
    double m_amount;

public:
    Payment(double amount)
    {
        m_amount = amount;
    }

    virtual void processPayment() = 0;
};

class CreditCardPayment : public Payment
{

private:
    string m_cardNumber;
    string m_expirationDate;
    string cvv;

public:
    CreditCardPayment(double amount, string cardNumber, string expirationDate, string Cvv) : Payment(amount)
    {
        this->m_cardNumber = cardNumber;
        this->m_expirationDate = expirationDate;
        this->cvv = Cvv;
    }
    virtual void processPayment()
    {

        cout << "Processing credit card payment of $" << m_amount << " with card number " << m_cardNumber << endl;
        cout << "Successfully paid!!" << endl;
    }
};

class CashPayment : public Payment
{
public:
    CashPayment(double amount) : Payment(amount) {}
    virtual void processPayment()
    {

        cout << "Processing cash payment of $" << m_amount << endl;
        cout << "Successfully paid!!" << endl;
    }
};

class login : public Customer
{
private:
    string UserName;
    string Password;
    vector<Customer>::iterator c;
    vector<Product>::iterator p;

public:
    void logincheck(string username, string password)
    {
        int flag;
        this->UserName = username;
        this->Password = password;
        vector<Customer>::iterator it = customers.begin();
        for (it; it != customers.end(); it++)
        {
            if (it->username == UserName)
            {
                c = it;
                flag = it->checkPassword(Password);
            }
        }
        if (flag == 1)
        {
            cout << "Login Successful!!" << endl;
        }
        else if (flag == 0)
        {
            cout << "please try again wrong credentials!!" << endl;
            exit(1);
        }
    }

    int checkProduct(string Pname, int quantity)
    {
        vector<Product>::iterator it = products.begin();
        int flag = 0;

        for (it; it != products.end(); it++)
        {

            if (it->getName() == Pname)
            {

                if (it->getQuantity() >= quantity)
                {

                    flag = 1;
                    p = it;
                }
                else
                {
                    flag = 0;
                }
            }
        }
        if (flag == 0)
        {

            return 0;
        }
        else if (flag == 1)
        {

            return 1;
        }
    }
    void addProduct(int quantity)
    {

        shopingCart cart(*c);

        cart.addToCart(*p, quantity);
    }

    void viewCart()
    {
        shopingCart cart(*c);
        cart.displayCart();
    }
    void Payment()
    {
        int ch;
        shopingCart cart(*c);
        cout << "enter your payment choice:" << endl;
        cout << "press 1 for card payment:" << endl;
        cout << "press 2 for cash payment: " << endl;
        cin >> ch;
        if (ch == 1)
        {
            string cardno;
            string expiry_Date;
            string cvv;

            cout << "enter expiry_Datre:" << endl;
            cin >> expiry_Date;
            cout << "enter the cardNo:" << endl;
            cin >> cardno;
            cout << "enter the cvv:" << endl;
            cin >> cvv;
            CreditCardPayment obj(cart.totalBill(), cardno, expiry_Date, cvv);
            obj.processPayment();
        }
        else if (ch == 2)
        {

            CashPayment cash(cart.totalBill());
            cash.processPayment();
        }
    }
};
int count = 1;
int position = 0;
void add_customer()
{
    ofstream file("users.txt", std ::ios ::app);

    string name, address, phone_number, username, password;
    cout << "****** | Enter the details of the customer to be added | ******" << endl
         << endl;
    cout << "\tEnter name: ";
    getline(cin, name);
    cout << "\tEnter address: ";
    getline(cin, address);
    cout << "\tEnter phone number: ";
    getline(cin, phone_number);
    cout << "\tEnter username: ";
    getline(cin, username);
    cout << "\tEnter password: ";
    getline(cin, password);

    file << "Details of the customer " << count << " : " << endl;
    file << "Customer name :" << name + "\n";
    file << "Customer address :" << address + "\n";
    file << "Customer phone number : " << phone_number + "\n";
    file << "Customer user Name : " << username + "\n";
    file << "Customer password : " << password + "\n"
         << endl;

    file.close();
    count++;

    Customer new_customer(name, address, phone_number, username, password);
    customers.push_back(new_customer);

    cout << "\tHurray!! Customer added successfully." << endl;
}

void add_product()
{
    string name;
    double price;
    int quantity;
    cout << "****** | Enter the details of the product to be added | ******" << endl
         << endl;
    cout << "\tEnter name: ";
    getline(cin, name);
    cout << "\tEnter price: ";
    cin >> price;
    cout << "\tEnter quantity: ";
    cin >> quantity;

    Product new_product(name, price, quantity);
    products.push_back(new_product);

    cout << "\tProduct added successfully." << endl;
}

void create_sale()
{
    string customer_name, product_name;
    int quantity;
    vector<Customer>::iterator c;

    cout << "\tEnter customer name to create sale: ";
    getline(cin, customer_name);

    bool found_customer = false;
    for (c = customers.begin(); c != customers.end(); c++)
    {
        if (c->getName() == customer_name)
        {
            found_customer = true;
            break;
        }
    }

    if (!found_customer)
    {
        cout << "\tOOPS!! Customer not found." << endl;
        return;
    }

    cout << "Enter product name: ";
    getline(cin, product_name);
    vector<Product>::iterator p;
    bool found_product = false;
    for (p = products.begin(); p != products.end(); p++)
    {
        if (p->getName() == product_name)
        {
            found_product = true;
            break;
        }
    }

    if (!found_product)
    {
        cout << "\tProduct not found." << endl;
        return;
    }

    cout << "\tEnter quantity: ";
    cin >> quantity;

    Sale new_sale(Customer(customer_name, "", ""), Product(product_name, 0.0, 0), quantity);

    sales.push_back(new_sale);
    cout << "\tWell done! Sale created successfully." << endl;
}

void list_customers()
{
    cout << "The list of all Customers is as follows:" << endl;
    vector<Customer>::iterator c;
    for (c = customers.begin(); c != customers.end(); c++)
    {
        cout << "\tName: " << c->getName() << endl;
        cout << "\tAddress: " << c->getAddress() << endl;
        cout << "\tPhone number: " << c->getPhoneNumber() << endl
             << endl;
    }
}

void list_products()
{
    cout << "The list of all Products is as follows:" << endl;
    vector<Product>::iterator p;
    for (p = products.begin(); p != products.end(); p++)
    {
        cout << "\tName: " << p->getName() << endl;
        cout << "\tPrice: $" << p->getPrice() << endl;
        cout << "\tQuantity: " << p->getQuantity() << endl
             << endl;
    }
}

void list_sales()
{
    cout << "The list of all Sales is as follows::" << endl;
    vector<Sale>::iterator s;
    for (s = sales.begin(); s != sales.end(); s++)
    {
        cout << "\tCustomer: " << s->getCustomer().getName() << endl;
        cout << "\tProduct: " << s->getProduct().getName() << endl;
        cout << "\tQuantity: " << s->getQuantity() << endl;
        cout << "\tTotal: $" << s->getTotal() << endl
             << endl;
    }
}

void update_product_quantity()
{
    string product_name;
    int quantity_change;
    cout << "Enter the name of the product to update quantity: ";
    getline(cin, product_name);
    vector<Product>::iterator p;
    bool found_product = false;
    for (p = products.begin(); p != products.end(); p++)
    {
        if (p->getName() == product_name)
        {
            found_product = true;
            cout << "\tEnter quantity change: ";
            cin >> quantity_change;
            p->updateQuantity(quantity_change);
            cout << "\tQuantity updated successfully!!" << endl;
            break;
        }
    }

    if (!found_product)
    {
        cout << "sorry!! Product not found." << endl;
    }
}
int main()
{
    system("color f3");
    int choice;
    int PaymentChoice;
    login user;
    string username, password;
    int choice2;
    string productName;
    int quantity;

    cout << " ---------------------------------------------------------------------------------\n";
    cout << "|                                                                                 |\n";
    cout << "|                                                                                 |\n";
    cout << "|  OOOOOO    OOOOOO  OOOOOO  OOOOOO  OOOOOO  OOOOOO  O      O  OOOOOOO   OOOOOO   |\n";
    cout << "|  O         O    O  O       O         O       O     O O    O  O         O        |\n";
    cout << "|  O  OOOOO  OOOOOO  OOOOO   OOOOO     O       O     O  O   O  O  OOOOO  OOOOOO   |\n";
    cout << "|  O    O    O  O    O       O         O       O     O   O  O  O    O         O   |\n";
    cout << "|  OOOOOO    O   O   OOOOOO  OOOOOO    O     OOOOOO  O    O O  OOOOOO    OOOOOO   |\n";
    cout << "|                                                                                 |\n";
    cout << " ---------------------------------------------------------------------------------\n\n\n";

    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*       -----------------------------           *\n";
    cout << "\t\t*          WELCOME TO ONLINE PORTAL             *\n";
    cout << "\t\t*       -----------------------------           *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*  Brought To You By Rahul,Shivesh,Kuldeep,Kush *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

    for (int i = 0; i < 82; i++)
    {
        cout << "-";
    }
    cout << endl;

    cout << "\nPress ENTER key to continue:" << endl;

    cin.get();
    system("cls");

    do
    {
        cout << "***********  || MAIN MENU ||  ***********\n\n"
             << endl;

        cout << "***** || Sales Management System || ******\n\n " << endl;
        cout << " Please enter your choice from menu :\n"
             << endl;

        cout << "ENTER 1 --> Add customer" << endl;
        cout << "ENTER 2 --> Add product" << endl;
        cout << "ENTER 3 --> Create sale" << endl;
        cout << "ENTER 4 --> List customers" << endl;
        cout << "ENTER 5 --> List products" << endl;
        cout << "ENTER 6 --> List sales" << endl;
        cout << "ENTER 7 --> Update product quantity" << endl;
        cout << "ENTER 8 --> Login to customer: " << endl;
        cout << "ENTER 0 --> Exit" << endl
             << endl;
        cout << "\tEnter your choice: ";
        cin >> choice;
        cout << endl
             << endl;
        cin.ignore();

        switch (choice)
        {
        case 1:
            add_customer();
            break;
        case 2:
            add_product();
            break;
        case 3:
            create_sale();
            break;
        case 4:
            list_customers();
            break;
        case 5:
            list_products();
            break;
        case 6:
            list_sales();
            break;
        case 7:
            update_product_quantity();
            break;
        case 8:
            cout << "Enter the user name :" << endl;
            cin >> username;
            cout << "Enter password:" << endl;
            cin >> password;
            user.logincheck(username, password);
            do
            {
                cout << "" << endl;
                cout << "ENTER 0 --> To Logout:" << endl;
                cout << "ENTER 1 --> View cart:" << endl;
                cout << "ENTER 2 --> Add to cart:" << endl;
                cout << "ENTER 3 --> Payment:" << endl;

                cin >> choice2;
                switch (choice2)
                {
                case 1:
                    user.viewCart();
                    break;
                case 2:
                    cout << "\tEnter the product name :" << endl;
                    cin >> productName;
                    cout << "\tEnter the quantity of the product: " << endl;
                    cin >> quantity;
                    if (user.checkProduct(productName, quantity))
                    {

                        user.addProduct(quantity);
                    }
                    else
                    {
                        cout << "\tProduct either missing or available less in quantity" << endl;
                    }
                    break;
                case 3:
                    user.Payment();
                }
            } while (choice2 != 0);

        case 0:
            cout << "\tExiting program." << endl;
            break;
        default:
            cout << "\tInvalid choice." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
