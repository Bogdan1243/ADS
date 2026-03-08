#include <iostream>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

class RBTree {
private:
    Node* root;
    Node* TNULL;

    void initializeNULLNode(Node* node, Node* parent) {
        node->data = 0;
        node->color = BLACK;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
    }

    void preOrderHelper(Node* node) {
        if (node != TNULL) {
            cout << node->data << (node->color == RED ? "(R) " : "(B) ");
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }
    void printHelper(Node* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }

            string sColor = root->color == RED ? "(RED)" : "(BLACK)";
            cout << root->data << sColor << endl;

            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    Node* searchTreeHelper(Node* node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    void fixDelete(Node* x) {
        Node* s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node* node, int key) {
        Node* z = TNULL;
        Node* x;
        Node* y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        Color y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }

    void fixInsert(Node* k) {
        Node* u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

public:
    RBTree() {
        TNULL = new Node;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preOrder() {
        preOrderHelper(this->root);
        cout << endl;
    }

    Node* searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node* maximum(Node* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }
    void printTree() {
        if (root == TNULL) {
            cout << "Tree is empty." << endl;
        } else {
            printHelper(this->root, "", true);
        }
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insert(int key) {
        Node* node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }
        fixInsert(node);
    }

    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

    // Helper for main
    Node* getRoot() {
        return this->root;
    }
};

int main() {
    // To run the project, first the object has to be created: RBTree tree;
    // tree.insert(value) - used for inserting nodes in the RB tree
    // tree.printTree() - used to see the tree structure and node colors after inserting
    // tree.minimum(node) - used to obtain the minimum value
    // tree.maximum(node) - used to obtain the maximum value
    // tree.searchTree(value) - used to find an integer
    // tree.deleteNode(value) - used to delete nodes from the tree
    // Recommended use: Insert nodes, print the tree, find the minimum and maximum node,
    // try searching an integer, delete a node after which print the tree again to see how it changed
    RBTree tree;

    // Example usage of the methods:
    // tree.insert(55);
    // tree.insert(40);
    // tree.insert(65);
    // tree.insert(60);
    // tree.insert(75);
    // tree.insert(57);
    // tree.insert(62);
    // tree.insert(54);
    // tree.insert(51);
    // tree.insert(69);
    //
    //
    // cout << "Tree Structure: " << endl;
    // tree.printTree();
    // cout << "----------------------" << endl;
    //
    // Node* minNode = tree.minimum(tree.getRoot());
    // cout << "Minimum value: " << minNode->data << endl;
    //
    // Node* maxNode = tree.maximum(tree.getRoot());
    // cout << "Maximum value: " << maxNode->data << endl;
    //
    // int searchVal = 60;
    // Node* found = tree.searchTree(searchVal);
    // if (found->data != 0) {
    //     cout << "Found node: " << found->data << " with color " << (found->color == RED ? "RED" : "BLACK") << endl;
    // }
    // cout << "----------------------" << endl;
    //
    // tree.deleteNode(40);
    // cout << "Tree Structure after deletion of 40: " << endl;
    // tree.printTree();

    return 0;
}