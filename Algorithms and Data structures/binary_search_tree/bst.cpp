#include <iostream>
//#include <Windows.h>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
};
Node* Insert(Node* root, int data) {
    if (root == NULL)
    {
        Node* node = new Node;
        node->key = data;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    else {
        Node* cur;
        if (data <= root->key) {
            cur = Insert(root->left, data);
            root->left = cur;
        }
        else {
            cur = Insert(root->right, data);
            root->right = cur;
        }
        return root;
    }
}

Node* Delete(Node* root, int numToDel)
{
    if (root == NULL)
        return root;
    if (root->key > numToDel) {
        root->left = Delete(root->left, numToDel);
        return root;
    }
    else if (root->key < numToDel) {
        root->right = Delete(root->right, numToDel);
        return root;
    }
    if (root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    }
    else {
        Node* Parent = root;
        Node* succ = root->right;
        while (succ->left != NULL) {
            Parent = succ;
            succ = succ->left;
        }

        if (Parent != root)
            Parent->left = succ->right;
        else
            Parent->right = succ->right;

        root->key = succ->key;
        delete succ;
        return root;
    }
}
Node* Search(Node* root, int key) {
    if (root == NULL)
    {
        cout << '0' << endl;
        return root;
    }
    if (root->key == key)
    {
        cout << '1' << endl;
        return root;
    }

    if (root->key < key)
        return Search(root->right, key);
    else
        return Search(root->left, key);
}
int minKey(Node* node)
{
    Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current->key;
}
int maxKey(Node* node)
{
    Node* current = node;
    while (current && current->right != NULL)
        current = current->right;

    return current->key;
}
int main()
{
    /*HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));*/
    Node* root = NULL;
    Node* temp = NULL;
    char command;
    bool quit = false;
    while (!quit)
    {
        cin >> command;
        switch (command)
        {
        case '+':
            int newNumber;
            cin >> newNumber;
            root = Insert(root, newNumber);
            break;
        case '-':
            int numToDel;
            cin >> numToDel;
            root = Delete(root, numToDel);
            break;
        case '?':
            int num;
            cin >> num;
            Search(root, num);
            break;
        case 'm':
            int min;
            min = minKey(root);
            cout << min << endl;
            break;
        case 'M':
            int max;
            max = maxKey(root);
            cout << max << endl;
            break;
        case 'q':
            quit = true;
            break;
        }
    }
    return 0;
}