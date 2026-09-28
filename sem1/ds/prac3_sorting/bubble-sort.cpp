#include <iostream>
using namespace std;

// Performs Bubble Sort on the given array
void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        // The last i elements are already in their correct positions
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swapped = true;
                swap(arr[j], arr[j + 1]);
            }
        }
        // Exit the loop after first iteration if no swaps were made (Array already sorted)
        if (!swapped)
        {
            break;
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
        cout << "1. Bubble Sort\n";
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
            bubbleSort(arr, size);
            cout << "Array After Sorting: ";
            displayArray(arr, size);
            break;

        case 2:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
        }
        return 0;
}