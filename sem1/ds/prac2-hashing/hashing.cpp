#include <iostream>
#include <string>
using namespace std;

int hashTable[100];
int tableSize;
int collisions;

// Initialise all hash table positions as empty
void initialiseHashTable()
{
    for (int i = 0; i < tableSize; i++)
        hashTable[i] = -1;

    collisions = 0;
}

// Find an empty position using Linear Probing
int linearProbe(int index)
{
    int start = index;

    while (hashTable[index] != -1)
    {
        index = (index + 1) % tableSize;
        collisions++;

        if (index == start)
            return -1;
    }

    return index;
}

// Display the hash table
void displayHashTable()
{
    cout << "\nHash Table:\n";

    for (int i = 0; i < tableSize; i++)
    {
        cout << "Index " << i << ": ";

        if (hashTable[i] == -1)
            cout << "Empty";
        else
            cout << hashTable[i];

        cout << endl;
    }

    cout << "Total Collisions: " << collisions << endl;
}

// Modulo Division Hashing
void moduloDivision()
{
    initialiseHashTable();

    int choice;

    do
    {
        cout << "\nMODULO DIVISION\n";
        cout << "1. Insert Key\n";
        cout << "2. Display Hash Table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;

            cout << "Enter key: ";
            cin >> key;

            // Check that the key is a valid number
            if (cin.fail() || key < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid key. Please enter a non-negative number." << endl;
                continue;
            }

            int index = key % tableSize;
            int position = linearProbe(index);

            if (position == -1)
                cout << "Hash Table is full." << endl;
            else
            {
                hashTable[position] = key;
                cout << "Key inserted at index " << position << endl;
            }
        }
        else if (choice == 2)
            displayHashTable();
        else if (choice != 3)
            cout << "Invalid choice. Please enter 1, 2 or 3." << endl;

    } while (choice != 3);
}

// Extract selected digits from the key
int extractDigits(int key, int positions[], int numberOfPositions)
{
    int result = 0;
    int multiplier = 1;

    for (int i = 0; i < numberOfPositions; i++)
    {
        int temp = key;

        for (int j = 1; j < positions[i]; j++)
            temp /= 10;

        int digit = temp % 10;

        result += digit * multiplier;
        multiplier *= 10;
    }

    return result;
}

// Count number of digits in a key
int getDigits(int number)
{
    int digits = 0;

    do
    {
        digits++;
        number /= 10;
    } while (number > 0);

    return digits;
}

// Digit Extraction Hashing
void digitExtraction()
{
    initialiseHashTable();

    int choice;

    do
    {
        cout << "\nDIGIT EXTRACTION\n";
        cout << "1. Insert Key\n";
        cout << "2. Display Hash Table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;

            cout << "Enter key: ";
            cin >> key;

            // Check that the key is a valid number
            if (cin.fail() || key < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid key. Please enter a non-negative number." << endl;
                continue;
            }

            int digits = getDigits(key);
            int numberOfPositions;
            int positions[10];

            cout << "Enter number of digits to extract (1-" << digits << "): ";
            cin >> numberOfPositions;

            if (cin.fail() || numberOfPositions < 1 || numberOfPositions > digits)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid number of positions." << endl;
                continue;
            }

            cout << "Enter positions from right side (1 = units digit): ";

            bool valid = true;

            for (int i = 0; i < numberOfPositions; i++)
            {
                cin >> positions[i];

                if (cin.fail() || positions[i] < 1 || positions[i] > digits)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid digit position." << endl;
                    valid = false;
                    break;
                }
            }

            if (!valid)
                continue;

            int index = extractDigits(key, positions, numberOfPositions);

            if (index >= tableSize)
                index = index % tableSize;

            cout << "Hash index = " << index << endl;

            int position = linearProbe(index);

            if (position == -1)
                cout << "Hash Table is full." << endl;
            else
            {
                hashTable[position] = key;
                cout << "Key inserted at index " << position << endl;
            }
        }
        else if (choice == 2)
            displayHashTable();
        else if (choice != 3)
            cout << "Invalid choice. Please enter 1, 2 or 3." << endl;

    } while (choice != 3);
}

// Find k from the number of hash table locations
int getK()
{
    int maxIndex = tableSize - 1;
    return getDigits(maxIndex);
}

// Folding Hashing
int foldingHash(int key)
{
    int k = getK();
    int groups[20];
    int count = 0;
    int divisor = 1;

    for (int i = 0; i < k; i++)
        divisor *= 10;

    while (key > 0)
    {
        groups[count] = key % divisor;
        key /= divisor;
        count++;
    }

    if (count == 0)
        groups[count++] = 0;

    int sum = 0;

    for (int i = 0; i < count; i++)
        sum += groups[i];

    // Keep only k digits and ignore the carry
    int limit = 1;

    for (int i = 0; i < k; i++)
        limit *= 10;

    sum = sum % limit;

    return sum;
}

