#pragma once
#include "../shared.hpp"

#ifdef INTERCEPT_GLM_INTEROP
#include <glm/glm.hpp>
#endif //INTERCEPT_GLM_INTEROP

namespace intercept {
    constexpr float pi = 3.14159265358979323846f;
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

        template <typename T>
        class vector2_base;

        template<typename T>
        class vector3_base {
        public:

            T x;
            T y;
            T z;

            constexpr vector3_base() noexcept : x{0}, y{0}, z{0}
            {
            }

            constexpr vector3_base(const T x_, const T y_, const T z_) noexcept : x{x_}, y{y_}, z{z_}
            {
            }

            vector3_base(std::istream & read_) {
                // Constructor to read from a stream
                read_.read(reinterpret_cast<char *>(&x), sizeof(T));
                read_.read(reinterpret_cast<char *>(&y), sizeof(T));
                read_.read(reinterpret_cast<char *>(&z), sizeof(T));
            }

            explicit vector3_base(const float* buffer) noexcept : x{buffer[0]}, y{buffer[1]}, z{buffer[2]} {
            }

            constexpr vector3_base(const vector3_base& copy_) noexcept : x{copy_.x}, y{copy_.y}, z{copy_.z} {
            }

            //Allow operations between vector2 and vector3; in the case of vector2, we always assume z = 0 (which is why operator/ was not added)
            constexpr explicit vector3_base(const vector2_base<T>& copy_) noexcept : x{copy_.x}, y{copy_.y}, z{0} {
            }

#ifdef INTERCEPT_GLM_INTEROP
            constexpr vector3_base(const glm::vec3& copy_) noexcept : x{copy_.x}, y{copy_.y}, z{copy_.z} {
            }

            operator glm::vec3() const {
                return {x, y, z};
            }
#endif  //INTERCEPT_GLM_INTEROP

            constexpr T& operator[](unsigned int index_) noexcept {
                switch (index_) {
                    case (0): return x;
                    case (1): return y;
                    default: return z;
                }
            }

            constexpr T operator[](unsigned int index_) const noexcept {
                switch (index_) {
                    case (0): return x;
                    case (1): return y;
                    default: return z;
                }
            }

            constexpr vector3_base& operator= (const vector3_base& other) noexcept { x = other.x; y = other.y; z = other.z; return *this; }
            constexpr vector3_base operator * (const T& val) const noexcept { return vector3_base(x * val, y * val, z * val); }
            constexpr vector3_base operator / (const T& val) const noexcept { T invVal = T(1) / val; return vector3_base(x * invVal, y * invVal, z * invVal); }
            constexpr vector3_base operator + (const vector3_base& v) const noexcept { return vector3_base(x + v.x, y + v.y, z + v.z); }
            constexpr vector3_base operator + (const vector2_base<T>& v) const noexcept { return vector3_base(x + v.x, y + v.y, z); }
            constexpr vector3_base operator / (const vector3_base& v) const noexcept { return vector3_base(x / v.x, y / v.y, z / v.z); }
            constexpr vector3_base operator * (const vector3_base& v) const noexcept { return vector3_base(x * v.x, y * v.y, z * v.z); }
            constexpr vector3_base operator * (const vector2_base<T>& v) const noexcept { return vector3_base(x * v.x, y * v.y, 0); }
            constexpr vector3_base operator - (const vector3_base& v) const noexcept { return vector3_base(x - v.x, y - v.y, z - v.z); }
            constexpr vector3_base operator - (const vector2_base<T>& v) const noexcept { return vector3_base(x - v.x, y - v.y, z); }
            constexpr vector3_base operator - () const noexcept { return vector3_base(-x, -y, -z); }

