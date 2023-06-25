#pragma once

#include "Polygon.hpp"
#include "Axis.hpp"
#include <numbers>

/// <summary>
/// Main class that finds axes of symmetry
/// </summary>
/// <typeparam name="T">template parameter</typeparam>
template <class T>
class SymmetryFinder {
    public:
        /// <summary>
        /// Method for find axes of symmetry 
        /// </summary>
        /// <param name="p">Copy of polygon</param>
        /// <param name="epsilon">presision</param>
        /// <returns>vector with axes of symmetry</returns>
        std::vector<Axis<T>> findSymmetry(Polygon<T> p, double epsilon) {
            
            //get center and move it in (0, 0)
            auto center { p.getCenter() };
            p.translate(center);

            // Get candidates
            auto candidates { findCandidates(p) };
            Polygon<T> r { p };

            //Try rotate polygon by pi and axis as candidate(this axis end with point and start with (0,0))
            std::vector<Point2<T>> result{};
            for(const Point2<T>& candidate : candidates) {
                auto direction { candidate.getNormalized() };
                
                r.rotate(std::acos(-1), direction);
                
                if(p.isEqual(r, epsilon)) {
                    // get selected candidate without translate
                    result.push_back(candidate + center);
                }

                // return rotated polygon in start position 
                r.rotate(std::acos(-1), direction);
            }
            
            return getAxes(center, result, epsilon);
        }
    private:
        /// <summary>
        /// Get all axes of symmetry
        /// </summary>
        /// <param name="center">center of polygon</param>
        /// <param name="points">founded candidates</param>
        /// <returns>vector with axes of symmetry</returns>
        std::vector<Axis<T>> getAxes(Point2<T>& center, std::vector<Point2<T>>& points, double epsilon) {
            std::vector<Axis<T>> candidates{};
            auto size { points.size() };

            for (int i{}; i < size; ++i) {
                for(int j { i + 1 }; j < size; ++j) {
                    auto dx { (center.x - points[i].x) }, dy{ (center.y - points[i].y) },
                         tx { (points[j].x - points[i].x) }, ty{ (points[j].y - points[i].y) };
                    // If is line
                    if(abs(dx * ty - dy * tx) < epsilon) {
                        candidates.push_back(Axis<T>(points[i], points[j]));
                    }
                }
            }
            
            return candidates;
        }

        /// <summary>
        /// Get candidates in axis of symmetry. It only by angle point, and middle edge point
        /// </summary>
        /// <param name="p">Polygon</param>
        /// <returns>vector of candidates</returns>
        std::vector<Point2<T>> findCandidates(const Polygon<T>& p) {

            std::vector<Point2<T>> candidates(p.getNodes());
            auto size{ candidates.size() };

            for (int i{}; i < size - 1; ++i) {
                candidates.push_back((candidates[i] + candidates[i + 1]) / 2.0);
            }
                
            candidates.push_back((candidates[0] + candidates[size - 1]) / 2.0);

            return candidates;
        }
};