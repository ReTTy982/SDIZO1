#include "RBTree.hpp"
#include <iostream>
#include <queue>

#define REDBG "\x1B[41m"
#define RESETBG "\x1B[0m"

template <typename T>
void RBTree<T>::eat_children(Node *parent)
{

    if (parent->left_child)
        eat_children(parent->left_child);
    if (parent->right_child)
        eat_children(parent->right_child);

    delete parent;
}

template <typename T>
RBTree<T>::~RBTree()
{
    if (root)
    {
        eat_children(root);
    }
}

template <typename T>
void RBTree<T>::push(const T &value)
{
    if (!root)
    {
        // std::cout << "No root, making new" << std::endl;

        Node *node = new Node();
        node->value = value;
        node->color = Color::BLACK;
        root = node;
    }
    else
    {
        /* BACZEK TUTAJ
        Node *browse = root;

        // std::cout << "Our hero ascends into the pit of red-black madness. What "
        //"will he find in the depths?"
        //<< std::endl;

        Node *last_not_null = browse;
        while (browse != nullptr)
        {
            last_not_null = browse;
            if (browse->value > value)
            {
                browse = browse->left_child;
            }
            else
            {
                browse = browse->right_child;
            }
        }

        // std::cout << "Done with downwards traversal" << std::endl;

        Node *node = new Node();
        node->value = value;
        node->parent = last_not_null;

        if (last_not_null->value > value)
        {
            last_not_null->left_child = node;
        }
        else
        {
            last_not_null->right_child = node;
        }

        // std::cout << "As all things should be" << std::endl;
        fix_balance(node);
        */
        Node **browse = &root;
        Node *parent;

        while (*browse)
        {
            parent = *browse;

            if (parent->value > value)
            {
                browse = &parent->left_child;
            }
            else
            {
                browse = &parent->right_child;
            }
        }

        Node *node = new Node;
        node->value = value;
        node->parent = parent;
        *browse = node;

        fix_balance(node);
    }
}
/*
template <typename T>
void RBTree<T>::fix_balance(Node *node)
{
    // std::cout << "Establishing balance" << std::endl;

    if (node->parent == root)
    {
        // std::cout << "Twój stary korzeń" << std::endl;
    }
    if (node->parent->color == Color::RED)
    {
        // std::cout << "Twój stary czerwony" << std::endl;
    }
    else
    {
        // std::cout << "Twój stary czarny" << std::endl;
    }

    while (node != root &&
           node->parent->color ==
               Color::RED) // Ojciec nie jest czarny a wezel nie jest korzeniem
    {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;

        Node *uncle = get_uncle(parent);

        if (!uncle || uncle->color == Color::BLACK) // Wujek jest czarny/NIL
        {
            // Najpierw musimy przejsc z przypadku trójkątnego do liniowego
            if (parent->value < node->value &&
                grandparent->value >
                    node->value) // wierzcholek trojkata skierowany w lewo
            {
                rotateL(node);

                node = node->left_child;
                parent = node->parent;
                grandparent = parent->parent;
            }
            else if (parent->value > node->value &&
                     grandparent->value <
                         node->value) // wierzcholek traojkata skierowany w prawo
            {
                rotateR(node);

                node = node->right_child;
                parent = node->parent;
                grandparent = parent->parent;
            }

            // zmieniam kolory zanim nadpisze zmienne kolejna rotacja
            parent->color = Color::BLACK;
            node->color = Color::RED;
            grandparent->color = Color::RED;

            // rotacja z przypadku liniowego
            if (parent->left_child == node)
            {

                rotateR(parent);
            }
            else
            {
                rotateL(parent);
            }
            break;
        }

        // Przypadek kiedy wujaszek jest czerwony
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;
        node = grandparent;
    }

    root->color = Color::BLACK; // korzen zawsze bedzie czarny wiec jest to
                                // ostatni krok funkcji
}*/

template <typename T>
void RBTree<T>::fix_balance(Node *node)
{
    while (node != root && node->parent->color == Color::RED) // Ojciec nie jest czarny a wezel nie jest korzeniem
    {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;
        Node *uncle = get_uncle(parent);

        if (!uncle || uncle->color == Color::BLACK) // Wujek jest czarny/NIL
        {
            // Najpierw musimy przejsc z przypadku trójkątnego do liniowego
            if (parent->value < node->value && grandparent->value > node->value) // wierzcholek trojkata skierowany w lewo
            {
                rotateL(parent);
                
                node = node->left_child;
                parent = node->parent;
                grandparent = parent->parent;
                
            }
            else if (parent->value > node->value && grandparent->value < node->value) // wierzcholek traojkata skierowany w prawo
            {
                rotateR(parent);
                
                node = node->right_child;
                parent = node->parent;
                grandparent = parent->parent;
                
            }

            // zmieniam kolory zanim nadpisze zmienne kolejna rotacja
            parent->color = Color::BLACK;
            node->color = Color::RED;
            grandparent->color = Color::RED;

            // rotacja z przypadku liniowego
            if (parent->left_child == node)
            {

                rotateR(grandparent);
            }
            else
            {
                rotateL(grandparent);
            }
            break;
        }

        // Przypadek kiedy wujaszek jest czerwony
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;
        node = grandparent;
    }

    root->color = Color::BLACK; // korzen zawsze bedzie czarny wiec jest to ostatni krok funkcji
}

