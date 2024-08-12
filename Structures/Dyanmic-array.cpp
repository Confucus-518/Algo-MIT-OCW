/*Dynamic arrays are yet another data structure that was gone through in the lectures. It's kinda just a static arr on crack
It works by assigning more space at the end of the array such that ops on the end of the arr such as insert and delete are constant.
It also retains the constant time needed for get_at and set_at froms static
Case scenario is that you assign n space behind the existing arr so that for the next n insertions it is constant
Through amortization, it can be seen that the benefit balances out the cost such that the constant time is obtained*/

#include <iostream>

using namespace std;

template <typename T>
class DynArr{
    private:
        T* arr; //pointer to array
        int size; //size of array elements
        int capacity;//capacity of structure, important for resizing ops

        void resize(){
            capacity *= 2;
            T* newArr = new T[capacity];
            for (int i = 0; i < size; i++){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }

    public:

        DynArr(){
            size = 0;
            capacity = 2;
            arr = new T[capacity];
        }

        ~DynArr(){
            delete[] arr;
        }

        void add(T data){
            if (size == capacity) resize();
            arr[size++] = data;
        }

        void remove(int i){
            if (i < 0 || i >= size){
                throw out_of_range("Index out of range >:(");
            }
            for (int n = i; n < size - 1; n++){
                arr[i] = arr[i+1];
            }
            size--;
        }    

        T get(int i) const{
            if (i < 0 || i >= size){
                throw out_of_range("Index out of range >:(");
            }
            return  arr[i];
        }

        void set(int i, T data){
            if (i < 0 || i >= size){
                throw out_of_range("Index out of range >:(");
            }

            arr[i] = data;
        }

        void print() const{
            for (int i = 0; i < size; i++){
                cout << arr[i] << "  ";
            }
            cout << endl;
        }

        int getSize() const{
            return size;
        }

        int getCapacity() const{
            return capacity;
        }

};

int main(){
    DynArr<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);

    arr.print();

    cout<<"At index 1, the value is "<<arr.get(1)<<endl;
    cout <<"Size of the array is "<<arr.getSize()<<endl;
    cout << "Capacity of the array is " <<arr.getCapacity() << endl;


    arr.set(1, 5);

    arr.print();

    arr.remove(1);

    arr.print();

    return 0;
}