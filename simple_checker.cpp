#include <iostream>
#include <vector>
using namespace std;

int checker(vector<int> nums){
    int n = nums.size();
    for (int i = 0; i < n ; i++){
        if (nums[i] == 6){
            return i;
        }
    }
    return -1;
}

int main(){
    vector<int> nums = {0,1,2,3,4,5};
    int ans = checker(nums);
    cout << ans;
}