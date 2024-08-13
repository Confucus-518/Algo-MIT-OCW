/*Hash tables are the final data structure I will be coding out.
In contrast to linked lists and dynamic arrays, hash tables are sets and not sequences, meaning that the elements are not in order (hence the name unordered_map)
Hash tables work by assigning a hash to each key where the key is kinda like the index of the element but is not neccessarily ordered numbers and could be words
The hash is obtained through a hash function that is usually something like dividing a large prime number by table size or some complicated math stuff
However there is always a possibility of hash collision causing one hash to hold multiple keys, for simplicity we can use chaining which stored the keys in a dynamic array 
Find, insert and delete are all constant !! This makes it frequently used as it is fast and practical

*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashTable{
    int size;
    vector<list<pair<int, int>>> table;

    public:
        HashTable(int s);
        int hashFunction(int k);
        void insertItem(int k);
        void deleteItem(int k);
        int searchItem(int k);
        void print();
};

HashTable::HashTable(int s){
    size = s;
    table.resize(size);
}

int HashTable::hashFunction(int k){
    return k%size;
}

