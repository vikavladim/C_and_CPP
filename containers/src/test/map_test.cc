#include <map>
#include <set>
#include <vector>

#include "gtest/gtest.h"
#include "vv_containers.h"

TEST(map, create) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(std::pair<int, int>(i, i)).second,
              map.insert(std::pair<int, int>(i, i)).second);
  }

  auto it = map.begin();
  auto jt = tree.begin();
  for (; it != map.end(); ++jt, ++it) {
    EXPECT_EQ((*it).first, (*jt).first);
  }

  EXPECT_EQ(tree.insert(std::pair<int, int>(5, 5)).first == tree.end(),
            map.insert(std::pair<int, int>(5, 5)).first == map.end());
  EXPECT_EQ(tree.insert(std::pair<int, int>(5, 5)).second,
            map.insert(std::pair<int, int>(5, 5)).second);
}

TEST(map, iterator1) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(std::pair<int, int>(i, i)).second,
              map.insert(std::pair<int, int>(i, i)).second);
  }

  auto it = map.end();
  auto jt = tree.end();
  --it;
  --jt;
  for (; it != map.end() && jt != tree.end(); --it, --jt) {
    EXPECT_EQ((*it).first, (*jt).first);
  }
}

TEST(map, iterator2) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(std::pair<int, int>(i, i)).second,
              map.insert(std::pair<int, int>(i, i)).second);
  }

  auto it = map.cend();
  auto jt = tree.cend();
  --it;
  --jt;
  for (; it != map.cend() && jt != tree.cend(); --it, --jt) {
    EXPECT_EQ((*it).first, (*jt).first);
  }

  it = map.cbegin();
  jt = tree.cbegin();
  for (; it != map.cend() && jt != tree.cend(); ++it, ++jt) {
    EXPECT_EQ((*it).first, (*jt).first);
  }
}

TEST(map, iterator3) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(std::pair<int, int>(i, i)).second,
              map.insert(std::pair<int, int>(i, i)).second);
  }
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.erase(i), map.erase(map[i]));
    auto it = map.begin();
    auto jt = tree.begin();
    for (; it != map.end(); ++jt, ++it) {
      EXPECT_EQ((*it).first, (*jt).first);
    }
  }
}

TEST(map, create2) {
  vv::Map<int, int> tree{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> map{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto it = map.begin();
  auto jt = tree.begin();
  for (; it != map.end(); ++jt, ++it) {
    EXPECT_EQ((*it).first, (*jt).first);
  }
}

TEST(map, copy) {
  vv::Map<int, int> tree{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  vv::Map<int, int> tree2(tree);
  auto it = tree2.begin();
  auto jt = tree.begin();
  for (; it != tree2.end(); ++jt, ++it) {
    EXPECT_EQ((*it).first, (*jt).first);
  }
}

TEST(map, op_eq) {
  vv::Map<int, int> tree{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  vv::Map<int, int> tree2;
  tree2 = tree;
  auto it = tree2.begin();
  auto jt = tree.begin();
  for (; it != tree2.end(); ++jt, ++it) {
    EXPECT_EQ((*it).first, (*jt).first);
  }
}

TEST(map, access_iterator) {
  vv::Map<int, int> tree;
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i, i);
  }
  auto jt = tree.begin();
  ++jt;
  for (auto it = tree.begin(); jt != tree.end(); ++jt, ++it) {
    if ((*jt).first == 50) (*jt).second = 88;
    if ((*it).first == 50) {
      EXPECT_EQ(88, (*it).second);
    }

    if ((*jt).first == 40) tree.at(40) = 33;
    if ((*it).first == 40) {
      EXPECT_EQ(33, (*it).second);
    }

    if ((*jt).first == 55) tree[55] = 77;
    if ((*it).first == 55) {
      EXPECT_EQ(77, (*it).second);
    }

    EXPECT_LT((*it).first, (*jt).first);
  }

  EXPECT_ANY_THROW(tree.at(-5));
}

TEST(map, clear_empty) {
  vv::Map<int, int> tree;
  EXPECT_TRUE(tree.empty());
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i, i);
  }
  EXPECT_FALSE(tree.empty());
  tree.clear();
  EXPECT_TRUE(tree.empty());
}

TEST(map, erase) {
  vv::Map<int, int> tree;
  for (size_t i = 0; i < 1000; ++i) {
    tree.insert(i, i);
  }
  for (size_t i = 500; i < 1000; ++i) {
    tree.erase(i);
    auto jt = tree.begin();
    ++jt;
    for (auto it = tree.begin(); jt != tree.end(); ++jt, ++it) {
      EXPECT_LT((*it).first, (*jt).first);
    }
  }
  for (size_t i = 0; i < 500; ++i) {
    tree.erase(i);
    auto jt = tree.begin();
    if (jt == tree.end()) break;
    ++jt;
    for (auto it = tree.begin(); jt != tree.end(); ++jt, ++it) {
      EXPECT_LT((*it).first, (*jt).first);
    }
  }
  EXPECT_TRUE(tree.empty());
}

