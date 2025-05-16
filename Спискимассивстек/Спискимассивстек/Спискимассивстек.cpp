#include <iostream>
using namespace std;

class Array 
{
public:
    int size = 0;
    int sizearray = 5;
    int* massiv = new int[sizearray];
    Array() {  }
    ~Array() 
    {
        delete[] massiv;
    }

private:
    void copy(int V[], int New[], int size)
    {
        for (int i = 0; i < size; i++)
            New[i] = V[i];
    }
    
    void AvailabilitySpace()
    {
        if (size > (sizeof(int) * sizearray - 1))
        {
            int* newArray = new int[sizearray * 2];
            copy(massiv, newArray, size);
            delete[] massiv;
            massiv = newArray;
            sizearray = sizearray * 2;
        }
    }

public:
    void ArrayGet(int position)
    {
        if (position < size)
            printf("%d", massiv[position]);
        else
            printf("Error\n");
    }

    void ArrayAdd(int position, int value)
    {
        if (position <= size)
        {
            AvailabilitySpace();
            for (int i = size; i > position; i--)
                massiv[i] = massiv[i - 1];
            massiv[position] = value;
            size++;
        }
        else
            printf("Error\n");
    }

    void ArrayRemove(int position)
    {
        if (position < size)
        {
            for (int i = position; i < size; i++)
                massiv[i] = massiv[i + 1];
            massiv[size] = NULL;
            size--;
        }
        else
            printf("Error\n");
    }

    void PrintArray() 
    {
        for (int i = 0; i < size; i++)
            printf("V[%d] = %d\n", i, massiv[i]);
    }
};

class Node 
{
public:
    int data;
    Node* next;
    Node* previous;
    Node(int data) 
    {
        this->data = data;
        this->next = this->previous = nullptr;
    }
};

class List
{
public:
    Node* head;
    Node* tail;
    int size;
    
    List() 
    {
        this->head= this->tail = nullptr;
        size = 0;
    }

    ~List()
    {
        while (head != nullptr) 
        {
            ListRemove(size);
            size--;
        }
    }

public:
    Node* ListGet(int position)
    {
        if (size <= position)
            printf("Error\n");
        else
        {
            Node* current = head;
            while (position > 0)
            {
                current = current->next;
                position--;
            }
            return current;
        }
    }

    void ListAdd(int data, int position)
    {
        if (position == 0)
        {
            Node* newNode = new Node(data);
            newNode->next = head;
            if (head != nullptr)
                head->previous = newNode;
            if (tail == nullptr)
                tail = newNode;
            head = newNode;
            newNode->previous = nullptr;
        }
        else
        {
            if (position == size)
            {
                Node* newNode = new Node(data);
                newNode->previous = tail;
                if (tail != nullptr)
                    tail->next = newNode;
                if (head == nullptr)
                    head = newNode;
                tail = newNode;
                newNode->next = nullptr;
            }
            else
            {
                if (size != 0) 
                {
                    Node* currentnext = ListGet(position);
                    Node* currentprev = currentnext->previous;

                    Node* newNode = new Node(data);

                    newNode->next = currentnext;
                    newNode->previous = currentprev;
                    currentnext->previous = newNode;
                    currentprev->next = newNode;
                }
            }
        }
        size++;
    }

    void ListRemove(int position)
    {
        if (size > 0)
        {
            if (position == 1)
            {
                Node* current = head;
                head = head->next;
                head->previous = nullptr;
                delete current;
            }
            else
            {
                if (position == size)
                {
                    Node* current = tail;
                    tail = tail->previous;
                    tail->next = nullptr;
                    delete current;
                }
                else
                {
                    Node* current = ListGet(position);
                    Node* currentnext = current->next;
                    Node* currentprev = current->previous;
                    currentprev->next = currentnext;
                    currentnext->previous = currentprev;
                    delete current;
                }
            }
            size--;
        }
        else
            printf("List is empty\n");
    }

    void PrintList() 
    {
        Node* current = head;
        while (current != nullptr)
        {
            printf("%d\n", current->data);
            current = current->next;
        }
    }
};


int main()
{
    Array Array;
    List List;

    int choose = 0;
    int position = 0;
    int value = 0;

    Node* current = nullptr;

    char input[20], output[20];

    printf("Choose the action:\n 1. Add the data in Array\n 2. Remove the data of Array\n 3. Print the Array\n 4. Print the value from Array of position\n 5. Add the data in List\n 6. Remove the data of List\n 7. Print the List\n 8. Print the value from List of position\n 0. Close the program\n");
    scanf_s("%d\n", &choose);

    while (choose != 0)
    {
        switch (choose)
        {
        case 1:
            printf("Input value ");
            scanf_s("%d\n", &value);
            printf("Input nomber position ");
            scanf_s("%d\n", &position);
            Array.ArrayAdd(position, value);
            break;
        case 2:
            printf("Input nomber position ");
            scanf_s("%d\n", &position);
            Array.ArrayRemove(position);
            break;
        case 3:
            Array.PrintArray();
            break;
        case 4:
            printf("Input nomber position ");
            scanf_s("%d\n", &position);
            Array.ArrayGet(position);
            break;
        case 5:
            printf("Input value ");
            scanf_s("%d\n", &value);
            printf("Input nomber position ");
            scanf_s("%d\n", &position);
            List.ListAdd(value, position);
            break;
        case 6:
            printf("Input nomber position ");
            scanf_s("%d\n", &position);
            List.ListRemove(position);
            break;
        case 7:
            List.PrintList();
            break;
        case 8:
            printf("Input nomber position ");
            scanf_s("%d\n", &position);
            current = List.ListGet(position);
            printf("%d", current->data);
            break;
        default:
            printf("Error\n");
        }
        printf("Choose the action.. ");
        scanf_s("%d\n", &choose);
    }

    delete current;
    Array.~Array();
    List.~List();
    return 0;
}

