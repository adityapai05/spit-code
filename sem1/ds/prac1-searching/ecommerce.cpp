#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Product
{
    int productID;
    string productName;
    double price;
};

// Products are stored in ascending order of Product ID  for Binary Search
Product products[] =
{
    {101, "Laptop", 55000.50},
    {102, "Smartphone", 24999.99},
    {103, "Headphones", 1999.50},
    {104, "Keyboard", 1499.00},
    {105, "Mouse", 799.99},
    {106, "Smartwatch", 3499.50},
    {107, "Tablet", 18999.00},
    {108, "Bluetooth Speaker", 2499.99},
    {109, "Power Bank", 1299.50},
    {110, "USB Cable", 499.00},
    {111, "Monitor", 12500.75},
    {112, "Webcam", 2299.99},
    {113, "Printer", 8999.50},
    {114, "External Hard Drive", 6499.00},
    {115, "Gaming Chair", 15999.99},

    {116, "Mechanical Keyboard", 3499.00},
    {117, "Wireless Mouse", 1199.50},
    {118, "Gaming Mouse", 2499.00},
    {119, "Gaming Headset", 3999.99},
    {120, "Laptop Stand", 1299.00},
    {121, "USB Hub", 899.99},
    {122, "SSD 500GB", 4299.50},
    {123, "SSD 1TB", 7499.00},
    {124, "RAM 8GB", 2199.99},
    {125, "RAM 16GB", 3999.00},
    {126, "Graphics Card", 32999.99},
    {127, "Motherboard", 12999.50},
    {128, "Computer Cabinet", 4499.00},
    {129, "CPU Cooler", 2499.99},
    {130, "Power Supply", 3999.50},

    {131, "Smart TV", 35999.00},
    {132, "Soundbar", 8999.99},
    {133, "Home Theater System", 15999.50},
    {134, "Streaming Stick", 3499.00},
    {135, "Projector", 18999.99},
    {136, "Digital Camera", 42999.00},
    {137, "Action Camera", 8999.50},
    {138, "Camera Tripod", 1799.99},
    {139, "Camera Bag", 2499.00},
    {140, "Memory Card 128GB", 999.50},

    {141, "Wireless Earbuds", 1999.99},
    {142, "Neckband", 1499.00},
    {143, "Portable Speaker", 2999.50},
    {144, "Smart Band", 2499.99},
    {145, "Fitness Tracker", 3499.00},
    {146, "Wireless Charger", 1299.99},
    {147, "Fast Charger", 999.00},
    {148, "Car Charger", 699.50},
    {149, "Phone Holder", 599.99},
    {150, "Selfie Stick", 899.00},

    {151, "Gaming Console", 44999.99},
    {152, "Game Controller", 4999.00},
    {153, "Gaming Monitor", 18999.50},
    {154, "Gaming Keyboard", 4999.99},
    {155, "Gaming Mouse Pad", 1299.00},
    {156, "Gaming Desk", 8999.50},
    {157, "VR Headset", 29999.99},
    {158, "Racing Wheel", 15999.00},
    {159, "Console Headset", 5499.50},
    {160, "Game Storage Drive", 6999.99},

    {161, "Air Conditioner", 38999.00},
    {162, "Air Cooler", 8999.50},
    {163, "Ceiling Fan", 2499.99},
    {164, "Table Fan", 1799.00},
    {165, "Room Heater", 2299.50},
    {166, "Vacuum Cleaner", 7999.99},
    {167, "Air Purifier", 11999.00},
    {168, "Electric Kettle", 1499.50},
    {169, "Microwave Oven", 8999.99},
    {170, "Induction Cooktop", 2199.00},

    {171, "Refrigerator", 32999.50},
    {172, "Washing Machine", 28999.99},
    {173, "Dishwasher", 35999.00},
    {174, "Mixer Grinder", 3499.50},
    {175, "Juicer", 2999.99},
    {176, "Toaster", 1499.00},
    {177, "Coffee Maker", 3999.50},
    {178, "Hand Blender", 1799.99},
    {179, "Rice Cooker", 2499.00},
    {180, "Electric Chopper", 1299.50},

    {181, "Backpack", 1999.99},
    {182, "Laptop Backpack", 2499.00},
    {183, "Travel Bag", 2999.50},
    {184, "Trolley Bag", 5499.99},
    {185, "Office Chair", 8999.00},
    {186, "Study Table", 6999.50},
    {187, "Bookshelf", 4999.99},
    {188, "Desk Lamp", 999.00},
    {189, "LED Bulb", 299.50},
    {190, "Smart LED Bulb", 799.99},

    {191, "Fitness Band", 2299.00},
    {192, "Yoga Mat", 899.50},
    {193, "Dumbbell Set", 3499.99},
    {194, "Resistance Bands", 999.00},
    {195, "Treadmill", 29999.50},
    {196, "Exercise Cycle", 14999.99},
    {197, "Football", 1299.00},
    {198, "Cricket Bat", 3499.50},
    {199, "Badminton Racket", 1999.99},
    {200, "Tennis Racket", 2999.00}
};

const int SIZE = sizeof(products) / sizeof(products[0]);

// Displays details of one product
void displayProduct(const Product& product)
{
    cout << "Product ID   : " << product.productID << endl;
    cout << "Product Name : " << product.productName << endl;
    cout << "Price        : Rs. "
         << fixed << setprecision(2) << product.price << endl;
}

