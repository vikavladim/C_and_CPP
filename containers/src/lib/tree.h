#ifndef VV_CONTAINERS_LIB_TREE_H
#define VV_CONTAINERS_LIB_TREE_H

#include <exception>
#include <functional>
#include <memory>

namespace vv {

enum class Color { RED, BLACK };

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
struct Tree {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  struct Node {
    value_type data;
    Color color = Color::RED;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    explicit Node(key_type key = key_type()) : data(key) {}
    Node(key_type key, Node *parent) : data(key), parent(parent) {}

    Node *theLeftmost() {
      Node *theLeft = this;
      while (theLeft->left != nullptr) {
        theLeft = theLeft->left;
      }
      return theLeft;
    }

    Node *theRightmost() {
      Node *theRight = this;
      while (theRight->right != nullptr) {
        theRight = theRight->right;
      }
      return theRight;
    }

    Node *predecessor() {
      if (!parent) return nullptr;
      if (parent->right == this)
        return parent;
      else
        return parent->predecessor();
    }

    Node *successor() {
      if (!parent) return nullptr;
      if (parent->left == this)
        return parent;
      else
        return parent->successor();
    }
  };

  using NodeAllocator =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
  using NodeAllocatorTraits =
      typename std::allocator_traits<Allocator>::template rebind_traits<Node>;

  struct Iterator {
    Node *node = nullptr;

    Iterator() {}

    explicit Iterator(Node *node) : node(node) {}

    reference operator*() { return node->data; }

    Iterator &operator--() {
      if (node->left)
        node = node->left->theRightmost();
      else
        node = node->predecessor();
      return *this;
    }

    Iterator &operator++() {
      if (node->right)
        node = node->right->theLeftmost();
      else
        node = node->successor();
      return *this;
    }

    bool operator==(const Iterator &other) const { return node == other.node; }

    bool operator!=(const Iterator &a) const { return !(*this == a); }
  };

  struct ConstIterator {
    friend class Tree;

    Node *node = nullptr;

    ConstIterator() {}

    explicit ConstIterator(Node *node) : node(node) {}

    bool operator==(const ConstIterator &other) const {
      return node == other.node;
    }

    bool operator!=(const ConstIterator &a) const { return !(*this == a); }

    const_reference operator*() const { return node->data; }

    ConstIterator &operator--() {
      if (node->left)
        node = node->left->theRightmost();
      else
        node = node->predecessor();
      return *this;
    }

    ConstIterator &operator++() {
      if (node->right)
        node = node->right->theLeftmost();
      else
        node = node->successor();
      return *this;
    }
  };

  using iterator = Tree::Iterator;
  using const_iterator = Tree::ConstIterator;

  explicit Tree(std::initializer_list<value_type> const &items,
                bool isMulti = false) {
    createFakeForEnd();
    for (auto &item : items) insert(item, isMulti);
  }

  Tree(const Tree &other) {
    createFakeForEnd();
    if (&other == this) return;
    copy(other.root_);
  }

  Tree(Tree &&other) {
    if (&other == this) return;
    root_ = other.root_;
    other.root_ = nullptr;
  }

  ~Tree() {
    deleteTree(root_);
    NodeAllocatorTraits::destroy(allocator, fakeForEnd);
    NodeAllocatorTraits::deallocate(allocator, fakeForEnd, 1);
  }

  Tree() { createFakeForEnd(); }

  Tree &operator=(const Tree &other) {
    if (&other == this) return *this;
    deleteTree(root_);
    copy(other.root_);
    return *this;
  }

  Tree &operator=(Tree &&other) noexcept {
    if (other == *this) return *this;
    swap(other);
    return *this;
  }

  std::pair<iterator, bool> insert(const Key &key, bool isMulty = false) {
    Node *newNode = nullptr;
    bool success = true;
    if (root_ == nullptr) {
      ++count;
      newNode = NodeAllocatorTraits::allocate(allocator, 1);
      NodeAllocatorTraits::construct(allocator, newNode, key);
      toRoot(newNode);
    } else {
      std::pair<Node *, bool> p = insert(root_, key, isMulty);
      newNode = p.first;
      success = p.second;
    }
    return std::pair<iterator, bool>(Iterator(newNode), success);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key) {
    Node *newNode = nullptr;
    bool success = true;
    if (root_ == nullptr) {
      ++count;
      newNode = NodeAllocatorTraits::allocate(allocator, 1);
      NodeAllocatorTraits::construct(allocator, newNode, key);
      toRoot(newNode);
    } else {
      std::pair<Node *, bool> p = insert(root_, key);
      newNode = p.first;
      success = p.second;
    }
    return std::pair<iterator, bool>(Iterator(newNode), success);
  }

