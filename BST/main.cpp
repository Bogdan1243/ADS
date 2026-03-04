#include <iostream>

using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    bool search(Node* node, int val) {
        if (node == nullptr) return false;
        if (node->data == val) return true;

        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) return node;

        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    bool search(int val) {
        return search(root, val);
    }

    void remove(int val) {
        root = deleteNode(root, val);
    }

    int getMin() {
        if (root == nullptr) throw runtime_error("Tree is empty");
        return findMin(root)->data;
    }

    int getMax() {
        if (root == nullptr) throw runtime_error("Tree is empty");
        Node* current = root;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    void print() {
        inorder(root);
        cout << endl;
    }
};

int main() {
// To run the project, first the object has to be created: BST tree;
//tree.insert() - used for inserting nodes in the BST
//tree.print() - used to see the tree in order after inserting
// tree.getMin() - used to obtain the minimum value
// tree.getMax() - used ot obbtain the maximum value
//tree.search() - used to find an integer
//tree.remove() - used to delete nodes from the tree


    return 0;
}