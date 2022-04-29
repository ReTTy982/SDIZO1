#pragma once
#include <iostream>
#include <queue>


template <typename T>
class RBTree
{

    enum class Color
    {
        RED,
        BLACK,
        GREY
    };

    struct Node
    {
        T value;

        Color color = Color::RED;

        Node *parent = nullptr;
        Node *left_child = nullptr;
        Node *right_child = nullptr;
    };

    Node *root = nullptr;

    void fix_balance(Node *node);
    void rotateR(Node *node);
    void rotateL(Node *node);
    Node *&get_parent_slot(const Node *node);
    Node *&get_uncle(const Node *node);
    Node *bst_search(const T &value);
    Node *get_succesor( Node *node);
    Node *find_replace(Node *node);
    Node *get_brother(Node *node);
    void eat_children(Node *parent);
    void delete_node(Node *node);
    int count_children(Node *node);
    bool bst_delete(Node *node);
    void delete_fix(Node *node);
    void fix_double_black(Node *node);
    bool has_red_child(Node *node);




public:
    RBTree() = default;
    ~RBTree();

    void push(const T &value);
    bool pop(const T &value);
    void print();
    bool search(const T &value);
};