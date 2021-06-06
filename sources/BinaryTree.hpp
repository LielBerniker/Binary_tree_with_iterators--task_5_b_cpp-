#pragma once
#include <string> // string
#include <map>    // for the map data base
#include <iostream>
#include <vector>    // vector
#include <exception> // hold the exeptions
#include <queue>     // for queue
namespace ariel
{
    const std::string NOT_FOUND = "did not found the correct value to set his son";
    template <typename T>
    class BinaryTree
    {

    public:
        class TreeNode
        {
        private:
            T val;
            TreeNode *left;
            TreeNode *right;

        public:
            TreeNode(const T &val) : val(val), left(nullptr), right(nullptr) {}
            TreeNode(TreeNode &t_node) : val(t_node.get_val()), left(nullptr), right(nullptr)
            {
                if (t_node.get_left() != nullptr)
                {
                    left = new TreeNode(*t_node.get_left());
                }

                if (t_node.get_right() != nullptr)
                {
                    right = new TreeNode(*t_node.get_right());
                }
            }
            ~TreeNode()
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

            TreeNode(TreeNode &&t_node) noexcept
            {
                if (left != nullptr)
                {
                    delete left;
                }
                if (right != nullptr)
                {
                    delete right;
                }
                if (t_node != nullptr)
                {
                    val = t_node.get_val();
                    if (t_node.get_left() != nullptr)
                    {
                        left = new TreeNode(*t_node.get_left());
                    }
                    else
                    {
                        left = nullptr;
                    }
                    if (t_node.get_right() != nullptr)
                    {
                        right = new TreeNode(*t_node.get_right());
                    }
                    else
                    {
                        right = nullptr;
                    }
                    t_node.set_left(nullptr);
                    t_node.set_right(nullptr);
                }
            }
            TreeNode &operator=(TreeNode t_node)
            {
                if (this == &t_node)
                {
                    return *this;
                }
                val = t_node.get_val();
                if (left != nullptr)
                {
                    delete left;
                }
                if (right != nullptr)
                {
                    delete right;
                }

                left = new TreeNode(*t_node.get_left());
                right = new TreeNode(*t_node.get_right());

                return *this;
            }
            TreeNode &operator=(TreeNode &&t_node) noexcept
            {
                val = t_node.get_val();
                if (left != nullptr)
                {
                    delete left;
                }
                if (right != nullptr)
                {
                    delete right;
                }
                left = t_node.get_left();
                right = t_node.get_right();
                t_node.set_left = nullptr;
                t_node.set_right = nullptr;
                return *this;
            }
            T &get_val()
            {
                return val;
            }
            void set_val(const T &val_temp)
            {
                val = val_temp;
            }
            void add_left_child(const T &p)
            {

                if (left == nullptr)
                {
                    TreeNode *node_n = new TreeNode(p);
                    left = node_n;
                }
                else
                {
                    this->left->set_val(p);
                }
            }
            void add_right_child(const T &p)
            {

                if (right == nullptr)
                {
                    TreeNode *node_n = new TreeNode(p);
                    right = node_n;
                }
                else
                {
                    this->right->set_val(p);
                }
            }
            void set_left(TreeNode *left_n)
            {
                left = left_n;
            }
            void set_right(TreeNode *right_n)
            {
                right = right_n;
            }
            TreeNode *get_left() { return (left); }
            TreeNode *get_right() { return (right); }
        };

        class iterator_preorder
        {
        private:
            TreeNode *cur_node;
            std::queue<TreeNode *> order;
            void fill_queue(TreeNode *v)
            {
                if (v != nullptr)
                {
                    order.push(v);
                    fill_queue(v->get_left());
                    fill_queue(v->get_right());
                }
            }

        public:
            iterator_preorder(TreeNode *v)
            {
                cur_node = nullptr;
                fill_queue(v);
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
            }
            iterator_preorder &operator++()
            {
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
                else
                {
                    cur_node = nullptr;
                }
                return *this;
            }
            iterator_preorder operator++(int)
            {
                iterator_preorder temp = *this;
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
                else
                {
                    cur_node = nullptr;
                }
                return temp;
            }
            T &operator*() const
            {
                return cur_node->get_val();
            }
            bool operator!=(const iterator_preorder &other) const
            {
                return cur_node != other.cur_node;
            }
            bool operator==(const iterator_preorder &other) const
            {
                return cur_node == other.cur_node;
            }
            const T *operator->() const
            {
                return &(cur_node->get_val());
            }
        };

        class iterator_inorder
        {
        private:
            TreeNode *cur_node;
            std::queue<TreeNode *> order;
            void fill_queue(TreeNode *v)
            {
                if (v != nullptr)
                {
                    fill_queue(v->get_left());
                    order.push(v);
                    fill_queue(v->get_right());
                }
            }

