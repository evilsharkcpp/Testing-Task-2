
#include "SymmetryFinder.hpp"
#include "Point2.hpp"
#include <iostream>
#include <fstream>

/// <summary>
/// Write all axes in console
/// </summary>
/// <typeparam name="T">template parameter</typeparam>
/// <param name="axes">vector of axes that contains axes of symmetry</param>
template<typename T>
void writeAxes(std::vector<Axis<T>>& axes) {
    for (const auto& axis : axes) {
        std::cout << axis.toString() << std::endl;
    }
}

/// <summary>
/// Read polygon from file
/// </summary>
/// <typeparam name="T">template parameter</typeparam>
/// <param name="filename">string that contains directory for file</param>
/// <returns>polygon object</returns>
template<typename T>
Polygon<T> readPolygon(std::string filename) {
    std::vector<Point2<double>> nodes{};

    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::exception("File not found");
    }

    while (!in.eof()) {
       double x{}, y{};
       in >> x >> y;
       nodes.push_back(Point2<double>(x, y));
    }
    in.close();

    return Polygon<T> { nodes };
}

/// <summary>
/// Entry point for find axes of symmetry
/// </summary>
/// <param name="argc">arguments count</param>
/// <param name="argv">vector of arguments</param>
/// <returns>0 if success else -1</returns>
int main(int argc, char* argv[]) {
    try {
        
        //Parse command arguments
        if (argc < 2) {
            throw std::exception("Run program with filename as parameter");
        }

        //Read polygon from file 
        std::string filename{ argv[1] };
        auto poly { readPolygon<double>(filename) };
        
        //Find axes of symmetry
        SymmetryFinder<double> finder{};
        auto result { finder.findSymmetry(poly, 1e-8) };

        //Print results
        if (result.size() == 0) {
            std::cout << "non-symmetric" << std::endl;
        } else {
            writeAxes<double>(result);
        }
         
        return 0;
   }
   catch (std::exception& ex) {
      std::cerr << ex.what() << std::endl;
      return -1;
   }
}