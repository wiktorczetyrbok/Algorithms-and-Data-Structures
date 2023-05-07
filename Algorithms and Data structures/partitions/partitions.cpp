#include <iostream>

#define MAX_SIZE 256

using namespace std;

struct Result { /// every possibility is in a struct
    int arr[MAX_SIZE];
    int size;
    int indexNum;
};
int bonusCheck(bool prime[], int result[], int size) { ///bonus is for counting the representation of parts
    int sum = 0;
    for (int j = 0; j < size; j++) {
        int number = result[j];
        int bonus = 1;
        for (int i = 0; i <= number; i++) {
            if (i < number && prime[i] == true)bonus *= 10;
        }
        sum += bonus;
    }
    return sum;
}
// Finding prime numbers smaller than n
static void findPrimeNumbers(bool primeArr[], int n)
{
    // first two numbers are not priem
    primeArr[0] = false;
    primeArr[1] = false;
    // starting from 2 (first prime)
    for (int i = 2; i <= n; ++i)
    {
        primeArr[i] = true;
    }
    for (int i = 2; i * i <= n; ++i)
    {
        if (primeArr[i] == true)
        {
            // When i is prime number then i squared is not prime and i times intinger >1 is not prime either
            for (int j = i * i; j <= n; j += i)
            {
                primeArr[j] = false;
            }
        }
    }
}
// Display calculated result
static void printing(struct Result values[], int firstPrime, int resultArrIndex)
{
    for (int j = 0; j < resultArrIndex; j++)
    {
        int size = values[j].size;
        if (firstPrime >= values[j].arr[size - 1])
        {
            cout << firstPrime;
            for (int i = size - 1; i >= 0; --i)
            {
                cout << "+" << values[j].arr[i];
            }
            cout << "\n";
        }
    }
}
static void sortArray(Result array[], int size)   ///sorting structure
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < (size - 1); i++)
        {
            if (array[i].indexNum > array[i + 1].indexNum)
            {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}
void partition(int value, bool primeArr[], int result[], int index, int sum, int num, int firstPrime, int indexCount, int* resultArrIndex, struct Result values[])
{
    if (primeArr[firstPrime] == true)
    {
        if (sum == num)
        {
            indexCount = bonusCheck(primeArr, result, index); // assining values to the struct after finding the partition
            values[*resultArrIndex].indexNum = indexCount;
            values[*resultArrIndex].size = index;
            for (int i = 0; i < index; i++)values[*resultArrIndex].arr[i] = result[i];
            *resultArrIndex += 1; //increasig the index of possible result
            return;
        }
        if (index >= num / 2 || sum > num)
        {
            return;   // Stop when sum is bigger than number and index is off the limit
        }
        for (int i = value; i <= num; ++i)
        {
            if (primeArr[i] == true)// checking if i prime
            {
                result[index] = i;
                partition(i, primeArr, result, index + 1, sum + i, num, firstPrime, indexCount, resultArrIndex, values); // searching for the next number
            }
        }
    }
}
void primePartition(int num, int smaller_num, struct Result values[])
{
    int  indexCount = 0, resultArrIndex = 0;
    if (num <= 1)
    {
        return;
    }
    bool prime[MAX_SIZE];// This are collecting prime number
    int result[MAX_SIZE]; // Use to collect result
    findPrimeNumbers(prime, num);        // Find prime number
    partition(2, prime, result, 0, 0, num - smaller_num, smaller_num, indexCount, &resultArrIndex, values);// Find partition and summing the index
    sortArray(values, resultArrIndex); //sorting structure
    printing(values, smaller_num, resultArrIndex);//printing the output
}
int main()
{
    int howManyNum, base, firstPrime;
    cin >> howManyNum;
    Result values[MAX_SIZE];
    for (int i = 0; i < howManyNum; i++) {
        cin >> base;
        cin >> firstPrime;
        primePartition(base, firstPrime, values);
    }
    return 0;
}