  void swap(Tree &other) { std::swap(root_, other->root_); }

  void merge(Tree &other) { merge(other.root_); }

  bool empty() const { return root_ == nullptr; }

  iterator begin() {
    if (!root_)
      return end();
    else {
      return iterator(root_->theLeftmost());
    }
  }

  iterator end() { return iterator(fakeForEnd); }

  const_iterator cbegin() {
    if (!root_)
      return cend();
    else {
      return const_iterator(root_->theLeftmost());
    }
  }

  const_iterator cend() { return const_iterator(fakeForEnd); }

  void clear() {
    deleteTree(root_);
    root_ = nullptr;
    fakeForEnd->left = nullptr;
  }

  bool erase(Node *node) {
    if (node == fakeForEnd) return false;
    if (node->right && node->left)
      replaceNodeWithShip(node, node->right->theLeftmost());
    deleteOneChild(node);

    return true;
  }

  size_type max_size() {
    // return allocator.max_size();
    // return std::numeric_limits<std::ptrdiff_t>::max() / sizeof(value_type);
    return std::allocator_traits<NodeAllocator>::max_size(allocator);
  }

  size_type size() { return count; }

  Node *root_ = nullptr;
  Node *fakeForEnd = nullptr;
  NodeAllocator allocator = NodeAllocator();
  size_type count = 0;

  void createFakeForEnd() {
    fakeForEnd = NodeAllocatorTraits::allocate(allocator, 1);
    NodeAllocatorTraits::construct(allocator, fakeForEnd);
    fakeForEnd->parent = fakeForEnd;
    fakeForEnd->right = fakeForEnd;
  }

  void copy(Node *otherRoot) {
    if (!otherRoot) return;
    ++count;
    Node *newNode = NodeAllocatorTraits::allocate(allocator, 1);
    NodeAllocatorTraits::construct(allocator, newNode, otherRoot->data);
    toRoot(newNode);
    copy(newNode, otherRoot->left, true);
    copy(newNode, otherRoot->right, false);
  }

  void merge(Node *node) {
    if (!node) return;
    insert(node->data);
    merge(node->left);
    merge(node->right);
  }

  void copy(Node *parent, Node *other, bool isLeft) {
    if (other == nullptr) return;
    ++count;
    Node *newNode = NodeAllocatorTraits::allocate(allocator, 1);
    NodeAllocatorTraits::construct(allocator, newNode, other->data, parent);
    if (!isLeft) {
      parent->right = newNode;
    } else {
      parent->left = newNode;
    }
    copy(newNode, other->left, true);
    copy(newNode, other->right, false);
  }

  std::pair<Node *, bool> insert(Node *node, const Key &key,
                                 bool isMulty = false,
                                 const Comparator &comparator = Comparator()) {
    if (!comparator(node->data, key) && !comparator(key, node->data) &&
        !isMulty) {
      return std::pair<Node *, bool>(node, false);
    }
    Node *newNode = nullptr;
    if (comparator(key, node->data)) {
      if (node->left == nullptr) {
        ++count;
        newNode = NodeAllocatorTraits::allocate(allocator, 1);
        NodeAllocatorTraits::construct(allocator, newNode, key, node);
        node->left = newNode;
        insertCase1(node->left);
      } else {
        return insert(node->left, key, isMulty);
      }
    } else {
      if (node->right == nullptr) {
        ++count;
        newNode = NodeAllocatorTraits::allocate(allocator, 1);
        NodeAllocatorTraits::construct(allocator, newNode, key, node);
        node->right = newNode;
        insertCase1(node->right);
      } else {
        return insert(node->right, key, isMulty);
      }
    }

    return std::pair<Node *, bool>(newNode, true);
  }

