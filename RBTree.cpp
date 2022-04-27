#include "RBTree.hpp"
#include <iostream>
#include <queue>

#define REDBG "\x1B[41m"
#define RESETBG "\x1B[0m"

template <typename T> void RBTree<T>::eat_children(Node *parent) {

  if (parent->left_child)
    eat_children(parent->left_child);
  if (parent->right_child)
    eat_children(parent->right_child);

  delete parent;
}

template <typename T> RBTree<T>::~RBTree() {
  if (root) {
    eat_children(root);
  }
}

template <typename T> void RBTree<T>::push(const T &value) {
  if (!root) {
    std::cout << "No root, making new" << std::endl;

    Node *node = new Node();
    node->value = value;
    node->color = Color::BLACK;
    root = node;
  } else {
    Node *browse = root;

    std::cout << "Our hero ascends into the pit of red-black madness. What "
                 "will he find in the depths?"
              << std::endl;

    Node *last_not_null = browse;
    while (browse != nullptr) {
      last_not_null = browse;
      if (browse->value > value) {
        browse = browse->left_child;
      } else {
        browse = browse->right_child;
      }
    }

    std::cout << "Done with downwards traversal" << std::endl;

    Node *node = new Node();
    node->value = value;
    node->parent = last_not_null;

    if (last_not_null->value > value) {
      last_not_null->left_child = node;
    } else {
      last_not_null->right_child = node;
    }

    std::cout << "As all things should be" << std::endl;
    fix_balance(node);
  }
}

template <typename T> void RBTree<T>::fix_balance(Node *node) {
  std::cout << "Establishing balance" << std::endl;

  if (node->parent == root) {
    std::cout << "Twój stary korzeń" << std::endl;
  }
  if (node->parent->color == Color::RED) {
    std::cout << "Twój stary czerwony" << std::endl;
  } else {
    std::cout << "Twój stary czarny" << std::endl;
  }

  while (node != root &&
         node->parent->color ==
             Color::RED) // Ojciec nie jest czarny a wezel nie jest korzeniem
  {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;
    std::cout << "Getting uncle" << std::endl;
    Node *uncle = get_uncle(parent);
    std::cout << "uncle found" << std::endl;

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
      } else if (parent->value > node->value &&
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
      if (parent->left_child == node) {

        rotateR(parent);
      } else {
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
  std::cout << "mordo" << std::endl;

  root->color = Color::BLACK; // korzen zawsze bedzie czarny wiec jest to
                              // ostatni krok funkcji
}

template <typename T>
inline auto RBTree<T>::get_parent_slot(const RBTree<T>::Node *node)
    -> RBTree<T>::Node *& {
  if (node == root) {
    return root;
  } else {
    if (node->parent->left_child == node) {
      return node->parent->left_child;
    } else {
      return node->parent->right_child;
    }
  }
}

template <typename T>
inline auto RBTree<T>::get_uncle(const RBTree<T>::Node *node)
    -> RBTree<T>::Node *& {
  if (node->parent->left_child == node) {
    return node->parent->right_child;
  } else {
    return node->parent->left_child;
  }
}

template <typename T> void RBTree<T>::rotateR(RBTree<T>::Node *node) {

  Node *parent = node->parent;

  Node **child_from, **child_to, *child;

  child_from = &node->right_child; // miejsce przenoszonego dziecka
  child_to = &parent->left_child;  // miejsce w ktore trafi dziecko

  child = *child_from; // podmiana dziecka na wezel woko ktorego rotujemy
  *child_from = parent;
  node->parent = parent->parent; // prawdziadek zostaje ojcem wezla rotowanego
  get_parent_slot(parent) =
      node; // dowiadujemy sie jakim dzieckiem byl wezel wokol ktorego rotujemy
  parent->parent = node; // i wstawiamy tam rotowany wezel
  *child_to = child;     // zajmujemy sie przeniesionym dzieckiem
  if (child)
    child->parent = parent; // rotowanego wezla
}

template <typename T> void RBTree<T>::rotateL(RBTree<T>::Node *node) {

  Node *parent = node->parent;

  Node **child_from, **child_to, *child;

  child_from = &node->left_child;  // miejsce przenoszonego dziecka
  child_to = &parent->right_child; // miejsce w ktore trafi dziecko

  child = *child_from; // podmiana dziecka na wezel woko ktorego rotujemy
  *child_from = parent;
  node->parent = parent->parent; // prawdziadek zostaje ojcem wezla rotowanego
  get_parent_slot(parent) =
      node; // dowiadujemy sie jakim dzieckiem byl wezel wokol ktorego rotujemy
  parent->parent = node; // i wstawiamy tam rotowany wezel
  *child_to = child;     // zajmujemy sie przeniesionym dzieckiem
  if (child) {
    child->parent = parent; // rotowanego wezla
  }
}

template <typename T> void RBTree<T>::print() {
  if (!root)
    return;

  std::queue<Node *> kolejka, kolejka2;

  Node *empty = new Node();

  int pow = 1, row = 0;

  kolejka.push(root);
  kolejka2.push(root);
  while (!kolejka2.empty()) {
    if (kolejka.front() == empty)
      std::cout << "N";
    else if (kolejka.front()->color == Color::RED)
      std::cout << REDBG << kolejka.front()->value << RESETBG;
    else
      std::cout << kolejka.front()->value;

    std::cout << " ";

    if (++row == pow) {
      std::cout << std::endl;
      row = 0;
      pow *= 2;
    }

    if (kolejka.front()->left_child) {
      kolejka.push(kolejka.front()->left_child);
      kolejka2.push(kolejka.front()->left_child);
    } else
      kolejka.push(empty);

    if (kolejka.front()->right_child) {
      kolejka.push(kolejka.front()->right_child);
      kolejka2.push(kolejka.front()->right_child);
    } else
      kolejka.push(empty);

    if (kolejka.front() != empty)
      kolejka2.pop();

    kolejka.pop();
  }

  if (row != 0) {
    while (row++ < pow) {
      std::cout << "N ";
    }
  }

  std::cout << std::endl;

  delete empty;
}

template <typename T> bool RBTree<T>::search(const T &value) {
  const Node *search = root;
  while (search && search->value != value) {
    if (search->value > value)
      search = search->left_child;
    else
      search = search->right_child;
  }

  if (search)
    return true;

  return false;
}

template <typename T> bool RBTree<T>::pop(const T &value) {
  // przeszukiwanie drzewa
  Node *pop_node = root;
  while (pop_node && pop_node->value != value) {
    if (pop_node->value > value)
      pop_node = pop_node->left_child;
    else
      pop_node = pop_node->right_child;
  }

  if (!pop_node) {
    return false;
  }
  std::cout << pop_node->value;

  int children_counter = count_children(pop_node);
}

template <typename T> bool RBTree<T>::bst_delete(const T &value) {}

template <typename T> void RBTree<T>::delete_node(Node *node) { delete node; }

template <typename T> int RBTree<T>::count_children(Node *node) {
  int count = 0;
  if (node->left_child) {
    count++;
  }
  if (node->right_child) {
    count++;
  }
  return count;
}

template class RBTree<int>;
