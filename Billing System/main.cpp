#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<iomanip>
using namespace std;

class Shopping {
private:

    int code;
    int pcode;
    float price;
    float discount;
    string pname;
    int quantity;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void removeProduct();
    void list();
    void receipt();
};

// for main menu
void Shopping::menu() {
    int choice;
    do {
        cout << setw(115)<<"__________________________________________________________________________________" << endl;
        cout << setw(115)<<"|                               Supermarket Main Menu                            |" << endl;
        cout << setw(115)<<"|________________________________________________________________________________|" << endl;
        cout << setw(83)<<"| (1) Administrator |" << endl;
        cout << setw(75)<<"| (2) Buyer |" << endl;
        cout << setw(74)<<"| (3) Exit |" << endl;

        cout << "\n\t\t\t\t\t\tPlease Select: ";
        cin >> choice;

        switch(choice) {
            case 1:
                administrator();
                break;
            case 2:
                buyer();
                break;
            case 3:
                cout<<"EXITING ...";
                Sleep(3000);
                system("CLS");
                break;
            default:
                cout << setw(82)<<"Invalid Option! Please try again." << endl;
        }
    } while(choice != 3);
}

// for owner
void Shopping::administrator() {
    int choice;
     cout<<"Enter your code:" << endl;
     cin >> code;
    if(code == 345){
    do {
        cout << "\nAdministrator Menu" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Modify Product" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. View All Products" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                removeProduct();
                break;
            case 4:
                list();
                break;
            case 5:
                return;
            default:
                cout << "\t\t\t\t\t\tInvalid Choice!" << endl;
        }
        }
        while(true);
        }
        else{
    cout << "INVALID!!" << endl;
    menu();
        }
        }
// for customer
void Shopping::buyer() {
    int choice;
    do {
        cout << "\nBuyer Menu" << endl;
        cout << "1. Buy Product" << endl;
        cout << "2. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                receipt();
                break;
            case 2:
                return;
            default:
                cout << "\t\t\t\t\t\tInvalid Choice!" << endl;
        }
    } while(true);
}

// to add products in file
void Shopping::add() {
    fstream data;
    cout << "\nEnter Product Code: ";
    cin >> pcode;
    cout << "Enter Product Name: ";
    cin >> pname;
    cout << "Enter Product Price: ";
    cin >> price;
    cout << "Enter Discount: ";
    cin >> discount;
    cout << "Enter Product Quantity: ";
    cin >> quantity;

    data.open("data.txt", ios::app | ios::out);
    data << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
    data.close();

    cout << "\nProduct added successfully!" << endl;
}

// to edit product in file
void Shopping::edit() {
    fstream data, data1;
    int pkey, found = 0;
    cout << "\nEnter Product Code to Edit: ";
    cin >> pkey;

    data.open("data.txt", ios::in);
    if(!data) {
        cout << "File doesn't exist." << endl;
        return;
    }

    data1.open("temp.txt", ios::app | ios::out);
    while(data >> pcode >> pname >> price >> discount >> quantity) {
        if(pcode == pkey) {
            found = 1;
            cout << "Enter New Product Code: ";
            cin >> pcode;
            cout << "Enter New Product Name: ";
            cin >> pname;
            cout << "Enter New Product Price: ";
            cin >> price;
            cout << "Enter New Discount: ";
            cin >> discount;
            cout << "Enter New Product Quantity: ";
            cin >> quantity;
        }
        data1 << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
    }
    data.close();
    data1.close();

    if(found) {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        cout << "\nProduct edited successfully!" << endl;
    } else {
        cout << "\nProduct not found." << endl;
    }
}

//to remove product from file
void Shopping::removeProduct() {
    fstream data, data1;
    int pkey, found = 0;
    cout << "\nEnter Product Code to Remove: ";
    cin >> pkey;

    data.open("data.txt", ios::in);
    if(!data) {
        cout << "File doesn't exist." << endl;
        return;
    }

    data1.open("temp.txt", ios::app | ios::out);
    while(data >> pcode >> pname >> price >> discount >> quantity) {
        if(pcode == pkey) {
            found = 1;
            cout << "Product removed successfully." << endl;
            continue;
        }
        data1 << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
    }
    data.close();
    data1.close();

    if(found) {
        remove("data.txt");
        rename("temp.txt", "data.txt");
    } else {
        cout << "\nProduct not found." << endl;
    }
}

// to view products
void Shopping::list() {
    fstream data;
    data.open("data.txt", ios::in);
    if (!data) {
        cout << "No products available." << endl;
        return;
    }

    cout << setw(20) << "PRODUCT CODE:" << setw(20) << "PRODUCT NAME" << setw(20) << "PRICE:" << setw(20) << "DISCOUNT:" << setw(20) << "QUANTITY:" << endl;
    while(data >> pcode >> pname >> price >> discount >> quantity) {
         cout << setw(20) << pcode << setw(20) << pname << setw(20) << price << setw(20) << discount << setw(20) << quantity << "\n";

    }
    data.close();
}

