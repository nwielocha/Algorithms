#include <iostream>

class BST {
    struct Node {
        int key;
        Node *left, *right;
    };

    Node *root;

    Node* insertNode(int, Node*);
    Node* searchNode(int, Node*);
    Node* bstMin(Node*);
    Node* removeNode(int, Node*);
    void printBST(Node*); 

    public:
        BST() {
            root = NULL;
        }

        void insertNode(int x) {
            root = insertNode(x, root);
        }

        void searchNode(int x) {
            root = searchNode(x, root);
        }

        void removeNode(int x) {
            root = removeNode(x, root);
        }

        void printBST() {
            printBST(root);
            std::cout << std::endl;
        }
};

BST::Node* BST::insertNode(int x, Node* t) {
    if (t == NULL) {
        t = new Node;
        t->key = x;
        t->left = t->right = NULL;
    }
    else if (x < t->key) 
        t->left = insertNode(x, t->left);
    else if (x > t->key)
        t->right = insertNode(x, t->right);

    return t;
}

BST::Node* BST::searchNode(int x, Node* t) {
    if (t == NULL)
        return NULL;
    else if (x < t->key)
        return searchNode(x, t->left);
    else if (x > t->key)
        return searchNode(x, t->right);
    else
        return t;
}

BST::Node* BST::bstMin(Node* t) {
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else 
        return bstMin(t->left);
}

BST::Node* BST::removeNode(int x, Node* t) {
    Node* temp;

    if (t == NULL)
        return NULL;
    else if (x < t->key) 
        t->left = removeNode(x, t->left);
    else if (x > t->key)
        t->right = removeNode(x, t->right);
    else if (t->left && t->right) {
        temp = bstMin(t->right);
        t->key = temp->key;
        t->right = removeNode(t->key, t->right);
    }
    else {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        delete temp;
    }

    return t;
}

void BST::printBST(Node* t) {
    if (t == NULL)
        return;
    printBST(t->left);
    std::cout << t->key << " ";
    printBST(t->right);
}

int main() {
    BST t;
    t.insertNode(180);
    t.insertNode(11);
    t.insertNode(6);
    t.insertNode(30);
    t.insertNode(21);
    t.insertNode(19);
    t.insertNode(8);
    t.insertNode(22);
    t.insertNode(23);
    t.insertNode(5);
    t.insertNode(20);
    t.insertNode(26);
    t.insertNode(17);
    t.printBST();
    t.removeNode(8);
    t.removeNode(30);
    t.removeNode(180);
    t.removeNode(11);
    t.printBST();

    return 0;
}
