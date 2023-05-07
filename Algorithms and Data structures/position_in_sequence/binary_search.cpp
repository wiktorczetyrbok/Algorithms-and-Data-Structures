#include <iostream>

using namespace std;
int search_index(int arr[], int l, int r, int x)
{
    int one = 1;
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)  return mid;
        if (arr[mid] > x && arr[0] < arr[1]) return search_index(arr, l, mid - one, x);
        else if (arr[mid] < x && arr[0] > arr[1])return search_index(arr, l, mid - one, x);
        else   return search_index(arr, mid + one, r, x);
    }
    return -1;
}
void input(int* sequence_array, int size_of_sequence) {
    for (int i = 0; i < size_of_sequence; i++) {
        cin >> sequence_array[i];
    }
}
int main() {
    int number_of_scenarios, size_of_sequence, number_to_find, number_of_elements_find;
        cin >> number_of_scenarios;
                while(number_of_scenarios!=0){
            cin >> size_of_sequence;
            int* sequence_array = new int[size_of_sequence];
            input(sequence_array, size_of_sequence);
            cin >> number_of_elements_find;
                for (int n = 0; n < number_of_elements_find; n++) {
                    cin >> number_to_find;
                    cout << search_index(sequence_array, 0, size_of_sequence - 1, number_to_find) << endl;
                }
            number_of_scenarios--;
            delete[] sequence_array;
                }
        return 0;
}