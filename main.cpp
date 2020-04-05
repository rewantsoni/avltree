#include "iostream"
#include <random>
#include "queue"

namespace ranges {
    template<typename Range, typename Generator>
    void generate(Range &range, Generator generator) {
        return std::generate(begin(range), end(range), generator);
    }
}

using namespace std;

//Node class
class Node {
public:
    int data;
    Node *left;
    Node *right;

    explicit Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

//PLR
//preOrder Recursive Function
void preOrder(Node *root) {
    if (!root) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

//LRP
//postOrder Recursive Function
void postOrder(Node *root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

//LPR
//inOrder Recursive Function
void inOrder(Node *root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

//Height of the Tree
int height(Node *root) {
    if (!root) return 0;
    return max(height(root->left), height(root->right)) + 1;
}

Node *rightRotation(Node *root) {
    Node *a = root->left;
    root->left = a->right;
    a->right = root;
    return a;
}

Node *leftLeftRotation(Node *root) {
    Node *a = root->right;
    root->right = a->left;
    a->left = root;
    return a;
}

Node *leftRotation(Node *root) {
    Node *a = root->right;
    root->right = a->left;
    a->left = root;
    return a;
}

Node *rightRightRotation(Node *root) {
    Node *a = root->left;
    root->left = a->right;
    a->right = root;
    return a;
}

Node *insertAVL(Node *root, int v) {
    if (!root) return new Node(v);
    else if (root->data == v) return root;
    else if (root->data > v) root->left = insertAVL(root->left, v);
    else if (root->data < v) root->right = insertAVL(root->right, v);

    int balance = height(root->left) - height(root->right);
    if (balance > 1 && root->left->data > v) root = rightRotation(root);
    else if (balance > 1 && root->left->data < v) {
        root->left = leftLeftRotation(root->left);
        root = rightRotation(root);
    } else if (balance < -1 && root->right->data < v) root = leftRotation(root);
    else if (balance < -1 && root->right->data > v) {
        root->right = rightRightRotation(root->right);
        root = leftRotation(root);
    }
    return root;
}

bool balance(Node *root) {
    if (!root) return true;
    int bal = height(root->left) - height(root->right);
    if (bal <= 1 && bal >= -1) return (balance(root->left) && balance(root->right));
    return false;
}

int main() {
    //Self Balancing AVL TREES
    vector<int> ar0 = {15, 12, 20, 10, 14, 8};
    vector<int> ar1 = {15, 12, 20, 10, 13, 14};
    vector<int> ar2 = {15, 12, 20, 17, 25, 30};
    vector<int> ar3 = {15, 12, 20, 17, 25, 16};

    Node *root = nullptr;
    cout << "First Case: " << endl;
    for (auto f: ar0) {
        root = insertAVL(root, f);
    }
    inOrder(root);
    cout << endl;
    preOrder(root);
    cout << endl;
    root = nullptr;
    cout << "Second Case: " << endl;
    for (auto f: ar1) {
        root = insertAVL(root, f);
    }
    inOrder(root);
    cout << endl;
    preOrder(root);
    cout << endl;
    root = nullptr;
    cout << "Third Case: " << endl;
    for (auto f: ar2) {
        root = insertAVL(root, f);
    }
    inOrder(root);
    cout << endl;
    preOrder(root);
    cout << endl;
    root = nullptr;
    cout << "Fourth Case: " << endl;
    for (auto f: ar3) {
        root = insertAVL(root, f);
    }
    inOrder(root);
    cout << endl;
    preOrder(root);
    cout << endl;

    root = nullptr;
    vector<int> randArray(512, 0);

    auto randomNumberBetween = [](int low, int high) {
        auto randomFunc = [distribution_ = std::uniform_int_distribution<int>(low, high),
                random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
            return distribution_(random_engine_);
        };
        return randomFunc;
    };
    ranges::generate(randArray, randomNumberBetween(1, 100000));
    for (int i = 0; i < 512; i++) {
        root = insertAVL(root, randArray[i]);
    }
    cout << endl << "balance of new tree is : " << balance(root);
    cout << endl;
    inOrder(root);
    return 0;
}