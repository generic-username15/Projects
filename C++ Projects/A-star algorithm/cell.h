#include <SFML/Graphics.hpp>

#ifndef UNTITLED2_CELL_H
#define UNTITLED2_CELL_H

//definition of global constants
const int win_width = 1000;
const int win_height = 1000;
const int cols = 100;
const int rows = 100;

//cell class
class cell {
public:
    std::vector<cell>neighbours;
    int x;
    int y;
    int distance;
    double heuristics;
    double overall_cost;
    bool wall = false;

    cell();
    sf::RectangleShape show(sf::Color col)const;
    void addNeighbours(std::vector<cell>&grid);
    bool operator==(const cell& A)const;
};

//initialization of functions
int idx(int a, int b);
bool isInSet(std::vector<cell>&Set, cell& A);
double heuristics(const cell& A, const cell& end);
bool random(int prob);

#endif //UNTITLED2_CELL_H
