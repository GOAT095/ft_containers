
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
void printTree(Node* node, Trunk *prev, bool isLeft)
{
    if (node == nullptr) {
        return;
    }
 
    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
 
    printTree(node->right, trunk, true);
 
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
    std::cout << node->data << std::endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(node->left, trunk, false);
}
//node stuff

//insert ina bst using AVL

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
// rotate subtree nodeed with y
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
 
    // Return new node
    return x;
}
// A utility function to left
// rotate subtree nodeed with x
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
 
    // Return new node
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
        
    //node is node here
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
//delete in a bst using AVL
/* Given a non-empty binary search tree,
return the node with minimum data value
found in that tree. Note that the entire
tree does not need to be searched. */
Node * minValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node
// with given data from subtree with
// given node. It returns node of the
// modified subtree.
Node* deleteNode(Node* node, int data)
{
     
    // base case
    if (node == NULL)
        return node;
 
    // If the data to be deleted is
    // smaller than the node's
    // data, then it lies in left subtree
    if (data < node->data)
        node->left = deleteNode(node->left, data);
 
    // If the data to be deleted is
    // greater than the node's
    // data, then it lies in right subtree
    else if (data > node->data)
        node->right = deleteNode(node->right, data);
 
    // if data is same as node's data, then This is the node
    // to be deleted
    else {
        // node has no child
        if (node->left==NULL and node->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (node->left == NULL) {
             Node* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
             Node* temp = node->left;
            free(node);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
         Node* temp = minValueNode(node->right);
 
        // Copy the inorder successor's content to this node
        node->data = temp->data;
 
        // Delete the inorder successor
        node->right = deleteNode(node->right, temp->data);
    }
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
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
	r = insert(r, 20);
    r = insert(r, 7);
    r = insert(r, 89);
    r = insert(r, 9);
	printTree(r, nullptr, false);
    deleteNode(r, 1);
    printTree(r, nullptr, false);
	return 0;
}
