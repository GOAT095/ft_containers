
#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
// using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
    struct Node* parent;
	int height;
	// val is the key or the value that
	// has to be added to the data part
	
};


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
Node  *insert(Node *r,int data){
        
		if(r==NULL){
            Node *n = newNode(data);
            r = n;
            return r;
        }
        else{
            if(data < r->data)
            	r->left = insert(r->left, data);
            else
            	r->right = insert(r->right, data);
        }
		return r;
}
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
//
// Function to perform inorder traversal on the BST
void inorder(Node* root)
{
    if (root == nullptr) {
        return;
    }
 
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

// Helper function to find minimum value node in the subtree rooted at `curr`
Node* getMinimumKey(Node* curr)
{
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}
// Iterative function to search in the subtree rooted at `curr` and set its parent.
// Note that `curr` and `parent` is passed by reference to the function.
void searchKey(Node* &curr, int key, Node* &parent)
{
    // traverse the tree and search for the key
    while (curr != nullptr && curr->data != key)
    {
        // update the parent to the current node
        parent = curr;
 
        // if the given key is less than the current node, go to the left subtree;
        // otherwise, go to the right subtree
        if (key < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
}
// Function to delete a node from a BST
void deleteNode(Node*& root, int key)
{
    // pointer to store the parent of the current node
    Node* parent = nullptr;
 
    // start with the root node
    Node* curr = root;
 
    // search key in the BST and set its parent pointer
    searchKey(curr, key, parent);
 
    // return if the key is not found in the tree
    if (curr == nullptr) {
        return;
    }
 
    // Case 1: node to be deleted has no children, i.e., it is a leaf node
    if (curr->left == nullptr && curr->right == nullptr)
    {
        // if the node to be deleted is not a root node, then set its
        // parent left/right child to null
        if (curr != root)
        {
            if (parent->left == curr) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
        // if the tree has only a root node, set it to null
        else {
            root = nullptr;
        }
 
        // deallocate the memory
        free(curr);        // or delete curr;
    }
 
    // Case 2: node to be deleted has two children
    else if (curr->left && curr->right)
    {
        // find its inorder successor node
        Node* successor = getMinimumKey(curr->right);
 
        // store successor value
        int val = successor->data;
 
        // recursively delete the successor. Note that the successor
        // will have at most one child (right child)
        deleteNode(root, successor->data);
 
        // copy value of the successor to the current node
        curr->data = val;
    }
 
    // Case 3: node to be deleted has only one child
    else {
        // choose a child node
        Node* child = (curr->left)? curr->left: curr->right;
 
        // if the node to be deleted is not a root node, set its parent
        // to its child
        if (curr != root)
        {
            if (curr == parent->left) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
 
        // if the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
        }
 
        // deallocate the memory
        free(curr);
    }
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
    deleteNode(r, 6);
    printTree(r, nullptr, false);
	return 0;
}
