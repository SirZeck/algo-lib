#include <vector>
#include <numeric>
#include <iostream>

struct union_find {
    struct node {
        int parent_or_size;
        node () : parent_or_size(-1) {}
    };

    mutable std::vector<node> data;

    union_find(int SZ = 0) : data(SZ) {}

    // Returns the root of the component containing i
    int find(int i) const {
        if (data[i].parent_or_size < 0)
            return i;
        data[i].parent_or_size = find(data[i].parent_or_size);
        return data[i].parent_or_size;
    }

    int size(int i) const {
        return -data[find(i)].parent_or_size;
    }

    bool is_root(int i) const {
        return data[i].parent_or_size < 0;
    }

    node& operator[] (int i) const {
        return data[find(i)];
    }

    /* Unites the components containing a and b if they are different.
     * Returns a boolean indicating whether a and b were in different components.
     */
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (-data[a].parent_or_size < -data[b].parent_or_size)
            std::swap(a, b);

        data[a].parent_or_size += data[b].parent_or_size;
        data[b].parent_or_size = a;

        return true;
    }

    friend void pr(const union_find& u) {
        std::cout << "{";
        bool first = 1;
        for (int i = 0; i < int(u.data.size()); i++) {
            if (u.is_root(i)) {
                if (!first) std::cout << ", ";
                else first = 0;
                std::cout << "[ " << i << " | size=" << u.size(i) << " ]";
            }
        }
        std::cout << "}";
    }
};