template <typename T>
inline auto RBTree<T>::get_parent_slot(const RBTree<T>::Node *node)
    -> RBTree<T>::Node *&
{
    if (node == root)
    {
        return root;
    }
    else
    {
        if (node->parent->left_child == node)
        {
            return node->parent->left_child;
        }
        else
        {
            return node->parent->right_child;
        }
    }
}

template <typename T>
inline auto RBTree<T>::get_uncle(const RBTree<T>::Node *node)
    -> RBTree<T>::Node *&
{
    if (node->parent->left_child == node)
    {
        return node->parent->right_child;
    }
    else
    {
        return node->parent->left_child;
    }
}

template <typename T>
inline auto RBTree<T>::get_succesor(RBTree<T>::Node *node) -> RBTree<T>::Node *
{
    while (node->left_child != nullptr)
    {
        node = node->left_child;
    }
    return node;
}


template <typename T>
void RBTree<T>::rotateR(RBTree<T>::Node *node)
{
    // new parent will be node's left child
    Node *new_parent = node->left_child;

    // update root if current node is root
    if (node == root)
        root = new_parent;

    if (node->parent != NULL)
    {
        if (node->parent->left_child == node)
        {
            node->parent->left_child = new_parent;
        }
        else
        {
            node->parent->right_child = new_parent;
        }
    }
    new_parent->parent = node->parent;
    node->parent = new_parent;

    // connect x with new parent's right element
    node->left_child = new_parent->right_child;
    // connect new parent's right element with node
    // if it is not null
    if (new_parent->right_child != nullptr)
        new_parent->right_child->parent = node;

    // connect new parent with x
    new_parent->right_child = node;
}

template <typename T>
void RBTree<T>::rotateL(RBTree<T>::Node *node)
{
    // new parent will be node's left child
    Node *new_parent = node->right_child;

    // update root if current node is root
    if (node == root)
        root = new_parent;

    if (node->parent != NULL)
    {
        if (node->parent->left_child == node)
        {
            node->parent->left_child = new_parent;
        }
        else
        {
            node->parent->right_child = new_parent;
        }
    }
    new_parent->parent = node->parent;
    node->parent = new_parent;

    // connect x with new parent's right element
    node->right_child = new_parent->left_child;
    // connect new parent's right element with node
    // if it is not null
    if (new_parent->left_child != nullptr)
        new_parent->left_child->parent = node;

    // connect new parent with x
    new_parent->left_child = node;
}


template <typename T>
void RBTree<T>::print()
{
    if (!root)
        return;

    std::queue<Node *> kolejka, kolejka2;

    Node *empty = new Node();

    int pow = 1, row = 0;

    kolejka.push(root);
    kolejka2.push(root);
    while (!kolejka2.empty())
    {
        if (kolejka.front() == empty)
            std::cout << "N";
        else if (kolejka.front()->color == Color::RED)
            std::cout << REDBG << kolejka.front()->value << RESETBG;
        else
            std::cout << kolejka.front()->value;

        std::cout << " ";

        if (++row == pow)
        {
            std::cout << std::endl;
            row = 0;
            pow *= 2;
        }

        if (kolejka.front()->left_child)
        {
            kolejka.push(kolejka.front()->left_child);
            kolejka2.push(kolejka.front()->left_child);
        }
        else
            kolejka.push(empty);

        if (kolejka.front()->right_child)
        {
            kolejka.push(kolejka.front()->right_child);
            kolejka2.push(kolejka.front()->right_child);
        }
        else
            kolejka.push(empty);

        if (kolejka.front() != empty)
            kolejka2.pop();

        kolejka.pop();
    }

    if (row != 0)
    {
        while (row++ < pow)
        {
            std::cout << "N ";
        }
    }

    std::cout << std::endl;

    delete empty;
}

template <typename T>
bool RBTree<T>::search(const T &value)
{
    const Node *search = root;
    while (search && search->value != value)
    {
        if (search->value > value)
            search = search->left_child;
        else
            search = search->right_child;
    }

    if (search)
        return true;

    return false;
}

