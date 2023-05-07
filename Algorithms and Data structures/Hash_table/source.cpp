#include <iostream>
#include <string>
#define PRIME 13
using namespace std;
#define CAPACITY 100000
struct Item {
        string value;
        int occur;

};
struct HashTable {
        Item** item;
        static unsigned long int hash_table(string str) {
                unsigned long i = 3942;
                for (int j = 0; j < str.length(); j++) {
                        int k = (int)str[j];
                        i = i * PRIME + k;
                }
                return i % CAPACITY;
        }
        void deleting(const string& str) const {
                int index = hash_table(str);
                for (int i = index; i < CAPACITY; i++)
                {
                        if (item[i] == nullptr) {
                                return;
                        }
                        else if (item[i]->value == str) {
                                item[i]->occur = 0;
                                return;
                        }
                }
        }
        void search(const string& str) {
                int index = hash_table(str);
                for (int i = index; i < CAPACITY; i++)
                {
                        if (item[i] == nullptr) {
                                return;
                        }
                        else if (item[i]->value == str) {
                                cout << item[i]->occur << endl;
                                return;
                        }
                }
        }
        void insert(const string& str) {
                int index = hash_table(str);
                Item* element = new Item;
                element->value = str;
                element->occur = 1;
                for (int j = index; j < CAPACITY; j++) {
                        if (item[j] == nullptr||item[j]->occur==0) {
                                item[j] = element;
                                return;
                        }
                        else if (item[j]->value == str) {
                                item[j]->occur++;

                                delete element;
                element = nullptr;
                                return;
                        }
                }
        }
};
int main() {
        HashTable array{};
        array.item = new Item * [CAPACITY];
        string word;
        for (int i = 0; i < CAPACITY; i++)
        {
                array.item[i] = nullptr;
        }
        while (true) {
                cin >> word;
                if (word[0] == '?') {
                        word = word.substr(1, word.length() - 1);
                        array.search(word);
                }
                else if (word[0] == '-') {
                        word = word.substr(1, word.length() - 1);
                        array.deleting(word);
                }
                else if (word[0] == 'q' && word.length() == 1) {

                        for (int i = 0; i < CAPACITY; i++)
                        {
                                if (array.item[i] != nullptr) {
                    array.item[i]= nullptr;
                                        delete array.item[i];

                                }
                                array.item[i] = nullptr;
                        }
                        delete[] array.item;
                        return 0;
                }
                else {
                        array.insert(word);
                }
        }
}