#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

namespace ariel
{
    enum kinds
    {
        INORDER,
        PREORDER,
        POSTORDER
    };
    template <typename T>
    class BinaryTree
    {
    private:
        class Node
        {
        public:
            T data = 0;
            Node *right = nullptr;
            Node *left = nullptr;

            Node(const T &value) : data(value) {}

            Node(Node *newNode, const Node *n) //deep copy tree
            {
                if (n == nullptr)
                {
                    newNode = nullptr;
                }
                else
                {
                    newNode = new Node(n->data);
                    Node(newNode->left, n->left);
                    Node(newNode->right, n->right);
                }
            }
            ~Node()
            {
                if (left != nullptr)
                {
                    delete left;
                }
                if (right != nullptr)
                {
                    delete right;
                }
            }
        };

    public:
        BinaryTree() {}
        ~BinaryTree()
        {
            if (root != nullptr)
            {
                delete root;
            }
        };

        Node *root = nullptr;

        class Iterator
        {
            std::vector<Node *> vec;
            unsigned int pointInVector = 0;
            void PREORDERff(kinds type, Node *n);
            void INORDERff(kinds type, Node *n);
            void POSTORDERff(kinds type, Node *n);

        public:
            Iterator(kinds type = INORDER, Node *n = nullptr)
            {
                if (type == POSTORDER)
                {
                    POSTORDERff(type, n);
                }
                if (type == PREORDER)
                {
                    PREORDERff(type, n);
                }
                if (type == INORDER)
                {
                    INORDERff(type, n);
                }

                vec.push_back(nullptr);
            }
            Iterator operator++(int)
            {
                Iterator it = *this;
                pointInVector++;
                return it;
            }
            Iterator &operator++()
            {
                pointInVector++;
                return *this;
            }

            T &operator*() const { return vec[pointInVector]->data; }

            T *operator->() const { return &(vec[pointInVector]->data); }

            bool operator!=(Iterator const &o)
            {
                return !(vec[pointInVector] == o.vec[o.pointInVector]);
            }

            bool operator==(Iterator const &o)
            {
                return vec[pointInVector] == o.vec[o.pointInVector];
            }
        };
        //from the example https://www.geeksforgeeks.org/search-a-node-in-binary-tree/
        Node *find(Node *n, T value) //find if there is in the tree node have this value.if so return pointer to this node else return nullptr.
        {

            if (n == nullptr)
            {
                return nullptr;
            }

            if (n->data == value)
            {
                return n;
            }
            Node *right_node = find(n->right, value);
            if (right_node != nullptr)
            {
                return right_node;
            }

            Node *left_node = find(n->left, value);
            return left_node;
        }

        BinaryTree(const BinaryTree &b)
        {
            if (b.root == nullptr)
            {
                this->root = nullptr;
            }
            else
            {
                Node(this->root, b.root);
            }
        }

        BinaryTree &operator=(const BinaryTree &b)
        {
            if (this == &b)
            {
                return *this;
            }
            delete (this->root);
            this->root = new Node(b.root->data);
            return *this;
        }

     
        BinaryTree &add(const T &to_find, const T &value, int x)
        {

            if (find(root, to_find) == nullptr)
            {
                throw std::invalid_argument("this value does not exist in the tree ");
            }
            if (x == 1)
            {
                if (find(root, to_find)->right == nullptr)
                {
                    find(root, to_find)->right = new Node(value);
                }
                else
                {
                    find(root, to_find)->right->data = value;
                }
            }
            else
            {
                if (find(root, to_find)->left == nullptr)
                {
                    find(root, to_find)->left = new Node(value);
                }
                else
                {
                    find(root, to_find)->left->data = value;
                }
            }
            return *this;
        }
        BinaryTree &add_right(const T &to_find, const T &value)
        {
            return add(to_find, value, 1);
        }
        BinaryTree &add_left(const T &to_find, const T &value)
        {
            return add(to_find, value, 0);
            ;
        }
        BinaryTree<T> &add_root(const T &value)
        {
            if (root == nullptr)
            {
                root = new Node(value);
            }
            else
            {
                root->data = value;
            }
            return *this;
        }

        Iterator begin_postorder()
        {
            return Iterator(POSTORDER, root);
        }

        Iterator begin_inorder()
        {
            return Iterator(INORDER, root);
        }

        Iterator begin_preorder()
        {
            return Iterator(PREORDER, root);
        }
        Iterator end_postorder()
        {
            return Iterator();
        }

        Iterator end_preorder()
        {
            return Iterator();
        }

        Iterator end_inorder()
        {
            return Iterator();
        }

        Iterator begin()
        {
            return begin_inorder();
        }

        Iterator end()
        {
            return end_inorder();
        }
    };

    template <typename T>
    void ariel::BinaryTree<T>::Iterator::PREORDERff(kinds type, Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (type == PREORDER)
        {
            vec.push_back(node);
        }
        PREORDERff(type, node->left);
        PREORDERff(type, node->right);
    }

    template <typename T>
    void ariel::BinaryTree<T>::Iterator::INORDERff(kinds type, Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        INORDERff(type, node->left);
        if (type == INORDER)
        {
            vec.push_back(node);
        }
        INORDERff(type, node->right);
    }

    template <typename T>
    void ariel::BinaryTree<T>::Iterator::POSTORDERff(kinds type, Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        POSTORDERff(type, node->left);
        POSTORDERff(type, node->right);
        if (type == POSTORDER)
        {
            vec.push_back(node);
        }
    }

}; // namespace ariel
