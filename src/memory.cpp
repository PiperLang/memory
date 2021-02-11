#include <memory/memory.hpp>

namespace piper {
    size_t next_power_of_two(size_t n) {
        size_t p = 1;

        if (n && !(n & (n - 1))) {
            return n;
        }

        while (p < n) {
            p <<= 1;
        }

        return p;
    }
}
