#pragma once

#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
#include "map-utils.hpp"
#include "map_iter.hpp"

namespace ft{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public:
            typedef T mapped_type;
            typedef Key key_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef	size_t                             size_type;
            typedef	size_t                             difference_type;
            typedef pair<const key_type,mapped_type>   value_type;

            //typedef ft::Node<
            //constractors and stuff
            //empty
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                _size = 0;
                al = alloc;
                kc = comp;
                _capacity = 0;
                _Root = NULL;

                _Root = insert(_Root, ft::pair<Key, T>(1,1));
                _Root = insert(_Root, ft::pair<Key, T>(2,1));
                _Root = insert(_Root, ft::pair<Key, T>(3,1));
                _Root = insert(_Root, ft::pair<Key, T>(4,1));
                _Root = insert(_Root, ft::pair<Key, T>(5,1));
                _Root = insert(_Root, ft::pair<Key, T>(6,1));
                _Root = insert(_Root, ft::pair<Key, T>(7,1));
                _Root = insert(_Root, ft::pair<Key, T>(8,1));
                _Root = insert(_Root, ft::pair<Key, T>(9,1));
                _Root = insert(_Root, ft::pair<Key, T>(10,1));
                _Root = insert(_Root, ft::pair<Key, T>(-1,1));
                _Root = insert(_Root, ft::pair<Key, T>(-2,1));    
                _Root = insert(_Root, ft::pair<Key, T>(-3,1));
                _Root = insert(_Root, ft::pair<Key, T>(-6,1));
                _Root = insert(_Root, ft::pair<Key, T>(-4,1));
                _Root = insert(_Root, ft::pair<Key, T>(-5,1));
                printTree(_Root, nullptr, false);
                
