#include<iostream>
#include<string>
#define sizeHeap 10000
using namespace std;

const int YEARS = 10;
const int MONTHS = 5;
const int DAYS = 2;

struct Date
{
    char arrDMY[10];
    string NAME;
    int capacity;
};
void swap(Date& x, Date& y)
{
    Date temp = x;
    x = y;
    y = temp;
}
class MaxHeap
{
public:

    Date* heapArr;
    int capacity;
    int Size;
    MaxHeap(int cap)
    {
        Size = 0;
        capacity = cap;
        heapArr = new Date[cap];

    }
    static int parent(int i)
    {
        return (i - 1) / 2;
    }
    static int left(int i)
    {
        return (2 * i + 1);
    }
    static int right(int i)
    {
        return (2 * i + 2);
    }
    static bool comparenames(Date* d1, Date* d2)
    {
        if (d1->NAME < d2->NAME)return true;
        else if (d1->NAME > d1->NAME)return false;
        else return false;
    }
    static bool comparedates(Date* d1, Date* d2)
    {
        int y = 6, m = 3, d = 0;
        while (y < YEARS)
        {
            if (d1->arrDMY[y] > d2->arrDMY[y]) return true;
            else if (d1->arrDMY[y] < d2->arrDMY[y]) return false;
            else y++;
        }

        while (m < MONTHS)
        {
            if (d1->arrDMY[m] > d2->arrDMY[m]) return true;
            else if (d1->arrDMY[m] < d2->arrDMY[m]) return false;
            else m++;
        }

        while (d < DAYS)
        {
            if (d1->arrDMY[d] > d2->arrDMY[d]) return true;
            else if (d1->arrDMY[d] < d2->arrDMY[d]) return false;
            else d++;
        }
        return false;
    }
    
    void insertKey(Date k)
    {
        
        Size++;
        int i = Size - 1;
        heapArr[i] = k;
        while (i != 0 && comparenames(&heapArr[i], &heapArr[parent(i)]))
        {
            swap(heapArr[i], heapArr[parent(i)]);
            i = parent(i);
        }
    }
    void insertOther(Date k)
    {
        
        Size++;
        int i = Size - 1;
        heapArr[i] = k;
        while (i != 0 && comparedates(&heapArr[parent(i)], &heapArr[i]))
        {
            swap(heapArr[i], heapArr[parent(i)]);
            i = parent(i);
        }
    }
    Date ExtractMax()
    {
        if (Size == 1)
        {
            Size--;
            return heapArr[0];
        }
        Date data = heapArr[0];
        heapArr[0] = heapArr[Size - 1];
        Size--;
        Heapify(0);
        return data;
    }
    Date ExtractMin()
    {
        //if (Size <= 0) exit(0);
        if (Size == 1)
        {
            Size--;
            return heapArr[0];
        }
        Date data = heapArr[0];
        heapArr[0] = heapArr[Size - 1];
        Size--;
        OtherHeapify(0);
        return data;

    }
    void Heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i; //0
        if (l < Size && comparenames(&heapArr[l], &heapArr[i])) largest = l;
        if (r < Size && comparenames(&heapArr[r], &heapArr[largest])) largest = r;
        if (largest != i)
        {
            swap(heapArr[i], heapArr[largest]);
            Heapify(largest);
        }
    }
    void OtherHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < Size && comparedates(&heapArr[i], &heapArr[l])) largest = l;
        if (r < Size && comparedates(&heapArr[largest], &heapArr[r])) largest = r;
        if (largest != i)
        {
            swap(heapArr[i], heapArr[largest]);
            OtherHeapify(largest);

        }
    }
    void printArray()
    {
        if (Size > 0)
        {
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    cout << heapArr[i].arrDMY[j];
                }
                cout << " " << heapArr[i].NAME;
                cout << endl;
            }
        }
        else
        {
            cout << endl;
        }
        cout << endl;
    }
    void BuildHeap()
    {
        for (int i = parent(Size - 1); i >= 0; i--)
        {
            Heapify(i);
        }
    }
    void BuildOtherHeap()
    {
        for (int i = parent(Size - 1); i >= 0; i--)
        {
            OtherHeapify(i);
            OtherHeapify(i);
        }
    }
};
int main()
{
    MaxHeap heap(sizeHeap);
    char command;
    int size = 0;
    int n = 0;
    bool changeHeap = true;
    while (cin >> command)
    {
        switch (command)
        {
        case 'q':
            exit(0);
        case '+':
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                size++;

                for (int j = 0; j < 10; j++)
                {
                    cin >> heap.heapArr[heap.Size].arrDMY[j];
                }
                
                    cin >> heap.heapArr[heap.Size].NAME;

                if (changeHeap)
                {
                    heap.insertKey(heap.heapArr[heap.Size]);
                }
                else
                {
                    heap.insertOther(heap.heapArr[heap.Size]);
                }
            }
            break;
        case '-':
            int m;
            cin >> m;

            for (int k = 0; k < m; k++)
            {
                size--;
                if (changeHeap)
                {
                    int i = 0;
                    for (int j = 0; j < 10; j++)
                    {
                        cout << heap.heapArr[i].arrDMY[j];
                    }
                    cout << " " << heap.heapArr[i].NAME << endl;
                    heap.ExtractMax();
                }
                else
                {
                    int i = 0;
                    for (int j = 0; j < 10; j++)
                    {
                        cout << heap.heapArr[i].arrDMY[j];
                    }
                    cout << " " << heap.heapArr[i].NAME << endl;
                    heap.ExtractMin();
                }
            }
            break;
        case 'p':
            heap.printArray();
            break;
        case 'r':
            if (changeHeap)
            {
                changeHeap = false;
                heap.BuildOtherHeap();
            }
            else
            {
                changeHeap = true;
                heap.BuildHeap();
            }
            break;
        }
    }
    return 0;
}