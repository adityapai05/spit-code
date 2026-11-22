#include <iostream>
using namespace std;

class DoublyLinkedList
{
    struct node
    {
        int data;
        node *prev;
        node *next;
    };
    node *head;

public:
    DoublyLinkedList()
    {
        head = nullptr;
    }

    int countNodes()
    {
        int count = 0;
        node *p = head;
        while (p != nullptr)
        {
            count++;
            p = p->next;
        }
        return count;
    }

    void insertAtBeginning(int x)
    {
        node *newnode = new node;
        newnode->data = x;
        newnode->prev = nullptr;

        if (head == nullptr)
        {
            newnode->next = nullptr;
            head = newnode;
            cout << "\nNode inserted @ First\n";
        }
        else
        {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
            cout << "\nNode inserted @ First\n";
        }
        display();
    }

    void insertAtEnd(int x)
    {
        node *newnode = new node;
        newnode->data = x;
        newnode->next = nullptr;

        if (head == nullptr)
        {
            newnode->prev = nullptr;
            head = newnode;
            cout << "\nNode inserted @ First & Last\n";
        }
        else
        {
            node *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = newnode;
            newnode->prev = p;
            cout << "\nNode inserted @ Last\n";
        }
        display();
    }

    void insertBeforeValue(int valToFind, int x)
    {
        if (head == nullptr)
        {
            cout << "\nList is empty\n";
            return;
        }

        if (head->data == valToFind)
        {
            insertAtBeginning(x);
            return;
        }

        node *p = head;
        while (p != nullptr && p->data != valToFind)
        {
            p = p->next;
        }

        if (p == nullptr)
        {
            cout << "\nValue " << valToFind << " not found in the list\n";
        }
        else
        {
            node *newnode = new node;
            newnode->data = x;
            newnode->next = p;
            newnode->prev = p->prev;
            p->prev->next = newnode;
            p->prev = newnode;
            cout << "\nElement " << x << " inserted before " << valToFind << "\n";
            display();
        }
    }

    void insertAfterValue(int valToFind, int x)
    {
        if (head == nullptr)
        {
            cout << "\nList is empty\n";
            return;
        }

        node *p = head;
        while (p != nullptr && p->data != valToFind)
        {
            p = p->next;
        }

        if (p == nullptr)
        {
            cout << "\nValue " << valToFind << " not found in the list\n";
        }
        else
        {
            node *newnode = new node;
            newnode->data = x;
            newnode->next = p->next;
            newnode->prev = p;
            if (p->next != nullptr)
            {
                p->next->prev = newnode;
            }
            p->next = newnode;
            cout << "\nElement " << x << " inserted after " << valToFind << "\n";
            display();
        }
    }

    void deleteFromFront()
    {
        if (head == nullptr)
        {
            cout << "\nNode is empty. You can't delete any element...\n";
            return;
        }

        node *p = head;
        if (head->next == nullptr)
        {
            head = nullptr;
            cout << "\nThe First element " << p->data << " is deleted from the linked list\n";
            delete p;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
            cout << "\nThe First element " << p->data << " is deleted from the linked list\n";
            delete p;
        }
        display();
    }

    void deleteFromEnd()
    {
        if (head == nullptr)
        {
            cout << "\nNode is empty. You can't delete any element...\n";
            return;
        }

        node *p = head;
        if (head->next == nullptr)
        {
            head = nullptr;
            cout << "\nThe Last element " << p->data << " is deleted from the linked list\n";
            delete p;
            display();
            return;
        }

        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->prev->next = nullptr;
        cout << "\nThe Last element " << p->data << " is deleted from the linked list\n";
        delete p;
        display();
    }

    void deleteAtPosition(int pos)
    {
        int len = countNodes();
        if (head == nullptr)
        {
            cout << "\nNode is empty. You can't delete any element...\n";
            return;
        }
        else if (pos < 1 || pos > len)
        {
            cout << "\nInvalid Position !!!\n";
            return;
        }
        else if (pos == 1)
        {
            node *p = head;
            head = p->next;
            if (head != nullptr)
                head->prev = nullptr;
            cout << "\nThe 1st position " << p->data << " element is deleted....\n";
            delete p;
            display();
        }
        else
        {
            node *p = head;
            for (int i = 1; i < pos; i++)
            {
                p = p->next;
            }
            p->prev->next = p->next;
            if (p->next != nullptr)
            {
                p->next->prev = p->prev;
            }
            cout << "\nThe " << pos << " position element " << p->data << " is deleted\n";
            delete p;
            display();
        }
    }

