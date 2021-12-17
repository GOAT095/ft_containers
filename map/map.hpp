#pragma once

#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
#include "../vector/Vector.hpp"
#include "../vector/reverse_iterator.hpp"
#include "map-utils.hpp"
#include "map_iter.hpp"

namespace ft{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class Map
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
            class value_compare
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
                friend class map;
                protected:
                    Compare comp;
                public:
                value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
                // value_compare(const value_compare& rhs){comp = rhs.comp;}
                public:
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
            };
            // typedef value_compare value_comp;
            explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                _size = 0;
                al = alloc;
                kc = comp;
                _Root = NULL;
            }
            template <class InputIterator>
            Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            { 
                _size = 0;
                al = alloc;
                kc = comp;
                this->insert(first, last);
            }
            ~Map(){
                clear();
            }
        private:
            size_t  _size;
            Alloc   al;
            // value_compare _value_comp;
            key_compare kc;

            struct Node {
                value_type *data;

                Node* left;
                Node* right;
                Node* parent;
                int height;
            };
            typename Alloc::template rebind<Node>::other aloc;
            Node* _Root;
            // Node* end;
            Node* last_insert;
            Node* not_inserted;
            public:
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
            Node    *getRoot()
            {
                return _Root;
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
                std::cout << root->data->first;
                if (root->parent)
                    std::cout << "p:"<< root->parent->data->first <<std::endl;
                else
                    std::cout <<std::endl;
                if (prev) {
                    prev->str = prev_str;
                }
                trunk->str = "   |";
            
                printTree(root->left, trunk, false);
            }
            private:
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
            Node *T2 = x->right;
        
            // Perform rotation
            // if (!x){return y;}
            // just to fix seg fault not working

            
            // if (x == _Root)
            //     x->parent = y;
            if (x->right)
                x->right->parent = y;
            x->right = y;
            y->left = T2;

            //update parents
            
            x->parent = y->parent;
            y->parent = x;
            // Update heights
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;
        
            // Return new root
            // _Root->parent = _Root; 
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
            // if (x == _Root)
            //     x->parent = x;
            if (y->left)
                y->left->parent = x;
            y->left = x;
            x->right = T2;

            //update parents
            
            y->parent = x->parent;
            x->parent = y;
            // Update heights
            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) + 1;
        
            // Return new root
            // _Root->parent = _Root;
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
            Node* newNode = aloc.allocate(1);
            newNode->data = al.allocate(1);
            al.construct(newNode->data, val);
            
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->height = 1;
            newNode->parent = NULL;
            _size++;
            return (newNode);
        }
        Node  *balance_tree_delete(Node *node, value_type data)
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
                if (node->left->left) //just right rotate node 
                    return rightRotate(node);
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        
            // Right Left Case
            if (balance < -1 && kc(data.first, node->right->data->first))
            {
                if (node->right->right) //just left rotate node 
                    return leftRotate(node);
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            // _Root->parent = _Root; 
            return (node);
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
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        
            // Right Left Case
            if (balance < -1 && kc(data.first, node->right->data->first))
            {
                
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            return (node);
        }

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
            }else if(kc(node->data->first, data.first)){
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
            while (current &&current->left != NULL)
                current = current->left;
        
            return current;
        }
        Node * maxValueNode(Node* node) 
        {
            Node* current = node;
        
            /* loop down to find the leftmost leaf */
            while (current && current->right != NULL)
                current = current->right;
        
            return current;
        }
        Node * minValueNode(Node* node) const
        {
            Node* current = node;
        
            /* loop down to find the leftmost leaf */
            while (current &&current->left != NULL)
                current = current->left;
        
            return current;
        }
        Node * maxValueNode(Node* node) const
        {
            Node* current = node;
        
            /* loop down to find the leftmost leaf */
            while (current && current->right != NULL)
                current = current->right;
        
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
            if (kc(data.first, root->data->first))
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
                    Node *tmp = root->parent;
                    temp = root->left ? root->left : root->right;
                    // No child case
                    if (temp == NULL)
                    {
                        temp = root;
                        root = NULL;
                    }
                    
                    else // One child case
                    {
                       *root = *temp;
                       root->parent = tmp;

                    } // Copy the contents of
                                // the non-empty child
                    // al.deallocate(temp->data, 1);
                    //needs to be changed to free

                    al.destroy(temp->data);
                    aloc.destroy(temp);
                    temp= NULL;
                    
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
                _size--;
                
            }

            // If the tree had only one node
            // then return
            if (root == NULL)
                return root;
            return(balance_tree_delete(root, data));
        }
        Node* search(Node *node, const key_type& first)const 
        {
            if (node == NULL)
                return NULL;
            if(kc(first, node->data->first)){
                node =search(node->left, first);
            
            }else if(kc(node->data->first, first)){
                node = search(node->right, first);
            }
            return node;
        }

        public:
            typedef typename ft::map_iter<Node, value_type, Compare> iterator;
            typedef typename ft::map_iter<Node, const value_type, Compare> const_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            // typedef typename Alloc rebind<Node>::other node_allocator;

        iterator begin(){return (iterator(minValueNode(_Root), _Root));}
        const_iterator begin() const{return (const_iterator(minValueNode(_Root), _Root));}
        iterator end(){return(iterator(NULL, _Root, maxValueNode(_Root)));}
        const_iterator end() const{return(const_iterator(NULL, _Root, maxValueNode(_Root)));}

        reverse_iterator rend(){return(reverse_iterator(begin()));}
        const_reverse_iterator rend() const{return(const_reverse_iterator(begin()));}
        
        reverse_iterator rbegin(){return(reverse_iterator(end()));}
        const_reverse_iterator rbegin()const {return(const_reverse_iterator(end()));}
        
        //capacity
        size_type max_size() const{return al.max_size();}
        size_type size() const{return _size;}
        bool empty() const{return (_size == 0);}
        //inserts
        pair<iterator,bool> insert (const value_type& val)
        {
            size_t s = _size;
            _Root = insert(_Root, val);
            if (s == _size)
                return(ft::make_pair(iterator(not_inserted,_Root), false));
            else
            {   
                // _size++; 
                return(ft::make_pair(iterator(last_insert,_Root), true));
            }
        }
        // this one is weird just ignore position param
        void insert (iterator position, const value_type& val)
        {
            (void) position;
            insert(val);

        }
        template <class InputIterator>

        void insert (InputIterator first, InputIterator last)
        {
            while (first != last)
            {
               insert(*first);
                first++;
            }
        }
        //erases
        size_type erase (const key_type& k)
        {
            
            _Root = deleteNode(_Root, ft::make_pair(k,mapped_type()));
            return (_size);
        }
        void erase (iterator position)
        {
            erase(position->first);
        }
        void erase (iterator first, iterator last)
        {
            size_t i = 0;
            ft::Vector<key_type> vec;
            
            if (first == last)
                return ;
            while (first != last)
            {
                // ft::Map<key_type> vec;
                vec.push_back(first.getNode()->data->first);
                first++;
            }
            while (i < vec.size())
            {
                
                erase(vec[i]);
                std::cout << vec[i] << ">" << _size << std::endl;
                i++;
            }
        }
        void swap (Map& x)
        {
            std::swap(_size, x._size);
            std::swap(_Root, x._Root);
            std::swap(kc, x.kc);

        }
        //element access
        mapped_type& operator[] (const key_type& k)
        {
            return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
        }

        //modifiers
        void clear()
        {
            erase(begin(), end());
        }

        key_compare key_comp() const{return (kc);}

        allocator_type get_allocator() const{return al;}
        

        size_type count(const key_type& k) const
        {
            if(search(_Root, k))
            {
                return 1;
            }
            return 0;
        }
        iterator find(const key_type& k)
        {
            return (iterator(search(_Root, k), _Root));
        }
        const_iterator find (const key_type& k) const
        {
            return (const_iterator(search(_Root, k), _Root));
        }
        iterator lower_bound (const key_type& k)
        {
            iterator it;
            for(it = begin(); it != end(); it++)
            {
                if(it->first > k)
                    return(it);
                else if(it->first == k)
                    return it;
            }
            return (end());
        }

        const_iterator lower_bound (const key_type& k)const
        {
            const_iterator it;
            for(it = begin(); it != end(); it++)
            {
                if(it->first > k)
                    return(it);
                else if(it->first == k)
                    return it;
            }
            return (end());
        }

        iterator upper_bound (const key_type& k)
        {
            iterator it;

            
            for(it = begin(); it != end(); it++)
            {
                if(it->first == k)
                {   it++; return it;}
            }
            return (end());
        }
        const_iterator upper_bound (const key_type& k) const
        {
            const_iterator it;

            
            for(it = begin(); it != end(); it++)
            {
                if(it->first == k)
                {   it++; return it;}
            }
            return (end());
        }
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        pair<iterator,iterator> equal_range (const key_type& k)
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        value_compare value_comp() const
        {
            return (value_compare(kc));
        }
    };
    //relational operators
    template <class Key, class T, class Compare, class Alloc>
    bool operator== (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs)
    {
        return(!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator> (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs)
    {
        return(rhs < lhs);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator<= (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs < rhs || lhs == rhs)
            return(true);
        return (false);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return(true);
        return (false);
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
}