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
#include <cstring>
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
    char firstName[nameLength],   // Name of account holder
    lastName[nameLength];
    char balance[bytesPerRecord - 5 - 2 * nameLength];               // Account balance

    void print() {
        std::cout << " : " << acctID 
        << " " << firstName 
        << " " << lastName 
        << " " << balance << std::endl;
    }
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

    double stoi(const std::string&);
    long pow(int, int);
//--------------------------------------------------------------------

int main () {

    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    std::string searchID;                         // User input account ID
    long recordNum = 0;                   // Record number
    std::string record;
    std::string piece;
    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.

    while(std::getline(acctFile, record)) {

        entry.setKey(stoi(record.substr(0, 4)));
        entry.recNum = recordNum;
        index.insert(entry);
        ++recordNum;
    }

    // Output the account IDs in ascending order.
    cout << endl << "Account IDs :" << endl;
    index.writeKeys();
    cout << endl;

    // Clear the status flags for the database file.
    acctFile.clear();

    // Read an account ID from the keyboard and output the
    // corresponding record.

    cout << "Enter account ID : ";
    std::getline(std::cin, searchID);

    while(searchID[0]) {

        int j = 0;

        if(!index.retrieve(stoi(searchID), entry)) 
            break;

        acctFile.seekg(entry.recNum * bytesPerRecord);
        std::getline(acctFile, record);

        acctRec.acctID = stoi(record.substr(0, 4));
        piece = record.substr(5, nameLength);
        for(int i = 0; i < piece.length(); ++i) {

            if(piece[i] == ' ') ++j;
            else acctRec.firstName[i - j] = piece[i];
        }

        j = 0;

        piece = record.substr(16, nameLength).c_str();
        for(int i = 0; i < piece.length(); ++i) {

            if(piece[i] == ' ') ++j;
            else acctRec.lastName[i - j] = piece[i];
        }

        j = 0;
        piece = record.substr(27, 10);
        for(int i = 0; i < piece.length(); ++i) {

            if(piece[i] == ' ') ++j;
            else acctRec.balance[i - j] = piece[i];
        }


        acctFile.clear();
        acctFile.seekg(acctFile.beg);
        // Output the account IDs in ascending order



        cout << entry.recNum;
        acctRec.print();

        cout << "Enter account ID : ";
        std::getline(std::cin, searchID);
    }

    return 0;
}

/**
 * \brief Converts string to integer
 *
 * Runs through every character, converts it to an int and then multiplies it by 10 ^ index
 *
 * @param String to convert
 * @return The integer equivelant
 * @pre A string with digits
 * @post The string will be converted
 **/
double stoi(const std::string& str) {

    int result = 0;

    for(int i = str.length() - 1; i >= 0; --i) {

        if(str[str.length() - 1 - i] == ' ');
        else result += (str[str.length() - 1 - i] - '0') * pow(10, i);
        if(str[str.length() - 1 - i] == '.') {

            --i;
            int j = 1;
            while(i >= 0) {

                result += (str[str.length() - 1 - i] - '0') / pow(10, j);
                --i;
                ++j;
            }
            return result;
        }
    }

    return result;
}

/**
 * \brief Returns the power of a ^ b
 *
 * A really cool algorithm that calculates the power using (best case) half the number of multiplications
 * that for(i < b) result *= a does. Also has many parts that make it more efficient like (b&1) to check if power is odd
 * and b >>= 1 instead of dividing by 2.
 * 
 * @param Base and Exponent
 * @return result of Base ^ Exponent
 * @pre Valid base and exponent
 * @post No Change
 **/
long pow(int a, int b) {

    long result = 1;

    while(b) {

        if(b & 1) 
            result *= a;
        b >>= 1;
        a *= a;
    }

    return result;
}