
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
        // else{
        //     if(data < r->data)
        //     r->left = insert(r->left,data);
        //     else
        //     r->right = insert(r->right,data);
        // }
		return r;
}
void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);    
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
	Node *r = insert(r, 1);
	printBT(r);
	return 0;
}
