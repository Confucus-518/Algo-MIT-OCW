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

    int parent(int i){return (i-1)/2;} //calculate the parent index, works cause the 1/2 is rounded down to just give i 

    int leftChild(int i){return (2*i)+1;} //calculate the left child 

    int rightChild(int i){return (2*i)+2;} //calculate the right child

    //This ensures that the inserted node is sorted into the right position by recursively checking down the tree
    void heapifyDown(int i){
        int left = leftChild(i); //find the index of the left child for the current node
        int right = rightChild(i); 
        int max = i; // Initialise a tracker for the index of the current max value in the heap

        //Check if the left child is larger
        if (left < heap.size() && heap[left] > heap[max]){
            max = left; //set the index for the max value as the left 
        }

        //check if the right child is larger
        if (right < heap.size() && heap[right] > heap[max]){
            max = right;
        }

        //Ensure that the max value was changed and is not the current node
        if (max != i){
            swap(heap[i], heap[max]); //swap the elements of the current node and the maximum node to correct positions
            heapifyDown(max); //recurse starting from the new maximum value, this ensures that if the left child was larger than the right but the right replaced the current node, it is accounted for
        }
    }

    //check if newly inserted element should be sorted upwards
    void heapifyUp(int i){
        //check if the current node is larger than its parent
        if (i < heap.size() && heap[i] > heap[parent(i)]){
            swap(heap[i], heap[parent(i)]); //if so then swap the positions
            heapifyUp(parent(i)); //recursively check upwards till the parent is larger
        }
    }
public:
    void insert(int e){
        heap.push_back(e); //add to the back of the tree using vector ops as it is implicit and not ptrs needed :)
        int i = heap.size() - 1; //set index for the new element
        heapifyUp(i); //bring it to its right position
    }

    //removing elements is slightly complicated like the binary tree since we need to ensure the deleted element is a leaf 
    void remove(int e){
        //iterate through the heap
        for (int i = 0 ; i < heap.size() -1 ; i++){
            //check if current element is the element to be deleted
            if (heap[i] == e){ 
                heap[i] = heap.back(); //set the to-be-deleted element to the end of the heap to ensure its a leaf and can be deleted without complications and also pop_back can be used
                heap.pop_back(); //delete the last element
                //check if the swapped element is larger or smaller than the parent then heapify up or down accordingly
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

    //simple function to get max value by checking the root since the tree is sorted by layer and the top layer is always the largest element
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
    //if you are wondering why some elements are not sorted, it is because the sorting is only between layers. We can only confirm layer 1 is larger than 2 and so on, the distinction between elements in the layers would require extra stuff.

}