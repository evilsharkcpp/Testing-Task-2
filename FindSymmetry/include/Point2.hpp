#pragma once

#include<string>
#include<algorithm>

/// <summary>
/// This struct represents point in 2D plane (x, y)
/// </summary>
/// <typeparam name="T">template parameter</typeparam>
template <typename T>
struct Point2 {
    T x, y;

    /// <summary>
    /// Init constructor
    /// </summary>
    /// <param name="x">x coord</param>
    /// <param name="y">y coord</param>
    Point2(const T& x, const T& y) : x(x), y(y) {}
    
    /// <summary>
    /// base constructor
    /// </summary>
    Point2() : Point2(0, 0) {}

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="p">copied point</param>
    Point2(const Point2& p) : x(p.x), y(p.y) {}

    //Assignment operations

    Point2& operator=(const Point2& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

    Point2& operator+=(const Point2& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point2& operator-=(const Point2& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point2& operator/=(double a) {
        x /= a;
        y /= a;
        return *this;
    }

    //Math operations

    friend Point2 operator+(const Point2& p1, const Point2& p2) {
        return Point2(p1.x + p2.x, p1.y + p2.y);
    }

    friend Point2 operator-(const Point2& p1, const Point2& p2) {
        return Point2(p1.x - p2.x, p1.y - p2.y);
    }

    friend Point2 operator*(const Point2& p, T a) {
        return Point2(a * p.x, a * p.y);
    }

    friend Point2 operator*(T a, const Point2& p) {
        return Point2(a * p.x, a * p.y);
    }

    friend Point2 operator/(const Point2& p, T a) {
        return Point2(p.x / a, p.y / a);
    }

    friend Point2 operator/(T a, const Point2& p) {
        return Point2(a / p.x, a / p.y);
    }

    /// <summary>
    /// Compare 2 points with presision epsilon
    /// </summary>
    /// <param name="p">point for compare</param>
    /// <param name="epsilon">presision</param>
    /// <returns>true if this point is equal p else false</returns>
    bool isEqual(Point2& p, double epsilon) {
        return equalValues(x, p.x, epsilon) && equalValues(y, p.y, epsilon);
    }

    bool Point2::equalValues(double a, double b, double epsilon) {
        double max = std::max({ 1.0, std::fabs(a) , std::fabs(b) });
        return std::fabs(a - b) <= epsilon * max;
    }

    /// <summary>
    /// Normalize point
    /// </summary>
    /// <returns>return normalized point</returns>
    Point2 getNormalized() const {
        T norm { sqrt(x * x + y * y) };
        
        if(norm == 0) {
            throw std::exception("division by 0");
        }
        
        return Point2(x / norm, y / norm);
    }

    /// <summary>
    /// Convert point into string format
    /// </summary>
    /// <returns></returns>
    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};