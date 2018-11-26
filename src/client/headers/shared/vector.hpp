#pragma once
#include "../shared.hpp"
namespace intercept {
    namespace types {

        template<class _Ty> //Copy from STL headers. Because GCC6 doesn't support it
        constexpr const _Ty& clamp(const _Ty& _Val, const _Ty& _Min_val,
            const _Ty& _Max_val) {// returns _Val constrained to [_Min_val, _Max_val] ordered by _Pred
            return (_Max_val < _Val
                ? _Max_val
                : _Val < _Min_val
                ? _Min_val
                : _Val);
        }


        template<typename T>
        class vector3_base {
        public:

            T x;
            T y;
            T z;

            vector3_base() noexcept
            {
                x = 0;
                y = 0;
                z = 0;
            }

            vector3_base(const T x_, const T y_, const T z_) noexcept
            {
                x = x_;
                y = y_;
                z = z_;
            }

            vector3_base(std::istream & read_) {
                // Constructor to read from a stream
                read_.read(reinterpret_cast<char *>(&x), sizeof(T));
                read_.read(reinterpret_cast<char *>(&y), sizeof(T));
                read_.read(reinterpret_cast<char *>(&z), sizeof(T));
            }

            explicit vector3_base(const float *buffer) noexcept {
                x = buffer[0];
                y = buffer[1];
                z = buffer[2];
            }

            constexpr vector3_base(const vector3_base& copy_) noexcept {
                x = copy_.x;
                y = copy_.y;
                z = copy_.z;
            }

            constexpr vector3_base& operator= (const vector3_base& other) noexcept { x = other.x; y = other.y; z = other.z; return *this; }
            constexpr vector3_base operator * (const T& val) const noexcept { return vector3_base(x * val, y * val, z * val); }
            constexpr vector3_base operator / (const T& val) const noexcept { T invVal = T(1) / val; return vector3_base(x * invVal, y * invVal, z * invVal); }
            constexpr vector3_base operator + (const vector3_base& v) const noexcept { return vector3_base(x + v.x, y + v.y, z + v.z); }
            constexpr vector3_base operator / (const vector3_base& v) const noexcept { return vector3_base(x / v.x, y / v.y, z / v.z); }
            constexpr vector3_base operator * (const vector3_base& v) const noexcept { return vector3_base(x * v.x, y * v.y, z * v.z); }
            constexpr vector3_base operator - (const vector3_base& v) const noexcept { return vector3_base(x - v.x, y - v.y, z - v.z); }
            constexpr vector3_base operator - () const noexcept { return vector3_base(-x, -y, -z); }

