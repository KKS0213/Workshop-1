#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
using namespace sql;

//connect to localhost
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "";

Driver* driver;
Connection* con;
Statement* stmt;
PreparedStatement* pstmt;
ResultSet* rs;

void login(), staff(), manager(), addappointment(), updateappointment(), report(), earning(), modify();

#include "Login.h"
#include "Staff.h"
#include "Manager.h"

int main()
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    
    //name of the created database in localhost
    con->setSchema("mts");
    stmt = con->createStatement();
   
    login();
   
    system("pause");
    return 0;
}
