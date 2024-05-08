
#include <iostream>
using namespace std;
#define size 10

class element
{
public:
    string name;
    int teleno;

    element()
    {
        name = "";
        teleno = -1;
    }
};

class hashing
{
    element *arr = new element[size];

public:
    bool isFull()
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i].teleno == -1)
            {
                return false;
            }
        }
        return true;
    }

    int hashteleno(int a)
    {
        return (3*a + 5) % 10;
    }

    //  linear probing without replacement

    void hashFunction_without_replacement(element obj1)
    {
        int i = hashteleno(obj1.teleno);

        if (isFull())
        {
            cout << "Hash Table is FULL.";
            return;
        }

        while (arr[i].teleno != -1)
        {
            i = (i + 1) % size;
        }
        arr[i].name = obj1.name;
        arr[i].teleno = obj1.teleno;
    }

    // linear probing with replacement

    void hashFunction_with_replacement(element obj1)
    {
        int i = hashteleno(obj1.teleno);

        if (isFull())
        {
            cout << "Hash Table is FULL." << endl;
            return;
        }

        if (arr[i].teleno == -1)
        {

            arr[i].teleno = obj1.teleno;
            arr[i].name = obj1.name;
        }
        else if (hashteleno(arr[i].teleno) == i)
        {

            hashFunction_without_replacement(obj1);
        }
        else if (hashteleno(arr[i].teleno) != i)
        {
            element temp;
            temp.teleno = arr[i].teleno;
            temp.name = arr[i].name;
            arr[i].teleno = obj1.teleno;
            arr[i].name = obj1.name;
            hashFunction_with_replacement(temp);
        }
    }

    //  Printing Hash Table
    void printHashTable()
    {

        for (int i = 0; i < size; i++)
        {
            cout << i << "->"
                 << " -----> " << arr[i].teleno << " " << arr[i].name << endl;
        }
    }

    //  Searching obj1 in Hash Table

    bool search_in_hashTable(element obj1)
    {

        for (int i = 0; i < size; i++)
        {
            if (arr[i].teleno == obj1.teleno)
            {
                return true;
            }
        }

        return false;
    }

    //  Deleting an element

    void delete_from_hashTable(element obj1)
    {

        for (int i = 0; i < size; i++)
        {
            if (arr[i].teleno == obj1.teleno)
            {
                arr[i].teleno = -1;
                arr[i].name = "";
            }
        }
    }
};
int main()
{
    element obj1;
    hashing h1, h2;
    int n;
    cout << "-----MENU-----\n1.Insert data\n2.Search data\n3.Delete data\n4.Display\n5.Exit\n";

    while (1)
    {
        cout << "\nChoice:";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << "Name: " << endl;
            cin.ignore();
            getline(cin, obj1.name);
            cout << "Telephone number " << endl;
            cin >> obj1.teleno;

            h1.hashFunction_with_replacement(obj1);
            h2.hashFunction_without_replacement(obj1);
            break;

        case 2:
            cout << "data: ";
            cin >> obj1.teleno;

            if (h1.search_in_hashTable(obj1))
            {
                cout << obj1.teleno << " is present in Hash TAble." << endl;
            }
            else
            {
                cout << obj1.teleno << " is not present in Hash TAble." << endl;
            }
            break;

        case 3:
            cout << "data: ";
            cin >> obj1.teleno;

            h1.delete_from_hashTable(obj1);
            h2.delete_from_hashTable(obj1);
            break;

        case 4:
            cout << "Hash Table with Replacement." << endl;
            h1.printHashTable();

            cout << "\n\nHash Table without Replacement." << endl;
            h2.printHashTable();
            break;
        }
        if (n == 5)
            break;
    }

    return 0;
}
