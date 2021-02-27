// {{{ data_structures/monotonic_stack }}}

#include <algorithm>
#include <cassert>
#include <functional>

template <typename T, typename LessThan = std::less<T>>
struct monotonic_queue {
    monotonic_stack<T, LessThan> in, out;
    LessThan less_than;

  public:
    bool empty() const { return in.empty() && out.empty(); }
    int size() const { return in.size() + out.size(); }
    T front() {
        assert(!empty());
        refill();
        return out.top();
    }

    void push(const T &item) { in.push(item); }

    void pop() {
        assert(!empty());
        refill();
        out.pop();
    }

    T min() const {
        assert(!empty());
        if (in.empty())
            return out.min();
        if (out.empty())
            return in.min();
        return std::min(in.min(), out.min(), less_than);
    }

    T min(const T &default_value) const { return empty() ? default_value : min(); }

  private:
    void refill() {
        if (!out.empty())
            return;
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }
};
