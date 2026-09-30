#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Structure to store the details of each student
struct Student
{
    int rollNo;
    string name;
    int marks;
};

// Static student dataset used for generating examination rankings
Student students[] = {
    {1, "Student01", 78}, {2, "Student02", 92}, {3, "Student03", 65}, {4, "Student04", 88}, {5, "Student05", 74}, {6, "Student06", 95}, {7, "Student07", 61}, {8, "Student08", 83}, {9, "Student09", 70}, {10, "Student10", 89}, {11, "Student11", 56}, {12, "Student12", 97}, {13, "Student13", 68}, {14, "Student14", 81}, {15, "Student15", 76}, {16, "Student16", 90}, {17, "Student17", 63}, {18, "Student18", 85}, {19, "Student19", 72}, {20, "Student20", 94}, {21, "Student21", 59}, {22, "Student22", 87}, {23, "Student23", 79}, {24, "Student24", 66}, {25, "Student25", 91}, {26, "Student26", 73}, {27, "Student27", 98}, {28, "Student28", 62}, {29, "Student29", 84}, {30, "Student30", 77}, {31, "Student31", 69}, {32, "Student32", 93}, {33, "Student33", 58}, {34, "Student34", 80}, {35, "Student35", 75}, {36, "Student36", 96}, {37, "Student37", 64}, {38, "Student38", 86}, {39, "Student39", 71}, {40, "Student40", 89}, {41, "Student41", 55}, {42, "Student42", 82}, {43, "Student43", 78}, {44, "Student44", 99}, {45, "Student45", 67}, {46, "Student46", 88}, {47, "Student47", 74}, {48, "Student48", 92}, {49, "Student49", 60}, {50, "Student50", 83}, {51, "Student51", 76}, {52, "Student52", 95}, {53, "Student53", 68}, {54, "Student54", 81}, {55, "Student55", 73}, {56, "Student56", 90}, {57, "Student57", 57}, {58, "Student58", 85}, {59, "Student59", 79}, {60, "Student60", 94}, {61, "Student61", 63}, {62, "Student62", 87}, {63, "Student63", 70}, {64, "Student64", 96}, {65, "Student65", 65}, {66, "Student66", 89}, {67, "Student67", 77}, {68, "Student68", 91}, {69, "Student69", 54}, {70, "Student70", 84}, {71, "Student71", 72}, {72, "Student72", 98}, {73, "Student73", 61}, {74, "Student74", 86}, {75, "Student75", 75}, {76, "Student76", 93}, {77, "Student77", 69}, {78, "Student78", 80}, {79, "Student79", 66}, {80, "Student80", 97}, {81, "Student81", 59}, {82, "Student82", 83}, {83, "Student83", 78}, {84, "Student84", 90}, {85, "Student85", 64}, {86, "Student86", 88}, {87, "Student87", 71}, {88, "Student88", 95}, {89, "Student89", 67}, {90, "Student90", 82}, {91, "Student91", 56}, {92, "Student92", 85}, {93, "Student93", 74}, {94, "Student94", 99}, {95, "Student95", 62}, {96, "Student96", 79}, {97, "Student97", 87}, {98, "Student98", 73}, {99, "Student99", 92}, {100, "Student100", 81}};

const int SIZE = sizeof(students) / sizeof(students[0]);

// Copies the student dataset so that the original data remains unchanged
void copyData(Student source[], Student destination[])
{
    for (int i = 0; i < SIZE; i++)
        destination[i] = source[i];
}

// Displays the complete student dataset in a table
void displayAllStudents()
{
    cout << "\n---------------- STUDENT RESULT DATA ----------------\n";

    cout << left
         << setw(10) << "Roll No"
         << setw(20) << "Name"
         << "Marks" << endl;

    cout << "------------------------------------------------------\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << left
             << setw(10) << students[i].rollNo
             << setw(20) << students[i].name
             << students[i].marks << endl;
    }

    cout << "------------------------------------------------------\n";
}

// Counts the number of comparisons performed by Quick Sort
int quickComparisons = 0;