// Displays all products in a table
void displayAllProducts()
{
    cout << "\n---------------- E-COMMERCE PRODUCT CATALOGUE ----------------\n";

    cout << left
         << setw(10) << "ID"
         << setw(28) << "Product Name"
         << "Price" << endl;

    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << left
             << setw(10) << products[i].productID
             << setw(28) << products[i].productName
             << "Rs. " << fixed << setprecision(2)
             << products[i].price << endl;
    }

    cout << "---------------------------------------------------------------\n";
}

// Linear Search searches for a Product ID one element at a time and takes O(n) time
int linearSearch(int targetID, int& comparisons)
{
    comparisons = 0;

    for (int i = 0; i < SIZE; i++)
    {
        comparisons++;

        if (products[i].productID == targetID)
        {
            return i;
        }
    }

    return -1;
}

// Binary Search works because products are sorted by Product ID and takes O(logn) time
int binarySearch(int targetID, int& comparisons)
{
    int low = 0, high = SIZE - 1;

    comparisons = 0;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        comparisons++;

        if (products[mid].productID == targetID)
        {
            return mid;
        }
        else if (products[mid].productID < targetID)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

// Linear Search is used for price range searching because the products are not sorted by price
void searchByPriceRange(double minimumPrice, double maximumPrice)
{
    if (minimumPrice > maximumPrice)
    {
        cout << "\nInvalid price range. Minimum price cannot be "
             << "greater than maximum price.\n";
        return;
    }

    bool found = false;

    cout << "\nProducts between Rs. "
         << fixed << setprecision(2) << minimumPrice
         << " and Rs. " << maximumPrice << ":\n\n";

    cout << left
         << setw(10) << "ID"
         << setw(28) << "Product Name"
         << "Price" << endl;

    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < SIZE; i++)
    {
        if (products[i].price >= minimumPrice &&
            products[i].price <= maximumPrice)
        {
            found = true;

            cout << left
                 << setw(10) << products[i].productID
                 << setw(28) << products[i].productName
                 << "Rs. " << fixed << setprecision(2)
                 << products[i].price << endl;
        }
    }

    if (!found)
    {
        cout << "No products found in the given price range.\n";
    }

    cout << "---------------------------------------------------------------\n";
}

// Compares Linear Search and Binary Search using
// the number of comparisons required
void compareSearches(int targetID)
{
    int linearComparisons = 0;
    int binaryComparisons = 0;

    int linearResult = linearSearch(targetID, linearComparisons);
    int binaryResult = binarySearch(targetID, binaryComparisons);

    cout << "\n--------------- SEARCH PERFORMANCE COMPARISON ---------------\n";

    cout << "Product ID searched : " << targetID << endl;

    cout << "\nLinear Search\n";
    cout << "Result              : ";

    if (linearResult != -1)
    {
        cout << "Product Found\n";
    }
    else
    {
        cout << "Product Not Found\n";
    }

    cout << "Comparisons         : " << linearComparisons << endl;

    cout << "\nBinary Search\n";
    cout << "Result              : ";

    if (binaryResult != -1)
    {
        cout << "Product Found\n";
    }
    else
    {
        cout << "Product Not Found\n";
    }

    cout << "Comparisons         : " << binaryComparisons << endl;

    cout << "\nTime Complexity\n";
    cout << "Linear Search      : O(n)\n";
    cout << "Binary Search      : O(log n)\n";

    cout << "---------------------------------------------------------------\n";
}

// Searches for a product using Linear Search
void performLinearSearch()
{
    int targetID;

    cout << "\nEnter Product ID to search: ";
    cin >> targetID;

    int comparisons = 0;
    int index = linearSearch(targetID, comparisons);

    if (index == -1)
    {
        cout << "\nProduct not found.\n";
    }
    else
    {
        cout << "\nProduct found.\n\n";
        displayProduct(products[index]);
    }

    cout << "Number of comparisons: " << comparisons << endl;
}

// Searches for a product using Binary Search
void performBinarySearch()
{
    int targetID;

    cout << "\nEnter Product ID to search: ";
    cin >> targetID;

    int comparisons = 0;
    int index = binarySearch(targetID, comparisons);

    if (index == -1)
    {
        cout << "\nProduct not found.\n";
    }
    else
    {
        cout << "\nProduct found.\n\n";
        displayProduct(products[index]);
    }

    cout << "Number of comparisons: " << comparisons << endl;
}

int main()
{
    int option = 0;

    cout << "===============================================================\n";
    cout << "              E-COMMERCE PRODUCT SEARCH SYSTEM\n";
    cout << "===============================================================\n";

    while (option != 6)
    {
        cout << "\nMENU\n";
        cout << "1. Linear Search by Product ID\n";
        cout << "2. Binary Search by Product ID\n";
        cout << "3. Search Products by Price Range\n";
        cout << "4. Compare Linear Search and Binary Search\n";
        cout << "5. Display All Products\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> option;

        switch (option)
        {
            case 1:
                performLinearSearch();
                break;

            case 2:
                performBinarySearch();
                break;

            case 3:
            {
                double minimumPrice;
                double maximumPrice;

                cout << "\nEnter Minimum Price: ";
                cin >> minimumPrice;

                cout << "Enter Maximum Price: ";
                cin >> maximumPrice;

                searchByPriceRange(minimumPrice, maximumPrice);
                break;
            }

            case 4:
            {
                int targetID;

                cout << "\nEnter Product ID to compare searches: ";
                cin >> targetID;

                compareSearches(targetID);
                break;
            }

            case 5:
                displayAllProducts();
                break;

            case 6:
                cout << "\nExiting program...\n";
                break;

            default:
                cout << "\nInvalid choice. Please enter a number "
                     << "between 1 and 6.\n";
        }
    }

    return 0;
}