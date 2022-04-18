#include "cell.h"
#include <cmath>
#include <random>
#include <ctime>

//function returning true with probability prob%
bool random(int prob){
    int tmp = std::rand()%100;
    if ( tmp < prob){
        return true;
    }
    return false;
}

//function which returns index in 1D array based on location of a cell
int idx(int x, int y){
    return y+x*cols;
}

//function which displays given cell in given color
sf::RectangleShape cell::show(sf::Color col)const {
    sf::RectangleShape position;
    int pos_x = x * win_width/cols;
    int pos_y = y * win_height/rows;
    position.setSize(sf::Vector2f(win_width/cols,win_height/rows));
    position.setPosition(sf::Vector2f(pos_x,pos_y));
    position.setOutlineThickness(1);
    position.setFillColor(col);
    position.setOutlineColor(sf::Color::White);
    return position;
}

//function which adds neighbours to given cell
void cell::addNeighbours(std::vector<cell>&grid){
    if( x > 0){
        int tmp = idx(x-1,y);
        neighbours.push_back(grid[tmp]);
    }
    if( x < rows - 1){
        int tmp = idx(x+1,y);
        neighbours.push_back(grid[tmp]);

    }
    if( y > 0){
        int tmp = idx(x,y - 1);
        neighbours.push_back(grid[tmp]);
    }
    if( y < cols - 1){
        int tmp = idx(x,y + 1);
        neighbours.push_back(grid[tmp]);
    }
}

//cell constructor function
cell::cell(){
    x = 0;
    y = 0;
}


// == operator overload
bool cell::operator==(const cell& A)const{
    if(x==A.x && y==A.y){
        return true;
    }
    else{
        return false;
    }
}

//function checking if cell is in given set
bool isInSet(std::vector<cell>&Set, cell& A){
    for(size_t i = 0; i < Set.size(); i++){
        if(Set[i] == A) {
            return true;
        }
    }
    return false;
}

//function evaluating heuristics of a given cell
double heuristics(const cell& A, const cell& end){
    double tmp = pow(end.x - A.x,2) + pow(end.y - A.y, 2);
    return sqrt(tmp);
}
