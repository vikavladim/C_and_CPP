#include <set>

#include "gtest/gtest.h"
#include "vv_containers.h"

TEST(multiset, create) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }

  auto it = multiset.begin();
  auto jt = tree.begin();
  for (; it != multiset.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(multiset, iterator1) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }

  auto it = multiset.end();
  auto jt = tree.end();
  --it;
  --jt;
  for (; it != multiset.end() && jt != tree.end(); --it, --jt) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(multiset, iterator2) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }

  auto it = multiset.cend();
  auto jt = tree.cend();
  --it;
  --jt;
  for (; it != multiset.cend() && jt != tree.cend(); --it, --jt) {
    EXPECT_EQ(*it, *jt);
  }

  it = multiset.cbegin();
  jt = tree.cbegin();
  for (; it != multiset.cend() && jt != tree.cend(); ++it, ++jt) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(multiset, iterator3) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }
  for (size_t i = 0; i < 100; ++i) {
    tree.erase(tree.begin());
    multiset.erase(multiset.begin());
    auto it = multiset.begin();
    auto jt = tree.begin();
    for (; it != multiset.end(); ++jt, ++it) {
      EXPECT_EQ(*it, *jt);
    }
  }
}

TEST(multiset, create2) {
  vv::Multiset<int> tree{1, 2, 3, 4, 4, 4, 4, 5};
  std::multiset<int> multiset{1, 2, 3, 4, 4, 4, 4, 5};
  auto it = multiset.begin();
  auto jt = tree.begin();
  for (; it != multiset.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(multiset, copy) {
  vv::Multiset<int> tree{1, 2, 3, 4, 5, 5, 5};
  vv::Multiset<int> tree2(tree);
  auto it = tree2.begin();
  auto jt = tree.begin();
  for (; it != tree2.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(multiset, op_eq) {
  vv::Multiset<int> tree{1, 2, 3, 4, 5, 5, 5};
  vv::Multiset<int> tree2;
  tree2 = tree;
  auto it = tree2.begin();
  auto jt = tree.begin();
  for (; it != tree2.end(); ++jt, ++it) {
    EXPECT_EQ(*it, *jt);
  }
}

TEST(multiset, clear_empty) {
  vv::Multiset<int> tree;
  EXPECT_TRUE(tree.empty());
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
  }
  EXPECT_FALSE(tree.empty());
  tree.clear();
  EXPECT_TRUE(tree.empty());
}

TEST(multiset, erase) {
  vv::Multiset<int> tree;
  for (size_t i = 0; i < 1000; ++i) {
    tree.insert(i);
  }
  for (size_t i = 500; i < 1000; ++i) {
    tree.erase(i);
    auto jt = tree.begin();
    ++jt;
    for (auto it = tree.begin(); jt != tree.end(); ++jt, ++it) {
      EXPECT_LE(*it, *jt);
    }
  }
  for (size_t i = 0; i < 500; ++i) {
    tree.erase(tree.begin());
    auto jt = tree.begin();
    if (jt == tree.end()) break;
    ++jt;
    for (auto it = tree.begin(); jt != tree.end(); ++jt, ++it) {
      EXPECT_LE(*it, *jt);
    }
  }
  EXPECT_TRUE(tree.empty());
}

TEST(multiset, erase2) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 1000; ++i) {
    tree.insert(i);
    tree.insert(i);
    multiset.insert(i);
    multiset.insert(i);
  }
  for (size_t i = 500; i < 1000; ++i) {
    tree.erase(i);
    multiset.erase(i);
    auto jt = multiset.begin();
    for (auto it = tree.begin(); jt != multiset.end(); ++jt, ++it) {
      EXPECT_EQ(*it, *jt);
    }
  }
  for (size_t i = 0; i < 500; ++i) {
    tree.erase(i);
    multiset.erase(i);
    auto jt = multiset.begin();
    for (auto it = tree.begin(); jt != multiset.end(); ++jt, ++it) {
      EXPECT_EQ(*it, *jt);
    }
  }
  EXPECT_TRUE(tree.empty());
}

TEST(multiset, contains) {
  vv::Multiset<int> tree;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
  }
  EXPECT_FALSE(tree.contains(-5));
  EXPECT_TRUE(tree.contains(5));
}

