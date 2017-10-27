//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.cpp"



//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 37;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    std::string firstName,   // Name of account holder
                lastName;
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
    int setKey (int key)
        { acctID = key; }
};

int stoi(std::string);
long pow(int, int);
//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number
    std::string record;
    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.

    while(std::getline(acctFile, record)) {

        entry.setKey(stoi(record.substr(0, 4)));
        index.insert(entry);
    }

    // Output the account IDs in ascending order.
    index.writeKeys();

    // Clear the status flags for the database file.
    acctFile.clear();
    acctFile.seekg(acctFile.beg);

    // Read an account ID from the keyboard and output the
    // corresponding record.

    std::cin >> searchID;
    std::cout << searchID << std::endl;

    
    while(std::cin.good()) {

        index.retrieve(searchID, entry);

        acctFile.seekg(entry.recNum * bytesPerRecord);

        std::getline(acctFile, record);
        acctRec.acctID = stoi(record.substr(0, 4));
        acctRec.firstName = record.substr(5, nameLength);
        acctRec.lastName = record.substr(5 + nameLength, nameLength);
        acctRec.balance = stoi(record.substr(5 + 2 * nameLength, bytesPerRecord - 5 - 2 * nameLength));

        acctFile.clear();
        acctFile.seekg(acctFile.beg);

        // Output the account IDs in ascending order.
        cout << endl << "Account IDs :" << endl;
        index.writeKeys();
        cout << endl;

        cout << "Enter account ID : ";
        cin >> searchID;


        cout << recNum
        << " : " << acctRec.acctID
        << " " << acctRec.firstName
        << " " << acctRec.lastName
        << " " << acctRec.balance;

        std::cin >> searchID;
    }

    return 0;
}

int stoi(std::string str) {

    int result;

    for(int i = str.length() - 1; i >= 0; ++i) {

        result += (str[i] - '0') * pow(10, i);
    }

    return result;
}
long pow(int a, int b) {

    while(b) {

        if(b & 1) 
            a *= a;
        b >>= 1;
        a *= a;
    }

    return a;
}