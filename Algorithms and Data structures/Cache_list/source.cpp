#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstdlib>
#define ITER_ARR_SIZE 10
#define MAX_COMMAND_SIZE 4

using namespace std;

class Node {
public:
        unsigned long long int key;
        Node* next;
        Node* prev;
};
void addlast(Node** tail, Node** head, unsigned long long int new_data)
{
        if (*head == NULL) {     ///case for empty list
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
                new_node->prev = *tail;
                *tail = new_node;
        }
}
void insert_front(Node** head, Node** tail, unsigned long long int new_key)
{
        Node* newNode = new Node;
        newNode->key = new_key;
        newNode->next = (*head);
        newNode->prev = NULL;
        if ((*head) != NULL) { (*head)->prev = newNode; }
        (*head) = newNode;
        if ((*head)->next == NULL)*tail = *head;// for th list that contains one element
}
void printList(Node* Node)
{
        while (Node != NULL)
        {
                cout << Node->key << " ";
                Node = Node->next;
        }
        cout << endl;
}
void deleteNode(Node** head,Node** tail, Node* delPtr, Node* arr[], int n)
{
        if (*head == NULL || delPtr == NULL) //the case with empty list
                return;
        if (*head == delPtr) {
                *head = delPtr->next;
                for (int i = 0; i < ITER_ARR_SIZE; i++) {
                        if(arr[i]==delPtr)arr[i] = NULL;
                }
        }
        if (*tail == delPtr&& arr[n] != NULL) {// case when deleting node is tail
                *tail = delPtr->prev;
                for (int i = 0; i < ITER_ARR_SIZE; i++) {
                        if (arr[i] == delPtr)arr[i] = delPtr->prev; //iterator is updated to point one node back
                }
        }
        if (delPtr->next != NULL) {
                delPtr->next->prev = delPtr->prev;
        }
        if (delPtr->prev != NULL) {
                delPtr->prev->next = delPtr->next;
        }
        if (delPtr->next != NULL && delPtr->prev != NULL) {
                for (int i = 0; i < ITER_ARR_SIZE; i++) {
                        if (arr[i] == delPtr&&arr[i]!=NULL)arr[i] = delPtr->next; // iterator points to the next node when deleted
                }
        }
        delete delPtr;
        return;
}
void addAfterPos(Node** tail, Node** head, unsigned long long int new_key, int position, char command[]) { //ading next node to the list after given position
        if (strcmp(command, ".A") == 0) { if (position > 1)position = position - 1; }
        Node* newNode = new Node;
        newNode->key = new_key;
        Node* temp = *head;
        Node* temp2 = NULL;
        while (position != 1) {
                temp = temp->next;
                position--;
        }
        if (temp != NULL) {
                temp2 = temp->next;
                temp->next = newNode;
                newNode->next = temp2;
                newNode->prev = temp;
        }
        else{
                addlast(tail, head, new_key); //case when we add after the tail
        }
}
void deleteLast(Node** tail, Node** head) {
        if ((*head)->next == NULL) { // when the list contains one element
                delete* head;                   
                *head = NULL;
        }
        else {
                Node* temp = (*tail)->prev;
                temp->next = NULL;
                delete* tail;
                *tail = temp;
        }
}
void deleteFirst(Node** head) { //deleting first node in the list
        if (*head != NULL) {
                Node* temp = *head;
                *head = (*head)->next;
                delete temp;    
                if (*head != NULL)
                        (*head)->prev = NULL;
        }
}
void addAfteriterator(Node** tail, Node* arr[], int x, unsigned long long int new_data) { //adding node after iterator
        Node* temp = new Node;
        temp->key = new_data;
        if (arr[x]->next != NULL) {
                temp->next = arr[x]->next;
                arr[x]->next = temp;
        }
        else {
                arr[x]->next = temp;
                temp->next = NULL;
                *tail = temp; ///when we add the tail
        }
        temp->prev = arr[x];
        if (temp->next != NULL)
                temp->next->prev = temp;
}
void addbeforeiterator(Node** head,Node* arr[], int x, unsigned long long int new_data) {
        Node* temp = new Node;
        temp->key = new_data;
        temp->prev = arr[x]->prev;
        temp->next = arr[x];
        arr[x]->prev = temp;

        if (temp->prev != NULL) {
                temp->prev->next = temp;
        }
        else {
                *head = temp; //case when we add head
        }
}
void addIter(int i, Node* arr[], Node** head, Node** tail, char where[]) { //initialisation of interator
        int position = 0;
        Node* temp = *head;
        if (strcmp(where, "BEG") == 0) {
                arr[i] = temp;
                return;
        }
        else if (strcmp(where, "END") == 0) {
                temp = *tail;
                arr[i] = temp;
                return;
        }
        else {
                sscanf(where, "%d", &position);//for reading the position
                while (position != 0) {
                        temp = temp->next;
                        position--;
                }
                arr[i] = temp;
        }
}
void arrInit(Node* arr[]) { //intialisation of array
        for (int i = 0; i < ITER_ARR_SIZE; i++) {
                arr[i] = NULL;
        }
}
void freeing(Node** head, Node* arr[]) {///freeing the whole list 
        Node* current = *head;
        while (current != NULL) {
                Node* next = current->next;
                current->prev = NULL;
                delete current;
                current = next;
        }
        arrInit(arr);
}
int main() {

        char command[MAX_COMMAND_SIZE], where[MAX_COMMAND_SIZE];
        int  iter_index = 0, count = 0;
        unsigned long long  int key = 0;
        Node* head = NULL;
        Node* tail = NULL;
        Node* iter_arr[ITER_ARR_SIZE];
        arrInit(iter_arr);
        
        while (true)
        {
                scanf("%3s", command);
                if (feof(stdin) != 0)
                {
                        break;
                }
                if (strcmp(command, "I") == 0) {
                        cin >> key;
                }
                else if (strcmp(command, "P") == 0) {
                        scanf("%3s", where);
                        if (strcmp(where, "ALL") == 0)printList(head);
                        else {
                                sscanf(where, "%d", &iter_index);
                                if (iter_arr[iter_index] != NULL)cout << iter_arr[iter_index]->key << endl;
                                else cout << endl;
                        }
                }
                else if (strcmp(command, ".A") == 0 || strcmp(command, "A.") == 0) {
                        count++;
                        scanf("%3s %llu", where, &key);
                        if (strcmp(where, "BEG") == 0) {
                                if (strcmp(command, "A.") == 0 && head != NULL)addAfterPos(&tail, &head, key, 1, command);
                                else  insert_front(&head, &tail, key);
                        }
                        else if (strcmp(where, "END") == 0) {
                                if (strcmp(command, "A.") == 0)addlast(&tail, &head, key);
                                else if (strcmp(command, ".A") == 0) { addAfterPos(&tail, &head, key, count - 1, command); }
                        }
                        else {
                                sscanf(where, "%d", &iter_index);
                                if (strcmp(command, "A.") == 0)addAfteriterator(&tail, iter_arr, iter_index, key);
                                else addbeforeiterator(&head, iter_arr, iter_index, key);
                        }
                }
                else if (strcmp(command, "R") == 0) {
                        scanf("%3s", where);
                        if (strcmp(where, "BEG") == 0)deleteFirst(&head);
                        else if (strcmp(where, "END") == 0)deleteLast(&tail, &head);
                        else {
                                sscanf(where, "%d", &iter_index);
                                deleteNode(&head, &tail, iter_arr[iter_index], iter_arr, iter_index);
                        }
                        if (count > 0)count--;
                }
                else if (strcmp(command, "i") == 0) {
                        scanf("%d %3s", &iter_index, where);
                        addIter(iter_index, iter_arr, &head, &tail, where);
                }
                else if (strcmp(command, "+") == 0) {
                        scanf("%d", &iter_index);
                        if (iter_arr[iter_index]->next != NULL)iter_arr[iter_index] = iter_arr[iter_index]->next;
                }
                else if (strcmp(command, "-") == 0) {
                        scanf("%d", &iter_index);
                        if (iter_arr[iter_index]->prev != NULL)iter_arr[iter_index] = iter_arr[iter_index]->prev;
                }
                else break;
        }
        freeing(&head, iter_arr);
        return 0;
}