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

        // Stop if no elements were swapped in the current pass
        if (!swapped)
            break;
    }
}

// Partitions the array around the first element as pivot
int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;

    // Move i until an element greater than the pivot is found
    while (i < j)
    {
        while (i <= high && arr[i] <= pivot)
            i++;

        // Move j until an element smaller than the pivot is found
        while (j >= low && arr[j] > pivot)
            j--;

        // Swap the elements if i is still before j
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // Place the pivot in its correct position
    swap(arr[low], arr[j]);

    return j;
}

// Performs Quick Sort using divide and conquer
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Performs Selection Sort on the given array
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minimum = i;

        // Find the smallest element in the unsorted portion
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minimum])
                minimum = j;
        }

        // Swap only if a different minimum element was found
        if (minimum != i)
            swap(arr[i], arr[minimum]);
    }
}

// Performs Insertion Sort on the given array
void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        // Shift larger elements one position to the right
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Merges two sorted portions of the array
void merge(int arr[], int low, int mid, int high)
{
    int temp[100];
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

// Performs Merge Sort using divide and conquer
void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// Displays all elements of the array
void displayArray(int arr[], int size)
{
    cout << endl;

    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";

    cout << endl;
}

int main()
{
    int option = 0;

    // Keep displaying the menu until the user chooses Exit
    while (option != 6)
    {
        cout << "\nMENU\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Quick Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Insertion Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Exit\n";
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

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
                break;
            }

            if (size < 1 || size > 100)
            {
                cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                break;
            }

            cout << "Enter " << size << " elements: ";

            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

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
        }

        case 2:
        {
            int size;
            int arr[100];

            cout << "Enter size of array (1-100): ";
            cin >> size;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
                break;
            }

            if (size < 1 || size > 100)
            {
                cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                break;
            }

            cout << "Enter " << size << " elements: ";

            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

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

            quickSort(arr, 0, size - 1);

            cout << "Array After Sorting: ";
            displayArray(arr, size);

            break;
        }

        case 3:
        {
            int size;
            int arr[100];

            cout << "Enter size of array (1-100): ";
            cin >> size;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
                break;
            }

            if (size < 1 || size > 100)
            {
                cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                break;
            }

            cout << "Enter " << size << " elements: ";

            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

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

        case 4:
        {
            int size;
            int arr[100];

            cout << "Enter size of array (1-100): ";
            cin >> size;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
                break;
            }

            if (size < 1 || size > 100)
            {
                cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                break;
            }

            cout << "Enter " << size << " elements: ";

            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

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

            insertionSort(arr, size);

            cout << "Array After Sorting: ";
            displayArray(arr, size);

            break;
        }

        case 5:
        {
            int size;
            int arr[100];

            cout << "Enter size of array (1-100): ";
            cin >> size;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
                break;
            }

            if (size < 1 || size > 100)
            {
                cout << "Invalid size. Please enter a size between 1 and 100." << endl;
                break;
            }

            cout << "Enter " << size << " elements: ";

            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

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

            mergeSort(arr, 0, size - 1);

            cout << "Array After Sorting: ";
            displayArray(arr, size);

            break;
        }

        case 6:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter 1 to 6." << endl;
        }
    }

    return 0;
}