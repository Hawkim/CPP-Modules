#include <iostream>
#include "Point.hpp"

int main() {
    Point a(0, 0);
    Point b(10, 0);
    Point c(0, 10);

    // Test cases
    Point inside(1, 1);       // Strictly inside
    Point outside(5, 5);      // Outside (would be on edge if triangle was 45°)
    Point vertex(0, 0);      // Exactly on vertex A
    Point edge(5, 0);        // Exactly on edge AB
    Point edge2(0, 5);       // Exactly on edge AC
    Point close_inside(0.1f, 0.1f);  // Very close to vertex but inside
    Point close_outside(-0.1f, -0.1f); // Very close but outside

    std::cout << "Inside (1,1): " << bsp(a, b, c, inside) << std::endl;
    std::cout << "Outside (5,5): " << bsp(a, b, c, outside) << std::endl;
    std::cout << "Vertex (0,0): " << bsp(a, b, c, vertex) << std::endl;
    std::cout << "Edge AB (5,0): " << bsp(a, b, c, edge) << std::endl;
    std::cout << "Edge AC (0,5): " << bsp(a, b, c, edge2) << std::endl;
    std::cout << "Close Inside (0.1,0.1): " << bsp(a, b, c, close_inside) << std::endl;
    std::cout << "Close Outside (-0.1,-0.1): " << bsp(a, b, c, close_outside) << std::endl;

    return 0;
}