// Fold Boundary Hashing
void foldBoundary()
{
    initialiseHashTable();

    int choice;

    do
    {
        cout << "\nFOLD BOUNDARY\n";
        cout << "1. Insert Key\n";
        cout << "2. Display Hash Table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;

            cout << "Enter key: ";
            cin >> key;

            // Check that the key is a valid number
            if (cin.fail() || key < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid key. Please enter a non-negative number." << endl;
                continue;
            }

            int k = getK();
            int divisor = 1;

            for (int i = 0; i < k; i++)
                divisor *= 10;

            int groups[20];
            int count = 0;
            int tempKey = key;

            while (tempKey > 0)
            {
                groups[count] = tempKey % divisor;
                tempKey /= divisor;
                count++;
            }

            if (count == 0)
                groups[count++] = 0;

            // Reverse the boundary groups
            if (count > 1)
            {
                int first = groups[count - 1];
                int last = groups[0];

                int firstReversed = 0;
                int lastReversed = 0;

                int temp = first;
                for (int i = 0; i < k; i++)
                {
                    firstReversed = firstReversed * 10 + temp % 10;
                    temp /= 10;
                }

                temp = last;
                for (int i = 0; i < k; i++)
                {
                    lastReversed = lastReversed * 10 + temp % 10;
                    temp /= 10;
                }

                groups[count - 1] = firstReversed;
                groups[0] = lastReversed;
            }

            int hashValue = 0;

            for (int i = 0; i < count; i++)
                hashValue += groups[i];

            // Ignore the carry above k digits
            hashValue = hashValue % divisor;

            int index = hashValue;

            cout << "k = " << k << endl;
            cout << "Folding value = " << hashValue << endl;

            // Apply modulo if value is outside index range
            if (index >= tableSize)
                index = index % tableSize;

            cout << "Hash index = " << index << endl;

            int position = linearProbe(index);

            if (position == -1)
                cout << "Hash Table is full." << endl;
            else
            {
                hashTable[position] = key;
                cout << "Key inserted at index " << position << endl;
            }
        }
        else if (choice == 2)
            displayHashTable();
        else if (choice != 3)
            cout << "Invalid choice. Please enter 1, 2 or 3." << endl;

    } while (choice != 3);
}

// Find the middle digit or middle two digits
int midSquareHash(int key)
{
    int square = key * key;

    string number = to_string(square);
    int length = number.length();

    int middle;

    if (length % 2 == 1)
    {
        // One central digit for odd number of digits
        middle = number[length / 2] - '0';
    }
    else
    {
        // Two central digits for even number of digits
        int first = number[length / 2 - 1] - '0';
        int second = number[length / 2] - '0';

        middle = first * 10 + second;
    }

    return middle;
}

// Mid Square Hashing
void midSquare()
{
    initialiseHashTable();

    int choice;

    do
    {
        cout << "\nMID SQUARE\n";
        cout << "1. Insert Key\n";
        cout << "2. Display Hash Table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;

            cout << "Enter key: ";
            cin >> key;

            // Check that the key is a valid number
            if (cin.fail() || key < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid key. Please enter a non-negative number." << endl;
                continue;
            }

            int square = key * key;
            int index = midSquareHash(key);

            cout << "Square = " << square << endl;
            cout << "Middle value = " << index << endl;

            // Apply modulo if middle value is outside table range
            if (index >= tableSize)
                index = index % tableSize;

            cout << "Hash index = " << index << endl;

            int position = linearProbe(index);

            if (position == -1)
                cout << "Hash Table is full." << endl;
            else
            {
                hashTable[position] = key;
                cout << "Key inserted at index " << position << endl;
            }
        }
        else if (choice == 2)
            displayHashTable();
        else if (choice != 3)
            cout << "Invalid choice. Please enter 1, 2 or 3." << endl;

    } while (choice != 3);
}

// Direct Hashing
void directHashing()
{
    initialiseHashTable();

    int choice;

    do
    {
        cout << "\nDIRECT HASHING\n";
        cout << "1. Insert Key\n";
        cout << "2. Display Hash Table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;

            cout << "Enter key: ";
            cin >> key;

            // Check that the key is a valid number
            if (cin.fail() || key < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid key. Please enter a non-negative number." << endl;
                continue;
            }

            // Direct hashing needs the key to be a valid index
            if (key >= tableSize)
            {
                cout << "Key must be between 0 and "
                     << tableSize - 1 << "." << endl;
                continue;
            }

            int position = linearProbe(key);

            if (position == -1)
                cout << "Hash Table is full." << endl;
            else
            {
                hashTable[position] = key;
                cout << "Key inserted at index " << position << endl;
            }
        }
        else if (choice == 2)
            displayHashTable();
        else if (choice != 3)
            cout << "Invalid choice. Please enter 1, 2 or 3." << endl;

    } while (choice != 3);
}

int main()
{
    int option = 0;

    cout << "Enter number of hash table locations (1-100): ";
    cin >> tableSize;

    // Make sure the table size is valid
    if (cin.fail() || tableSize < 1 || tableSize > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid table size. Please enter a value between 1 and 100." << endl;
        return 0;
    }

    while (option != 6)
    {
        cout << "\nHASHING MENU\n";
        cout << "1. Modulo Division\n";
        cout << "2. Digit Extraction\n";
        cout << "3. Fold Boundary\n";
        cout << "4. Mid Square\n";
        cout << "5. Direct Hashing\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        // Check if the user entered a valid number
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (option)
        {
        case 1:
            moduloDivision();
            break;

        case 2:
            digitExtraction();
            break;

        case 3:
            foldBoundary();
            break;

        case 4:
            midSquare();
            break;

        case 5:
            directHashing();
            break;

        case 6:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter 1 to 6." << endl;
        }
    }

    return 0;
}