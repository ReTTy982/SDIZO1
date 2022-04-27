#pragma once
#include <iostream>

template <typename T>
class List
{

public:
    struct Node
    {
        T value;
        Node *prev = nullptr;
        Node *next = nullptr;
    };
    List() = default;
    ~List();

    void push_front(const T &data);
    void push_back(const T &data);
    void push(const T &data, Node *&next_node);

    void pop_front();
    void pop_back();
    void pop(const T &val);
    void pop(Node *&node);

    bool search(const T &data);
    Node *get_node(const T &val) const;

    void print();

private:
    Node *head = nullptr;
    Node *tail = nullptr;

};