TEST(map, contains) {
  vv::Map<int, int> tree;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i, i);
  }
  EXPECT_FALSE(tree.contains(-5));
  EXPECT_TRUE(tree.contains(5));
}

TEST(map, insert_or_assign) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert_or_assign(std::pair<int, int>(i, i)).second,
              map.insert_or_assign(i, i).second);
  }
  EXPECT_EQ(tree.insert_or_assign(std::pair<int, int>(5, 5)).second,
            map.insert_or_assign(5, 5).second);
  EXPECT_EQ(
      tree.insert_or_assign(std::pair<int, int>(5, 5)).first == tree.end(),
      map.insert_or_assign(5, 5).first == map.end());
}

TEST(map, copy_and_move) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(std::pair<int, int>(i, i));
    map.insert(std::pair<int, int>(i, i));
  }
  vv::Map<int, int> tree2(tree);
  std::map<int, int> map2(map);
  vv::Map<int, int> tree5 = tree;
  std::map<int, int> map5 = map;
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(map2.contains(i), tree2.contains(i));
    EXPECT_EQ(map5.contains(i), tree5.contains(i));
  }
  vv::Map<int, int> tree3(std::move(tree));
  std::map<int, int> map3(std::move(map));
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(map3.contains(i), tree3.contains(i));
  }
  EXPECT_EQ(map.empty(), map.empty());

  vv::Map<int, int> tree6(tree6);
  std::map<int, int> map6(map6);

  EXPECT_EQ(tree6.empty(), map6.empty());

  for (size_t i = 0; i < 10; ++i) {
    tree6.insert(std::pair<int, int>(i, i));
    map6.insert(std::pair<int, int>(i, i));
  }

  vv::Map<int, int> tree4 = std::move(tree6);
  std::map<int, int> map4 = std::move(map6);

  EXPECT_EQ(map4.empty(), map4.empty());
  for (size_t i = 0; i < 10; ++i) {
    tree4.insert(std::pair<int, int>(i, i));
    map4.insert(std::pair<int, int>(i, i));
  }
}

TEST(map, merge) {
  vv::Map<int, int> tree;
  std::map<int, int> map;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(std::pair<int, int>(i, i));
    map.insert(std::pair<int, int>(i, i));
  }
  vv::Map<int, int> tree2;
  std::map<int, int> map2;
  for (size_t i = 10; i < 20; ++i) {
    tree2.insert(std::pair<int, int>(i, i));
    map2.insert(std::pair<int, int>(i, i));
  }
  tree.merge(tree2);
  map.merge(map2);
  for (size_t i = 0; i < 20; ++i) {
    EXPECT_EQ(map.contains(i), tree.contains(i));
  }
}

template <typename Key, typename Value,
          class Allocator = std::allocator<std::pair<const Key, Value>>>
struct MyAllocator {
  using value_type = std::pair<const Key, Value>;
  MyAllocator() noexcept {}
  template <typename U, typename C, typename A>
  MyAllocator(const MyAllocator<U, C, A>&) noexcept {}
  value_type* allocate(std::size_t n) {
    if (n > std::allocator<value_type>().max_size()) {
      throw std::bad_alloc();
    }
    return static_cast<value_type*>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(value_type* p, [[maybe_unused]] std::size_t n) noexcept {
    ::operator delete(static_cast<void*>(p));
  }
  std::size_t max_size() const noexcept {
    return std::allocator<value_type>().max_size();
  }
};

TEST(map, size) {
  vv::Map<int, int, std::less<int>> tree;
  std::map<int, int, std::less<int>> map;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(std::pair<int, int>(i, i));
    map.insert(std::pair<int, int>(i, i));
  }
  EXPECT_EQ(tree.size(), map.size());
  tree.erase(1);
  map.erase(1);
  EXPECT_EQ(tree.size(), map.size());
  tree.erase(1);
  map.erase(1);
  EXPECT_EQ(tree.size(), map.size());
  tree.clear();
  map.clear();
  EXPECT_EQ(tree.size(), map.size());
}

TEST(map, insert_many) {
  vv::Map<size_t, size_t> tree;
  auto vec1 = tree.insert_many(std::pair<size_t, size_t>(0, 0),
                               std::pair<size_t, size_t>(1, 1),
                               std::pair<size_t, size_t>(2, 2));
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ((*(vec1[i].first)).first, i);
    EXPECT_EQ(vec1[i].second, true);
  }
}