    void search(int val)
    {
        node *p = head;
        int position = 1;

        if (head == nullptr)
        {
            cout << "\nList is empty. You can't search any element from the list !!!\n";
            return;
        }

        while (p != nullptr)
        {
            if (p->data == val)
            {
                cout << "\nElement " << val << " is present at the position: " << position << "\n";
                return;
            }
            p = p->next;
            position++;
        }
        cout << "\nThe Element " << val << " is not found in the list\n";
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "\nTHE LIST IS EMPTY\n";
            return;
        }

        node *p = head;
        cout << "\nForward Traversal:\nNULL <- ";
        while (p != nullptr)
        {
            cout << p->data;
            if (p->next != nullptr)
                cout << " <-> ";
            p = p->next;
        }
        cout << " -> NULL\n";
    }

    void displayReverse()
    {
        if (head == nullptr)
        {
            cout << "\nTHE LIST IS EMPTY\n";
            return;
        }

        node *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }

        cout << "\nBackward Traversal:\nNULL <- ";
        while (p != nullptr)
        {
            cout << p->data;
            if (p->prev != nullptr)
                cout << " <-> ";
            p = p->prev;
        }
        cout << " -> NULL\n";
    }

    void sortList()
    {
        if (head == nullptr || head->next == nullptr)
        {
            cout << "\nList sorted\n";
            display();
            return;
        }

        node *p = head, *q;
        int temp;
        while (p->next != nullptr)
        {
            q = p->next;
            while (q != nullptr)
            {
                if (p->data > q->data)
                {
                    temp = p->data;
                    p->data = q->data;
                    q->data = temp;
                }
                q = q->next;
            }
            p = p->next;
        }
        cout << "\nList sorted in ascending order\n";
        display();
    }

    void reverseList()
    {
        if (head == nullptr)
        {
            cout << "\nList is empty\n";
            return;
        }

        node *curr = head, *temp = nullptr;
        while (curr != nullptr)
        {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }

        if (temp != nullptr)
        {
            head = temp->prev;
        }
        cout << "\nList reversed\n";
        display();
    }

    void concatenate(DoublyLinkedList &list2)
    {
        if (list2.head == nullptr)
        {
            cout << "\nSecond list is empty\n";
            display();
            return;
        }

        if (head == nullptr)
        {
            head = list2.head;
        }
        else
        {
            node *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = list2.head;
            list2.head->prev = p;
        }
        list2.head = nullptr;
        cout << "\nLists concatenated\n";
        display();
    }

    void mergeAlternating(DoublyLinkedList &list2)
    {
        if (head == nullptr)
        {
            head = list2.head;
            list2.head = nullptr;
            cout << "\nLists merged alternately\n";
            display();
            return;
        }
        if (list2.head == nullptr)
        {
            cout << "\nLists merged alternately\n";
            display();
            return;
        }

        node *p = head;
        node *q = list2.head;
        node *pNext = nullptr, *qNext = nullptr;

        while (p != nullptr && q != nullptr)
        {
            pNext = p->next;
            qNext = q->next;

            p->next = q;
            q->prev = p;

            if (pNext != nullptr)
            {
                q->next = pNext;
                pNext->prev = q;
            }

            p = pNext;
            q = qNext;
        }

        list2.head = nullptr;
        cout << "\nLists merged alternately\n";
        display();
    }

    bool contains(node *start, int val)
    {
        node *p = start;
        while (p != nullptr)
        {
            if (p->data == val)
                return true;
            p = p->next;
        }
        return false;
    }

    void appendSilent(int x)
    {
        node *newnode = new node;
        newnode->data = x;
        newnode->next = nullptr;

        if (head == nullptr)
        {
            newnode->prev = nullptr;
            head = newnode;
        }
        else
        {
            node *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = newnode;
            newnode->prev = p;
        }
    }

    DoublyLinkedList getUnion(DoublyLinkedList &list2)
    {
        DoublyLinkedList result;
        node *p = head;

        while (p != nullptr)
        {
            if (!contains(result.head, p->data))
            {
                result.appendSilent(p->data);
            }
            p = p->next;
        }

        node *q = list2.head;
        while (q != nullptr)
        {
            if (!contains(result.head, q->data))
            {
                result.appendSilent(q->data);
            }
            q = q->next;
        }

        return result;
    }

    DoublyLinkedList getIntersection(DoublyLinkedList &list2)
    {
        DoublyLinkedList result;
        node *p = head;

        while (p != nullptr)
        {
            if (contains(list2.head, p->data) && !contains(result.head, p->data))
            {
                result.appendSilent(p->data);
            }
            p = p->next;
        }

        return result;
    }

    void createCycle()
    {
        if (head == nullptr)
        {
            cout << "\nList is empty, cannot create cycle\n";
            return;
        }

        node *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = head;
        head->prev = p;
        cout << "\nCycle created (Circular Doubly Linked List formed)\n";
        displayCycle();
    }

    void displayCycle()
    {
        if (head == nullptr)
        {
            cout << "\nTHE LIST IS EMPTY\n";
            return;
        }

        node *p = head;
        cout << "\nCircular Doubly List elements:\nHead";
        do
        {
            cout << " <-> " << p->data;
            p = p->next;
        } while (p != head && p != nullptr);

        if (p == head)
            cout << " <-> (Back to Head: " << head->data << ")\n";
        else
            cout << " -> NULL (No cycle)\n";
    }

    void detectAndBreakCycle()
    {
        if (head == nullptr)
        {
            cout << "\nList is empty\n";
            return;
        }

        node *slow = head, *fast = head;
        bool hasCycle = false;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                hasCycle = true;
                break;
            }
        }

        if (!hasCycle)
        {
            cout << "\nNo cycle detected in the list\n";
            return;
        }

        cout << "\nCycle detected! Breaking cycle to restore normal doubly linked list...\n";
        slow = head;
        if (slow == fast)
        {
            while (fast->next != slow)
            {
                fast = fast->next;
            }
        }
        else
        {
            while (slow->next != fast->next)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
        fast->next = nullptr;
        head->prev = nullptr;
        display();
    }

    void createSecondList(DoublyLinkedList &list2)
    {
        int n, val;
        cout << "Enter number of nodes for 2nd list: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter value " << i + 1 << ": ";
            cin >> val;
            list2.appendSilent(val);
        }
    }
};

