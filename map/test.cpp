
#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
// using namespace std;
// node stuff
struct Node {
	int data;
	struct Node* left;
	struct Node* right;
    struct Node* parent;
	int height;
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
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *tmp;
    Node *x = y->left;
    Node *T2 = x? x->right : NULL;
 
    // Perform rotation
    if (!x){return y;}
    x->right = y;
    y->left = T2;

    tmp = y->parent;
    y->parent = x->parent;
    x->parent = tmp;
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
    Node *tmp;
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    tmp = y->parent;
    y->parent = x->parent;
    x->parent = tmp;
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

Node  *balance_tree(Node *node, int data)
{
    //UPDATE HEIGHT OF THE CURRENT NODE
    node->height = 1 + max(height(node->left),
                           height(node->right));

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
    return (node);
}

Node  *insert(Node *node,int data){
        
    //node is root here
    if(node == NULL){
        Node *n = newNode(data);
        node = n;
        return node;
    }
    if(data < node->data)
    {    node->left = insert(node->left, data); node->left->parent = node;}
    else
        {node->right = insert(node->right, data); node->right->parent = node;}
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    
    return (balance_tree(node, data));
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
// given root. It returns root of the
// modified subtree.
Node* deleteNode(Node* root, int data)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
    // If the data to be deleted is smaller
    // than the root's data, then it lies
    // in left subtree
    if ( data < root->data )
        root->left = deleteNode(root->left, data);
 
    // If the data to be deleted is greater
    // than the root's data, then it lies
    // in right subtree
    else if( data > root->data )
        root->right = deleteNode(root->right, data);
 
    // if data is same as root's data, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            Node *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's
            // data to this node
            root->data = temp->data;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
        return root;
    
    return (balance_tree(root, data));
    return root;
}
// void inorder(struct Node* root)
// {
//     if (root != NULL) {
//         inorder(root->left);
//         std::cout << root->data;
//         inorder(root->right);
//     }
// }

int main()
{

	Node *r = NULL;
	r = insert(r, 1);
	r = insert(r, 2);
	r = insert(r, 3);
	r = insert(r, 4);
	r = insert(r, 5);
    // // printTree(r, nullptr, false);
	r = insert(r, 6);
    // // printTree(r, nullptr, false);
    // // printTree(r, nullptr, false);
    // // printTree(r, nullptr, false);
	r = insert(r, 20);
    // // printTree(r, nullptr, false);
    // r = insert(r, 7);
    // // printTree(r, nullptr, false);
    r = insert(r, 89);
    r = insert(r, 9);
    // inorder(r);
	printTree(r, nullptr, false);
    r = deleteNode(r, 2);
    r = deleteNode(r, 3);
    r = deleteNode(r, 1);
    // // inorder(r);
    printTree(r, nullptr, false);
	return 0;
}