  void deleteTree(Node *node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    NodeAllocatorTraits::destroy(allocator, node);
    NodeAllocatorTraits::deallocate(allocator, node, 1);
    --count;
  }

  void toRoot(Node *node) {
    root_ = node;
    root_->parent = fakeForEnd;
    fakeForEnd->left = root_;
    root_->color = Color::BLACK;
  }

  Node *grandparent(Node *node) {
    if (!node || node->parent == fakeForEnd ||
        node->parent->parent == fakeForEnd)
      return nullptr;
    return node->parent->parent;
  }

  Node *sibling(Node *node) {
    if (!node || node->parent == fakeForEnd) return nullptr;
    if (node->parent->left == node)
      return node->parent->right;
    else
      return node->parent->left;
  }

  Node *uncle(Node *node) {
    Node *g = grandparent(node);
    if (!g) return nullptr;
    if (node->parent == g->left)
      return g->right;
    else
      return g->left;
  }

  void insertCase1(Node *node) {
    if (node->parent == fakeForEnd)
      toRoot(node);
    else
      insertCase2(node);
  }

  void insertCase2(Node *node) {
    if (node->parent->color == Color::BLACK) return;
    insertCase3(node);
  }

  void insertCase3(Node *node) {
    Node *u = uncle(node), *g = nullptr;
    if (u && u->color == Color::RED) {
      node->parent->color = Color::BLACK;
      u->color = Color::BLACK;
      g = grandparent(node);
      g->color = Color::RED;
      insertCase1(g);
    } else
      insertCase4(node);
  }

  void insertCase4(Node *node) {
    Node *g = grandparent(node);
    if (node->parent != fakeForEnd && node == node->parent->right &&
        node->parent == g->left) {
      rotateLeft(node->parent);
      node = node->left;
    } else if (node->parent != fakeForEnd && node == node->parent->left &&
               node->parent == g->right) {
      rotateRight(node->parent);
      node = node->right;
    }
    insertCase5(node);
  }

  void insertCase5(Node *node) {
    Node *g = grandparent(node);
    node->parent->color = Color::BLACK;
    g->color = Color::RED;
    if (node == node->parent->left && node->parent == g->left) {
      rotateRight(g);
    } else {
      rotateLeft(g);
    }
  }

  void rotateLeft(Node *node) {
    Node *pivot = node->right;
    pivot->parent = node->parent;
    if (node == root_) toRoot(pivot);
    if (node->parent != fakeForEnd) {
      if (node->parent->left == node)
        node->parent->left = pivot;
      else
        node->parent->right = pivot;
    }

    node->right = pivot->left;
    if (pivot->left != nullptr) pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;
  }

  void rotateRight(Node *node) {
    Node *pivot = node->left;
    pivot->parent = node->parent;
    if (node == root_) toRoot(pivot);
    if (node->parent != fakeForEnd) {
      if (node->parent->left == node)
        node->parent->left = pivot;
      else
        node->parent->right = pivot;
    }

    node->left = pivot->right;
    if (pivot->right != nullptr) pivot->right->parent = node;

    node->parent = pivot;
    pivot->right = node;
  }

  void replaceNode(Node *node, Node *child) {
    child->parent = node->parent;
    if (node->parent == fakeForEnd) {
      toRoot(child);
      return;
    }
    if (node == node->parent->left)
      node->parent->left = child;
    else
      node->parent->right = child;
  }

  void replaceRelative(Node *node, Node *child) {
    child->parent = node->parent;
    if (node->parent->left == node)
      node->parent->left = child;
    else
      node->parent->right = child;
    if (child->right) child->right->parent = node;
    if (child->left) child->left->parent = node;
    if (node->right == child) {
      node->right = child->right;
      child->right = node;
      if (node->left) node->left->parent = child;
      std::swap(node->left, child->left);
    } else {
      node->left = child->left;
      child->left = node;
      if (node->right) node->right->parent = child;
      std::swap(node->right, child->right);
    }
    node->parent = child;

    if (node == root_) {
      toRoot(child);
    }
  }