// Partitions the array using the first element as the pivot
// Students are arranged in descending order of marks
int partition(Student arr[], int low, int high)
{
    int pivot = arr[low].marks;
    int i = low;
    int j = high;

    while (i < j)
    {
        // Move i until a smaller element than the pivot is found
        while (i <= high && arr[i].marks >= pivot)
        {
            quickComparisons++;
            i++;
        }

        // Move j until a greater or equal element than the pivot is found
        while (j >= low && arr[j].marks < pivot)
        {
            quickComparisons++;
            j--;
        }

        // Swap the elements if i is still before j
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // Place the pivot in its correct position
    swap(arr[low], arr[j]);

    return j;
}

// Performs Quick Sort using divide and conquer
void quickSort(Student arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Counts the number of comparisons performed by Merge Sort
int mergeComparisons = 0;

// Merges two sorted portions of the array
// Students are arranged in descending order of marks
void merge(Student arr[], int low, int mid, int high)
{
    Student temp[SIZE];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        mergeComparisons++;

        if (arr[i].marks >= arr[j].marks)
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
void mergeSort(Student arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// Displays the student ranking after sorting
void displayRanking(Student arr[])
{
    cout << "\n---------------- STUDENT RANKING ----------------\n";

    cout << left
         << setw(8) << "Rank"
         << setw(10) << "Roll No"
         << setw(20) << "Name"
         << "Marks" << endl;

    cout << "--------------------------------------------------\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << left
             << setw(8) << i + 1
             << setw(10) << arr[i].rollNo
             << setw(20) << arr[i].name
             << arr[i].marks << endl;
    }

    cout << "--------------------------------------------------\n";
}

// Generates the student ranking using Quick Sort
// The number of comparisons is also displayed
void performQuickSort()
{
    Student data[SIZE];

    copyData(students, data);

    quickComparisons = 0;

    quickSort(data, 0, SIZE - 1);

    cout << "\nQuick Sort Ranking Generated.\n";
    cout << "Number of comparisons: " << quickComparisons << endl;

    displayRanking(data);
}

// Generates the student ranking using Merge Sort
// The number of comparisons is also displayed
void performMergeSort()
{
    Student data[SIZE];

    copyData(students, data);

    mergeComparisons = 0;

    mergeSort(data, 0, SIZE - 1);

    cout << "\nMerge Sort Ranking Generated.\n";
    cout << "Number of comparisons: " << mergeComparisons << endl;

    displayRanking(data);
}

// Creates a sorted dataset for performance comparison
void createSortedData(Student source[], Student destination[])
{
    copyData(source, destination);

    mergeSort(destination, 0, SIZE - 1);
}

// Creates a reverse-sorted dataset for performance comparison
void createReverseSortedData(Student source[], Student destination[])
{
    copyData(source, destination);

    mergeSort(destination, 0, SIZE - 1);

    for (int i = 0; i < SIZE / 2; i++)
        swap(destination[i], destination[SIZE - 1 - i]);
}

// Runs both sorting algorithms on the same dataset
// The number of comparisons is used to compare their performance
void compareSorts(Student source[], string dataType)
{
    Student quickData[SIZE];
    Student mergeData[SIZE];

    copyData(source, quickData);
    copyData(source, mergeData);

    quickComparisons = 0;
    mergeComparisons = 0;

    quickSort(quickData, 0, SIZE - 1);
    mergeSort(mergeData, 0, SIZE - 1);

    cout << "\n"
         << dataType << " Data\n";
    cout << "Quick Sort comparisons : " << quickComparisons << endl;
    cout << "Merge Sort comparisons : " << mergeComparisons << endl;
}

// Compares Quick Sort and Merge Sort for random, sorted and reverse-sorted data
void compareSortPerformance()
{
    Student sortedData[SIZE];
    Student reverseSortedData[SIZE];

    createSortedData(students, sortedData);
    createReverseSortedData(students, reverseSortedData);

    cout << "\n--------------- SORT PERFORMANCE COMPARISON ---------------\n";

    compareSorts(students, "Randomly Ordered");
    compareSorts(sortedData, "Sorted");
    compareSorts(reverseSortedData, "Reverse Sorted");

    cout << "------------------------------------------------------------\n";
}

int main()
{
    int option = 0;

    cout << "============================================================\n";
    cout << "          ONLINE EXAMINATION RESULT PROCESSING\n";
    cout << "============================================================\n";

    while (option != 5)
    {
        cout << "\nMENU\n";
        cout << "1. Sort using Quick Sort\n";
        cout << "2. Sort using Merge Sort\n";
        cout << "3. Compare Quick Sort and Merge Sort\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> option;

        // Handle cases where the user enters something other than a number
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (option)
        {
        case 1:
            performQuickSort();
            break;

        case 2:
            performMergeSort();
            break;

        case 3:
            compareSortPerformance();
            break;

        case 4:
            displayAllStudents();
            break;

        case 5:
            cout << "\nExiting program...\n";
            break;

        default:
            cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
        }
    }

    return 0;
}