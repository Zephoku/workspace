#include <iostream>
using namespace std;

int* mergesort(int* nums, int size) {
        if (size <= 1) {
            return nums;
        }
        int p1size = size/2;
        int p2size = size-p1size;
        int* p1 = mergesort(nums, p1size);
        int* p2 = mergesort(nums+p1size, p2size);
    }

int main () {
    int array[10] = { 9,4,2,6,7,3,7,3 };

    int* result = mergesort(array,10);
    for(int i=0;i<10;i++) {
        cout << result[i] << endl;
    }
    
}
