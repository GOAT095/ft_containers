
#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
// using namespace std;
// print tree
// node stuff
struct Node {
	int data;
	struct Node* left;
	struct Node* right;
    struct Node* parent;
	int height;
	// val is the data or the value that
	// has to be added to the data part
	
};
struct Trunk
{
    Trunk *prev;
    std::string str;
 
    Trunk(Trunk *prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }
 
    showTrunks(p->prev);
    std::cout << p->str;
}
void printTree(Node* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
 
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    std::cout << root->data << std::endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}
//node stuff
int max(int a, int b)
{
    return ((a > b)? a : b);
}
//height of node N
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *newNode(int val)
{
	Node* newNode = new Node();
	newNode->data = val;

	// Left and right child for node
	// will be initialized to null
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	return (newNode);
}
Node  *insert(Node *node,int data){
        
    //node is root here
    if(node == NULL){
        Node *n = newNode(data);
        node = n;
        return node;
    }
    if(data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
        /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
		return node;
}


int main()
{

	Node *r = NULL;
	r = insert(r, 2);
	r = insert(r, 1);
	r = insert(r, 5);
	r = insert(r, 6);
	r = insert(r, 3);
	r = insert(r, 4);
	r = insert(r, 7);
	printTree(r, nullptr, false);
    // deleteNode(r, 2);
    // printTree(r, nullptr, false);
	return 0;
}
