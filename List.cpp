#include <iostream>
#include "List.hpp"

template <typename T>
List<T>::~List()
{
    Node *node = head;

    while (node)
    {
        Node *next_del = node->next;

        delete node;
        node = next_del;
    }
}

template <typename T>
void List<T>::push_front(const T &data)
{

    Node *temp = head;

    head = new Node();
    head->value = data;
    head->next = temp;

    if (temp)
    {
        temp->prev = head;
    }
    else
    {
        tail = head;
    }
}

template <typename T>
void List<T>::push_back(const T &data)
{
    Node *node = new Node();
    node->value = data;
    node->prev = tail;

    if (tail)
    {
        tail->next = node;
    }
    else
    {
        head = node;
    }
    tail = node;
}

// next node bedzie po wprowadzonym nodzie
template <typename T>
void List<T>::push(const T &val, Node *&next_node)
{
    if(!next_node){
        throw std::runtime_error("Node does not exist\n");
    }

    Node *node =new Node();
    node->value = val;
    node->prev = next_node->prev;
    node->next = next_node;

    //next node might be head
    if(next_node->prev){
        next_node->prev->next = node;
    }

    next_node->prev = node;
}

template <typename T>
void List<T>::pop_front()
{
    if (!head)
    {
        std::cout << "No items to pop." << std::endl;
        return;
    }

    if (!head->next)
    {
        delete head;

        tail = nullptr;
        head = nullptr;
        return;
    }

    Node *temp = head;
    head = head->next;
    head->prev = nullptr;

    delete temp;
}

template <typename T>
void List<T>::pop_back()
{
    if (!tail)
    {
        std::cout << "No items to pop." << std::endl;
        return;
    }

    if (!tail->prev)
    {
        delete tail;

        tail = nullptr;
        head = nullptr;
        return;
    }

    Node *temp = tail;
    tail = tail->prev;
    tail->next = nullptr;

    delete temp;
}

template <typename T>
void List<T>::pop(const T &val)
{

    auto node = get_node(val);
    return pop(node);
}

template <typename T>
void List<T>::pop(Node *&node)
{
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        // head
        if (node->next)
        {
            head = node->next;
        }
        else
        {
            head = nullptr;
        }
    }

    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        if (node->prev)
        {
            tail = node->prev;
        }
        else
        {
            tail = nullptr;
        }
    }
    delete node;
    node = nullptr;
}

template <typename T>
bool List<T>::search(const T &data) 
{
    Node *node = get_node(data);
    return node;
}

template <typename T>
void List<T>::print()
{
    Node *node = head;

    while (node)
    {
        std::cout << node->value << " ";
        node = node->next;
    }

    std::cout << std::endl;
}

template <typename T>
auto List<T>::get_node(const T &val) const -> List<T>::Node *
{
    Node *node = head;
    while (node)
    {
        if (node->value == val)
        {
            return node;
        }
        node = node->next;
    }
    return nullptr;
}

template class List<int>;