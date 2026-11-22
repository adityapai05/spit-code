#include <iostream>
using namespace std;

class CircularLinkedList
{
    struct node
    {
        int data;
        node *next;
    };
    node *head;

public:
    CircularLinkedList()
    {
        head = nullptr;
    }

    int countNodes()
    {
        if (head == nullptr)
            return 0;

        int count = 0;
        node *p = head;
        do
        {
            count++;
            p = p->next;
        } while (p != head);
        return count;
    }

    void insertAtBeginning(int x)
    {
        node *newnode = new node;
        newnode->data = x;

        if (head == nullptr)
        {
            newnode->next = newnode; // Points to itself
            head = newnode;
            cout << "\nNode inserted @ First\n";
        }
        else
        {
            node *p = head;
            while (p->next != head)
            {
                p = p->next;
            }
            newnode->next = head;
            p->next = newnode;
            head = newnode;
            cout << "\nNode inserted @ First\n";
        }
        display();
    }

    void insertAtEnd(int x)
    {
        node *newnode = new node;
        newnode->data = x;

        if (head == nullptr)
        {
            newnode->next = newnode;
            head = newnode;
            cout << "\nNode inserted @ First & Last\n";
        }
        else
        {
            node *p = head;
            while (p->next != head)
            {
                p = p->next;
            }
            newnode->next = head;
            p->next = newnode;
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

        node *p = head, *q = nullptr;
        do
        {
            q = p;
            p = p->next;
        } while (p != head && p->data != valToFind);

        if (p == head)
        {
            cout << "\nValue " << valToFind << " not found in the list\n";
        }
        else
        {
            node *newnode = new node;
            newnode->data = x;
            newnode->next = p;
            q->next = newnode;
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
        bool found = false;
        do
        {
            if (p->data == valToFind)
            {
                found = true;
                break;
            }
            p = p->next;
        } while (p != head);

        if (!found)
        {
            cout << "\nValue " << valToFind << " not found in the list\n";
        }
        else
        {
            node *newnode = new node;
            newnode->data = x;
            newnode->next = p->next;
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
        if (head->next == head) // Only 1 node in list
        {
            head = nullptr;
            cout << "\nThe First element " << p->data << " is deleted from the linked list\n";
            delete p;
        }
        else
        {
            node *last = head;
            while (last->next != head)
            {
                last = last->next;
            }
            head = head->next;
            last->next = head;
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

        node *p = head, *q = nullptr;
        if (head->next == head) // Only 1 node
        {
            head = nullptr;
            cout << "\nThe Last element " << p->data << " is deleted from the linked list\n";
            delete p;
            display();
            return;
        }

        while (p->next != head)
        {
            q = p;
            p = p->next;
        }
        q->next = head;
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
            deleteFromFront();
        }
        else
        {
            node *p = head, *q = nullptr;
            for (int i = 1; i < pos - 1; i++)
            {
                p = p->next;
            }
            q = p->next;
            p->next = q->next;
            cout << "\nThe " << pos << " position element " << q->data << " is deleted\n";
            delete q;
            display();
        }
    }

    void search(int val)
    {
        if (head == nullptr)
        {
            cout << "\nList is empty. You can't search any element from the list !!!\n";
            return;
        }

        node *p = head;
        int position = 1;
        do
        {
            if (p->data == val)
            {
                cout << "\nElement " << val << " is present at the position: " << position << "\n";
                return;
            }
            p = p->next;
            position++;
        } while (p != head);

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
        cout << "\nThe elements present in the circular list are:\nHead";
        do
        {
            cout << " -> " << p->data;
            p = p->next;
        } while (p != head);
        cout << " -> (Back to Head: " << head->data << ")\n";
    }

    void sortList()
    {
        if (head == nullptr || head->next == head)
        {
            cout << "\nList sorted\n";
            display();
            return;
        }

        node *p = head, *q;
        int temp;
        while (p->next != head)
        {
            q = p->next;
            while (q != head)
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
        if (head == nullptr || head->next == head)
        {
            cout << "\nList reversed\n";
            display();
            return;
        }

        node *p = head, *q = nullptr, *r = nullptr;
        do
        {
            r = q;
            q = p;
            p = p->next;
            q->next = r;
        } while (p != head);

        head->next = q; // Old head now last node points to new head
        head = q;
        cout << "\nList reversed\n";
        display();
    }

    void mergeAlternating(CircularLinkedList &list2)
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

        // Temporarily break circular links into linear lists
        node *last1 = head;
        while (last1->next != head)
            last1 = last1->next;
        last1->next = nullptr;

        node *last2 = list2.head;
        while (last2->next != list2.head)
            last2 = last2->next;
        last2->next = nullptr;

        node *p = head;
        node *q = list2.head;
        node *pNext = nullptr, *qNext = nullptr;

        while (p != nullptr && q != nullptr)
        {
            pNext = p->next;
            qNext = q->next;

            p->next = q;
            if (pNext != nullptr)
            {
                q->next = pNext;
            }

            p = pNext;
            q = qNext;
        }

        // Find the new last node and point it back to head
        node *tail = head;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }
        tail->next = head;

        list2.head = nullptr;
        cout << "\nLists merged alternately\n";
        display();
    }

    void concatenate(CircularLinkedList &list2)
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
            while (p->next != head)
            {
                p = p->next;
            }

            node *q = list2.head;
            while (q->next != list2.head)
            {
                q = q->next;
            }

            p->next = list2.head;
            q->next = head; // Last node of list2 points back to head of list1
        }
        list2.head = nullptr;
        cout << "\nLists concatenated\n";
        display();
    }