// to make receipt (I used the concept of singly linked list here)
void Shopping::receipt() {
    struct Node {
        int pcode;
        string pname;
        float price;
        float discount;
        int quantity;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    int arrc[100], arrq[100], c = 0;
    float totalAmount = 0;
    string choice;
    fstream data, tempData;
    data.open("data.txt", ios::in);
    if(!data) {
        cout << "No products available." << endl;
        return;
    }

    cout << "\nAvailable Products:" << endl;
    cout << setw(20) << "PRODUCT CODE" << setw(20) << "PRODUCT NAME" << setw(20) << "PRICE" << setw(20) << "DISCOUNT" << setw(20) << "QUANTITY" << endl;

    while(data >> pcode >> pname >> price >> discount >> quantity) {
        cout << setw(20) << pcode << setw(20) << pname << setw(20) << price << setw(20) << discount << setw(20) << quantity << "\n";
    }
    data.close();

    do {
        cout << "\nEnter Product Code: ";
        cin >> arrc[c];                // array to store code of product
        cout << "Enter Quantity: ";
        cin >> arrq[c];                // array to store quantity
        c++;

        // making new node for the data of user and adding it to the list
        Node* newNode = new Node();
        newNode->pcode = arrc[c-1];    //array index start from zero but counter is from 1
        newNode->quantity = arrq[c-1];
        newNode->next = nullptr;

        data.open("data.txt", ios::in);
        bool productFound = false;
        while (data >> pcode >> pname >> price >> discount >> quantity) {
            if (pcode == newNode->pcode) {
                newNode->pname = pname;
                newNode->price = price;
                newNode->discount = discount;
                productFound = true;
                break;
            }
        }
        data.close();

        if (!productFound) {
            cout << "Product not found!" << endl;
            delete newNode;
            continue;
        }

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        cout << "Product added to cart!" << endl;

        cout << "Do you want to add more products? (y/n): ";
        cin >> choice;

    } while (choice == "y" || choice == "Y");

    string userChoice;
    do {
        cout << "\nYour Cart:" << endl;
        cout << setw(20) << "Product Code" << setw(20) << "Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;

        Node* temp = head;
        while (temp != nullptr) {
            cout << setw(20) << temp->pcode << setw(20) << temp->pname << setw(20) << temp->price
                 << setw(20) << temp->quantity << endl;
            temp = temp->next;
        }

        cout << "\nWould you like to:" << endl;
        cout << "1. Change Quantity of an Item" << endl;
        cout << "2. Remove an Item from Cart" << endl;
        cout << "3. Finalize the Order and Generate Receipt" << endl;
        cout << "Enter your choice: ";
        cin >> userChoice;

        if (userChoice == "1") {
            int pcodeToEdit, newQuantity;
            cout << "Enter Product Code to Edit Quantity: ";
            cin >> pcodeToEdit;
            cout << "Enter New Quantity: ";
            cin >> newQuantity;

            Node* temp = head;
            bool found = false;
            while (temp != nullptr) {
                if (temp->pcode == pcodeToEdit) {
                    temp->quantity = newQuantity;
                    found = true;
                    cout << "Quantity updated successfully!" << endl;
                    break;
                }
                temp = temp->next;
            }
            if (!found) {
                cout << "Product not found in the cart!" << endl;
            }
        }
        else if (userChoice == "2") {
            int pcodeToRemove;
            cout << "Enter Product Code to Remove: ";
            cin >> pcodeToRemove;

            Node* temp = head;
            Node* prev = nullptr;
            bool found = false;
            while (temp != nullptr) {
                if (temp->pcode == pcodeToRemove) {
                    if (prev == nullptr) {
                        head = temp->next;  //if product is at the beginning
                    } else {
                        prev->next = temp->next;
                    }
                    delete temp;
                    found = true;
                    cout << "Item removed from the cart!" << endl;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            if (!found) {
                cout << "Product not found in the cart!" << endl;
            }
        }
        else if (userChoice == "3") {
            cout << "\nReceipt:" << endl;
            cout << setw(20) << "Product Code" << setw(20) << "Name" << setw(20) << "Price" << setw(20) << "Quantity" << setw(20) << "Amount" << endl;

            Node* temp = head;
            while (temp != nullptr) {
                float amount = temp->price * temp->quantity;
                float finalAmount = amount - (amount * temp->discount / 100);
                totalAmount += finalAmount;

                cout << setw(20) << temp->pcode << setw(20) << temp->pname << setw(20) << temp->price
                     << setw(20) << temp->quantity << setw(20) << finalAmount << endl;

                // Update the product quantity in the file
                fstream file, tempFile;
                file.open("data.txt", ios::in);  // Open the original file for reading
                tempFile.open("temp.txt", ios::out);  // Open a new temporary file for writing

                int pcodeInFile, quantityInFile;
                string pname;
                float price, discount;

                // Read each line from the file
                while (file >> pcodeInFile >> pname >> price >> discount >> quantityInFile) {
                    if (pcodeInFile == temp->pcode) {
                        quantityInFile -= temp->quantity;  // Decrease the quantity by the purchased amount
                    }

                    tempFile << pcodeInFile << " " << pname << " " << price << " " << discount << " " << quantityInFile << "\n";
                }
                file.close();
                tempFile.close();
                // Remove the old file and rename the temporary file to the original file name
                remove("data.txt");
                rename("temp.txt", "data.txt");

                temp = temp->next;
            }

            cout << "\nTotal: RS." << totalAmount << "\n";
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (userChoice != "3");

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}



int main() {
    Shopping s;
    s.menu();
    return 0;
}
