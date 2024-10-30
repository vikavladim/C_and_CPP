#ifndef VV_CONTAINERS_LIB_PAIR_KEY_COMPARATOR_H
#define VV_CONTAINERS_LIB_PAIR_KEY_COMPARATOR_H

namespace vv {

namespace map_support {

template <typename Key, typename Value, typename Comparator>
struct PairKeyComparator {
  Comparator comp;

  bool operator()(const std::pair<const Key, Value> &lhs,
                  const std::pair<const Key, Value> &rhs) const {
    return comp(lhs.first, rhs.first);
  }
};

}  // namespace map_support

}  // namespace vv

#endif  // VV_CONTAINERS_LIB_PAIR_KEY_COMPARATOR_H
