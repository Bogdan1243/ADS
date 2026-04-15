#include <iostream>
#include <climits>

using namespace std;

struct Node {
    int key;
    int degree;
    Node* p;
    Node* child;
    Node* sibling;

    Node(int k) : key(k), degree(0), p(nullptr), child(nullptr), sibling(nullptr) {}
};

struct BinomialHeap {
    Node* head;
    BinomialHeap() : head(nullptr) {}
};

BinomialHeap* MakeBinomialHeap() {
    return new BinomialHeap();
}

Node* BinomialHeapMin(BinomialHeap* H) {
    Node* y = nullptr;
    Node* x = H->head;
    int min = INT_MAX;

    while (x != nullptr) {
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

void BinomialLink(Node* y, Node* z) {
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

Node* BinomialHeapMerge(BinomialHeap* H1, BinomialHeap* H2) {
    Node* a = H1->head;
    Node* b = H2->head;
    Node* head = nullptr;
    Node* tail = nullptr;

    if (!a && !b) return nullptr;

    if (a && b) {
        if (a->degree <= b->degree) { head = a; a = a->sibling; }
        else { head = b; b = b->sibling; }
    } else if (a) { head = a; a = a->sibling; }
    else { head = b; b = b->sibling; }

    tail = head;

    while (a && b) {
        if (a->degree <= b->degree) {
            tail->sibling = a;
            a = a->sibling;
        } else {
            tail->sibling = b;
            b = b->sibling;
        }
        tail = tail->sibling;
    }
    if (a) tail->sibling = a;
    if (b) tail->sibling = b;

    return head;
}

BinomialHeap* BinomialHeapUnion(BinomialHeap* H1, BinomialHeap* H2) {
    BinomialHeap* H = MakeBinomialHeap();
    H->head = BinomialHeapMerge(H1, H2);

    delete H1;
    delete H2;

    if (!H->head) return H;

    Node* prev_x = nullptr;
    Node* x = H->head;
    Node* next_x = x->sibling;

    while (next_x != nullptr) {
        if ((x->degree != next_x->degree) ||
            (next_x->sibling != nullptr && next_x->sibling->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        }
        else if (x->key <= next_x->key) {
            x->sibling = next_x->sibling;
            BinomialLink(next_x, x);
        }
        else {
            if (prev_x == nullptr) {
                H->head = next_x;
            } else {
                prev_x->sibling = next_x;
            }
            BinomialLink(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
    return H;
}

BinomialHeap* BinomialHeapInsert(BinomialHeap* H, Node* x) {
    BinomialHeap* H_prime = MakeBinomialHeap();
    x->p = nullptr;
    x->child = nullptr;
    x->sibling = nullptr;
    x->degree = 0;
    H_prime->head = x;
    return BinomialHeapUnion(H, H_prime);
}

Node* BinomialHeapExtractMin(BinomialHeap*& H) {
    if (!H || !H->head) return nullptr;

    Node* min_node = H->head;
    Node* prev_min = nullptr;
    Node* curr = H->head;
    Node* prev = nullptr;

    while (curr != nullptr) {
        if (curr->key < min_node->key) {
            min_node = curr;
            prev_min = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (prev_min == nullptr) {
        H->head = min_node->sibling;
    } else {
        prev_min->sibling = min_node->sibling;
    }

    Node* child = min_node->child;
    Node* prev_child = nullptr;
    Node* next_child = nullptr;
    while (child != nullptr) {
        next_child = child->sibling;
        child->sibling = prev_child;
        child->p = nullptr; // They become roots of trees
        prev_child = child;
        child = next_child;
    }
    BinomialHeap* H_prime = MakeBinomialHeap();
    H_prime->head = prev_child;
    H = BinomialHeapUnion(H, H_prime);

    return min_node;
}
void BinomialHeapDecreaseKey(BinomialHeap* H, Node* x, int k) {
    if (k > x->key) {
        cerr << "Error: new key is greater than current key" << endl;
        return;
    }
    x->key = k;
    Node* y = x;
    Node* z = y->p;

    while (z != nullptr && y->key < z->key) {
        swap(y->key, z->key);
        y = z;
        z = y->p;
    }
}

void BinomialHeapDelete(BinomialHeap*& H, Node* x) {
    BinomialHeapDecreaseKey(H, x, -INT_MAX);
    Node* min_node = BinomialHeapExtractMin(H);
    delete min_node;
}

int main() {
    // To run the project, first the heap has to be created: BinomialHeap* H = MakeBinomialHeap();
    // BinomialHeapInsert(H, new Node(value)) - used for inserting nodes into the binomial heap (returns the updated heap pointer)
    // BinomialHeapMin(H) - used to obtain the node with the minimum value
    // BinomialHeapExtractMin(H) - used to extract and return the node with the minimum value from the heap
    // BinomialHeapDecreaseKey(H, node, new_value) - used to decrease the key of a specific node
    // BinomialHeapDelete(H, node) - used to delete a specific node from the heap
    // BinomialHeapUnion(H1, H2) - used to merge two binomial heaps into one
    // Recommended use: Insert nodes, find the minimum node, extract the minimum to see how the heap changes,
    // try decreasing a node's key, and finally delete a node.
    BinomialHeap* H = MakeBinomialHeap();

    // Example usage of the methods:
    // H = BinomialHeapInsert(H, new Node(55));
    // H = BinomialHeapInsert(H, new Node(40));
    // H = BinomialHeapInsert(H, new Node(65));
    // H = BinomialHeapInsert(H, new Node(60));
    // H = BinomialHeapInsert(H, new Node(75));
    // H = BinomialHeapInsert(H, new Node(57));
    // H = BinomialHeapInsert(H, new Node(62));

    // Node* minNode = BinomialHeapMin(H);
    // if (minNode) cout << "Minimum value: " << minNode->key << endl;
    // Node* extracted = BinomialHeapExtractMin(H);
    // if (extracted) {
    //     cout << "Extracted minimum: " << extracted->key << endl;
    //     delete extracted; // Free the memory of the extracted node
    // }
    // minNode = BinomialHeapMin(H);
    // if (minNode) cout << "New minimum value after extraction: " << minNode->key << endl;
    // To test DecreaseKey or Delete, you would keep a pointer to the inserted node.
    // // Example:
    // // Node* targetNode = new Node(100);
    // // H = BinomialHeapInsert(H, targetNode);
    // // BinomialHeapDecreaseKey(H, targetNode, 10);
    // // cout << "Decreased key of target node to 10." << endl;
    // // BinomialHeapDelete(H, targetNode);
    // // cout << "Target node deleted." << endl;

    return 0;
}
