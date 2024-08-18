/*The fifth algorithm that I am coding
Tuple sort kidna confused me until I realised it just was sorting based on multiple keys where keys have different precedence
Ie. A tuple (a,2) has 2 keys: a, 2. The elements will be sorted based on which key is "more important". This creates a need for the algo to be stable
For now I will be coding one that takes the digits of a 2-digit number as keys for sorting(like in the lectures) but I may make one that includes alphabets in the future*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//set up an array of pairs to store the pair of digits
vector<pair<int, int>> tupleSort(vector<int>& arr){ 

    vector <pair <int, int>> separatedArr(arr.size()); //initialise the array to store the split numbers

    //size_t is something new I learnt, it is used here since it works better with the size() function, prevents negative indexing and is more adaptable to the word RAM size of the architecture
    for (size_t i ; i < arr.size(); ++i){
        separatedArr[i].first = arr[i] /10; //find first digit
        separatedArr[i].second = arr[i]%10; //find second digit

    }

    sort(separatedArr.begin(), separatedArr.end()); //use sort function from algorithm lib since it's convenient
    /*You maybe thinking that I'm dodging work or being lazy, and you would be right
    But for this scenario, a small dataset, the sort function is basically doing an insertion sort(which I've done) in lexographical order
    If I feel like it maybe I will revisit and actually code it out and then add more flexbility to the function e.g. more digits/alphabetical*/


    return separatedArr;

}

int main(){
    vector<int> arr = {13,42,45,36,85,22};

    vector<pair<int, int>> ans = tupleSort(arr);

    for (int i = 0; i <arr.size() -1 ; i++){
        cout<<ans[i].first<<ans[i].second<<" ";
    }
    cout <<endl;

    return 0;
}