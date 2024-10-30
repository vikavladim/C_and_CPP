#ifndef VV_CONTAINERS_LIB_MAP_H
#define VV_CONTAINERS_LIB_MAP_H

#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "pair_key_comparator.h"
#include "tree.h"

namespace vv {

template <typename Key, typename Value, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, Value>>>
class Map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  using TreeType =
      typename vv::Tree<std::pair<const Key, Value>,
                        map_support::PairKeyComparator<Key, Value, Comparator>,
                        Allocator>;

  using iterator = typename TreeType::Iterator;
  using const_iterator = typename TreeType::ConstIterator;

  Map() : tree() {}

  explicit Map(std::initializer_list<value_type> const &items) : tree(items) {}

  Map(const Map &other) : tree(other.tree) {
    if (&other == this) return;
  }

  Map(Map &&other) : tree(std::move(other.tree)) {
    if (this == &other) return;
  }

  Map &operator=(const Map &other) {
    if (this != &other) {
      tree = other.tree;
    }
    return *this;
  }

  Map &operator=(Map &&other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  ~Map() {}

  mapped_type &at(const key_type &key) {
    typename TreeType::Node *node = find(tree.root_, key);
    if (node == tree.fakeForEnd) throw std::out_of_range("There is no key");
    return node->data.second;
  }

  mapped_type &operator[](const key_type &key) {
    return find(tree.root_, key)->data.second;
  }

  std::pair<iterator, bool> insert(
      std::pair<const key_type &, const mapped_type &> p) {
    return tree.insert(p);
  }

  std::pair<iterator, bool> insert(const Key &key, const Value &value) {
    return insert(value_type(key, value));
  }

  std::pair<iterator, bool> insert_or_assign(
      std::pair<const key_type &, const mapped_type &> p) {
    return tree.insert_or_assign(p);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key,
                                             const Value &value) {
    return tree.insert_or_assign(
        std::pair<key_type, value_type>(value_type(key, value)));
  }

  void printTree() const { tree.printTree(); }

  void swap(Map &other) { tree.swap(other.tree); }

  void merge(Map &other) { tree.merge(other.tree); }

  bool contains(const Key &key) const {
    return find(tree.root_, key) != tree.fakeForEnd;
  }

  bool empty() const { return tree.empty(); }

  iterator begin() { return tree.begin(); }

  iterator end() { return tree.end(); }

  const_iterator cbegin() { return tree.cbegin(); }

  const_iterator cend() { return tree.cend(); }

  void clear() { tree.clear(); }

  bool erase(const key_type &key) { return tree.erase(find(tree.root_, key)); }

  bool erase(const iterator &pos) { return tree.erase(pos.node); }

  iterator find(const key_type &key) { return iterator(find(tree.root_, key)); }

  size_type max_size() { return tree.max_size(); }

  size_type size() { return tree.size(); }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    (result.push_back(insert(args)), ...);
    return result;
  }

 private:
  TreeType tree;

  typename TreeType::Node *find(
      typename TreeType::Node *node, const Key &key,
      const Comparator &comparator = Comparator()) const {
    if (!node) {
      return tree.fakeForEnd;
    }
    if (!comparator(node->data.first, key) &&
        !comparator(key, node->data.first)) {
      return node;
    }
    if (comparator(node->data.first, key)) {
      return find(node->right, key);
    } else {
      return find(node->left, key);
    }
  }
};

}  // namespace vv

#endif  // VV_CONTAINERS_LIB_MAP_H