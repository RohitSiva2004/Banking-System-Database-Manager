#include <iostream>
#include <occi.h>
using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

void displayMenu() {
    cout << "1) Find a Customer by ID" << endl;
    cout << "2) Find a Customer by Name" << endl;
    cout << "3) Customer Report" << endl;
    cout << "4) Add a Customer" << endl;
    cout << "5) Update a Customer" << endl;
    cout << "6) Remove a Customer" << endl;
    cout << "7) Exit" << endl;
    cout << "Enter your choice: ";
}

void executeCustomerReport(Connection* conn, const string& customerName, int customerId) {
    Statement* stmt = conn->createStatement();
    ResultSet* rs;
    string query = "SELECT C.CONTACTFIRSTNAME, C.CONTACTLASTNAME, O.CUSTOMERNUMBER, O.ORDERNUMBER, P.PRODUCTNAME \
FROM DBS211_CUSTOMERS C \
JOIN DBS211_ORDERS O ON C.CUSTOMERNUMBER = O.CUSTOMERNUMBER \
JOIN DBS211_ORDERDETAILS OD ON O.ORDERNUMBER = OD.ORDERNUMBER \
JOIN DBS211_PRODUCTS P ON OD.PRODUCTCODE = P.PRODUCTCODE \
WHERE ";

    if (!customerName.empty()) {
        query += "C.CUSTOMERNAME = '" + customerName + "'";
    }
    else {
        query += "C.CUSTOMERNUMBER = " + to_string(customerId);
    }

    rs = stmt->executeQuery(query);

    cout << "--------------------------- Customer Report ------------------------------------" << endl;
    cout << "FIRST NAME LAST NAME CUSTOMER NUMBER ORDER NUMBER PRODUCT NAME" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    while (rs->next()) {
        cout << rs->getString(1) << "\t " // First Name
            << rs->getString(2) << "\t " // Last Name
            << rs->getInt(3) << "\t " // Customer Number
            << rs->getInt(4) << "\t " // Order Number
            << rs->getString(5) << endl; // Product Name
    }
    cout << "-----------------------------------------------------------------------------" << endl;

    conn->terminateStatement(stmt);
}

void addCustomer(Connection* conn) {
    int customerNumber;
    string customerName, contactLastName, contactFirstName, phone, addressLine1, addressLine2, city, state, postalCode, country, salesRepEmployeeNumber;
    double creditLimit;

    cout << "Enter Customer Number: ";
    cin >> customerNumber;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, customerName);
    cout << "Enter Contact Last Name: ";
    getline(cin, contactLastName);
    cout << "Enter Contact First Name: ";
    getline(cin, contactFirstName);
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Address Line 1: ";
    getline(cin, addressLine1);
    cout << "Enter Address Line 2: ";
    getline(cin, addressLine2);
    cout << "Enter City: ";
    getline(cin, city);
    cout << "Enter State: ";
    getline(cin, state);
    cout << "Enter Postal Code: ";
    getline(cin, postalCode);
    cout << "Enter Country: ";
    getline(cin, country);
    cout << "Enter Sales Rep Employee Number: ";
    getline(cin, salesRepEmployeeNumber);
    cout << "Enter Credit Limit: ";
    cin >> creditLimit;

    Statement* stmt = conn->createStatement();
    stmt->executeUpdate("INSERT INTO DBS211_customers (CUSTOMERNUMBER, CUSTOMERNAME, CONTACTLASTNAME, CONTACTFIRSTNAME, PHONE, \
        ADDRESSLINE1, ADDRESSLINE2, CITY, STATE, POSTALCODE, COUNTRY, SALESREPEMPLOYEENUMBER, CREDITLIMIT) VALUES(" + to_string(customerNumber) + ",\
        '" + customerName + "', '" + contactLastName + "', '" + contactFirstName + "', '" + phone + "', '" + addressLine1 + "', '" + addressLine2 +
        "', '" + city + "', '" + state + "', '" + postalCode + "', '" + country + "', '" + salesRepEmployeeNumber + "', " + to_string(creditLimit) + ")");

    cout << "Customer added successfully." << endl;
    conn->terminateStatement(stmt);
}

void updateCustomer(Connection* conn) {
    int customerNumber;
    string columnName, newValue;

    cout << "Enter Customer Number: ";
    cin >> customerNumber;
    cin.ignore();
    cout << "Enter Column Name to Update: ";
    getline(cin, columnName);
    cout << "Enter New Value: ";
    getline(cin, newValue);

    Statement* stmt = conn->createStatement();
    stmt->executeUpdate("UPDATE DBS211_customers SET " + columnName + " = '" + newValue + "' WHERE CUSTOMERNUMBER = " + to_string(customerNumber));
    cout << "Customer updated successfully." << endl;
    conn->terminateStatement(stmt);
}

void removeCustomer(Connection* conn) {
    int customerNumber;

    cout << "Enter Customer Number to Remove: ";
    cin >> customerNumber;

    Statement* stmt = conn->createStatement();
    stmt->executeUpdate("DELETE FROM DBS211_customers WHERE CUSTOMERNUMBER = " + to_string(customerNumber));
    cout << "Customer removed successfully." << endl;
    conn->terminateStatement(stmt);
}

int main(void) {
    Environment* env = nullptr;
    Connection* conn = nullptr;
    string user = "dbs211_241nii27";
    string pass = "50627794";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(user, pass, constr);

        int choice = 0;
        string customerName;
        int customerId = 0;

        do {
            displayMenu();
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cout << "CUSTOMER " << customerId << " HAS BEEN SELECTED.\n";
                break;
            case 2:
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "CUSTOMER " << customerName << " HAS BEEN SELECTED.\n";
                break;
            case 3:
                executeCustomerReport(conn, customerName, customerId);
                break;
            case 4:
                addCustomer(conn);
                break;
            case 5:
                updateCustomer(conn);
                break;
            case 6:
                removeCustomer(conn);
                break;
            case 7:
                cout << "TERMINATING APPLICATION!" << endl;
                break;
            default:
                cout << "Invalid choice. Please input 1 - 7." << endl;
            }
        } while (choice != 7);

        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
    catch (SQLException& sqlExcp) {
        cout << "error";
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }

    return 0;
}

