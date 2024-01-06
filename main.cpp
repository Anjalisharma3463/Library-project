#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
using namespace std;

class book
{
private:
    int bookid;
    char title[20];
    float price;

public:
//constructor
    book()
    {
        bookid = 0;
        strcpy(title, "No title");
        price = 0;
    }

    void getbookdata()
    {
        cout << "Enter book id, title, and price of a book: ";
        cin >> bookid;
        cout<<endl;
        cin.ignore();
        cin.getline(title, 19);
        cout<<endl;  
        cin >> price;
        cout<<endl;
    }

    void showbookdata()
    {
        cout << "Book id: " << bookid << endl
             << "Title: " << title<<endl << " Price: " << price << endl;
    }

    int storebook();
    void viewallbooks();
    void searchbook(const char *t);
    void deletebook(const char *t);
};

void book::deletebook(const char *t)
{
    // Step 1: Open input and output files
    ifstream fin;
    ofstream fout;

    fin.open("book.dat", ios::binary | ios::in);
    if (!fin)
    {
        cout << "File not found";
        return; // Exit function if the file is not found
    }

    fout.open("temp.dat", ios::out | ios::binary);

    // Step 2: Read from the original file and write to the temporary file
    fin.read(reinterpret_cast<char *>(this), sizeof(*this));
    while (!fin.eof())
    {
        // Step 3: Check if the current object's title is not equal to the specified title
        if (strcmp(title, t) != 0)
        {
            // Step 4: Write the current object to the temporary file
            fout.write(reinterpret_cast<char *>(this), sizeof(*this));
        }

        // Step 5: Read the next object from the original file
        fin.read(reinterpret_cast<char *>(this), sizeof(*this));
    }

    // Step 6: Close files
    fin.close();
    fout.close();

    // Step 7: Remove the original file and rename the temporary file
    remove("book.dat");
    rename("temp.dat", "book.dat");
}


void book::searchbook(const char *t)
{
    ifstream fin;
    fin.open("book.dat", ios::binary | ios::in);

    if (!fin)
    {
        cout << "File not found";
        return; // Exit function if the file is not found
    }

    fin.read(reinterpret_cast<char *>(this), sizeof(*this));

    while (!fin.eof())
    {
        if (strcmp(title, t) == 0)
        {
            showbookdata();
            break; // Exit the loop after finding a match
        }

        fin.read(reinterpret_cast<char *>(this), sizeof(*this));
    }

    fin.close();
}

int book::storebook()
{
    if (bookid == 0 && price == 0)
    {
        cout << "Book data not initialized";
        return 0;
    }
    else
    {
        ofstream fout;
        fout.open("book.dat", ios::app | ios::binary);
        fout.write(reinterpret_cast<char *>(this), sizeof(*this));
        fout.close();
        return 1;
    }
}

void book::viewallbooks()
{
    ifstream fin;
    fin.open("book.dat", ios::binary | ios::in);

    if (!fin)
    {
        cout << "File not found";
        return; // Exit function if the file is not found
    }

    fin.read(reinterpret_cast<char *>(this), sizeof(*this));

    while (!fin.eof())
    {
        showbookdata();
        fin.read(reinterpret_cast<char *>(this), sizeof(*this));
    }

    fin.close();
}

int main()
{
    book b1;

    // b1.getbookdata();
    // b1.storebook();
    // b1.showbookdata();
    // b1.viewallbooks();
    // b1.deletebook("python");

    // cout << endl
    //      << "After deleting:" << endl;
    // b1.viewallbooks();

    return 0;
}