template <typename T>
bool RBTree<T>::pop(const T &value)
{
    Node *search = bst_search(value);
    delete_node(search);
    return true;

}

template <typename T>
inline auto RBTree<T>::bst_search(const T &value) -> RBTree<T>::Node *
{
    Node *search = root;
    while (search && search->value != value)
    {
        if (search->value > value)
            search = search->left_child;
        else
            search = search->right_child;
    }
    return search;
}

template <typename T>
inline auto RBTree<T>::get_brother(Node *node) -> RBTree<T>::Node *
{
    if (node->parent == nullptr)
    {
        return nullptr;
    }
    if (node->parent->left_child == node)
    {

        return node->parent->right_child;
    }
    else
    {

        return node->parent->left_child;
    }
}


template <typename T>
void RBTree<T>::delete_node(Node *node)
{
    Node *replacement = find_replace(node);
    Node *parent = node->parent;
    Node *brother = get_brother(node);
    bool both_black;
    if ((replacement == nullptr || replacement->color == Color::BLACK) && (node->color == Color::BLACK))
    {
        both_black = true;
    }
    else
    {
        both_black = false;
    }
    if (replacement == nullptr)
    {
        if (node == root)
        {
            root = nullptr;
        }
        else
        {

            if (both_black)
            {

                fix_double_black(node);
            }
            else
            {

                if (brother != nullptr)
                {
                    brother->color = Color::RED;
                }
            }

            if (node->parent->left_child == node)
            {
                parent->left_child = nullptr;
            }
            else
            {

                parent->right_child = nullptr;
            }
        }
        delete node;
        return;
    }

    if (node->left_child == nullptr || node->right_child == nullptr)
    {
        if (node == root)
        {
            node->value = replacement->value;
            node->left_child = node->right_child = nullptr;
            delete replacement;
        }
        else
        {
            if (node->parent->left_child == node)
            {
                parent->left_child = replacement;
            }
            else
            {
                parent->right_child = replacement;
            }
            delete node;
            replacement->parent = parent;
            if (both_black)
            {
                fix_double_black(replacement);
            }
            else
            {
                replacement->color = Color::BLACK;
            }
        }
        return;
    }
    T temp;
    temp = replacement->value;
    replacement->value = node->value;
    node->value = temp;
    delete_node(replacement);
}

template <typename T>
void RBTree<T>::fix_double_black(Node *node)
{
    if (node == root)
    {
        return;
    }

    Node *brother = get_brother(node);

    Node *parent = node->parent;

    if (brother == nullptr)
    {

        fix_double_black(parent);
    }
    else
    {

        if (brother->color == Color::RED)
        {
            parent->color = Color::RED;
            brother->color = Color::BLACK;
            if (brother->parent->left_child == brother)
            {
                rotateR(parent);
            }
            else
            {
                rotateL(parent);
            }
            fix_double_black(node);
        }
        else
        {

            if (has_red_child(brother))
            {

                if (brother->left_child != nullptr && brother->left_child->color == Color::RED)
                {

                    if (brother->parent->left_child == brother)
                    {

                        brother->left_child->color = brother->color;

                        brother->color = parent->color;

                        rotateR(parent);
                    }
                    else
                    {

                        brother->left_child->color = parent->color;
                        rotateR(brother);
                        rotateL(parent);
                    }
                }
                else
                {
                    if (brother->parent->left_child == brother)
                    {
                        brother->right_child->color = parent->color;
                        rotateL(brother);
                        rotateR(parent);
                    }
                    else
                    {
                        brother->right_child->color = brother->color;
                        brother->color = parent->color;
                        rotateL(parent);
                    }
                }

                parent->color = Color::BLACK;
            }
            else
            {

                brother->color = Color::RED;
                if (parent->color == Color::BLACK)
                {
                    fix_double_black(parent);
                }
                else
                {
                    parent->color = Color::BLACK;
                }
            }
        }
    }
}
template <typename T>
bool RBTree<T>::has_red_child(Node *node)
{
    if (node->left_child != nullptr && node->left_child->color == Color::RED)
    {
        return true;
    }
    if (node->right_child != nullptr && node->right_child->color == Color::RED)
    {
        return true;
    }
    else
        return false;
}
template <typename T>
inline auto RBTree<T>::find_replace(Node *node) -> RBTree<T>::Node *
{
    if (node->left_child != nullptr && node->right_child != nullptr)
    {
        return get_succesor(node->right_child);
    }

    if (node->left_child == nullptr && node->right_child == nullptr)
    {
        return nullptr;
    }
    if (node->left_child != nullptr)
    {
        return node->left_child;
    }
    else
    {
        return node->right_child;
    }
}





template class RBTree<int>;
