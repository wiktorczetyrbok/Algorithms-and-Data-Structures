#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;
typedef struct Nums
{
    int size;
    char* arr;
    int length;
    int capacity;
    bool isMinus;
}Nums;
void printArray(Nums arr[], int size);
int stringCompare(char number[], char pivot[], int pivotLenth, int length);
void quickSort(Nums arr[], int left, int right);
int partition(Nums nums[], int left, int right);
void overFlow(int* size, char** arr, int* capacity);
int main(void)
{
    int size = 0, capacity = 10, posIndex = 0;
    char number = 'a';
    cin >> size;
    Nums* nums = new Nums[size];
    cin.ignore();

    for (int i = 0; i < size; i++) {
        int index = 0;
        nums[posIndex].arr = new char[capacity];
        nums[posIndex].capacity = capacity;
        nums[posIndex].isMinus = false;
        while (number != '\n') {
            number = cin.get();
            if (number == '-')nums[posIndex].isMinus = true;
            if (number != '-') {
                //overFlow(&index, &nums[posIndex].arr, &nums[posIndex].capacity);
                if (index >= nums[posIndex].capacity) { 
                    char* tmp = nums[posIndex].arr;
                    nums[posIndex].arr = new char[(nums[posIndex].capacity) * 2];
                    for (int j = 0; j < nums[posIndex].capacity; j++) {
                        nums[posIndex].arr[j] = tmp[j];
                    }
                    nums[posIndex].capacity *= 2;
                    delete[] tmp;
                }
                nums[posIndex].arr[index] = number;

                index++;
            }
        }
        nums[posIndex].length = index - 1;
        number = 'a';
        posIndex++;

    }
    quickSort(nums, 0, posIndex - 1);


    printArray(nums, posIndex);
    delete[] nums;
    return 0;
}
void overFlow(int* size, char** arr, int* capacity) {
    if (size >= capacity) {
        char* tmp = *arr;
        *arr = new char[(*capacity) * 2];
        for (int i = 0; i < *capacity; i++) {
            *arr[i] = tmp[i];
        }
        //*capacity *= 2;
        delete[] tmp;
    }
}
void quickSort(Nums arr[], int left, int right) {
    if (left < right) {
        int q = partition(arr, left, right);
        quickSort(arr, left, q);
        quickSort(arr, q + 1, right);
    }
}
int partition(Nums nums[], int left, int right) {
    Nums pivot = nums[left];
    char* pivot_arr = pivot.arr;
    int left_p = left - 1;
    int right_p = right + 1;
    while (true) {
        while (true) {
            left_p++;
            if (stringCompare(nums[left_p].arr, pivot_arr, pivot.length, nums[left_p].length)) break;
        }
        while (true) {
            right_p--;

            if (stringCompare(pivot_arr, nums[right_p].arr, nums[right_p].length, pivot.length)) break;

        }
        if (left_p < right_p) {
            Nums temp = nums[left_p];
            nums[left_p] = nums[right_p];
            nums[right_p] = temp;
        }
        else {
            return right_p;
        }
    }
}
int stringCompare(char* number, char* pivot, int pivotLength, int length) {
    if (length > pivotLength) {
        return 1;
    }
    else if (length == pivotLength) {
        for (int i = 0; i < length; i++) {
            if (number[i] > pivot[i]) {
                return 1;
            }
            else if (number[i] < pivot[i]) {
                return 0;
            }
        }
        return 1;
    }
    else {
        return 0;
    }
}
void printArray(Nums arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i].isMinus) {
            cout << '-';
            for (int j = 0; j < arr[i].length; j++) {
                cout << arr[i].arr[j];
            }
            cout << endl;
        }
    }
    for (int i = 0; i < size; i++) {
        if (!arr[i].isMinus) {
            for (int j = 0; j < arr[i].length; j++) {
                cout << arr[i].arr[j];
            }
            cout << endl;
        }
    }
}