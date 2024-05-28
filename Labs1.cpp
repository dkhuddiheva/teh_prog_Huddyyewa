#include <iostream> 
#include <string> 

using namespace std;
struct Node 
{ 
    string str; 
    int v1; 
    double v2; 
    Node* next;
}; 

void pushFront(Node** head, const string& str, int v1, double v2) 
{ 
    Node* newNode = new Node{str, v1, v2, *head}; 
    *head = newNode; 
} 

void pushBack(Node** head, const string& str, int v1, double v2) 
{ 
    Node* newNode = new Node{str, v1, v2, nullptr}; 
    if (*head == nullptr) 
        *head = newNode; 
    else 
    { 
        Node* current = *head; 
        while (current->next != nullptr) 
            current = current->next; 
        current->next = newNode; 
    } 
}

void insertAfter(Node** head, int index, const string& str, int v1, double v2) 
{
    Node* current = *head;
    for (int i = 0; current != nullptr && i < index; i++)
        current = current->next;
        
    if (current != nullptr) 
    {
        Node* newNode = new Node{str, v1, v2, current->next};
        current->next = newNode;
    }
}

void insertBefore(Node** head, int index, const string& str, int v1, double v2)
{
    if (index == 0)
        pushFront(head, str, v1, v2);
    else 
    {
        Node* current = *head;
        for (int i = 0; current != nullptr && i < index - 1; i++)
            current = current->next;
            
        if (current != nullptr) 
        {
            Node* newNode = new Node{str, v1, v2, current->next};
            current->next = newNode;
        }
    }
}

void removeByName(Node** head, const string& str) 
{
    Node* current = *head;
    Node* prev = nullptr;
    while (current != nullptr) 
    {
        if (current->str == str) 
        {
            if (prev == nullptr) 
                *head = current->next;
            else 
                prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void printList(const Node* head) 
{ 
    while (head != nullptr) 
    { 
        cout << "String: " << head->str << ", Int: " << head->v1 << ", Double: " << head->v2 << endl; 
        head = head->next; 
    } 
} 

int main() 
{ 
    Node* head = nullptr;

    pushFront(&head, "First", 1, 1.5); 
    pushBack(&head, "Second", 2, 2.5); 
    pushFront(&head, "Third", 3, 3.5); 
    pushBack(&head, "Fourth", 4, 4.5); 
    printList(head); 
    
    cout<<endl<<endl;

    insertBefore(&head, 3,"Fifth", 5, 5.5);
    insertAfter(&head, 3,"Sixth", 6, 6.5);
    printList(head); 
    
    cout<<endl<<endl;
    
    removeByName(&head, "Fifth");
    printList(head); 

    
    while (head != nullptr) 
    { 
        Node* temp = head; 
        head = head->next; 
        delete temp; 
    } 



    return 0; 
}