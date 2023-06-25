#include <gtest/gtest.h>
#include "Polygon.hpp"
#include "Point2.hpp"
#include "Axis.hpp"
#include "SymmetryFinder.hpp"

#include <vector>

constexpr double epsilon{ 1e-20 };
constexpr double multiplier { 1e-8 };
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

TEST(SmallPresisionTest, SquareTest) {
    std::vector<Axis<double>> axes
    {
       { multiplier * Point2<double>(0,0),   multiplier * Point2<double>(1,1) },
       { multiplier * Point2<double>(1,0),   multiplier * Point2<double>(0,1) },
       { multiplier * Point2<double>(0.5,0), multiplier * Point2<double>(0.5,1) },
       { multiplier * Point2<double>(0,0.5), multiplier * Point2<double>(1,0.5) },
    };

    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {multiplier * 0,multiplier * 0},
          {multiplier * 1,multiplier * 0},
          {multiplier * 1,multiplier * 1},
          {multiplier * 0,multiplier * 1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(SmallPresisionTest, QuadrangleAxes) {
     std::vector<Axis<double>> axes
     {
        { multiplier * Point2<double>(0,0), multiplier * Point2<double>(0,3) },
     };
     Polygon<double> poly
     {
        std::vector<Point2<double>>
        {
           {multiplier * 0, multiplier * 0},
           {multiplier * 2, multiplier * 1},
           {multiplier * 0, multiplier * 3},
           {multiplier * -2, multiplier * 1},
        }
     };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(SmallPresisionTest, NonSymmetryPentagonAxes) {
    std::vector<Axis<double>> axes{};
    Polygon<double> poly
    {
        std::vector<Point2<double>>
        {
         {multiplier * 0.1, multiplier *  1.0},
         {multiplier * -1.0,multiplier *  0.0},
         {multiplier * 0.0, multiplier * -1.0},
         {multiplier * 1.0, multiplier * -0.5},
         {multiplier * 2.0, multiplier *  1.0},
        }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(SmallPresisionTest, EquilateralTriangleAxes) {
    std::vector<Axis<double>> axes
    {
       { multiplier * Point2<double>(0.5,0), multiplier * Point2<double>(0.5,sqrt(3)/2.0) },
       { multiplier * Point2<double>(0,0),   multiplier * Point2<double>(0.75,sqrt(3) / 4.0) },
       { multiplier * Point2<double>(1,0),   multiplier * Point2<double>(0.25,sqrt(3) / 4.0) },
    };
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          { multiplier * 0, multiplier * 0 },
          { multiplier * 1, multiplier * 0 },
          { multiplier * 0.5, multiplier * sqrt(3) / 2.0 },
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(SmallPresisionTest, RectangleAxes) {
    std::vector<Axis<double>> axes
    {
       { multiplier * Point2<double>(1,0),   multiplier * Point2<double>(1,1) },
       { multiplier * Point2<double>(0,0.5), multiplier * Point2<double>(2,0.5) },
    };
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {multiplier * 0,multiplier * 0},
          {multiplier * 2,multiplier * 0},
          {multiplier * 2,multiplier * 1},
          {multiplier * 0,multiplier * 1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(SmallPresisionTest, ParallelogramAxes) {
    std::vector<Axis<double>> axes{};
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {multiplier * 0,  multiplier * 0},
          {multiplier * 2,  multiplier * 0},
          {multiplier * 2.5,multiplier * 1},
          {multiplier * 0.5,multiplier * 1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}

TEST(SmallPresisionTest, SymmetricHexagonAxes) {
    std::vector<Axis<double>> axes
    {
       { multiplier * Point2<double>(-5,0), multiplier * Point2<double>(5,0) },
       { multiplier * Point2<double>(0,-1), multiplier * Point2<double>(0,1) },
    };
    Polygon<double> poly
    {
       std::vector<Point2<double>>
       {
          {multiplier * -5, multiplier *  0},
          {multiplier * -2, multiplier * -1},
          {multiplier * 2,  multiplier * -1},
          {multiplier * 5,  multiplier * 0},
          {multiplier * 2,  multiplier * 1},
          {multiplier * -2, multiplier * 1},
       }
    };
    SymmetryFinder<double> finder{};
    auto result { finder.findSymmetry(poly, epsilon) };
    EXPECT_TRUE(compareAxes(axes, result));
}