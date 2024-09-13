/*Binary trees are one of the last data structures gone through and it is definitely a unique one. Think of it as linked lists but 2-dimensional and better
They work like linked list as each node uses pointers to link to other nodes, but instead of just one leading to the next, binary nodes have 3: left, right and parent
The parent is self-explanatory, it's the node that leads to the current node, the left node is one that contains the smaller value and the right the greater value
There is a lot of theory and concepts to be gone through so I will explain more specifically in the code itself. 
Side note: This is an AVL tree, which is the first maintenance algorithm for binary trees and the only one gone through in the course(L7)*/

#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class node;

using nodeptr = unique_ptr<node>; //I am not fully familiar with what exactly unique ptrs are but in simple words, they ensure the ptr is only owned by one object and allows for easy dynamic operations without risk of memory leakage
class node{
public:
    int data; //element or actual stuff stored in the node
    nodeptr left, right; //left and right ptr
    node* parent; //parent ptr, it is raw since the parent node belongs to the other child node as well and cannot be unique
    int height;

    node(int x) : data(x), parent(nullptr), height(1){
        cout << "constructing"<<endl;
    } //construct

    ~node(){
        cout << "destroying" << endl;
    }

    void update(){
        cout <<"updating with data: " << data << endl;
        int left_h = left ? left -> height : 0;
        int right_h = right ? right -> height : 0;
        height = 1 + max(left_h, right_h);
        cout << "updated height: " << height << endl;
    }

    int get_skew() const{
        cout << "getting skew..." << endl;
        int left_h = left ? left -> height : 0;
        int right_h = right ? right -> height : 0;
        cout << "calculated skew: " << height << endl;
        return left_h - right_h;
        
    }

    nodeptr rotate_right(){
        cout << "rotating right..."<< endl;
        nodeptr new_root = move(left);
        if (new_root){
            left = move(new_root -> right);
            if (left){
                left -> parent = this;
            }

            new_root -> right.reset(this);
            new_root -> parent = parent;

            if (parent){
                if (parent -> left.get() == this){
                    parent -> left = move(new_root);
                }else{
                    parent -> right = move(new_root);
                }
            }
            parent = new_root.get();
            update();
            new_root -> update();
        }else{
            cout << "error: Trying to rotate right on a node with no left child" <<endl;
        }
        return new_root;
    }
    
    nodeptr rotate_left(){
        cout << "rotating left..." <<endl;
        nodeptr new_root = move(right);
        if (new_root){
            right = move(new_root -> left);
            if (right){
                right -> parent = this;
            }
            new_root -> left.reset(this);
            new_root -> parent = parent;

            if(parent){
                if (parent -> left.get() == this){
                    parent -> left = move(new_root);
                }else{
                    parent -> right = move(new_root);
                }
            }
            parent = new_root.get();
            update();
            new_root -> update();
        }else{
            cout << "error: Trying to rotate left on a node with no right child" << endl;
        }
        return new_root;
    }

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

    //removing the node is actly fairly complex at first since deleting a node with children would disrupt the tree
    nodeptr subtree_remove(){
        if (left || right){ //check for child ptrs
            node* Node = left ? predecessor() : successor(); //initialise a node for tracking
            swap (data, Node -> data); //swap data of current node to be deleted and the pred/succ
            //This makes the node to be deleted a leaf so it does not disrupt the tree, we are not moving the actual node but subsituting the data such that it is pretty much the exact same
            return Node -> subtree_remove(); //simply recurse to check if there are children
        }if (parent){ //if there is no child and it has a parent
            //check if current node is left or right
            if (parent -> left.get() == this) parent -> left.reset(); //if left then delete the left ptr of the parent. Interestingly, reset() is a specific to unique ptrs and if the ptr being reset is the last owner of the obj (or node in this case), the obj gets auto deleted. No more mem leakage :)
            else parent -> right.reset(); //same but right 
        }
        parent = nullptr;
        return nodeptr(this); //if node has no parents or child then its just a node, so... idk
    }
};

class BinaryTree{
private:
    nodeptr root; //make root node for the tree
    int size; // size meaning the number of nodes

    void rebalance(node* Node) {
        cout << "rebalancing node with data: " << Node -> data << endl;
        while (Node) {
            Node->update();
            int skew = Node->get_skew();
            cout << "skew is " << skew << endl;

            if (skew > 1) {
                if (Node->left->get_skew() < 0) {
                    Node->left = Node->left->rotate_left();
                    Node->left->parent = Node;  // Fix parent pointer
                }
                Node = Node->rotate_right().release();
            } else if (skew < -1) {
                if (Node->right->get_skew() > 0) {
                    Node->right = Node->right->rotate_right();
                    Node->right->parent = Node;  // Fix parent pointer
                }
                Node = Node->rotate_left().release();
            }
            if (!Node->parent) {
                root.reset(Node);
                break;
            }
            Node = Node->parent;
        }
    }
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
        nodeptr newnode = make_unique<node>(x); //make a new node with unique ptrs
        if (!root) root = move(newnode); //if there is no root meaning no tree then make the new node the root
        else{
            node* Node = root.get();//first find the root of the tree
            while (true){ //while true loop allows for ez iteration through tree and using break to stop loop
                if (x < Node -> data){ //if less
                    if (Node -> left) Node = Node -> left.get();//go to left since... well you alr know
                    else{
                        Node -> left = move(newnode); //if there is no left child then set left ptr of parent
                        Node -> left -> parent = Node; //connect parent ptr of new node
                        rebalance(Node -> left.get());
                        break; //BREAKKKK
                    }
                }else{ //if more
                    if (Node -> right) Node = Node -> right.get(); //check for right child if so then enter the right subtree
                    else{
                        Node -> right = move(newnode); //same stuff as above but vice versa
                        Node -> right -> parent = Node;
                        rebalance(Node -> right.get());
                        break;
                    }
                }
            }
            rebalance(Node);
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
            node* parent = Node -> parent;
            nodeptr deleted_node = Node -> subtree_remove(); //set current node and use the subtree_remove func above to ensure proper deletion
            if (Node == root.get()){
                root = move(deleted_node);
            }
            if (parent){
                rebalance(parent);
            }
            size --; //decrease size to account for one less node
        }else{
            cout << "Value to be deleted was not found" << endl;
        }
    }

};

int main(){
    BinaryTree tree;

    tree.insert(3);
    tree.insert(1);

    tree.traverse();

    return 0;
}