            constexpr vector3_base& operator *=(const vector3_base& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
            constexpr vector3_base& operator *=(T mag) noexcept { x *= mag; y *= mag; z *= mag; return *this; }
            constexpr vector3_base& operator /=(const vector3_base& v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
            constexpr vector3_base& operator /=(T mag) noexcept { x /= mag; y /= mag; z /= mag; return *this; }
            constexpr vector3_base& operator +=(const vector3_base& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
            constexpr vector3_base& operator -=(const vector3_base& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }

            constexpr bool operator == (const vector3_base& r) const noexcept { return (x == r.x && y == r.y && z == r.z); }
            constexpr bool operator >  (const vector3_base& r) const noexcept { if (*this == r) return false; return magnitude() > r.magnitude(); }
            constexpr bool operator <  (const vector3_base& r) const noexcept { if (*this == r) return false; return magnitude() < r.magnitude(); }
            constexpr bool operator >= (const vector3_base& r) const noexcept { if (*this == r) return true; return magnitude() > r.magnitude(); }
            constexpr bool operator <= (const vector3_base& r) const noexcept { if (*this == r) return true; return magnitude() < r.magnitude(); }

            constexpr T magnitude() const noexcept { return std::sqrt(x * x + y * y + z * z); }
            constexpr T magnitude_squared() const noexcept { return x * x + y * y + z * z; }
            constexpr T dot(const vector3_base& v) const noexcept { return (x * v.x + y * v.y + z * v.z); }
            constexpr T distance(const vector3_base& v) const noexcept { vector3_base dist = (*this - v); dist = dist * dist; return std::sqrt(dist.x + dist.y + dist.z); }
            constexpr T distance_squared(const vector3_base& v) const noexcept { vector3_base dist = (*this - v); dist = dist * dist; return (dist.x + dist.y + dist.z); }
            constexpr T distance_2d(const vector3_base& v) const noexcept { vector3_base dist = (*this - v); dist = dist * dist; return std::sqrt(dist.x + dist.y); }
            constexpr T distance_2d_squared(const vector3_base& v) const noexcept { vector3_base dist = (*this - v); dist = dist * dist; return (dist.x + dist.y); }
            constexpr vector3_base cross(const vector3_base& v) const noexcept { return vector3_base(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
            constexpr vector3_base normalize() const noexcept { return (*this / std::abs(magnitude())); }
            constexpr bool zero_distance() const noexcept { return ((x == 0.0f && y == 0.0f && z == 0.0f) ? true : false); }

            static constexpr vector3_base lerp(const vector3_base& A, const vector3_base& B, const T t) noexcept { return A*t + B*(1.f - t); }
            /// @brief linear interpolate
            constexpr vector3_base lerp(const vector3_base& B, const T t) noexcept { return vector3_base::lerp(*this, B, t); }

            /// @brief spherical linear interpolate
            static constexpr vector3_base slerp(vector3_base start, vector3_base end, T percent) noexcept {
                T dot = start.dot(end);
                dot = clamp(dot, -1.0f, 1.0f);

                T theta = std::acos(dot) * percent;
                vector3_base relative = end - start*dot;
                return ((start * std::cos(theta)) + (relative.normalize()*std::sin(theta)));
            }
            /// @brief spherical linear interpolate
            constexpr vector3_base slerp(const vector3_base& B, const T p) const noexcept {
                return vector3_base::slerp(*this, B, p);
            }
        };

        template<typename T>
        class vector2_base {
        public:

            T x;
            T y;

            constexpr vector2_base() noexcept
            {
                x = 0;
                y = 0;
            }

            constexpr vector2_base(const T x_, const T y_) noexcept
            {
                x = x_;
                y = y_;
            }

            vector2_base(std::istream & read_) {
                // Constructor to read from a stream
                read_.read(reinterpret_cast<char *>(&x), sizeof(T));
                read_.read(reinterpret_cast<char *>(&y), sizeof(T));
            }

            explicit vector2_base(const float *buffer) {
                x = buffer[0];
                y = buffer[1];
            }

            constexpr vector2_base(const vector2_base<T>& copy_) noexcept {
                x = copy_.x;
                y = copy_.y;
            }

            constexpr vector2_base& operator= (const vector2_base& other) noexcept { x = other.x; y = other.y; return *this; }
            constexpr vector2_base operator * (const T &val) const noexcept { return vector2_base(x * val, y * val); }
            constexpr vector2_base operator / (const T &val) const noexcept { T invVal = T(1) / val; return vector2_base(x * invVal, y * invVal); }
            constexpr vector2_base operator + (const vector2_base& v) const noexcept { return vector2_base(x + v.x, y + v.y); }
            constexpr vector2_base operator / (const vector2_base& v) const noexcept { return vector2_base(x / v.x, y / v.y); }
            constexpr vector2_base operator * (const vector2_base& v) const noexcept { return vector2_base(x * v.x, y * v.y); }
            constexpr vector2_base operator - (const vector2_base& v) const noexcept { return vector2_base(x - v.x, y - v.y); }
            constexpr vector2_base operator - () const noexcept { return vector2_base(-x, -y); }

            constexpr vector2_base& operator *=(const vector2_base& v) noexcept { x *= v.x; y *= v.y; return *this;}
            constexpr vector2_base& operator *=(T mag) noexcept { x *= mag; y *= mag; return *this; }
            constexpr vector2_base& operator /=(const vector2_base& v) noexcept { x /= v.x; y /= v.y; return *this; }
            constexpr vector2_base& operator /=(T mag) noexcept { x /= mag; y /= mag; return *this; }
            constexpr vector2_base& operator +=(const vector2_base& v) noexcept{ x += v.x; y += v.y; return *this; }
            constexpr vector2_base& operator -=(const vector2_base& v) noexcept{ x -= v.x; y -= v.y; return *this; }

            constexpr bool operator == (const vector2_base& r) const noexcept { return (x == r.x && y == r.y); }
            constexpr bool operator >  (const vector2_base& r) const noexcept { if (*this == r) return false; return magnitude() > r.magnitude(); }
            constexpr bool operator <  (const vector2_base& r) const noexcept { if (*this == r) return false; return magnitude() < r.magnitude(); }
            constexpr bool operator >= (const vector2_base& r) const noexcept { if (*this == r) return true; return magnitude() > r.magnitude(); }
            constexpr bool operator <= (const vector2_base& r) const noexcept { if (*this == r) return true; return magnitude() < r.magnitude(); }

            constexpr T magnitude() const noexcept { return std::sqrt(x * x + y * y); }
            constexpr T magnitude_squared() const noexcept { return x * x + y * y; }
            constexpr T dot(const vector2_base& v) const noexcept { return (x * v.x + y * v.y); }
            constexpr T distance(const vector2_base& v) const noexcept { vector2_base dist = (*this - v); dist = dist * dist; return std::sqrt(dist.x + dist.y); }
            constexpr T distance_squared(const vector2_base& v) const noexcept{ vector2_base dist = (*this - v); dist = dist * dist; return (dist.x + dist.y); }
            constexpr vector2_base normalize() const noexcept { return (*this / std::abs(magnitude())); }
            constexpr bool zero_distance() const noexcept { return ((x == 0.0f && y == 0.0f) ? true : false); }
            
            /// @brief linear interpolate
            static constexpr vector2_base lerp(const vector2_base& A, const vector2_base& B, const T t) noexcept { return A*t + B*(1.f - t); }
            /// @brief linear interpolate
            constexpr vector2_base lerp(const vector2_base& B, const T t) const noexcept { return vector2_base::lerp(*this, B, t); }
            
            /// @brief spherical linear interpolate
            static constexpr vector2_base slerp(vector2_base start, vector2_base end, T percent) noexcept {
                T dot = start.dot(end);
                dot = clamp(dot, -1.0f, 1.0f);

                T theta = std::acos(dot) * percent;
                vector2_base relative = end - start*dot;
                return ((start * std::cos(theta)) + (relative.normalize()*std::sin(theta)));
            }
            /// @brief spherical linear interpolate
            constexpr vector2_base slerp(const vector2_base& B, const T p) const noexcept {
                return vector2_base::slerp(*this, B, p);
            }
        };

        typedef vector3_base<float> vector3;
        typedef vector2_base<float> vector2;
    }
}