        public:
            iterator_inorder(TreeNode *v)
            {
                cur_node = nullptr;
                fill_queue(v);
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
            }
            iterator_inorder &operator++()
            {
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
                else
                {
                    cur_node = nullptr;
                }
                return *this;
            }
            iterator_inorder operator++(int)
            {
                iterator_inorder temp = *this;
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
                else
                {
                    cur_node = nullptr;
                }
                return temp;
            }
            T &operator*() const
            {
                return cur_node->get_val();
            }
            bool operator!=(const iterator_inorder &other) const
            {
                return (cur_node != other.cur_node);
            }
            bool operator==(const iterator_inorder &other) const
            {
                return cur_node == other.cur_node;
            }
            const T *operator->() const
            {
                return &(cur_node->get_val());
            }
        };

        class iterator_postorder
        {
        private:
            TreeNode *cur_node;
            std::queue<TreeNode *> order;
            void fill_queue(TreeNode *v)
            {
                if (v == nullptr)
                {
                    return;
                }
                fill_queue(v->get_left());
                fill_queue(v->get_right());
                order.push(v);
            }

        public:
            iterator_postorder(TreeNode *v)
            {
                cur_node = nullptr;
                fill_queue(v);
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
            }
            iterator_postorder &operator++()
            {
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
                else
                {
                    cur_node = nullptr;
                }
                return *this;
            }
            iterator_postorder operator++(int)
            {
                iterator_postorder temp = *this;
                if (!order.empty())
                {
                    cur_node = order.front();
                    order.pop();
                }
                else
                {
                    cur_node = nullptr;
                }
                return temp;
            }
            T &operator*()
            {
                return cur_node->get_val();
            }
            bool operator!=(const iterator_postorder &other) const
            {
               
                return cur_node != other.cur_node;
            }
            bool operator==(const iterator_postorder &other) const
            {
                return cur_node == other.cur_node;
            }
            const T *operator->()
            {
                return &(cur_node->get_val());
            }
        };
        BinaryTree()
        {
            root = nullptr;
            find = false;
        }
        BinaryTree(BinaryTree &btree)
        {
            if (!root)
            {
                delete root;
            }
            root = btree.get_root();
            find = false;
        }
        BinaryTree(BinaryTree &&btree) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = btree.get_root();
            btree.set_root(nullptr);
            find = false;
        }
        ~BinaryTree()
        {
            if (root != nullptr)
            {
                delete root;
            }
        }
        BinaryTree &operator=(BinaryTree other)
        {
            if (root == other.get_root())
            {
                return *this;
            }
            if (other.get_root() == nullptr)
            {
                root = nullptr;
            }
            else
            {
                if (root != nullptr)
                {
                    delete root;
                }
                root = new TreeNode(*other.get_root());
            }

            find = false;
            return *this;
        }
        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = other.get_root();
            other.set_root(nullptr);
            find = false;
            return *this;
        }
        BinaryTree &add_root(T val)
        {
            if (root == nullptr)
            {
                TreeNode *t_Node = new TreeNode(val);
                root = t_Node;
            }
            else
            {
                root->set_val(val);
            }

            return *this;
        }
        BinaryTree &add_left(T current, T left_son)
        {
            find = false;
            if (!edit_son(1, current, left_son, root))
            {

                throw std::invalid_argument(NOT_FOUND);
            }

            return *this;
        }
        void set_root(TreeNode *root_n)
        {
            root = root_n;
        }
        BinaryTree &add_right(T current, T right_son)
        {

            find = false;
            if (!edit_son(0, current, right_son, root))
            {

                throw std::invalid_argument(NOT_FOUND);
            }

            return *this;
        }
        iterator_inorder begin()
        {
            return begin_inorder();
        }
        iterator_inorder end()
        {
            return end_inorder();
        }
        iterator_preorder begin_preorder()
        {
            return iterator_preorder{root};
        }
        iterator_preorder end_preorder()
        {
            return iterator_preorder{nullptr};
        }
        iterator_inorder begin_inorder()
        {
            return iterator_inorder{root};
        }
        iterator_inorder end_inorder()
        {
            return iterator_inorder{nullptr};
        }
        iterator_postorder begin_postorder()
        {
            return iterator_postorder{root};
        }
        iterator_postorder end_postorder()
        {
            return iterator_postorder{nullptr};
        }
        friend std::ostream &operator<<(std::ostream &out, BinaryTree<T> &btree)
        {
            return out;
        }
        TreeNode *get_root() const
        {
            return root;
        }

    private:
        TreeNode *root;
        bool find;
        bool edit_son(int son, T val_exist, T val_n, TreeNode *current)
        {
            if (find || current == nullptr)
            {
                return false;
            }
            if (current->get_val() == val_exist || edit_son(son, val_exist, val_n, current->get_left()) || edit_son(son, val_exist, val_n, current->get_right()))
            {
                if (current->get_val() == val_exist)
                {
                    find = true;
                    if (son == 1)
                    {
                        current->add_left_child(val_n);
                    }
                    else
                    {
                        current->add_right_child(val_n);
                    }
                }
                return true;
            }
            return false;
        }
    };
}
