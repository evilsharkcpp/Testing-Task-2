#pragma once

#include "Point2.hpp"
#include <vector>

/// <summary>
/// Class that represents Polygon(closed polyline).
/// Importantly that polygon set by clockwise(counterclockwise).
/// </summary>
/// <typeparam name="T">template parameter</typeparam>
template <class T>
class Polygon {
    public:
        /// <summary>
        /// base constructor
        /// </summary>
        Polygon() {}

        /// <summary>
        /// Init constructor
        /// </summary>
        /// <param name="nodes"></param>
        Polygon(const std::vector<Point2<T>>& nodes) : m_nodes(nodes) {}

        /// <summary>
        /// Get center of polygon
        /// </summary>
        /// <returns>center of polygon as Point2</returns>
        Point2<T> getCenter() {
            Point2<T> center{};
            
            for (const auto& node : m_nodes) {
                center += node;
            }
            center /= static_cast<T>(m_nodes.size());
            
            return center;
        }

        /// <summary>
        /// Get all nodes of polygon
        /// </summary>
        /// <returns>readonly nodes of polygon</returns>
        const std::vector<Point2<T>>& getNodes() const {
            return m_nodes;
        }

        /// <summary>
        /// Move polygon by point
        /// </summary>
        /// <param name="p">The point to which the polygon is moved </param>
        void translate(Point2<T>& p) {
            for(auto& node : m_nodes) {
                node -= p;
            }
        }

        /// <summary>
        /// Rotate polygon by angle around axis
        /// </summary>
        /// <param name="angle">rotated angle</param>
        /// <param name="axis">rotated axis</param>
        void rotate(T angle, Point2<T>& axis) {
            for(auto& node : m_nodes) {
                T nx { node.x * (cos(angle) + (1 - cos(angle)) * pow(axis.x, 2)) + 
                            node.y * ((1 - cos(angle)) * axis.x * axis.y) },
                       ny{ node.x * ((1 - cos(angle)) * axis.x * axis.y) + 
                            node.y * (cos(angle) + (1 - cos(angle)) * pow(axis.y, 2)) };
                node.x = nx;
                node.y = ny;
            }
        }

        /// <summary>
        /// Compare 2 polygons with one condition, which
        /// descripted in class description
        /// </summary>
        /// <param name="p">polygon for compare</param>
        /// <param name="epsilon">presision</param>
        /// <returns>true if this polygon is equal p else false</returns>
        bool isEqual(Polygon& p, double epsilon) {

            if (p.getNodes().size() != m_nodes.size()) {
                return false;
            }
            std::vector<Point2<T>> nodes1(m_nodes);
            std::vector<Point2<T>> nodes2(p.getNodes());
            int startIndex {-1};

            //try find shifted 0 - index
            for(int i{}; i < nodes2.size(); ++i) {
                if(nodes1.front().isEqual(nodes2[i], epsilon)) {
                    startIndex = i;
                    break;
                }
            }

            //If not found return false
            if(startIndex == -1) {
                return false;
            }

            // try to get rotation clockwise or counterclockwise
            bool isLeftRotation{};
            int newIndex {startIndex + 1 < nodes1.size() ? startIndex + 1 : 0};
            if(!nodes1[1].isEqual(nodes2[newIndex], epsilon)) {
                isLeftRotation = true;
            }

            // compare points
            for(int i{}, j{ startIndex }; i < nodes1.size(); ++i) {
                if(j == -1 && isLeftRotation) {
                    j = static_cast<int>(nodes1.size()) - 1;
                }

                if(j == nodes1.size() && !isLeftRotation) {
                    j = 0;
                }

                if(!nodes1[i].isEqual(nodes2[j], epsilon)) {
                    return false;
                }

                if(isLeftRotation) {
                    --j;
                } else {
                    ++j;
                }
            }

            return true;
        }
    private:
        std::vector<Point2<T>> m_nodes;
};