/*Hash tables are the final data structure I will be coding out.
In contrast to linked lists and dynamic arrays, hash tables are sets and not sequences, meaning that the elements are not in order (hence the name unordered_map)
Hash tables work by assigning a hash to each key where the key is kinda like the index of the element but is not neccessarily ordered numbers and could be words
The hash is obtained through a hash function that is usually something like dividing a large prime number by table size or some complicated math stuff
However there is always a possibility of hash collision causing one hash to hold multiple keys, for simplicity we can use chaining which stored the keys in a dynamic array 
Find, insert and delete are all constant !! This makes it frequently used as it is fast and practical
*/

/*Quick explanation of pairs: pairs are a type of object in the format [a,b], where a is referred to pair.first and b pair.second*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashTable{
    int size;
    vector<list<pair<int, int>>> table; //vector is overall table, list is the chain at each index, pair is the key and value

    public:
    //declarations
        HashTable(int s);
        int hashFunction(int k);
        void insertItem(int k, int value);
        void deleteItem(int k);
        int searchItem(int k);
        void print();
};

//constructor
HashTable::HashTable(int s){
    size = s;
    table.resize(size); //resize to specified size of table
}


int HashTable::hashFunction(int k){
    return k%size; //simple hash function
}

void HashTable::insertItem(int k, int value){
    int index = hashFunction(k); //first find index based on hashed key
    table[index].push_back({k, value}); //add new values to the index found
}

void HashTable::deleteItem(int k){
    int index = hashFunction(k); 
    auto& chain = table[index]; //reference to chain at index

    //iterate through the chain
    for (auto it = chain.begin(); it != chain.end(); it++){
        if (it -> first == k){
            chain.erase(it); //remove if the key matches
            return;
        }
    }
    cout << "Key not found" << endl;
}

int HashTable::searchItem(int k){
    int index = hashFunction(k);
    auto& chain = table[index];

    for (auto it = chain.begin(); it != chain.end() ; it++){
        if (it -> first == k){
            return it->second; //return data stored at key
        }
    }
    cout << "Nothing found for key "<<k<<endl;
    return -1;
}

void HashTable::print(){
    for (int i = 0; i < size; i++){
        cout<<"Index "<<i<<": ";
        for (auto x : table[i]){
            cout<<"["<<x.first<<": "<<x.second<<"]";
        }
        cout<<endl;
    }
}

int main(){
    HashTable ht(5);

    ht.insertItem(10, 1);
    ht.insertItem(13, 2);
    ht.insertItem(3, 3);
    ht.insertItem(123, 4);
    ht.insertItem(33, 5);

    ht.print();

    ht.searchItem(1);
    cout << "At index 13, the value is " << ht.searchItem(13)<< endl;

    ht.deleteItem(13);
    ht.deleteItem(1);

    ht.print();



}