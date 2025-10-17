#include <vector>
#include <iterator>
#include <type_traits>

static_assert(std::is_same_v<
    std::iterator_traits<std::vector<int>::iterator>::iterator_category,
    std::random_access_iterator_tag>);
