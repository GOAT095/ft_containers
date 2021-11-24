
#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
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
    string str;
 
    Trunk(Trunk *prev, string str)
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
    cout << p->str;
}
void printTree(Node* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    string prev_str = "    ";
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
    cout << root->data << endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}

int main()
{

	/*create root*/
	// Node *root = newNode(1);
	// /* following is the tree after above statement

	// 		1
	// 		/ \
	// 	NULL NULL
	// */

	// root->left = newNode(2);
	// root->right = newNode(3);
	// /* 2 and 3 become left and right children of 1
	// 				1
	// 			/ \
	// 			2	 3
	// 		/ \	 / \
	// 		NULL NULL NULL NULL
	// */

	// root->left->left = newNode(4);
	// root->left->right = newNode(5);
	// root->right->left = newNode(7);
	// root->right->right = newNode(8);
	/* 4 becomes left child of 2
			1
			/	 \
		2	 3
		/ \	 / \
		4 NULL NULL NULL
		/ \
	NULL NULL
	*/
	Node *r = NULL;
	r = insert(r, 2);
	r = insert(r, 1);
	r = insert(r, 5);
	r = insert(r, 6);
	r = insert(r, 3);
	r = insert(r, 4);
	r = insert(r, 7);
	printTree(r, nullptr, false);
	return 0;
}
