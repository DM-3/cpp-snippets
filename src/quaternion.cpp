#include <iostream>
#include <math.h>


template<typename T>
struct Quaternion
{
    T x;
    T y;
    T z;
    T w;

    static Quaternion identity;

    Quaternion(T x, T y, T z, T w) :
        x(x), y(y), z(z), w(w) { }

    Quaternion() : 
        Quaternion(0, 0, 0, 0) { }

    static Quaternion fromAxisAngle(T axisX, T axisY, T axisZ, T angle)
    {
        Quaternion q = Quaternion(axisX, axisY, axisZ, 0);
        q.normalize();
        q = q * sin(0.5 * angle);
        q.w = cos(0.5 * angle);
        return q;
    }

    Quaternion operator+(const Quaternion& other) const
        { return { x + other.x, y + other.y, z + other.z, w + other.w }; }

    Quaternion operator-(const Quaternion& other) const
        { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
    
    Quaternion operator*(const T scalar) const
    {
        return {
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar,
        };
    }

    Quaternion operator/(const T scalar) const
        { return *this * (T(1) / scalar); }

    Quaternion operator*(const Quaternion& other) const
    { 
        return { 
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z
        }; 
    }

    double magnitude() const
        { return sqrt(x * x + y * y + z * z + w * w); }

    void normalize()
    {
        double m = 1.0 / magnitude();
        x *= m; 
        y *= m; 
        z *= m; 
        w *= m;
    }

    Quaternion conjugate() const
        { return Quaternion(-x, -y, -z, w); }
};

template<typename T>
Quaternion<T> Quaternion<T>::identity = Quaternion<T>(0, 0, 0, 1);



int main()
{
    using QuatF = Quaternion<float>;
    using QuatD = Quaternion<double>;

    // representation of vector (0, 1, 1) in 3D space
    QuatD q = QuatD(0, 1, 1, 0);

    std::cout << "q: \t[" << q.x << ", " 
                          << q.y << ", " 
                          << q.z << ", " 
                          << q.w << "]" << std::endl;

    // rotate around x, then y, then z axes
    QuatD r1 = QuatD::fromAxisAngle(1, 0, 0, M_PI_2);
    QuatD r2 = QuatD::fromAxisAngle(0, 1, 0, M_PI_2);
    QuatD r3 = QuatD::fromAxisAngle(0, 0, 1, M_PI_2);
    QuatD r = r3 * r2 * r1;
    QuatD qr = r * q * r.conjugate();

    std::cout << "qr: \t[" << qr.x << ", " 
                           << qr.y << ", " 
                           << qr.z << ", " 
                           << qr.w << "]" << std::endl;
}
