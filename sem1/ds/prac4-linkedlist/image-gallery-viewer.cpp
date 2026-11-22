#include <iostream>
#include <string>
using namespace std;

class ImageGallery
{
    struct Image
    {
        int id;
        string name;
        Image *prev;
        Image *next;
    };
    Image *head;
    Image *current;

public:
    ImageGallery()
    {
        head = nullptr;
        current = nullptr;
    }

    void insertImage(int id, string name)
    {
        Image *newImg = new Image;
        newImg->id = id;
        newImg->name = name;
        newImg->next = nullptr;

        if (head == nullptr)
        {
            newImg->prev = nullptr;
            head = newImg;
            current = newImg;
        }
        else
        {
            Image *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = newImg;
            newImg->prev = p;
        }
        cout << "\nImage [" << id << " - " << name << "] added to gallery.\n";
        showCurrent();
    }

    void deleteCurrentImage()
    {
        if (current == nullptr)
        {
            cout << "\nGallery is empty. Nothing to delete.\n";
            return;
        }

        Image *toDelete = current;
        cout << "\nDeleted Image [" << toDelete->id << " - " << toDelete->name << "].\n";

        if (toDelete->prev != nullptr)
        {
            toDelete->prev->next = toDelete->next;
        }
        else
        {
            head = toDelete->next; // Deleting the first image
        }

        if (toDelete->next != nullptr)
        {
            toDelete->next->prev = toDelete->prev;
            current = toDelete->next; // Move viewer to next image
        }
        else
        {
            current = toDelete->prev; // Move viewer to previous image if last was deleted
        }

        delete toDelete;
        showCurrent();
    }

    void nextImage()
    {
        if (current == nullptr)
        {
            cout << "\nGallery is empty.\n";
            return;
        }

        if (current->next != nullptr)
        {
            current = current->next;
            showCurrent();
        }
        else
        {
            cout << "\nYou are already at the LAST image.\n";
            showCurrent();
        }
    }

    void prevImage()
    {
        if (current == nullptr)
        {
            cout << "\nGallery is empty.\n";
            return;
        }

        if (current->prev != nullptr)
        {
            current = current->prev;
            showCurrent();
        }
        else
        {
            cout << "\nYou are already at the FIRST image.\n";
            showCurrent();
        }
    }

    void showCurrent()
    {
        if (current == nullptr)
        {
            cout << "\n[Viewer]: No image open (Gallery Empty)\n";
        }
        else
        {
            cout << "\n[Currently Viewing]: ID #" << current->id << " | " << current->name << "\n";
        }
    }

    void displayAll()
    {
        if (head == nullptr)
        {
            cout << "\nGallery is empty.\n";
            return;
        }

        Image *p = head;
        cout << "\nAll Images in Gallery:\nNULL <- ";
        while (p != nullptr)
        {
            if (p == current)
                cout << "[" << p->id << ":" << p->name << " (ACTIVE)]";
            else
                cout << "[" << p->id << ":" << p->name << "]";

            if (p->next != nullptr)
                cout << " <-> ";
            p = p->next;
        }
        cout << " -> NULL\n";
    }
};

int main()
{
    ImageGallery gallery;
    int choice, id;
    string name;

    do
    {
        cout << "\n===== IMAGE GALLERY VIEWER =====\n";
        cout << "1. Insert Image\n";
        cout << "2. Delete Current Image\n";
        cout << "3. Next Image\n";
        cout << "4. Previous Image\n";
        cout << "5. Show Current Image\n";
        cout << "6. Display All Images\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Image ID: ";
            cin >> id;
            cout << "Enter Image Name (e.g., sunset.jpg): ";
            cin >> name;
            gallery.insertImage(id, name);
            break;

        case 2:
            gallery.deleteCurrentImage();
            break;

        case 3:
            gallery.nextImage();
            break;

        case 4:
            gallery.prevImage();
            break;

        case 5:
            gallery.showCurrent();
            break;

        case 6:
            gallery.displayAll();
            break;

        case 0:
            cout << "Exiting Gallery...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}