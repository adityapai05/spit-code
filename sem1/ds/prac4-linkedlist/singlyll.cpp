#include <iostream>
using namespace std;

class LinkedList
{
    struct node
    {
        int data;
        node *next;
    };
    node *head;

public:
    LinkedList()
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

        if (head == nullptr)
        {
            newnode->data = x;
            newnode->next = nullptr;
            head = newnode;
            cout << "\nNode inserted @ First\n";
        }
        else
        {
            newnode->data = x;
            newnode->next = head;
            head = newnode;
            cout << "\nNode inserted @ First\n";
        }
        display();
    }

    void insertAtEnd(int x)
    {
        node *newnode = new node;

        if (head == nullptr)
        {
            newnode->data = x;
            newnode->next = nullptr;
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
            newnode->data = x;
            newnode->next = nullptr;
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
        while (p != nullptr && p->data != valToFind)
        {
            q = p;
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
        else
        {
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
                cout << "\nThe First element " << p->data << " is deleted from the linked list\n";
                delete p;
            }
        }
        display();
    }

    void deleteFromEnd()
    {
        node *p = head, *q = nullptr;

        if (head == nullptr)
        {
            cout << "\nNode is empty. You can't delete any element...\n";
            return;
        }
        else if (head->next == nullptr)
        {
            head = nullptr;
            cout << "\nThe Last element " << p->data << " is deleted from the linked list\n";
            delete p;
            display();
            return;
        }
        else
        {
            while (p->next != nullptr)
            {
                q = p;
                p = p->next;
            }
            q->next = nullptr;
            cout << "\nThe Last element " << p->data << " is deleted from the linked list\n";
            delete p;
            display();
            return;
        }
    }

    void deleteAtPosition(int pos)
    {
        int i, len = countNodes();
        node *p = head, *q = nullptr;

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
            head = p->next;
            cout << "\nThe 1st position " << p->data << " element is deleted....\n";
            delete p;
            display();
        }
        else
        {
            for (i = 1; i < pos - 1; i++)
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
        node *p = head;
        int position = 1, flag = 0;

        if (head == nullptr)
        {
            cout << "\nList is empty. You can't search any element from the list !!!\n";
            return;
        }
        else
        {
            while (p != nullptr)
            {
                if (p->data == val)
                {
                    cout << "\nElement " << val << " is present at the position: " << position << "\n";
                    flag = 1;
                    return;
                }
                p = p->next;
                position++;
            }
            if (flag == 0)
            {
                cout << "\nThe Element " << val << " is not found in the list\n";
            }
        }
    }

    void display()
    {
        node *p;

        if (head == nullptr)
        {
            cout << "\nTHE LIST IS EMPTY\n";
            return;
        }
        else
        {
            p = head;
            cout << "\nThe elements present in the list are:\n";
            cout << "Head";
            while (p != nullptr)
            {
                cout << " -> " << p->data;
                p = p->next;
            }
            cout << "\n";
        }
    }

    void sortList()
    {
        if (head == nullptr || head->next == nullptr)
        {
            cout << "\nList sorted\n";
            display();
            return;
        }

        node *p, *q;
        int temp;
        p = head;
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

        node *p = head, *q=nullptr, *r=nullptr;
        while(p != nullptr) {
            r = q;
            q = p;
            p = p->next;
            q->next = r;
        }
        head = q;
        cout << "\nList reversed\n";
        display();
    }

    void concatenate(LinkedList &list2)
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
        }
        list2.head = nullptr;
        cout << "\nLists concatenated\n";
        display();
    }

    void mergeSorted(LinkedList &list2)
    {
        sortList();
        list2.sortList();

        node *p = head;
        node *q = list2.head;
        node *mergedHead = nullptr, *tail = nullptr;

        if (p == nullptr)
        {
            head = q;
            list2.head = nullptr;
            display();
            return;
        }
        if (q == nullptr)
        {
            display();
            return;
        }

        if (p->data <= q->data)
        {
            tail = p;
            mergedHead = p;
            p = p->next;
        }
        else
        {
            mergedHead = q;
            tail = q;
            q = q->next;
        }

        while (p != nullptr && q != nullptr)
        {
            if (p->data <= q->data)
            {
                tail->next = p;
                tail = p;
                p = p->next;
            }
            else
            {
                tail->next = q;
                tail = q;
                q = q->next;
            }
        }

        if (p != nullptr)
            tail->next = p;
        else
            tail->next = q;

        head = mergedHead;
        list2.head = nullptr;
        cout << "\nLists merged in sorted order\n";
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
        }
    }

    LinkedList getUnion(LinkedList &list2)
    {
        LinkedList result;
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

    LinkedList getIntersection(LinkedList &list2)
    {
        LinkedList result;
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
        cout << "\nCycle created (Last node now points to Head)\n";
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
        cout << "\nCircular List elements:\nHead";
        do
        {
            cout << " -> " << p->data;
            p = p->next;
        } while (p != head && p != nullptr);

        if (p == head)
            cout << " -> (Back to Head: " << head->data << ")\n";
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

        cout << "\nCycle detected! Breaking cycle to restore normal list...\n";
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
        display();
    }

    void createSecondList(LinkedList &list2)
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
    LinkedList list, list2, result;
    int choice, val, valToFind, pos;

    do
    {
        cout << "\n===== LINKED LIST MENU =====\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert Before Value\n";
        cout << "4. Insert After Value\n";
        cout << "5. Delete from Front\n";
        cout << "6. Delete from End\n";
        cout << "7. Delete at Specified Position\n";
        cout << "8. Search Element\n";
        cout << "9. Display Linked List\n";
        cout << "10. Count Nodes\n";
        cout << "11. Sort List\n";
        cout << "12. Reverse List\n";
        cout << "13. Concatenate with Another List\n";
        cout << "14. Merge Two Sorted Lists\n";
        cout << "15. Union of Two Lists\n";
        cout << "16. Intersection of Two Lists\n";
        cout << "17. Create Cycle & Display\n";
        cout << "18. Detect & Break Cycle\n";
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
            list2 = LinkedList();
            list.createSecondList(list2);
            list.concatenate(list2);
            break;

        case 14:
            list2 = LinkedList();
            list.createSecondList(list2);
            list.mergeSorted(list2);
            break;

        case 15:
            list2 = LinkedList();
            list.createSecondList(list2);
            result = list.getUnion(list2);
            cout << "\nUnion List:";
            result.display();
            break;

        case 16:
            list2 = LinkedList();
            list.createSecondList(list2);
            result = list.getIntersection(list2);
            cout << "\nIntersection List:";
            result.display();
            break;

        case 17:
            list.createCycle();
            break;

        case 18:
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