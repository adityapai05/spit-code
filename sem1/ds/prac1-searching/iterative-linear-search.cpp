#include <iostream>
using namespace std;

// Performs Linear Search on the given array
int linearSearch(int arr[], int size, int target) {
    // Check each element one by one until the target is found
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;
    }

    // Return -1 if the target is not present in the array
    return -1;
}

int main() {
    int option = 0;

    // Keep displaying the menu until the user chooses Exit
    while (option != 2) {
        cout << "\nMENU\n";
        cout << "1. Linear Search\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        // Handle cases where the user enters something other than a number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (option) {
            case 1: {
                int size;
                int arr[100];

                cout << "Enter size of array (1-100): ";
                cin >> size;

                // Check whether the entered array size is a valid integer
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    break;
                }

                // Prevent the user from entering a size outside the array limit
                if (size < 1 || size > 100) {
                    cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                    break;
                }

                cout << "Enter " << size << " elements: ";

                // Read the elements that will be searched
                for (int i = 0; i < size; i++) {
                    cin >> arr[i];

                    // Make sure each array element is an integer
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid element. Please enter integers only." << endl;
                        break;
                    }
                }

                if (cin.fail())
                    break;

                int target;

                cout << "Enter target element: ";
                cin >> target;

                // Validate the target before performing the search
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid target. Please enter an integer." << endl;
                    break;
                }

                int result = linearSearch(arr, size, target);

                // A return value of -1 means that the target was not found
                if (result == -1)
                    cout << "Target element not found." << endl;
                else
                    cout << "Target element found at index " << result << "." << endl;

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