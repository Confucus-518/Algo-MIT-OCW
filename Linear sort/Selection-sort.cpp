/*This is the first algorithm I will be coding out and it is a sorting one
The concept is simple, you iterate through the array and keep track the minimum value and swap as neccessary
This is pretty simple to implement as well, but it has a rather high time complexity of O(n^2)*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> selectionSort(vector<int> arr){
    for (int i = arr.size() -1 ; i >= 0 ; i--){
        int max = i;
        for (int j = 0; j < i ; j++){
            if (arr[max]<arr[j]){
                max=j;
            }
        }
        swap(arr[max], arr[i]);
    }
    return arr;
}

int main(){
    vector<int> ans = selectionSort({11,3,2,6,7,2,5,6,9});
    for (int i = 0; i < ans.size(); i++){
        cout <<ans[i];
        if (i != ans.size()-1){
            cout << " , ";
        }
    }
    cout<<endl;
    return 0;
}