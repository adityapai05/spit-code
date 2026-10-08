#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Book {
    long long isbn;
    string title;
    string author;
};

Book books[100];
long long hashTable[100];
int tableSize;
int bookCount;

// Initialise all hash table positions as empty
void initialiseHashTable() {
    for (int i = 0; i < tableSize; i++)
        hashTable[i] = -1;
    bookCount = 0;
}

// Count the number of digits in a number
int getDigits(long long number) {
    int digits = 0;
    do {
        digits++;
        number /= 10;
    } while (number > 0);
    return digits;
}

// Find k based on the number of hash table locations
int getK() {
    int maxIndex = tableSize - 1;
    return getDigits(maxIndex);
}

// Calculate the hash index using Folding Hashing
int foldingHash(long long isbn) {
    int k = getK();
    long long divisor = 1;

    for (int i = 0; i < k; i++)
        divisor *= 10;

    long long sum = 0;

    // Divide the ISBN into k-digit groups and add them
    while (isbn > 0) {
        sum += isbn % divisor;
        isbn /= divisor;
    }

    // Ignore extra higher digits
    sum = sum % divisor;

    // Apply modulo if the value is outside the table range
    if (sum >= tableSize)
        sum = sum % tableSize;

    return sum;
}

// Find an empty position using Linear Probing
int linearProbe(int index) {
    int start = index;

    while (hashTable[index] != -1) {
        index = (index + 1) % tableSize;

        if (index == start)
            return -1;
    }

    return index;
}

// Search for a book using its ISBN
int searchBook(long long isbn) {
    int index = foldingHash(isbn);
    int start = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == isbn)
            return index;

        index = (index + 1) % tableSize;

        if (index == start)
            break;
    }

    return -1;
}

// Add a new book to the library
void addBook() {
    if (bookCount == tableSize) {
        cout << "\nLibrary is full." << endl;
        return;
    }

    Book book;

    cout << "\nEnter ISBN: ";
    cin >> book.isbn;

    if (cin.fail() || book.isbn < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ISBN. Please enter a valid number." << endl;
        return;
    }

    // Prevent duplicate ISBNs
    if (searchBook(book.isbn) != -1) {
        cout << "Book with this ISBN already exists." << endl;
        return;
    }

    cin.ignore(1000, '\n');

    cout << "Enter book title: ";
    getline(cin, book.title);

    cout << "Enter author name: ";
    getline(cin, book.author);

    int index = foldingHash(book.isbn);
    int position = linearProbe(index);

    if (position == -1) {
        cout << "Library is full." << endl;
        return;
    }

    books[position] = book;
    hashTable[position] = book.isbn;
    bookCount++;

    cout << "Book inserted at index " << position << endl;
}

// Search and display a book
void searchBookMenu() {
    long long isbn;

    cout << "\nEnter ISBN to search: ";
    cin >> isbn;

    if (cin.fail() || isbn < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ISBN." << endl;
        return;
    }

    int position = searchBook(isbn);

    if (position == -1)
        cout << "Book not found." << endl;
    else {
        cout << "\nBook Found" << endl;
        cout << "ISBN   : " << books[position].isbn << endl;
        cout << "Title  : " << books[position].title << endl;
        cout << "Author : " << books[position].author << endl;
        cout << "Index  : " << position << endl;
    }
}

// Display all stored books
void displayBooks() {
    cout << "\n---------------- LIBRARY BOOKS ----------------\n";
    cout << left << setw(6) << "Index"
         << setw(16) << "ISBN"
         << setw(30) << "Title"
         << "Author" << endl;
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i] != -1) {
            cout << left << setw(6) << i
                 << setw(16) << books[i].isbn
                 << setw(30) << books[i].title
                 << books[i].author << endl;
        }
    }

    cout << "------------------------------------------------------------\n";
}

// Display ISBNs at their hash table positions
void displayHashTable() {
    cout << "\n---------------- HASH TABLE ----------------\n";

    for (int i = 0; i < tableSize; i++) {
        cout << "Index " << i << ": ";

        if (hashTable[i] == -1)
            cout << "Empty";
        else
            cout << hashTable[i];

        cout << endl;
    }
}

int main() {
    int option = 0;

    cout << "Enter number of hash table locations (1-100): ";
    cin >> tableSize;

    if (cin.fail() || tableSize < 1 || tableSize > 100) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid table size. Please enter a value between 1 and 100." << endl;
        return 0;
    }

    initialiseHashTable();

    while (option != 5) {
        cout << "\nLIBRARY BOOK MANAGEMENT\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ISBN\n";
        cout << "3. Display All Books\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (option) {
            case 1:
                addBook();
                break;
            case 2:
                searchBookMenu();
                break;
            case 3:
                displayBooks();
                break;
            case 4:
                displayHashTable();
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 1 to 5." << endl;
        }
    }

    return 0;
}