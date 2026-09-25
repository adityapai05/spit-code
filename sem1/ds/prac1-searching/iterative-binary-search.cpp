#include <iostream>
using namespace std;

// Performs Binary Search on a sorted array
int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

int main() {
    int option = 0;

    while (option != 2) {
        cout << "\nMENU\n";
        cout << "1. Binary Search\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        // Check if the user entered a valid number
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

                cout << "Enter size of sorted array (1-100): ";
                cin >> size;

                // Make sure the array size is a valid integer
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    break;
                }

                // The array can store a maximum of 100 elements
                if (size < 1 || size > 100) {
                    cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                    break;
                }

                cout << "Enter " << size << " elements in sorted order: ";

                for (int i = 0; i < size; i++) {
                    cin >> arr[i];

                    // Check that each array element is an integer
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

                // Check that the target is an integer
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid target. Please enter an integer." << endl;
                    break;
                }

                int result = binarySearch(arr, size, target);

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