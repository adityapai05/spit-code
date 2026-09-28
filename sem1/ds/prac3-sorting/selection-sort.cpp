#include <iostream>
using namespace std;

// Performs Selection Sort on the given array
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        // Select the current element as minimum element
        int minimum = i;
        for (int j = i + 1; j < size; j++)
        {
            // Compare every element with the minimum element
            if (arr[j] < arr[minimum])
            {
                minimum = j;
            }
        }
        // Only swap if the minimum element and the current element are not the same
        if (minimum != i)
        {
            swap(arr[i], arr[minimum]);
        }
    }
}

// Runs a loop over the array and displays each element
void displayArray(int arr[], int size)
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int option = 0;

    // Keep displaying the menu until the user chooses Exit
    while (option != 2)
    {
        cout << "\nMENU\n";
        cout << "1. Selection Sort\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        // Handle cases where the user enters something other than a number
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
        {
            int size;
            int arr[100];

            cout << "Enter size of array (1-100): ";
            cin >> size;

            // Check whether the entered array size is a valid integer
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
                break;
            }

            // Prevent the user from entering a size outside the array limit
            if (size < 1 || size > 100)
            {
                cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                break;
            }

            cout << "Enter " << size << " elements: ";

            // Read the elements that will be sorted
            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

                // Make sure each array element is an integer
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid element. Please enter integers only." << endl;
                    break;
                }
            }

            if (cin.fail())
                break;

            cout << "Array Before Sorting: ";
            displayArray(arr, size);
            selectionSort(arr, size);
            cout << "Array After Sorting: ";
            displayArray(arr, size);
            break;
        }

        case 2:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
    }
    return 0;
}