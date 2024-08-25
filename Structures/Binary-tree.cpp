/*Binary trees are one of the last data structures gone through and it is definitely a unique one. Think of it as linked lists but 2-dimensional and better
They work like linked list as each node uses pointers to link to other nodes, but instead of just one leading to the next, binary nodes have 3: left, right and parent
The parent is self-explanatory, it's the node that leads to the current node, the left node is one that contains the smaller value and the right the greater value
There is a lot of theory and concepts to be gone through so I will explain more specifically in the code itself. 
Side note: This is an AVL tree, which is the first maintenance algorithm for binary trees and the only one gone through in the course(L7)*/

#include <iostream>
#include <memory>

using namespace std;

class node;

using nodeptr = unique_ptr<node>; //I am not fully familiar with what exactly unique ptrs are but in simple words, they ensure the ptr is only owned by one object and allows for easy dynamic operations without risk of memory leakage
class node{
public:
    int data; //element or actual stuff stored in the node
    nodeptr left, right; //left and right ptr
    node* parent; //parent ptr, it is raw since the parent node belongs to the other child node as well and cannot be unique

    node(int x) : data(x), parent(nullptr){}; //construct
    
    /*iterate through the subtree selected and print out each node in traversal order
    Traversal order is simply defined as the left -> current -> right from small to largest.
    Every subtree/node in the left subtree is m */
    void subtree_iter() const{
        if (left) left -> subtree_iter();//check if left ptr exists and if so then recursively iterate through
        cout << data << " ";//if left ptr doesn't exist then print out current node
        if (right) right -> subtree_iter(); //then check if right ptr exists and iterate through that
    }

    //check for the first element of the subtree which would the leftmost node as it is the smallest
    node* subtree_first(){
        if (left) return left -> subtree_first(); //recursively find left node
        else return this; //if there is no left node then the current node is the smallest
    }

    //same as the subtree_first but finding the rightmost since it is the largest
    node* subtree_last(){
        if (right) return right -> subtree_last();
        else return this;
    }

    //find the next largest value after the current node
    node* successor(){
        if (right) return right -> subtree_first(); //go to the right subtree since it contains all larger values and find the smallest of that to get the next largest value of the current
        //if there is no right subtree then go up to find
        node* Node = this; //set current node
        //move up through the tree until the current node is not a right node
        while (Node -> parent && Node == Node -> parent -> right.get()){
            Node = Node -> parent;
        }
        return Node -> parent; //if current node is a left node then the next largest node will be the parent which is what is returned
    }
    
    //vice versa
    node* predecessor(){
        if (left) return left -> subtree_last();
        node* Node = this;
        while (Node -> parent && Node == Node -> parent -> left.get()){
            Node = Node -> parent;
        }
        return Node -> parent;
    }

    //insert a node before a certain node 
    void insert_before(nodeptr& B){
        //if there is a left node then there are values in subtree before B
        if (left){
            node* Node = left -> subtree_last(); //find the largest value in the left subtree
            Node -> right = move(B); //add the node to the right of that since it is greater than that value
            Node -> right -> parent = Node; //reconnect the parent ptr of the new node
        }else{ //if nothing to left
            left = move(B); //simply add to the left of the tree
            left -> parent = this; //connect ptr
        }
    }

    //vice versa
    void insert_after(nodeptr& B){
        if (right){
            node* Node = right -> subtree_first();
            Node -> left = move(B);
            Node -> left -> parent = Node;
        }else{
            right = move(B);
            right -> parent = this;
        }
    }

    //removing the node is actly fairly complex at first since deleting a node with children woudl disrupt the tree
    nodeptr subtree_remove(){
        if (left || right){ //check for child ptrs
            node* Node; //initialise a noden for tracking
            if (left) Node = predecessor(); //if there is a left child then set node to next smallest value
            else Node = successor();//else set to the next largest

            swap (data, Node -> data); //swap data of current node to be deleted and the pred/succ
            //This makes the node to be deleted a leaf so it does not disrupt the tree, we are not moving the actual node but subsituting the data such that it is pretty much the exact same
            return Node -> subtree_remove(); //simply recurse to check if there are children
        }if (parent){ //if there is no child and it has a parent
            //check if current node is left or right
            if (parent -> left.get() == this) parent -> left.reset(); //if left then delete the left ptr of the parent. Interestingly, reset() is a specific to unique ptrs and if the ptr being reset is the last owner of the obj (or node in this case), the obj gets auto deleted. No more mem leakage :)
            else parent -> right.reset(); //same but right 
        }
        return nullptr; //if node has no parents or child then its just a node, so... idk
    }
};

class BinaryTree{
private:
    nodeptr root; //make root node for the tree
    int size; // size meaning the number of nodes

public:
    BinaryTree(): root(nullptr), size(0){}; //constructor

    //return the size of the tree
    int len() const{
        return size; 
    }

    //use the subtree_iter func defined above to print out the nodes in-order
    void traverse() const{
        if (root) root -> subtree_iter();
        cout << endl;
    }

    //inserting function for the tree
    void insert(int x){
        nodeptr newnode = make_unique<node>(x); //make a new node with unqiue ptrs
        if (!root) root = move(newnode); //if there is no root meaning no tree then make the new node the root
        else{
            node* Node = root.get();//first find the root of the tree
            while (true){ //while true loop allows for ez iteration through tree and using break to stop loop
                if (x < Node -> data){ //if less
                    if (Node -> left) Node = Node -> left.get();//go to left since... well you alr know
                    else{
                        Node -> left = move(newnode); //if there is no left child then set left ptr of parent
                        Node -> left -> parent = Node; //connect parent ptr of new node
                        break; //BREAKKKK
                    }
                }else{ //if more
                    if (Node -> right) Node = Node -> right.get(); //check for right child if so then enter the right subtree
                    else{
                        Node -> right = move(newnode); //same stuff as above but vice versa
                        Node -> right -> parent = Node;
                        break;
                    }
                }
            }
        }
        size++;//increase size to account for new node
    }

    void remove(int x){
        node* Node = root.get();//find root node
        while (Node && Node -> data != x){ //check if current value is x 
            if (x < Node -> data) Node = Node -> left.get(); //if smaller then go left
            else Node = Node -> right.get(); //if greater then go right
        }
        if (Node){ //if there is a node
            nodeptr deleted_node = Node -> subtree_remove(); //set current node and use the subtree_remove func above to ensure proper deletion
            size --; //decrease size to account for one less node
        }else{
            cout << "Value to be deleted was not found" << endl;
        }
    }

};

int main(){
    BinaryTree tree;

    tree.insert(3);
    tree.insert(5);
    tree.insert(10);
    tree.insert(1);

    tree.traverse();

    return 0;
}