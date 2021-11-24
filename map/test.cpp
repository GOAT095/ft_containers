
#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;

	// val is the key or the value that
	// has to be added to the data part
	Node(int val)
	{
		data = val;

		// Left and right child for node
		// will be initialized to null
		left = NULL;
		right = NULL;
	}
};

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

	// /*create root*/
	struct Node* root = new Node(1);
	// /* following is the tree after above statement

	// 		1
	// 		/ \
	// 	NULL NULL
	// */

	// root->left = new Node(2);
	// root->right = new Node(3);
	// /* 2 and 3 become left and right children of 1
	// 				1
	// 			/ \
	// 			2	 3
	// 		/ \	 / \
	// 		NULL NULL NULL NULL
	// */

	// root->left->left = new Node(4);
	// root->left->right = new Node(5);
	// root->right->left = new Node(7);
	// root->right->right = new Node(8);
	/* 4 becomes left child of 2
			1
			/	 \
		2	 3
		/ \	 / \
		4 NULL NULL NULL
		/ \
	NULL NULL
	*/
	printBT(root);
	return 0;
}
