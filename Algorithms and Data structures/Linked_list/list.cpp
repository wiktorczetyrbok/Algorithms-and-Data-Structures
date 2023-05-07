#include <iostream>
using namespace std;
class Node {
public:
        int key;
        Node* next;
        Node* prev;
};
void addlast(Node** tail,Node** head, int new_data)
{
        if (*head== NULL){
                Node* new_node = new Node;
                new_node->key = new_data;
                new_node->next = NULL;
                new_node->prev = NULL;
                *head = new_node;
                *tail = new_node;
        }
        else {
                Node* new_node = new Node;
                new_node->key = new_data;
                new_node->next = NULL;
                (*tail)->next = new_node;
                new_node->prev =*tail;
                *tail = new_node;
        }
}
void find(Node* head, int n){
        Node* temp = head;
        int index = 0;
        while (index != n) {
                temp = temp->next;
                index++;
        }
        cout <<temp->key<< endl;
}
void deleteLast(Node** tail){
        cout << (*tail)->key << endl;
        Node* temp = (*tail);
        temp->next = NULL;
        (*tail) = temp->prev;
        if (temp->prev!= NULL)(*tail)->prev = temp->prev->prev;
        else return;
        (*tail)->next = NULL;
        delete temp;
}
void freeing(Node** head) {
        Node* current = *head;
        while (current != NULL) {
                Node* next = current->next;
                current->prev = NULL;
                delete current;
                current = next;
        }
}
int main() {

        char operation;
        int quit = 0, key;
        Node* head = NULL;
        Node* tail = NULL;

        while (!quit) {
                cin >> operation;
                switch (operation) {
                case 'i':
                        cin >> key;
                        addlast(&tail, &head, key);
                        break;
                case 'd':
                        deleteLast(&tail);
                        break;
                case 'g':
                        int l;
                        cin >>l;
                        find(head, l);
                        break;
                case 'q':
                        freeing(&head);
                        return quit=1;
                        break;
                }
        }
        return 0;
}