#pragma once
#include "shared.hpp"
namespace intercept {
    namespace types {

        template <typename T> T acos(T) { return -1; }
        template <typename T> T cos(T) { return -1; }
        template <typename T> T sin(T) { return -1; }

        template<typename T>
        class vector3_base {
        public:

            T x;
            T y;
            T z;

            vector3_base()
            {
                x = 0;
                y = 0;
                z = 0;
            }

            vector3_base(const T x_, const T y_, const T z_)
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

            vector3_base(const float *buffer) {
                x = buffer[0];
                y = buffer[1];
                z = buffer[2];
            }

            vector3_base(const vector3_base<T>& copy_) {
                x = copy_.x;
                y = copy_.y;
                z = copy_.z;
            }

            vector3_base<T> & operator= (const vector3_base<T>& other) { x = other.x; y = other.y; z = other.z; return *this; }
            vector3_base operator * (const T &val) const { return vector3_base(x * val, y * val, z * val); }
            vector3_base operator / (const T &val) const { T invVal = T(1) / val; return vector3_base(x * invVal, y * invVal, z * invVal); }
            vector3_base operator + (const vector3_base<T> &v) const { return vector3_base(x + v.x, y + v.y, z + v.z); }
            vector3_base operator / (const vector3_base &v) const { return vector3_base(x / v.x, y / v.y, z / v.z); }
            vector3_base operator * (const vector3_base &v) const { return vector3_base(x * v.x, y * v.y, z * v.z); }
            vector3_base operator - (const vector3_base &v) const { return vector3_base(x - v.x, y - v.y, z - v.z); }
            vector3_base operator - () const { return vector3_base(-x, -y, -z); }

            bool operator == (const vector3_base &r) const { return (x == r.x && y == r.y && z == r.z); }
            bool operator >  (const vector3_base &) const { throw 1; }
            bool operator <  (const vector3_base &) const { throw 1; }
            bool operator <= (const vector3_base &) const { throw 1; }
            bool operator >= (const vector3_base &) const { throw 1; }

            T magnitude() const { return sqrt(x * x + y * y + z * z); }
            T dot(const vector3_base &v) const { return (x * v.x + y * v.y + z * v.z); }
            T distance(const vector3_base &v) const { vector3_base dist = (*this - v); dist = dist * dist; return sqrt(dist.x + dist.y + dist.z); }
            T distance_squared(const vector3_base &v) const { vector3_base dist = (*this - v); dist = dist * dist; return (dist.x + dist.y + dist.z); }
            T distance_2d(const vector3_base &v) const { vector3_base dist = (*this - v); dist = dist * dist; return sqrt(dist.x + dist.y); }
            T distance_2d_squared(const vector3_base &v) const { vector3_base dist = (*this - v); dist = dist * dist; return (dist.x + dist.y); }
            vector3_base cross(const vector3_base &v) const { return vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
            vector3_base normalize(void) const { return (*this / abs(magnitude())); };
            bool zero_distance() { return ((x == 0.0f && y == 0.0f && z == 0.0f) ? true : false); }

            static float clamp(T x, T a, T b) { return x < a ? a : (x > b ? b : x); }

            static vector3_base lerp(const vector3_base& A, const vector3_base& B, const T t) { return A*t + B*(1.f - t); }
            vector3_base lerp(const vector3_base& B, const T t) { return vector3_base::lerp(*this, B, t); }

            static vector3_base slerp(vector3_base start, vector3_base end, T percent) {
                T dot = start.dot(end);
                dot = vector3_base::clamp(dot, -1.0f, 1.0f);

                T theta = acos(dot) * percent;
                vector3_base relative = end - start*dot;
                relative.normalize();
                return ((start * cos(theta)) + (relative*sin(theta)));
            }
            vector3_base slerp(const vector3_base& B, const T p) {
                return vector3_base::slerp(*this, B, p);
            }
        };

        template<typename T>
        class vector2_base {
        public:

            T x;
            T y;

            vector2_base()
            {
                x = 0;
                y = 0;
            }

            vector2_base(const T x_, const T y_)
            {
                x = x_;
                y = y_;
            }

            vector2_base(std::istream & read_) {
                // Constructor to read from a stream
                read_.read(reinterpret_cast<char *>(&x), sizeof(T));
                read_.read(reinterpret_cast<char *>(&y), sizeof(T));
            }
            vector2_base(const float *buffer) {
                x = buffer[0];
                y = buffer[1];
            }

            vector2_base(const vector2_base<T>& copy_) {
                x = copy_.x;
                y = copy_.y;
            }

            vector2_base<T> & operator= (const vector2_base<T>& other) { x = other.x; y = other.y; return *this; }
            vector2_base operator * (const T &val) const { return vector2_base(x * val, y * val); }
            vector2_base operator / (const T &val) const { T invVal = T(1) / val; return vector2_base(x * invVal, y * invVal); }
            vector2_base operator + (const vector2_base<T> &v) const { return vector2_base(x + v.x, y + v.y); }
            vector2_base operator / (const vector2_base &v) const { return vector2_base(x / v.x, y / v.y); }
            vector2_base operator * (const vector2_base &v) const { return vector2_base(x * v.x, y * v.y); }
            vector2_base operator - (const vector2_base &v) const { return vector2_base(x - v.x, y - v.y); }
            vector2_base operator - () const { return vector2_base(-x, -y); }

            bool operator == (const vector2_base &r) const { return (x == r.x && y == r.y); }
            bool operator >  (const vector2_base &) const { throw 1; }
            bool operator <  (const vector2_base &) const { throw 1; }
            bool operator <= (const vector2_base &) const { throw 1; }
            bool operator >= (const vector2_base &) const { throw 1; }

            T magnitude() const { return sqrt(x * x + y * y); }
            T dot(const vector2_base &v) const { return (x * v.x + y * v.y); }
            T distance(const vector2_base &v) const { vector2_base dist = (*this - v); dist = dist * dist; return sqrt(dist.x + dist.y); }
            T distance_squared(const vector2_base &v) const { vector2_base dist = (*this - v); dist = dist * dist; return (dist.x + dist.y); }
            vector2_base cross(const vector2_base &v) const { return vector2_base(v.y, -v.x); }
            vector2_base normalize(void) const { return (*this / abs(magnitude())); };
            bool zero_distance() { return ((x == 0.0f && y == 0.0f) ? true : false); }

            static float clamp(T x, T a, T b) { return x < a ? a : (x > b ? b : x); }

            static vector2_base lerp(const vector2_base& A, const vector2_base& B, const T t) { return A*t + B*(1.f - t); }
            vector2_base lerp(const vector2_base& B, const T t) { return vector2_base::lerp(*this, B, t); }

            static vector2_base slerp(vector2_base start, vector2_base end, T percent) {
                T dot = start.dot(end);
                dot = vector2_base::clamp(dot, -1.0f, 1.0f);

                T theta = acos(dot) * percent;
                vector2_base relative = end - start*dot;
                relative.normalize();
                return ((start * cos(theta)) + (relative*sin(theta)));
            }
            vector2_base slerp(const vector2_base& B, const T p) {
                return vector2_base::slerp(*this, B, p);
            }
        };

        typedef vector3_base<float> vector3;
        typedef vector2_base<float> vector2;
    }
}