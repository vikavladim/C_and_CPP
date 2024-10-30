#ifndef VV_CONTAINERS_LIB_MULTISET_H
#define VV_CONTAINERS_LIB_MULTISET_H

#include <exception>
#include <functional>
#include <memory>
#include <vector>

#include "tree.h"

namespace vv {

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class Multiset {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  using TreeType = typename vv::Tree<Key, Comparator, Allocator>;

  using iterator = typename TreeType::Iterator;
  using const_iterator = typename TreeType::ConstIterator;

  Multiset() : tree() {}

  explicit Multiset(std::initializer_list<value_type> const& items)
      : tree(items, true) {}

  Multiset(const Multiset& other) : tree(other.tree) {
    if (&other == this) return;
  }

  Multiset(Multiset&& other) : tree(std::move(other.tree)) {
    if (this == &other) return;
  }

  ~Multiset() {}

  Multiset& operator=(const Multiset& other) {
    if (this != &other) {
      tree = other.tree;
    }
    return *this;
  }

  Multiset& operator=(Multiset&& other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  value_type& at(const key_type& key) { return tree.at(key); }

  value_type& operator[](const key_type& key) { return tree[key]; }

  iterator insert(const Key& key) { return tree.insert(key, true).first; }

  void printTree() const { tree.printTree(); }

  void swap(Multiset& other) { tree.swap(other.tree); }

  void merge(Multiset& other) { tree.merge(other.tree); }

  bool contains(const Key& key) const {
    return find(tree.root_, key) != tree.fakeForEnd;
  }

  bool empty() const { return tree.empty(); }

  iterator begin() { return tree.begin(); }

  iterator end() { return tree.end(); }

  const_iterator cbegin() { return tree.cbegin(); }

  const_iterator cend() { return tree.cend(); }

  void clear() { tree.clear(); }

  bool erase(const key_type& key) {
    size_t elems = 0;
    std::vector<typename TreeType::Node*> vec;
    for (iterator i = lower_bound(key); i != upper_bound(key); ++i) {
      vec.push_back(i.node);
      ++elems;
    }
    for (const auto& elem : vec) tree.erase(elem);
    return elems;
  }

  bool erase(const iterator& pos) { return tree.erase(pos.node); }

  iterator find(const key_type& key) { return find(tree.root_, key); }

  size_type max_size() { return tree.max_size(); }

  size_type size() { return tree.size(); }

  iterator lower_bound(const key_type& key) {
    return iterator(lower_bound(tree.root_, key, nullptr));
  }

  iterator upper_bound(const key_type& key) {
    return iterator(upper_bound(tree.root_, key, nullptr));
  }

  size_type count(const Key& key) {
    size_t count = 0;
    for (iterator i = lower_bound(key); i != upper_bound(key); ++i, ++count);
    return count;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    (result.push_back(std::make_pair(insert(std::forward<Args>(args)), true)),
     ...);
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

  typename TreeType::Node* lower_bound(
      typename TreeType::Node* node, const Key& key,
      typename TreeType::Node* prev,
      const Comparator& comparator = Comparator()) const {
    if (!node) {
      if (prev) return prev;
      return tree.fakeForEnd;
    }
    if (comparator(node->data, key)) {
      return lower_bound(node->right, key, prev);
    }
    prev = node;
    return lower_bound(node->left, key, prev);
  }

  typename TreeType::Node* upper_bound(
      typename TreeType::Node* node, const Key& key,
      typename TreeType::Node* prev,
      const Comparator& comparator = Comparator()) const {
    if (!node) {
      if (prev) return prev;
      return tree.fakeForEnd;
    }
    if (comparator(key, node->data)) {
      prev = node;
      return upper_bound(node->left, key, prev);
    }
    return upper_bound(node->right, key, prev);
  }
};

}  // namespace vv

#endif  // VV_CONTAINERS_LIB_MULTISET_H