    bool contains(node *start, int val)
    {
        if (start == nullptr)
            return false;

        node *p = start;
        do
        {
            if (p->data == val)
                return true;
            p = p->next;
        } while (p != start);
        return false;
    }

    void appendSilent(int x)
    {
        node *newnode = new node;
        newnode->data = x;

        if (head == nullptr)
        {
            newnode->next = newnode;
            head = newnode;
        }
        else
        {
            node *p = head;
            while (p->next != head)
            {
                p = p->next;
            }
            newnode->next = head;
            p->next = newnode;
        }
    }

    CircularLinkedList getUnion(CircularLinkedList &list2)
    {
        CircularLinkedList result;

        if (head != nullptr)
        {
            node *p = head;
            do
            {
                if (!contains(result.head, p->data))
                {
                    result.appendSilent(p->data);
                }
                p = p->next;
            } while (p != head);
        }

        if (list2.head != nullptr)
        {
            node *q = list2.head;
            do
            {
                if (!contains(result.head, q->data))
                {
                    result.appendSilent(q->data);
                }
                q = q->next;
            } while (q != list2.head);
        }

        return result;
    }

    CircularLinkedList getIntersection(CircularLinkedList &list2)
    {
        CircularLinkedList result;

        if (head != nullptr && list2.head != nullptr)
        {
            node *p = head;
            do
            {
                if (contains(list2.head, p->data) && !contains(result.head, p->data))
                {
                    result.appendSilent(p->data);
                }
                p = p->next;
            } while (p != head);
        }

        return result;
    }

    void verifyCircularLink()
    {
        if (head == nullptr)
        {
            cout << "\nList is empty\n";
            return;
        }

        node *p = head;
        while (p->next != head && p->next != nullptr)
        {
            p = p->next;
        }

        if (p->next == head)
            cout << "\nVerified: Last node (" << p->data << ") properly points back to Head (" << head->data << ").\n";
        else
            cout << "\nWarning: Circular link is broken!\n";
    }

    void createSecondList(CircularLinkedList &list2)
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
    CircularLinkedList list, list2, result;
    int choice, val, valToFind, pos;

    do
    {
        cout << "\n===== CIRCULAR LINKED LIST MENU =====\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert Before Value\n";
        cout << "4. Insert After Value\n";
        cout << "5. Delete from Front\n";
        cout << "6. Delete from End\n";
        cout << "7. Delete at Specified Position\n";
        cout << "8. Search Element\n";
        cout << "9. Display Circular List\n";
        cout << "10. Count Nodes\n";
        cout << "11. Sort List\n";
        cout << "12. Reverse List\n";
        cout << "13. Concatenate with Another List\n";
        cout << "14. Merge Two Linked Lists\n";
        cout << "15. Union of Two Lists\n";
        cout << "16. Intersection of Two Lists\n";
        cout << "17. Verify Circular Link\n";
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
            cout << "\nTotal nodes: " << list.countNodes() << "\n";
            break;

        case 11:
            list.sortList();
            break;

        case 12:
            list.reverseList();
            break;

        case 13:
            list2 = CircularLinkedList();
            list.createSecondList(list2);
            list.concatenate(list2);
            break;

        case 14:
            list2 = CircularLinkedList();
            list.createSecondList(list2);
            list.mergeAlternating(list2);
            break;

        case 15:
            list2 = CircularLinkedList();
            list.createSecondList(list2);
            result = list.getUnion(list2);
            cout << "\nUnion List:";
            result.display();
            break;

        case 16:
            list2 = CircularLinkedList();
            list.createSecondList(list2);
            result = list.getIntersection(list2);
            cout << "\nIntersection List:";
            result.display();
            break;

        case 17:
            list.verifyCircularLink();
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