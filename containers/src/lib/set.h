#ifndef VV_CONTAINERS_LIB_SET_H
#define VV_CONTAINERS_LIB_SET_H

#include <exception>
#include <functional>
#include <memory>
#include <vector>

#include "tree.h"

namespace vv {

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class Set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  using TreeType = typename vv::Tree<Key, Comparator, Allocator>;

  using iterator = typename TreeType::Iterator;
  using const_iterator = typename TreeType::ConstIterator;

  Set() : tree() {}

  explicit Set(std::initializer_list<value_type> const& items) : tree(items) {}

  Set(const Set& other) : tree(other.tree) {
    if (&other == this) return;
  }

  Set(Set&& other) : tree(std::move(other.tree)) {
    if (this == &other) return;
  }

  ~Set() {}

  Set& operator=(const Set& other) {
    if (this != &other) {
      tree = other.tree;
    }
    return *this;
  }

  Set& operator=(Set&& other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  value_type& at(const key_type& key) { return tree.at(key); }

  value_type& operator[](const key_type& key) { return tree[key]; }

  std::pair<iterator, bool> insert(const Key& key) { return tree.insert(key); }

  std::pair<iterator, bool> insert_or_assign(const Key& key) {
    return tree.insert_or_assign(key);
  }

  void printTree() const { tree.printTree(); }

  void swap(Set& other) { tree.swap(other.tree); }

  void merge(Set& other) { tree.merge(other.tree); }

  bool contains(const Key& key) const {
    return find(tree.root_, key) != tree.fakeForEnd;
  }

  bool empty() const { return tree.empty(); }

  iterator begin() { return tree.begin(); }

  iterator end() { return tree.end(); }

  const_iterator cbegin() { return tree.cbegin(); }

  const_iterator cend() { return tree.cend(); }

  void clear() { tree.clear(); }

  bool erase(const key_type& key) { return tree.erase(find(tree.root_, key)); }

  bool erase(const iterator& pos) {
    return tree.erase(find(tree.root_, pos.node->data));
  }

  iterator find(const key_type& key) { return find(tree.root_, key); }

  size_type max_size() { return tree.max_size(); }

  size_type size() { return tree.size(); }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    (result.push_back(insert(std::forward<Args>(args))), ...);
    return result;
  }

 private:
  TreeType tree;

  typename TreeType::Node* find(
      typename TreeType::Node* node, const Key& key,
      const Comparator& comparator = Comparator()) const {
    if (!node) {
      return tree.fakeForEnd;
    }
    if (!comparator(node->data, key) && !comparator(key, node->data)) {
      return node;
    }
    if (comparator(node->data, key)) {
      return find(node->right, key);
    } else {
      return find(node->left, key);
    }
  }
};

}  // namespace vv

#endif  // VV_CONTAINERS_LIB_SET_H