#pragma once

#include<string>

/// <summary>
/// class that represents an axis as two points
/// </summary>
/// <typeparam name="T">template parameter</typeparam>
template<class T>
class Axis {
    public:
        /// <summary>
        /// base constructor
        /// </summary>
        Axis() : m_start({}), m_end({}) {}
        /// <summary>
        /// Init constructor
        /// </summary>
        /// <param name="a">first point</param>
        /// <param name="b">second point</param>
        Axis(const Point2<T>& a, const Point2<T>& b) : m_start(a), m_end(b) {}

        /// <summary>
        /// Compare two axis with epsilon presision
        /// </summary>
        /// <param name="axis">second axis</param>
        /// <param name="epsilon">presision</param>
        /// <returns>true if this axis is equal to another else false</returns>
        bool isEqual(Axis& axis, double epsilon) {
            return m_start.isEqual(axis.m_start, epsilon) && m_end.isEqual(axis.m_end, epsilon) ||
            m_start.isEqual(axis.m_end, epsilon) && m_end.isEqual(axis.m_start, epsilon);
        }

        /// <summary>
        /// It represents axis as string format 
        /// </summary>
        /// <returns></returns>
        std::string toString() const {
            return m_start.toString() + " - " + m_end.toString();
        }
    private:
        Point2<T> m_start, m_end;
};