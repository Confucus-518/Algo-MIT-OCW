/*Binary heaps should be the last structure that is gone through in the course and it is like a binary tree but not one
Binary heaps work on the concept of priority queue where the most important is the easiest to access and remove
Binary heaps are able to compromise between arrays (which use selection sort) and sorted arrays (using insertion sort)
It is able to insert and remove at a decent time of log(n) and is in-place
The way it differs from the tree is that is implicit, meaning that no pointers are used, only an array which in theory could be drawn as a tree
Instead of using the usual traversal, the nodes are simply traversed from left to right then to the leftmost of the next layer.
For this max heap implementation, the relation between parent and children is that the parent is equal or more than both children (root is largest value) though the children have no distinction between each others.
There is a lot more to say and I will try to explain in-code*/

#include <iostream>
#include <vector>

using namespace std;

class binaryheap{
private:
    vector<int> heap;

    int parent(int i){return (i-1)/2;}

    int leftChild(int i){return (2*i)+1;}

    int rightChild(int i){return (2*i)+2;}

    void heapifyDown(int i){
        int left = leftChild(i);
        int right = rightChild(i);
        int max = i;

        if (left < heap.size() && heap[left] > heap[max]){
            max = left;
        }

        if (right < heap.size() && heap[right] > heap[max]){
            max = right;
        }

        if (max != i){
            swap(heap[i], heap[max]);
            heapifyDown(max);
        }
    }

    void heapifyUp(int i){
        if (i < heap.size() && heap[i] > heap[parent(i)]){
            swap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }
public:
    void insert(int e){
        heap.push_back(e);
        int i = heap.size() - 1;
        heapifyUp(i);
    }

    void remove(int e){
        for (int i = 0 ; i < heap.size() -1 ; i++){
            if (heap[i] == e){
                heap[i] = heap.back();
                heap.pop_back();
                if (i && heap[i] > heap[parent(i)]){
                    heapifyUp(i);
                }else{
                    heapifyDown(i);
                }
                return;
            }
        }
        cout<<"Element not found"<<endl;
    }

    int getMax(){
        if (heap.size() == 0 ) throw out_of_range("heap is empty");
        return heap[0];
    }

    void print(){
        for (auto& a : heap){
            cout << a << " ";
        }
        cout<<endl;
    }
};

int main(){
    binaryheap heap;

    heap.insert(2);
    heap.insert(4);
    heap.insert(3);
    heap.insert(1);
    heap.insert(5);
    heap.insert(3);

    heap.print();

}