int main()
{
    DoublyLinkedList list, list2, result;
    int choice, val, valToFind, pos;

    do
    {
        cout << "\n===== DOUBLY LINKED LIST MENU =====\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert Before Value\n";
        cout << "4. Insert After Value\n";
        cout << "5. Delete from Front\n";
        cout << "6. Delete from End\n";
        cout << "7. Delete at Specified Position\n";
        cout << "8. Search Element\n";
        cout << "9. Display Forward\n";
        cout << "10. Display Backward (Reverse Traversal)\n";
        cout << "11. Count Nodes\n";
        cout << "12. Sort List\n";
        cout << "13. Reverse List\n";
        cout << "14. Concatenate with Another List\n";
        cout << "15. Merge Two Linked Lists\n";
        cout << "16. Union of Two Lists\n";
        cout << "17. Intersection of Two Lists\n";
        cout << "18. Create Cycle & Display\n";
        cout << "19. Detect & Break Cycle\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> val;
            list.insertAtBeginning(val);
            break;

        case 2:
            cout << "Enter value to insert: ";
            cin >> val;
            list.insertAtEnd(val);
            break;

        case 3:
            cout << "Enter value to find: ";
            cin >> valToFind;
            cout << "Enter value to insert: ";
            cin >> val;
            list.insertBeforeValue(valToFind, val);
            break;

        case 4:
            cout << "Enter value to find: ";
            cin >> valToFind;
            cout << "Enter value to insert: ";
            cin >> val;
            list.insertAfterValue(valToFind, val);
            break;

        case 5:
            list.deleteFromFront();
            break;

        case 6:
            list.deleteFromEnd();
            break;

        case 7:
            cout << "Enter position to delete: ";
            cin >> pos;
            list.deleteAtPosition(pos);
            break;

        case 8:
            cout << "Enter element to search: ";
            cin >> val;
            list.search(val);
            break;

        case 9:
            list.display();
            break;

        case 10:
            list.displayReverse();
            break;

        case 11:
            cout << "\nTotal nodes: " << list.countNodes() << "\n";
            break;

        case 12:
            list.sortList();
            break;

        case 13:
            list.reverseList();
            break;

        case 14:
            list2 = DoublyLinkedList();
            list.createSecondList(list2);
            list.concatenate(list2);
            break;

        case 15:
            list2 = DoublyLinkedList();
            list.createSecondList(list2);
            list.mergeAlternating(list2);
            break;

        case 16:
            list2 = DoublyLinkedList();
            list.createSecondList(list2);
            result = list.getUnion(list2);
            cout << "\nUnion List:";
            result.display();
            break;

        case 17:
            list2 = DoublyLinkedList();
            list.createSecondList(list2);
            result = list.getIntersection(list2);
            cout << "\nIntersection List:";
            result.display();
            break;

        case 18:
            list.createCycle();
            break;

        case 19:
            list.detectAndBreakCycle();
            break;

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}