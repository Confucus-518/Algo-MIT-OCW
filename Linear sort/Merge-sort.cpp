/*This is the third algorithm that I will be coding, also a sorting one
Merge sort is a more complex sorting algorithm both in concept and implementation
However, it does prove to be faster, especially for large datasets and has a time complexity of Olog(nlogn)
It basically works by recursively splitting the array into much smaller subarrays of 2 elements then sorting those and merging back into the big array */

#include <iostream>
#include <vector>

using namespace std;

//merging subarrays function
void merge(vector<int>& arr, int l, int m , int r){ //l is leftmost index, m is the last index of the left subarray, r is the rightmost/end index
    int i = l, j = m + 1, k = 0;
    /*set i to be l to start from start of left subarray so it iterates through it
    set j to first index of right subarray so it iterates through right subarray
    k is the index for the temp array for storing sorted elements*/
    vector<int> temp(r - l + 1); //initalise temp array with sum of size of r and l subarr
    //iterate through both subarr
    while (i <= m && j <= r){
        if(arr[i] <= arr[j]){ // this is where the key comparison is
            temp[k++] = arr[i++] ; //set element at index to that of l array then increment
        }else{
            temp[k++] = arr[j++] ;
        }
    }

    while (i <= m){
        temp[k++] = arr[i++]; //copy any remaining elements
    }

    while (j <= r){
        temp[k++] = arr[j++];
    }

    //copy over sorted elements in temp arr to original arr
    for (i = l, k = 0; i <= r ; i++, k++){
        arr[i] = temp[k];
    }
    

}

//sorting function
void mergeSort(vector<int>& arr, int l, int r){
    if (l < r){ //check if base case is reached
        int m = l + (r-l) / 2;
        
        mergeSort(arr, l , m); //split left half
        mergeSort(arr, m + 1, r); //split right half

        merge(arr, l, m, r); //merge sorted back into one

    }
    
}

int main(){
    vector<int> arr = {3,5,1,4,6,10,8,2,7,9,7};

    mergeSort(arr, 0, arr.size() - 1);

    for (int index : arr){
        cout << index << " ";        
    }
    cout << endl;

    return 0;

}