            constexpr vector3_base& operator *=(const vector3_base& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
            constexpr vector3_base& operator *=(const vector2_base<T>& v) noexcept { x *= v.x; y *= v.y; z = 0; return *this; }
            constexpr vector3_base& operator *=(T mag) noexcept { x *= mag; y *= mag; z *= mag; return *this; }
            constexpr vector3_base& operator /=(const vector3_base& v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
            constexpr vector3_base& operator /=(T mag) noexcept { x /= mag; y /= mag; z /= mag; return *this; }
            constexpr vector3_base& operator +=(const vector3_base& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
            constexpr vector3_base& operator +=(const vector2_base<T>& v) noexcept { x += v.x; y += v.y; return *this; }
            constexpr vector3_base& operator -=(const vector3_base& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
            constexpr vector3_base& operator -=(const vector2_base<T>& v) noexcept { x -= v.x; y -= v.y; return *this; }

            constexpr bool operator == (const vector3_base& r) const noexcept { return (x == r.x && y == r.y && z == r.z); }
            constexpr bool operator == (const vector2_base<T>& r) const noexcept { return (x == r.x && y == r.y && z == 0); }
            constexpr bool operator >  (const vector3_base& r) const noexcept { if (*this == r) return false; return magnitude() > r.magnitude(); }
            constexpr bool operator <  (const vector3_base& r) const noexcept { if (*this == r) return false; return magnitude() < r.magnitude(); }
            constexpr bool operator >= (const vector3_base& r) const noexcept { if (*this == r) return true; return magnitude() > r.magnitude(); }
            constexpr bool operator <= (const vector3_base& r) const noexcept { if (*this == r) return true; return magnitude() < r.magnitude(); }

            constexpr T magnitude() const noexcept { return std::sqrt(x * x + y * y + z * z); }
            constexpr T magnitude_squared() const noexcept { return x * x + y * y + z * z; }
            constexpr T dot(const vector3_base& v) const noexcept { return (x * v.x + y * v.y + z * v.z); }
            constexpr T dot(const vector2_base<T>& v) const noexcept { return (x * v.x + y * v.y); }
            constexpr T cos(const vector3_base& v) const noexcept { T m = magnitude() * v.magnitude(); if (m == 0.0f) return 0.0f; return dot(v) / m; }
            constexpr T cos(const vector2_base<T>& v) const noexcept { T m = magnitude() * v.magnitude(); if (m == 0.0f) return 0.0f; return dot(v) / m; }
            constexpr T angle(const vector3_base& v) const noexcept { return std::acos(cos(v)) / pi * 180.0f; }
            constexpr T angle(const vector2_base<T>& v) const noexcept { return std::acos(cos(v)) / pi * 180.0f; }
            //Azimuth from this vector to the other vector in radians
            constexpr T get_azimuth(const vector3_base& v) const noexcept { return atan2f(x * v.y - y * v.x, x * v.x + y * v.y); }
            //Azimuth from this vector to the other vector in radians
            constexpr T get_azimuth(const vector2_base<T>& v) const noexcept { return atan2f(x * v.y - y * v.x, x * v.x + y * v.y); }
            //Similar to the command: _pos1 getDir _pos2; except the result is in radians, CCW and returns negative for angle > pi
            constexpr T get_dir(const vector3_base& pos) const noexcept { return atan2f(x - pos.x, pos.y - y); }
            //Similar to the command: _pos1 getDir _pos2; except the result is in radians, CCW and returns negative for angle > pi
            constexpr T get_dir(const vector2_base<T>& pos) const noexcept { return atan2f(x - pos.x, pos.y - y); }
            constexpr T distance(const vector3_base& v) const noexcept { return vector3_base(*this - v).magnitude(); }
            constexpr T distance(const vector2_base<T>& v) const noexcept { return vector3_base(*this - v).magnitude(); }
            constexpr T distance_squared(const vector3_base& v) const noexcept { return vector3_base(*this - v).magnitude_squared(); }
            constexpr T distance_squared(const vector2_base<T>& v) const noexcept { return vector3_base(*this - v).magnitude_squared(); }
            constexpr T distance_2d(const vector3_base& v) const noexcept { return vector2_base<T>(v - *this).magnitude(); }
            constexpr T distance_2d(const vector2_base<T>& v) const noexcept { return vector2_base<T>(v - *this).magnitude(); }
            constexpr T distance_2d_squared(const vector3_base& v) const noexcept { return vector2_base<T>(v - *this).magnitude_squared(); }
            constexpr T distance_2d_squared(const vector2_base<T>& v) const noexcept { return vector2_base<T>(v - *this).magnitude_squared(); }
            constexpr vector3_base cross(const vector3_base& v) const noexcept { return vector3_base(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
            constexpr vector3_base cross(const vector2_base<T>& v) const noexcept { return vector3_base(- z * v.y, z * v.x, x * v.y - y * v.x); }
            constexpr vector3_base normalize() const noexcept { T m = magnitude(); if (m == 0) return {0.f, 0.f, 0.f}; return (*this / m); }
            constexpr vector3_base dir_to(const vector3_base& v) const noexcept { return vector3_base(v - * this).normalize(); }
            constexpr vector3_base dir_to(const vector2_base<T>& v) const noexcept { return vector3_base(v - *this).normalize(); }
            constexpr vector3_base dir_to_2d(const vector3_base& v) const noexcept { return vector3_base(vector2_base<T>(v - *this).normalize()); }
            constexpr vector3_base dir_to_2d(const vector2_base<T>& v) const noexcept { return vector3_base(vector2_base<T>(v - *this).normalize()); }
            constexpr vector3_base rotate_x(const T& rad) const noexcept { return vector3_base(x, y * std::cos(rad) - z * std::sin(rad), y * std::sin(rad) + z * std::cos(rad)); }
            constexpr vector3_base rotate_y(const T& rad) const noexcept { return vector3_base(x * std::cos(rad) + z * std::sin(rad), y, z * std::cos(rad) - x * std::sin(rad)); }
            constexpr vector3_base rotate_z(const T& rad) const noexcept { return vector3_base(x * std::cos(rad) - y * std::sin(rad), y * std::cos(rad) + x * std::sin(rad), z); }
            constexpr vector3_base rotate_x_deg(const T& deg) const noexcept { return rotate_x(deg * pi / 180.0f); }
            constexpr vector3_base rotate_y_deg(const T& deg) const noexcept { return rotate_y(deg * pi / 180.0f); }
            constexpr vector3_base rotate_z_deg(const T& deg) const noexcept { return rotate_z(deg * pi / 180.0f); }
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

            constexpr vector2_base() noexcept : x{0}, y{0} {
            }

            constexpr vector2_base(const T x_, const T y_) noexcept : x{x_}, y{y_} {
            }

            vector2_base(std::istream& read_) {
                // Constructor to read from a stream
                read_.read(reinterpret_cast<char*>(&x), sizeof(T));
                read_.read(reinterpret_cast<char*>(&y), sizeof(T));
            }

            explicit vector2_base(const float* buffer) noexcept : x{buffer[0]}, y{buffer[1]} {
            }

            constexpr vector2_base(const vector2_base& copy_) noexcept : x{copy_.x}, y{copy_.y} {
            }

            constexpr explicit vector2_base(const vector3_base<T>& copy_) noexcept : x{copy_.x}, y{copy_.y} {
            }

#ifdef INTERCEPT_GLM_INTEROP
            constexpr vector2_base(const glm::vec2& copy_) noexcept : x{copy_.x}, y{copy_.y} {
            }

            operator glm::vec2() const {
                return {x, y};
            }
#endif  //INTERCEPT_GLM_INTEROP

            constexpr T& operator[](unsigned int index_) noexcept {
                return (index_ == 0) ? x : y;
            }

            constexpr T operator[](unsigned int index_) const noexcept {
                return (index_ == 0) ? x : y;
            }

            constexpr vector2_base& operator= (const vector2_base& other) noexcept { x = other.x; y = other.y; return *this; }
            constexpr vector2_base operator * (const T &val) const noexcept { return vector2_base(x * val, y * val); }
            constexpr vector2_base operator / (const T &val) const noexcept { T invVal = T(1) / val; return vector2_base(x * invVal, y * invVal); }
            constexpr vector2_base operator + (const vector2_base& v) const noexcept { return vector2_base(x + v.x, y + v.y); }
            constexpr vector2_base operator + (const vector3_base<T>& v) const noexcept { return vector2_base(x + v.x, y + v.y); }
            constexpr vector2_base operator / (const vector2_base& v) const noexcept { return vector2_base(x / v.x, y / v.y); }
            constexpr vector2_base operator / (const vector3_base<T>& v) const noexcept { return vector2_base(x / v.x, y / v.y); }
            constexpr vector2_base operator * (const vector2_base& v) const noexcept { return vector2_base(x * v.x, y * v.y); }
            constexpr vector2_base operator * (const vector3_base<T>& v) const noexcept { return vector2_base(x * v.x, y * v.y); }
            constexpr vector2_base operator - (const vector2_base& v) const noexcept { return vector2_base(x - v.x, y - v.y); }
            constexpr vector2_base operator - (const vector3_base<T>& v) const noexcept { return vector2_base(x - v.x, y - v.y); }
            constexpr vector2_base operator - () const noexcept { return vector2_base(-x, -y); }

            constexpr vector2_base& operator *=(const vector2_base& v) noexcept { x *= v.x; y *= v.y; return *this;}
            constexpr vector2_base& operator *=(const vector3_base<T>& v) noexcept { x *= v.x; y *= v.y; return *this;}
            constexpr vector2_base& operator *=(T mag) noexcept { x *= mag; y *= mag; return *this; }
            constexpr vector2_base& operator /=(const vector2_base& v) noexcept { x /= v.x; y /= v.y; return *this; }
            constexpr vector2_base& operator /=(const vector3_base<T>& v) noexcept { x /= v.x; y /= v.y; return *this; }
            constexpr vector2_base& operator /=(T mag) noexcept { x /= mag; y /= mag; return *this; }
            constexpr vector2_base& operator +=(const vector2_base& v) noexcept{ x += v.x; y += v.y; return *this; }
            constexpr vector2_base& operator +=(const vector3_base<T>& v) noexcept{ x += v.x; y += v.y; return *this; }
            constexpr vector2_base& operator -=(const vector2_base& v) noexcept{ x -= v.x; y -= v.y; return *this; }
            constexpr vector2_base& operator -=(const vector3_base<T>& v) noexcept{ x -= v.x; y -= v.y; return *this; }

            constexpr bool operator == (const vector2_base& r) const noexcept { return (x == r.x && y == r.y); }
            constexpr bool operator == (const vector3_base<T>& r) const noexcept { return (x == r.x && y == r.y); }
            constexpr bool operator >  (const vector2_base& r) const noexcept { if (*this == r) return false; return magnitude() > r.magnitude(); }
            constexpr bool operator <  (const vector2_base& r) const noexcept { if (*this == r) return false; return magnitude() < r.magnitude(); }
            constexpr bool operator >= (const vector2_base& r) const noexcept { if (*this == r) return true; return magnitude() > r.magnitude(); }
            constexpr bool operator <= (const vector2_base& r) const noexcept { if (*this == r) return true; return magnitude() < r.magnitude(); }

            constexpr T magnitude() const noexcept { return std::sqrt(x * x + y * y); }
            constexpr T magnitude_squared() const noexcept { return x * x + y * y; }
            constexpr T dot(const vector2_base& v) const noexcept { return (x * v.x + y * v.y); }
            constexpr T dot(const vector3_base<T>& v) const noexcept { return (x * v.x + y * v.y); }
            constexpr T cos(const vector2_base& v) const noexcept { T m = magnitude() * v.magnitude(); if (m == 0.0f) return 0.0f; return dot(v) / m; }
            constexpr T cos(const vector3_base<T>& v) const noexcept { T m = magnitude() * v.magnitude(); if (m == 0.0f) return 0.0f; return dot(v) / m; }
            constexpr T angle(const vector2_base& v) const noexcept { return std::acos(cos(v)) / pi * 180.0f; }
            constexpr T angle(const vector3_base<T>& v) const noexcept { return std::acos(cos(v)) / pi * 180.0f; }
            //Azimuth from this vector to the other vector in radians
            constexpr T get_azimuth(const vector2_base& v) const noexcept { return atan2f(x * v.y - y * v.x, x * v.x + y * v.y); }
            //Azimuth from this vector to the other vector in radians
            constexpr T get_azimuth(const vector3_base<T>& v) const noexcept { return atan2f(x * v.y - y * v.x, x * v.x + y * v.y); }
            //Similar to the command: _pos1 getDir _pos2; except the result is in radians, CCW and returns negative for angle > pi
            constexpr T get_dir(const vector2_base& pos) const noexcept { return atan2f(x - pos.x, pos.y - y); }
            //Similar to the command: _pos1 getDir _pos2; except the result is in radians, CCW and returns negative for angle > pi
            constexpr T get_dir(const vector3_base<T>& pos) const noexcept { return atan2f(x - pos.x, pos.y - y); }
            constexpr T distance(const vector2_base& v) const noexcept { return vector2_base(*this - v).magnitude(); }
            constexpr T distance(const vector3_base<T>& v) const noexcept { return vector2_base(*this - v).magnitude(); }
            constexpr T distance_squared(const vector2_base& v) const noexcept{ return vector2_base(*this - v).magnitude_squared(); }
            constexpr T distance_squared(const vector3_base<T>& v) const noexcept { return vector2_base(*this - v).magnitude_squared(); }
            constexpr vector2_base normalize() const noexcept { T m = magnitude(); if (m == 0) return {0.f, 0.f}; return (*this / m); }
            constexpr vector2_base rotate(const T& rad) const noexcept { return vector2_base(x * std::cos(rad) - y * std::sin(rad), y * std::cos(rad) + x * std::sin(rad)); }
            constexpr vector2_base rotate_deg(const T& deg) const noexcept { return rotate(deg * pi / 180.0f); }
            constexpr bool zero_distance() const noexcept { return ((x == 0.0f && y == 0.0f) ? true : false); }
            constexpr vector2_base dir_to(const vector2_base& v) const noexcept { return vector2_base(v - *this).normalize(); }
            constexpr vector2_base dir_to(const vector3_base<T>& v) const noexcept { return vector2_base(v - *this).normalize(); }
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
