#include "shared/vector.hpp"


namespace intercept {
    namespace types {
        template <> float acos(float n) { return ::acosf(n); }
        template <> double acos(double n) { return ::acos(n); }
        template <> float cos(float n) { return ::cosf(n); }
        template <> double cos(double n) { return ::cos(n); }
        template <> float sin(float n) { return ::sinf(n); }
        template <> double sin(double n) { return ::sin(n); }
    }
}