  void replaceNodeWithShip(Node *node, Node *child) {
    if (node == child->parent) {
      replaceRelative(node, child);
      return;
    }
    Node *nodeParent = node->parent;

    if (node == node->parent->left && child == child->parent->left)
      std::swap(node->parent->left, child->parent->left);
    else if (node == node->parent->left && child == child->parent->right)
      std::swap(node->parent->left, child->parent->right);
    else if (node == node->parent->right && child == child->parent->left)
      std::swap(node->parent->right, child->parent->left);
    else if (node == node->parent->right && child == child->parent->right)
      std::swap(node->parent->right, child->parent->right);
    if (node->right) node->right->parent = child;
    if (node->left) node->left->parent = child;
    if (child->right) child->right->parent = node;
    if (child->left) child->left->parent = node;

    std::swap(node->parent, child->parent);
    std::swap(node->left, child->left);
    std::swap(node->right, child->right);

    if (nodeParent == fakeForEnd) {
      toRoot(child);
    }
  }

  void deleteOneChild(Node *node) {
    Node *child = nullptr;
    if (node->left)
      child = node->left;
    else
      child = node->right;
    if (child) replaceNode(node, child);
    if (node->color == Color::BLACK) {
      if (child && child->color == Color::RED)
        child->color = Color::BLACK;
      else if (child)
        deleteCase1(child);
      else
        deleteCase1(node);
    }

    if ((node->parent == fakeForEnd || !node->parent) && !child) {
      root_ = nullptr;
      fakeForEnd->left = nullptr;
    } else if (node->parent && node->parent->left == node)
      node->parent->left = nullptr;
    else if (node->parent && node->parent->right == node)
      node->parent->right = nullptr;
    NodeAllocatorTraits::destroy(allocator, node);
    NodeAllocatorTraits::deallocate(allocator, node, 1);
    --count;
  }

  void deleteCase1(Node *node) {
    if (node && node->parent != fakeForEnd) deleteCase2(node);
  }

  void deleteCase2(Node *node) {
    Node *s = sibling(node);
    if (s && s->color == Color::RED) {
      node->parent->color = Color::RED;
      s->color = Color::BLACK;
      if (node == node->parent->left)
        rotateLeft(node->parent);
      else
        rotateRight(node->parent);
    }
    deleteCase3(node);
  }

  void deleteCase3(Node *node) {
    Node *s = sibling(node);
    if ((node->parent->color == Color::BLACK) &&
        (!s || s->color == Color::BLACK) &&
        (!s || !s->left || s->left->color == Color::BLACK) &&
        (!s || !s->right || s->right->color == Color::BLACK)) {
      if (s) s->color = Color::RED;
      deleteCase1(node->parent);
    } else
      deleteCase4(node);
  }

  void deleteCase4(Node *node) {
    Node *s = sibling(node);
    if ((node->parent->color == Color::RED) &&
        (!s || s->color == Color::BLACK) &&
        (!s || !s->left || s->left->color == Color::BLACK) &&
        (!s || !s->right || s->right->color == Color::BLACK)) {
      if (s) s->color = Color::RED;
      node->parent->color = Color::BLACK;
    } else
      deleteCase5(node);
  }

  void deleteCase5(Node *node) {
    Node *s = sibling(node);
    if (s && s->color == Color::BLACK && (s->right || s->left)) {
      if ((!s->right || s->right->color == Color::BLACK) &&
          (!s->left || s->left->color == Color::BLACK)) {
        if ((node == node->parent->left) &&
            (!s->right || s->right->color == Color::BLACK) &&
            (s->left->color == Color::RED)) {
          s->color = Color::RED;
          s->left->color = Color::BLACK;
          rotateRight(s);
        } else if ((node == node->parent->right) &&
                   (!s->left || s->left->color == Color::BLACK) &&
                   (s->right->color == Color::RED)) {
          s->color = Color::RED;
          s->right->color = Color::BLACK;
          rotateLeft(s);
        }
      }
    }
    deleteCase6(node);
  }

  void deleteCase6(Node *node) {
    Node *s = sibling(node);
    if (s) s->color = node->parent->color;
    node->parent->color = Color::BLACK;

    if (node == node->parent->left) {
      if (s && s->right) s->right->color = Color::BLACK;
      rotateLeft(node->parent);
    } else {
      if (s && s->left) s->left->color = Color::BLACK;
      rotateRight(node->parent);
    }
  }
};

}  // namespace vv

#endif  // VV_CONTAINERS_LIB_TREE_H