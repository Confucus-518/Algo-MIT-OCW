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



};

int main(){

}