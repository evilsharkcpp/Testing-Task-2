#include <gtest/gtest.h>
#include "Polygon.hpp"
#include "Point2.hpp"
#include "Axis.hpp"
#include "SymmetryFinder.hpp"

#include <vector>

constexpr double epsilon{ 1e-6 };
static bool compareAxes(std::vector<Axis<double>>& a, std::vector<Axis<double>>& b) {
   if (a.size() != b.size())
      return false;
   for (int i{}; i < a.size(); i++)
   {
      bool isEqual{};
      for (int j{}; j < b.size(); j++)
      {
         if (a[i].isEqual(b[j], epsilon))
            isEqual = true;
      }
      if (!isEqual)
         return false;
   }
   return true;
}

TEST(PresisionTest, SquareTest) {
    std::vector<Axis<double>> axes
    {
       { Point2<double>(0,0), Point2<double>(1,1) },
       { Point2<double>(1,0), Point2<double>(0,1) },
       { Point2<double>(0.5,0), Point2<double>(0.5,1) },
       { Point2<double>(0,0.5), Point2<double>(1,0.5) },
    };

    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {0,0},
          {1,0},
          {1,1},
          {0,1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(PresisionTest, QuadrangleAxes) {
     std::vector<Axis<double>> axes
     {
        { Point2<double>(0,0), Point2<double>(0,3) },
     };
     Polygon<double> poly
     {
        std::vector<Point2<double>>
        {
           {0,0},
           {2,1},
           {0,3},
           {-2,1},
        }
     };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(PresisionTest, NonSymmetryPentagonAxes) {
    std::vector<Axis<double>> axes{};
    Polygon<double> poly
    {
        std::vector<Point2<double>>
        {
         {0.1,1.0},
         {-1.0,0.0},
         {0.0,-1.0},
         {1.0,-0.5},
         {2.0, 1.0},
        }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(PresisionTest, EquilateralTriangleAxes) {
    std::vector<Axis<double>> axes
    {
       { Point2<double>(0.5,0), Point2<double>(0.5,sqrt(3)/2.0) },
       { Point2<double>(0,0), Point2<double>(0.75,sqrt(3) / 4.0) },
       { Point2<double>(1,0), Point2<double>(0.25,sqrt(3) / 4.0) },
    };
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          { 0, 0 },
          { 1, 0 },
          { 0.5, sqrt(3) / 2.0 },
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(PresisionTest, RectangleAxes) {
    std::vector<Axis<double>> axes
    {
       { Point2<double>(1,0), Point2<double>(1,1) },
       { Point2<double>(0,0.5), Point2<double>(2,0.5) },
    };
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {0,0},
          {2,0},
          {2,1},
          {0,1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(PresisionTest, ParallelogramAxes) {
    std::vector<Axis<double>> axes{};
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {0,0},
          {2,0},
          {2.5,1},
          {0.5,1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(PresisionTest, SymmetricHexagonAxes) {
    std::vector<Axis<double>> axes
    {
       { Point2<double>(-5,0), Point2<double>(5,0) },
       { Point2<double>(0,-1), Point2<double>(0,1) },
    };
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {-5,0},
          {-2,-1},
          {2,-1},
          {5,0},
          {2,1},
          {-2,1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}