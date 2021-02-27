#include <algorithm>
#include <cassert>
#include <functional>
#include <stack>

template <typename T, typename LessThan = std::less<T>>
struct monotonic_stack {
    std::stack<std::pair<T, T>> data;
    LessThan less_than;

  public:
    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }
    T top() const { return data.top().first; };

    void push(const T &item) {
        T next_min = empty() ? item : std::min(item, min(), less_than);
        data.push({item, next_min});
    }

    void pop() {
        assert(!empty());
        data.pop();
    }

    T min() const {
        assert(!empty());
        return data.top().second;
    };

    T min(const T &default_value) const { return empty() ? default_value : min(); }
};
