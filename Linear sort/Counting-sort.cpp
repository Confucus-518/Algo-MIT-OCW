/*This is the fourth algo and yet another sorting one, but much more different
Counting sort works by taking the minimum value and maximum value and creating an array with the number of elements based on the difference
The array is then iterated through and the number of times each element appears adds 1 to a counter
This sorting is stable, meaning the order of duplicate elements maintian their order from input
The time complexity is a weird Olog(n+u), where u is the number of keys*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& arr){
    int max =* max_element(arr.begin(), arr.end()); //find max value
    int min =* min_element(arr.begin(), arr.end()); //find min value

    int range = max - min + 1; //find range of values 

    vector<int> count(range, 0); //initialise array for keeping count with range of numbers

    for (int num : arr){ //context loop where num is element at each iteration not the index
        count[num-min]++; //populate count arr with each iteration the element is checked and the count at its index is incremented
    }

    //loop for cumulative frequency array, allowing for positioning of elements when inputted into output array
    for (int i = 1; i < range ; i++){
        count[i] += count[i-1]; //add number of elements less than or equal to current element
    }
    vector<int> output(arr.size()); //initialise output array

    /*iterate throught the output array and add elements in sorted position, reverse to maintain stability
    Let's look at the examples first few elements [..., 9, 3, 0, 3]
    The count array would be [1,2,3,5,6,8,9,10,11,12]
    for 3, output[5-1] = arr[i]
    so [x,x,x,x,3,...] and count array becomes [1,2,3,4,...]
    for 0, output[1-1] = arr[i]
    so [0,x,x,x,3,...] and count array becomes [0,2,3,4...]
    for the second 3, output[4-1] = arr[i]
    so [0,x,x,3,3,...] and count array becomes [0,2,3,3,...]*/
    for (int i = arr.size() - 1; i >= 0 ; i--){
        output[count[arr[i]-min] -1] = arr[i]; //find the correct position of element and add element at i in original to that
        count[arr[i] - min]--; //decrement the count at that specific index to ensure if there is a duplicate element it will not just be placed at same index and is instead placed later
    }

    for (int i = 0; i < arr.size(); i++){
        arr[i]= output[i];
    }
}

int main(){
    vector<int> arr = {4,1,2,5,5,8,6,7,9,3,0,3};

    countingSort(arr);

    for (int num : arr){
        cout << num << " ";
    }
    cout << endl;

}