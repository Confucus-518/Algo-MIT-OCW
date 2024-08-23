

#include <iostream>
#include <memory>

using namespace std;

class node;

using nodeptr = unique_ptr<node>;

class node{
public:
    int data;
    nodeptr left, right;
    node* parent;

    node(int x) : data(x), parent(nullptr){};
    
    void subtree_iter() const{
        if (left) left -> subtree_iter();
        cout << data << " ";
        if (right) right -> subtree_iter();
    }

    node* subtree_first(){
        if (left) return left -> subtree_first();
        else return this;
    }

    node* subtree_last(){
        if (right) return right -> subtree_last();
        else return this;
    }

    node* successor(){
        if (right) return right -> subtree_first();
        node* Node = this;
        while (Node -> parent && Node == Node -> parent -> right.get()){
            Node = Node -> parent;
        }
        return Node -> parent;
    }
    
    node* predecessor(){
        if (left) return left -> subtree_last();
        node* Node = this;
        while (Node -> parent && Node == Node -> parent -> left.get()){
            Node = Node -> parent;
        }
        return Node -> parent;
    }

    void insert_before(nodeptr& B){
        if (left){
            node* Node = left -> subtree_last();
            Node -> right = move(B);
            Node -> right -> parent = Node;
        }else{
            left = move(B);
            left -> parent = this;
        }
    }

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

    nodeptr subtree_remove(){
        if (left || right){
            node* Node;
            if (left) Node = predecessor();
            else Node = successor();

            swap (data, Node -> data);
            return Node -> subtree_remove();
        }if (parent){
            if (parent -> left.get() == this) parent -> left.reset();
            else parent -> right.reset();
        }
        return nullptr;
    }
};

class BinaryTree{
private:
    nodeptr root;
    int size;

public:
    BinaryTree(): root(nullptr), size(0){};

    int len() const{
        return size;
    }

    void traverse() const{
        if (root) root -> subtree_iter();
        cout << endl;
    }

    void insert(int x){
        nodeptr newnode = make_unique<node>(x);
        if (!root) root = move(newnode);
        else{
            node* Node = root.get();
            while (true){
                if (x < Node -> data){
                    if (Node -> left) Node = Node -> left.get();
                    else{
                        Node -> left = move(newnode);
                        Node -> left -> parent = Node;
                        break;
                    }
                }else{
                    if (Node -> right) Node = Node -> right.get();
                    else{
                        Node -> right = move(newnode);
                        Node -> right -> parent = Node;
                        break;
                    }
                }
            }
        }
        size++;
    }

    void remove(int x){
        node* Node = root.get();
        while (Node && Node -> data != x){
            if (x < Node -> data) Node = Node -> left.get();
            else Node = Node -> right.get();
        }
        if (Node){
            nodeptr deleted_node = Node -> subtree_remove();
            size --;
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