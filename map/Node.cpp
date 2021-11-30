#include "map-utils.hpp"

template<typename T, class Compare, class Alloc = std::allocator<T> >
class Node
{
    
    public:
        typedef T value_type;
        typedef typename Alloc::template rebind<Node<T, Compare> >::other node_allocator;
        // typedef Node node;

        Alloc   pair_alloc;
        value_type   value;
        Node  *right;
        Node  *left;
        Node  *parent;
        Node  *root;
        int   height;
        node_allocator al;
        Compare key_compare;

        
        Node(): key_compare(Compare())
        {
            right = left = root = parent = NULL;
            // value = NULL;
            height = 0;
        }
        Node(const value_type& val): key_compare(Compare())
        {
            // value = al.allocate(1);
            value = val;
            right = left = NULL;
            height = 1;
            root = this;
            parent = NULL;
        }
        Node(Node<value_type, Compare, Alloc> *root): key_compare(Compare())
        {
            right = left = parent = NULL;
            height = root->height;
            this->root = root;
        }
        Node &operator=(const Node &rhs)
        {
            root = rhs.root;
            left = rhs.left;
            right = rhs.right;
            parent = rhs.parent;
            // if (value)
            //     al.deallocate(value, 1);
            // value = al.allocate(1);
            value = rhs.value;
            height = rhs.height;
            return (*this);
        }
        ~Node(){}
        int max(int a, int b)
        {
            return ((a > b)? a : b);
        }
        int Getheight(Node *N)
        {
            if (N == NULL)
                return 0;
            return N->height;
        }
        int getBalance(Node *N)
        {
            if (N == NULL)
                return 0;
            return (Getheight(N->left) - Getheight(N->right));
        }
        Node*   rightRotate(Node* y)
        {
            Node* x = y->left;
            Node* T2 = x->right;

            // do rotate
            if (x->right)
                x->right->parent = y;
            x->right = y;
            y->left = T2;
            // update parent
            x->parent = y->parent;
            y->parent = x;
            // recalculate x and y heights
            x->height = std::max(Getheight(x->left), Getheight(x->right)) + 1;
            y->height = std::max(Getheight(y->left), Getheight(y->right)) + 1;

            // return new tree root
            return (x);
        }

        Node*   leftRotate(Node* x)
        {
            Node *y = x->right;
            Node *T2 = y->left;

            // Perform rotation
            if (y->left)
                y->left->parent = x;
            y->left = x;
            x->right = T2;
            // update parents
            y->parent = x->parent;
            x->parent = y;

            // Update heights
            x->height = max(Getheight(x->left), Getheight(x->right)) + 1;
            y->height = max(Getheight(y->left), Getheight(y->right)) + 1;
            // Return new root
            return y;
        }
        Node  *balance_tree(Node *node, value_type &value)
        {
            //UPDATE HEIGHT OF THE CURRENT NODE
            node->height = 1 + max(Getheight(node->left), Getheight(node->right));

            int balance = getBalance(node);
            
            // If this node becomes unbalanced, then
            // there are 4 cases
            std::cout << balance << " " <<  value.first << "blanace"<< std::endl;
            // Left Left Case
            if (balance > 1 && key_compare(value.first, node->left->value.first))
                return rightRotate(node);
            // std::cout << root->value.first << " " <<  node->value.first << "blanace"<< std::endl;
            // Right Right Case
            if (balance < -1 && key_compare( node->right->value.first, value.first))
             {   
                return leftRotate(node);
             
             }
         
            // Left Right Case
            if (balance > 1 && !key_compare(value.first , node->left->value.first))
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
       
            // Right Left Case
            if (balance < -1 && key_compare(value.first,node->right->value.first))
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            
            return (this->root);
        }
        //insert function

    Node    *insert2(Node *root, Node *node)
    {
        
        if(key_compare(node->value.first, root->value.first))
        {   
          
            if (root->left == nullptr)
            {    
                
                root->left = node; node->parent = root; 
                
                return this->root;}
            root->left = insert2(root->left, node);    root->left->parent = root;
            
        }
        else if(key_compare(root->value.first, node->value.first))
            {
                if (root->right == nullptr)
                 root->right = node; node->parent = root; return root;
                root->right = insert2(root->right, node);  root->right->parent = root;}
        
        return root;
    }
    Node  *insert(const value_type& value){
        
        
        Node    *node = al.allocate(1);
        node->parent = node->left = node->right = nullptr;
         node->height = 0;
        //node is root here
        // node->value = pair_alloc.allocate(1);
        pair_alloc.construct(&(node->value), value);
        if (!root)
            return node;
        
        root = insert2(root, node);
        // /* Get the balance factor of this ancestor
        //     node to check whether this node became
        //     unbalanced */
        
        return (balance_tree(root, node->value));
            return root;
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
    Node* deleteNode(Node* root, value_type data)
    {
        
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL)
            return root;
        // If the data to be deleted is smaller
        // than the root's data, then it lies
        // in left subtree
        if ( data.first < root->data.first )
            root->left = deleteNode(root->left, data.first);
    
        // If the data to be deleted is greater
        // than the root's data, then it lies
        // in right subtree
        else if( data.first > root->data.first)
            root->right = deleteNode(root->right, data.first);
    
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
                root->data.first = temp->data.first;
    
                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data.first);
            }
        }
    
        // If the tree had only one node
        // then return
        if (root == NULL)
            return root;
        
        return (balance_tree(root, data.first));
        return root;
    }
    void printBThelper(Node  *root, int level) // https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram-in-java
        {
              if(root==NULL)
                   return;
              printBThelper(root->right, level+1);
              if(level != 0){
                  for(int i=0;i<level-1;i++)
                      std::cout << "|\t";
                  std::cout << "|-------" << root->value.first << " | ";
                // root->color? std::cout << "Red" : std::cout <<"Black";
                std::cout << std::endl;
              }
              else
            {
                  std::cout << root->value.first << " | ";
                // root->color? std::cout << "Red" : std::cout <<"Black";
                std::cout << std::endl;
            }
              printBThelper(root->left, level+1);
        }

        void    printBT()
        { 
            printBThelper(root, 0);
        }
};

int main(){
    typedef Node<ft::pair<int, int>, std::less<int> > node;
    node root;
    root = root.insert(ft::pair<int, int>(2,2));
    root = root.insert(ft::pair<int, int>(1,1));
    root = root.insert(ft::pair<int, int>(3,3));
    root = root.insert(ft::pair<int, int>(4,4));
    root = root.insert(ft::pair<int, int>(5,5));
    root = root.insert(ft::pair<int, int>(11,11));
    root.printBT();
}