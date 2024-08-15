/*This is the second algorithm I am coding and it is also a rather simple sorting algo
Insertion sort works by repeatedly comparing an element to the left and swapping until the left value is smaller or the same
Like selection sort it has a high time complexity of O(n^2) but unlike selection sort it is stable*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> insertionSort(vector<int> arr){
    //iterate thrrough array from left to right
    for (int i = 1; i < arr.size(); i++){ //start i at one so first comparison is between arr[0] and arr[1]
            int j = i; //initialise starting index
            while (j>0 && arr[j] < arr[j-1]){
                swap(arr[j-1], arr[j]);
                j--; //decrement within the subarray
            }
    }
    return arr;
}

int main(){
    vector<int> arr = {3,5,6,2,1,8,10,9,4,7,7};
    arr = insertionSort(arr);
    for (int i = 0; i < arr.size(); i++){
        cout <<arr[i];
        if (i != arr.size()-1){
            cout << " , ";
        }
    }
    cout<<endl;
    return 0;

}