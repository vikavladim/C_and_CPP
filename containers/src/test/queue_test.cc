#include <list>
#include <queue>

#include "gtest/gtest.h"
#include "test_class.h"
#include "vv_containers.h"

class QueueTest : public ::testing::Test {
 protected:
  QueueTest() {}

  template <typename T, template <typename> class ContainerFirst,
            template <typename> class ContainerSecond>
  static void check_with_std(vv::queue<T, ContainerFirst<T>> que,
                             std::queue<T, ContainerSecond<T>> stdque) {
    EXPECT_EQ(que.size(), stdque.size());
    while (stdque.size() > 0) {
      EXPECT_EQ(que.front(), stdque.front());
      EXPECT_EQ(que.size(), stdque.size());
      que.pop();
      stdque.pop();
    }
  }
};

TEST_F(QueueTest, ListBase) {
  testClass name("Maron", "Kubanov");
  vv::queue<testClass> a = {
      {"Alfa", "Omega"}, {"Delta", "Theta"}, {"union", "except"}};
  std::queue b(std::list<testClass>{
      {"Alfa", "Omega"}, {"Delta", "Theta"}, {"union", "except"}});
  check_with_std<testClass, vv::list, std::list>(a, b);
  a.push(name);
  b.push(name);
  check_with_std<testClass, vv::list, std::list>(a, b);
  a.push(testClass("232", "3232"));
  b.push(testClass("232", "3232"));
  check_with_std<testClass, vv::list, std::list>(a, b);
  vv::queue for_swap(vv::list<testClass>{{"1", "2"}, {"3", "4"}, {"5", "6"}});
  std::queue std_for_swap(
      std::list<testClass>{{"1", "2"}, {"3", "4"}, {"5", "6"}});
  for_swap.swap(a);
  std_for_swap.swap(b);
  check_with_std<testClass, vv::list, std::list>(a, b);
  check_with_std<testClass, vv::list, std::list>(for_swap, std_for_swap);
}