                _Root = deleteNode(_Root, ft::pair<Key, T>(-5,1));
                printTree(_Root, nullptr, false);
                std::cout << "root->"<< _Root->data->first << std::endl;
                _Root = deleteNode(_Root, ft::pair<Key, T>(9,1));
                printTree(_Root, nullptr, false);
                std::cout << "root->"<< _Root->data->first << std::endl;
                _Root = deleteNode(_Root, ft::pair<Key, T>(8,1));
                printTree(_Root, nullptr, false);
                std::cout << "root->"<< _Root->data->first << std::endl;
                _Root = deleteNode(_Root, ft::pair<Key, T>(10,1));
                printTree(_Root, nullptr, false);
                std::cout << "root->"<< _Root->data->first << std::endl;
                _Root = deleteNode(_Root, ft::pair<Key, T>(-2,1));
                printTree(_Root, nullptr, false);
                std::cout << "root->"<< _Root->data->first << std::endl;
            }
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                
                //need insert with iters
                difference_type diff = std::distance(last, first);
                while (first != last)
                {
                    insert(_Root, first);
                    first++;
                }
                kc = comp;
                al = alloc;
                _size = 0;
            }
            map (const map& x)
            {
                _size = 0;
                *this = x;
            }
            ~map(){
                //clear();
            }
        private:
            size_t  _size;
            size_t  _capacity;
            Alloc   al;
            key_compare kc;

            struct Node {
                value_type *data;
                Node* left;
                Node* right;
                Node* parent;
                int height;
            };

            Node* _Root;
            Node* last_insert;
            Node* not_inserted;
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
                    trunk->str = ".——|";
                    prev_str = "   |";
                }
                else {
                    trunk->str = "`——|";
                    prev->str = prev_str;
                }
            
                showTrunks(trunk);
                std::cout << root->data->first<< "p:" << root->parent->data->first <<std::endl;
            
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
            // Node *tmp;
            Node *x = y->left;
            Node *T2 = x? x->right : NULL;
        
            // Perform rotation
            // if (!x){return y;}
            // just to fix seg fault not working
            if (y == _Root)
                y->parent = y;
            else if (x == _Root)
                x->parent = y;
            x->right = y;
            y->left = T2;

            //update parents
            
            x->parent = y->parent;
            y->parent = x;
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
            // Node *tmp;
            Node *y = x->right;
            Node *T2 = y->left;
        
            // Perform rotation
            // just to fix seg fault not working
            if (y == _Root)
                y->parent = x;
            else if (x == _Root)
                x->parent = x;
            y->left = x;
            x->right = T2;

            //update parents
            
            y->parent = x->parent;
            x->parent = y;
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

        Node *newNode(value_type val)
        {
            Node* newNode = new Node();
            newNode->data = al.allocate(1);
            al.construct(newNode->data, val);
            
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->height = 1;
            _size++;
            return (newNode);
        }
        Node  *balance_tree(Node *node, value_type data)
        {
            //UPDATE HEIGHT OF THE CURRENT NODE
            node->height = 1 + max(height(node->left),
                                height(node->right));

            int balance = getBalance(node);
        
            // If this node becomes unbalanced, then
            // there are 4 cases
        
            // Left Left Case
            if (balance > 1 && kc(data.first, node->left->data->first))
                return rightRotate(node);
        
            // Right Right Case
            if (balance < -1 && !kc(data.first, node->right->data->first))
                return leftRotate(node);
        
            // Left Right Case
            if (balance > 1 && !kc(data.first, node->left->data->first))
            {
                if (node->left->left)
                    return rightRotate(node);
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        
            // Right Left Case
            if (balance < -1 && kc(data.first, node->right->data->first))
            {
                if (node->right->right)
                    return leftRotate(node);
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            return (node);
        }
        // Node  *balance_tree(Node *node, value_type data)
        // {
        //     //UPDATE HEIGHT OF THE CURRENT NODE
        //     node->height = 1 + max(height(node->left),
        //                         height(node->right));

        //     int balance = getBalance(node);
        
        //     // If this node becomes unbalanced, then
        //     // there are 4 cases
        
        //     // Left Left Case
        //     if (balance > 1 && data.first < node->left->data->first)
        //         return rightRotate(node);
        
        //     // Right Right Case
        //     if (balance < -1 && data.first > node->right->data->first)
        //         return leftRotate(node);
        
        //     // Left Right Case
        //     if (balance > 1 &&data.first > node->left->data->first)
        //     {
               
        //         node->left = leftRotate(node->left);
        //         return rightRotate(node);
        //     }
        
        //     // Right Left Case
        //     if (balance < -1 && data.first < node->right->data->first)
        //     {
                
        //         node->right = rightRotate(node->right);
        //         return leftRotate(node);
        //     }
        //     return (node);
        // }

        Node  *insert(Node *node,const value_type& data){
                
            //node is root here
            //need a rebind and allocation
            if(node == NULL){
                Node *n = newNode(data);
                node = n;
                last_insert = n;
                return node;
            }
            if(kc(data.first, node->data->first)){
                node->left = insert(node->left, data);
                node->left->parent = node;
            }else if(!kc(data.first, node->data->first)){
                node->right = insert(node->right, data);
                node->right->parent = node;
            }
            //to know if not inserted
            else{
                not_inserted = node;
                return node;
            }
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
        Node* deleteNode(Node* root,const value_type& data)
        {
            
            // STEP 1: PERFORM STANDARD BST DELETE
            if (root == NULL)
                return root;
            // If the data to be deleted is smaller
            // than the root's data, then it lies
            // in left subtree
            if ( data.first < root->data->first )
                root->left = deleteNode(root->left, data);
        
            // If the data to be deleted is greater
            // than the root's data, then it lies
            // in right subtree
            else if(kc(root->data->first, data.first))
                root->right = deleteNode(root->right, data);
        
            // if data is same as root's data, then
            // This is the node to be deleted
            else
            {
                // node with only one child or no child
                if( (root->left == NULL) || (root->right == NULL) )
                {
                    Node *temp = newNode(data);
                    temp = root->left ? root->left : root->right;
        
                    // No child case
                    if (temp == NULL)
                    {
                        temp = root;
                        root = NULL;
                    }
                    else // One child case
                        *root = *temp; // Copy the contents of
                                // the non-empty child
                    // al.deallocate(temp->data, 1);
                    //needs to be changed to free
                    temp = nullptr;
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
                    root->right = deleteNode(root->right, *temp->data);
                }
            }
        
            // If the tree had only one node
            // then return
            if (root == NULL)
                return root;
            
            return (balance_tree(root, data));
            // _Root = root;
            return root;
        }

        public:
            typedef typename ft::map_iter<Node, value_type, Compare> iterator;
            typedef typename ft::map_iter<Node, value_type, Compare> const_iterator;
            // typedef typename Alloc rebind<Node>::other node_allocator;
        // const_iterator begin() const{return ();}
        pair<iterator,bool> insert (const value_type& val)
        {
            size_t s = _size;
            _Root = insert(_Root, val);
            if (s == _size)
                return(make_pair(iterator(not_inserted, false)));
            else
                return(make_pair(iterator(last_insert, true)));
        }
    };

}