TEST(multiset, copy_and_move) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }
  vv::Multiset<int> tree2(tree);
  std::multiset<int> multiset2(multiset);
  EXPECT_EQ(tree2.empty(), multiset2.empty());
  EXPECT_EQ(tree.empty(), multiset.empty());
  vv::Multiset<int> tree5 = tree;
  std::multiset<int> multiset5 = multiset;
  EXPECT_EQ(tree5.empty(), multiset5.empty());
  EXPECT_EQ(tree.empty(), multiset.empty());
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(multiset2.contains(i), tree2.contains(i));
    EXPECT_EQ(multiset5.contains(i), tree5.contains(i));
  }

  vv::Multiset<int> tree3(std::move(tree));
  std::multiset<int> multiset3(std::move(multiset));
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(multiset3.contains(i), tree3.contains(i));
  }
  EXPECT_EQ(multiset.empty(), multiset.empty());

  vv::Multiset<int> tree6(tree6);
  std::multiset<int> multiset6(multiset6);

  EXPECT_EQ(tree6.empty(), multiset6.empty());

  for (size_t i = 0; i < 10; ++i) {
    tree6.insert(i);
    multiset6.insert(i);
  }

  vv::Multiset<int> tree7;
  std::multiset<int> multiset7;
  for (size_t i = 0; i < 10; ++i) {
    tree7.insert(i);
    multiset7.insert(i);
  }

  vv::Multiset<int> tree4 = std::move(tree7);
  std::multiset<int> multiset4 = std::move(multiset7);

  EXPECT_EQ(multiset4.empty(), multiset4.empty());
  for (size_t i = 0; i < 10; ++i) {
    tree4.insert(i);
    multiset4.insert(i);
  }
}

TEST(multiset, merge) {
  vv::Multiset<int> tree;
  std::multiset<int> multiset;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
    multiset.insert(i);
    tree.insert(i);
    multiset.insert(i);
  }
  vv::Multiset<int> tree2;
  std::multiset<int> multiset2;
  for (size_t i = 10; i < 20; ++i) {
    tree2.insert(i);
    multiset2.insert(i);
  }
  tree.merge(tree2);
  multiset.merge(multiset2);
  for (size_t i = 0; i < 20; ++i) {
    EXPECT_EQ(multiset.contains(i), tree.contains(i));
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

TEST(multiset, size) {
  vv::Multiset<int, std::less<int>> tree;
  std::multiset<int, std::less<int>> multiset;
  for (size_t i = 0; i < 10; ++i) {
    tree.insert(i);
    multiset.insert(i);
  }
  EXPECT_EQ(tree.size(), multiset.size());
  tree.erase(tree.begin());
  multiset.erase(multiset.begin());
  EXPECT_EQ(tree.size(), multiset.size());
  tree.erase(tree.begin());
  multiset.erase(multiset.begin());
  EXPECT_EQ(tree.size(), multiset.size());
  tree.clear();
  multiset.clear();
  EXPECT_EQ(tree.size(), multiset.size());
}

TEST(multiset, bounds) {
  vv::Multiset<int, std::less<int>> tree;
  std::multiset<int, std::less<int>> multiset;
  for (size_t i = 0; i < 20; ++i) {
    tree.insert(i);
    multiset.insert(i);
    tree.insert(i);
    multiset.insert(i);
  }
  auto it = multiset.begin();
  for (; it != multiset.end(); ++it) {
    EXPECT_EQ(*(multiset.lower_bound(*it)), *(tree.lower_bound(*it)));
  }
  it = multiset.begin();
  for (; it != multiset.end(); ++it) {
    if (multiset.upper_bound(*it) != multiset.end()) {
      EXPECT_EQ(*(multiset.upper_bound(*it)), *(tree.upper_bound(*it)));
    }
  }
}

TEST(multiset, count) {
  vv::Multiset<int> tree{1, 2, 3, 3, 4, 5, 5, 5};
  std::multiset<int> multiset{1, 2, 3, 3, 4, 5, 5, 5};
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(tree.count(i), multiset.count(i));
  }
}

TEST(multiset, equal_range) {
  vv::Multiset<int> tree{1, 2, 3, 3, 4, 5, 5, 5};
  std::multiset<int> multiset{1, 2, 3, 3, 4, 5, 5, 5};
  for (int i = 0; i < 6; ++i) {
    auto it = tree.equal_range(i).first;
    auto jt = multiset.equal_range(i).first;
    for (; jt != multiset.equal_range(i).second; ++jt, ++it) {
      EXPECT_LE(*it, *jt);
    }
  }
}

TEST(multiset, insert_many) {
  vv::Multiset<size_t> tree;
  auto vec1 = tree.insert_many(size_t(0), size_t(1), size_t(2));
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(*(vec1[i].first), i);
    EXPECT_EQ(vec1[i].second, true);
  }
}
