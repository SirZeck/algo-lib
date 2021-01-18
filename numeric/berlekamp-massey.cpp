#include <vector>
#include <cstdint>

template<typename T> struct LFSR {
    std::vector<T> seq;
    std::vector<T> fib;
    std::vector<T> galois;

    LFSR(std::vector<T> seq_) : seq(seq_) {
        std::vector<T> C = {1}, B = {1}; T b = 1;
        for (int i = 0, m = 1; i < int(seq.size()); i++, m++) {
            T d = 0; for (int j = 0; j < int(C.size()); j++) d += C[j] * seq[i - j];
            if (d == 0) continue;
            std::vector<T> B_ = C; C.resize(std::max(int(C.size()), m+int(B.size())));
            T dbi = d/b; for (int j = 0; j < int(B.size()); j++) C[m+j] -= dbi * B[j];
            if (int(B_.size()) < m+int(B.size())) { B = B_; b = d; m = 0; }
        }
        galois = vector_operators::reversed(C);
        fib = move(C); fib.erase(fib.begin()); fib *= T{-1};
    }

    T operator[](int64_t n) const {
        std::vector<T> r = vector_operators::dot(seq, vector_operators::mod_pow({0,1}, n, galois));
        return accumulate((r).begin(), (r).end(), T{0});
    }
};
