/*Linked lists is the second data structure that is gone through
It works by creating n number of nodes(mini arrays kinda) with the expected item at the index followed by a pointer to the next node
Althought this allows for faster insert_first and delete_first at O(1), get_at and set_at are slower at O(n)
In other words more dynamic at the expense of access speed 
*/;

#include <iostream>

using namespace std;

struct Node{
    int item; //item data to be stored in node
    Node* next; //ptr to next

    Node(int value) : item(value), next(nullptr){} //initialiser
};

class LinkedList{

private:
    Node* head; //pointer to head of the list, the first node

public:

    LinkedList(): head(nullptr){} //initialiser

    ~LinkedList(){
        Node* current = head; //set current node to the head
        while (current != nullptr){
            Node* nextNode = current -> next; //iterate through list
            delete current; //remove current node, deallocate memory
            current = nextNode;
        }
    }

    void insertFirst(int value){
        Node *newNode = new Node(value); //initialise new node
        newNode -> next = head; // use pointer to assign next field of newNode to head
        head = newNode; // Set head to newNode
    }

    void insertLast(int value){
        Node *newNode = new Node(value); 
        if (head == nullptr){ 
            head = newNode; // check if LinkedList is empty if so, simply add newNode
        }else{
            Node* current = head; // else, first set the current node being checked to first
            while (current -> next != nullptr){
                current = current -> next; //Iterate through the LinkedList and stopping at last by checking if next points to nothing then insert
            }
        }
    }

    void deleteValue(int value){
        if (head == nullptr) return; //stop if LinkedList is empty

        // If first node is the specified one to delete, then delete
        if (head -> item == value) {
            Node* temp  = head; //create temporary pointer for first node
            head = head -> next; //set first node to next node
            delete temp; // delete original first node through temp
            return;
        }

        Node* current = head;   
        //check that node is not the last and that next node is not the specified one
        while (current -> next != nullptr && current->next->item != value ){
            current = current -> next; //move on to next node
        }
        //
        if (current -> next != nullptr){
            Node* temp = current -> next; 
            current -> next = current -> next -> next;
            delete temp;
            return;
        }

        if (current -> next == nullptr && current->item != value){
            cout << "Specified value to delete was not found"<< endl;
        }
    }

    void deleteIndex(int value){
        if (head == nullptr) return;

        //check that node is the first one
        if (value == 0){
            Node* temp  = head; //create temporary pointer for first node
            head = head -> next; //set first node to next node
            delete temp; // delete original first node through temp
            return;
        }
        
        Node* current = head;

        int i =0;
        //iterate until the right index
        while(i < value -1 && current-> next != nullptr){
            current = current -> next;
            i++;
        }
        if (current -> next != nullptr){
            Node* temp = current -> next; 
            current -> next = current -> next -> next;
            delete temp;
        }
    }

    void display() const{
        Node* current = head;
        while (current != nullptr){
            cout << current -> item;
            if (current -> next != nullptr){
                cout << " > ";
            }else{
                cout << endl;
            }
            current = current -> next;
        }
    }

};

int main(){
    LinkedList llist;

    llist.insertLast(3);    
    llist.insertFirst(2);
    llist.insertFirst(1);

    llist.display();

    llist.deleteValue(3);

    llist.display();

    llist.deleteIndex(1);

    llist.display();

    return 0;
}