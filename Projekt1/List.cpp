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

    if (temp) // jesli wartosc jest jedynym skladnikiem to jest zarowno poczatkiem jak i koncem listy
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

    if (tail) // Jesli wartosc jest jedynym skladnikiem to jest zarowno koncem jak i poczatkiem
    {
        tail->next = node;
    }
    else
    {
        head = node;
    }
    tail = node;
}

// Nowy wezel zostanie wprowadzony po elemencie node_at
template <typename T>
void List<T>::push(const T &val, Node *&node_at)
{
    if (!node_at)
    {
        throw std::runtime_error("Node does not exist\n");
    }

    Node *node = new Node();
    node->value = val;
    node->prev = node_at->prev;
    node->next = node_at;

    //  Jesli node_at to poczatek listy to znaczy ze wpisany wezel bedzie poczatkiem
    if (node_at->prev)
    {
        node_at->prev->next = node;
    }
    else
    {
        head = node;
    }

    node_at->prev = node;
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
bool List<T>::pop(const T &val)
{

    auto node = get_node(val);
    return pop(node);
}

template <typename T>
bool List<T>::pop(Node *&node)
{
    if(!node){
        return false;
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
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
    return true;
    

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