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

// Returns the largest element in the array
int getMax(int arr[], int size)
{
    int maximum = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maximum)
            maximum = arr[i];
    }

    return maximum;
}

// Performs Radix Sort on the given array
void radixSort(int arr[], int size)
{
    // Find the largest number
    int maximum = getMax(arr, size);

    // Process each digit position
    for (int place = 1; maximum / place > 0; place *= 10)
    {
        int bucket[10][100] = {};
        int count[10] = {0};

        // Put numbers into buckets according to current digit
        for (int i = 0; i < size; i++)
        {
            int digit = (arr[i] / place) % 10;
            bucket[digit][count[digit]] = arr[i];
            count[digit]++;
        }

        // Copy buckets back into the array
        int index = 0;

        for (int digit = 0; digit < 10; digit++)
        {
            for (int j = 0; j < count[digit]; j++)
            {
                arr[index] = bucket[digit][j];
                index++;
            }
        }
    }
}

// Performs Shell Sort on the given array
void shellSort(int arr[], int size)
{
    // Start with a gap of half the array size
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        // Perform insertion sort for the elements with the given gap
        for (int i = gap; i < size; i++)
        {
            int key = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > key)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = key;
        }
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
    while (option != 8)
    {
        cout << "\nMENU\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Quick Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Insertion Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Radix Sort\n";
        cout << "7. Shell Sort\n";
        cout << "8. Exit\n";
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

            cout << "Enter " << size << " non-negative elements: ";

            bool valid = true;

            for (int i = 0; i < size; i++)
            {
                cin >> arr[i];

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid element. Please enter integers only." << endl;
                    valid = false;
                    break;
                }

                if (arr[i] < 0)
                {
                    cout << "Radix Sort supports only non-negative integers." << endl;
                    cin.ignore(1000, '\n');
                    valid = false;
                    break;
                }
            }

            if (!valid)
                break;

            cout << "Array Before Sorting: ";
            displayArray(arr, size);

            radixSort(arr, size);

            cout << "Array After Sorting: ";
            displayArray(arr, size);

            break;
        }

        case 7:
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

            shellSort(arr, size);

            cout << "Array After Sorting: ";
            displayArray(arr, size);

            break;
        }

        case 8:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter 1 to 8." << endl;
        }
    }

    return 0;
}