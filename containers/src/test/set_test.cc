#include <set>

#include "gtest/gtest.h"
#include "vv_containers.h"

TEST(set, create) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(i).second, set.insert(i).second);
  }

  auto it = set.begin();
  auto jt = tree.begin();
  for (; it != set.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }

  EXPECT_EQ(tree.insert(5).first == tree.end(),
            set.insert(5).first == set.end());
  EXPECT_EQ(tree.insert(5).second, set.insert(5).second);
}

TEST(set, iterator1) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(i).second, set.insert(i).second);
  }

  auto it = set.end();
  auto jt = tree.end();
  --it;
  --jt;
  for (; it != set.end() && jt != tree.end(); --it, --jt) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(set, iterator2) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(i).second, set.insert(i).second);
  }

  auto it = set.cend();
  auto jt = tree.cend();
  --it;
  --jt;
  for (; it != set.cend() && jt != tree.cend(); --it, --jt) {
    EXPECT_EQ(*it, *jt);
  }

  it = set.cbegin();
  jt = tree.cbegin();
  for (; it != set.cend() && jt != tree.cend(); ++it, ++jt) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(set, iterator3) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.insert(i).second, set.insert(i).second);
  }
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.erase(i), set.erase(i));
    auto it = set.begin();
    auto jt = tree.begin();
    for (; it != set.end(); ++jt, ++it) {
      EXPECT_EQ(*it, *jt);
    }
  }
}

TEST(set, create2) {
  vv::Set<int> tree{1, 2, 3, 4, 5};
  std::set<int> set{1, 2, 3, 4, 5};
  auto it = set.begin();
  auto jt = tree.begin();
  for (; it != set.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(set, copy) {
  vv::Set<int> tree{1, 2, 3, 4, 5};
  vv::Set<int> tree2(tree);
  auto it = tree2.begin();
  auto jt = tree.begin();
  for (; it != tree2.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(set, op_eq) {
  vv::Set<int> tree{1, 2, 3, 4, 5};
  vv::Set<int> tree2;
  tree2 = tree;
  auto it = tree2.begin();
  auto jt = tree.begin();
  for (; it != tree2.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(set, clear_empty) {
  vv::Set<int> tree;
  EXPECT_TRUE(tree.empty());
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
  }
  EXPECT_FALSE(tree.empty());
  tree.clear();
  EXPECT_TRUE(tree.empty());
}

TEST(set, erase) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 1000; ++i) {
    tree.insert(i);
    set.insert(i);
  }
  for (size_t i = 500; i < 1000; ++i) {
    tree.erase(i);
    set.erase(i);
    auto jt = set.begin();
    for (auto it = tree.begin(); jt != set.end(); ++jt, ++it) {
      EXPECT_EQ(*it, *jt);
    }
  }
  for (size_t i = 0; i < 500; ++i) {
    tree.erase(i);
    set.erase(i);
    auto jt = set.begin();
    for (auto it = tree.begin(); jt != set.end(); ++jt, ++it) {
      EXPECT_EQ(*it, *jt);
    }
  }
  EXPECT_TRUE(tree.empty());
}

TEST(set, contains) {
  vv::Set<int> tree;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
  }
  EXPECT_FALSE(tree.contains(-5));
  EXPECT_TRUE(tree.contains(5));
}

TEST(set, copy_and_move) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
    set.insert(i);
  }
  vv::Set<int> tree2(tree);
  std::set<int> set2(set);
  EXPECT_EQ(tree2.empty(), set2.empty());
  EXPECT_EQ(tree.empty(), set.empty());
  vv::Set<int> tree5 = tree;
  std::set<int> set5 = set;
  EXPECT_EQ(tree5.empty(), set5.empty());
  EXPECT_EQ(tree.empty(), set.empty());
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(set2.contains(i), tree2.contains(i));
    EXPECT_EQ(set5.contains(i), tree5.contains(i));
  }

  vv::Set<int> tree3(std::move(tree));
  std::set<int> set3(std::move(set));
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(set3.contains(i), tree3.contains(i));
  }
  EXPECT_EQ(set.empty(), set.empty());

  vv::Set<int> tree6(tree6);
  std::set<int> set6(set6);

  EXPECT_EQ(tree6.empty(), set6.empty());

  for (size_t i = 0; i < 10; ++i) {
    tree6.insert(i);
    set6.insert(i);
  }

  vv::Set<int> tree7;
  std::set<int> set7;
  for (size_t i = 0; i < 10; ++i) {
    tree7.insert(i);
    set7.insert(i);
  }

  vv::Set<int> tree4 = std::move(tree7);
  std::set<int> set4 = std::move(set7);

  EXPECT_EQ(set4.empty(), set4.empty());
  for (size_t i = 0; i < 10; ++i) {
    tree4.insert(i);
    set4.insert(i);
  }
}

TEST(set, merge) {
  vv::Set<int> tree;
  std::set<int> set;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
    set.insert(i);
  }
  vv::Set<int> tree2;
  std::set<int> set2;
  for (size_t i = 10; i < 20; ++i) {
    tree2.insert(i);
    set2.insert(i);
  }
  tree.merge(tree2);
  set.merge(set2);
  for (size_t i = 0; i < 20; ++i) {
    EXPECT_EQ(set.contains(i), tree.contains(i));
  }
}

// template <typename Key, typename Value,
//           class Allocator = std::allocator<std::pair<const Key, Value>>>
// struct MyAllocator {
//   using value_type = std::pair<const Key, Value>;
//   MyAllocator() noexcept {}
//   template <typename U, typename C, typename A>
//   MyAllocator(const MyAllocator<U, C, A>&) noexcept {}
//   value_type* allocate(std::size_t n) {
//     if (n > std::allocator<value_type>().max_size()) {
//       throw std::bad_alloc();
//     }
//     return static_cast<value_type*>(::operator new(n*sizeof(value_type)));
//   }

//   void deallocate(value_type* p, [[maybe_unused]] std::size_t n) noexcept{
//     ::operator delete(static_cast<void*>(p));
//   }
//   std::size_t max_size() const noexcept {
//   return std::allocator<value_type>().max_size();
// }
// };

TEST(set, size) {
  vv::Set<int, std::less<int>> tree;
  std::set<int, std::less<int>> set;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
    set.insert(i);
  }
  EXPECT_EQ(tree.size(), set.size());
  tree.erase(1);
  set.erase(1);
  EXPECT_EQ(tree.size(), set.size());
  tree.erase(1);
  set.erase(1);
  EXPECT_EQ(tree.size(), set.size());
  tree.clear();
  set.clear();
  EXPECT_EQ(tree.size(), set.size());
}

TEST(set, insert_many) {
  vv::Set<size_t> tree;
  auto vec1 = tree.insert_many(size_t(0), size_t(1), size_t(2));
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(*(vec1[i].first), i);
    EXPECT_EQ(vec1[i].second, true);
  }
}