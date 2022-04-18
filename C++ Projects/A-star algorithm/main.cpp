#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "cell.h"


int main() {
    //definition of grid vector, random seed, and bool noLoop variable
    srand(time(nullptr));
    std::vector<cell>grid(rows*cols);
    bool noLoop = false;
    //setting up the window
    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Window",sf::Style::Close);
    sf::RectangleShape tlo(sf::Vector2f(window.getSize().x, window.getSize().y));
    tlo.setFillColor(sf::Color(0, 0, 0));
    window.setFramerateLimit(100);
    glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0, 1.0, -1.0);
    //setting up all grid's elements
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            int tmp = idx(i,j);
            grid[tmp].x = i;
            grid[tmp].y = j;
            grid[tmp].wall = random(30);
        }
    }
    //defying specifics of first (current) and last (end) cell
    grid[idx(cols-1,rows-1)].wall = false;
    const cell end = grid[idx(cols-1,rows-1)];
    cell current = grid[0];
    current.wall = false;
    current.distance = 0;
    current.heuristics = heuristics(current,end);
    current.overall_cost = current.distance + current.heuristics;
    //defying the closed set and open set containing current cell
    std::vector<cell>openSet = {current};
    std::vector<cell>closedSet;
    //endles drawing loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(tlo);
        //drawing whole grid
        for (int i = 0; i < cols; i++){
            for (int j = 0; j < rows; j++){
                int tmp = idx(i,j);
                if(grid[tmp].wall) {
                    window.draw(grid[tmp].show(sf::Color::Black));
                }
                else {
                    window.draw(grid[tmp].show(sf::Color::White));
                }
            }
        }

        //evaluating the overall cost of every neighbour of the current cell and pushing them to open set
        current.addNeighbours(grid);
        for(size_t i = 0; i < current.neighbours.size(); i++){
            cell neighbour = current.neighbours[i];
            if(!isInSet(closedSet, neighbour) && !neighbour.wall) {
                int closestDistance = current.distance + 1;
                if (isInSet(openSet,neighbour)){
                    if(neighbour.distance > closestDistance) {
                        neighbour.distance = closestDistance;
                    }
                }
                else{
                    neighbour.distance = closestDistance;

                }
                neighbour.heuristics = heuristics(neighbour,end);
                neighbour.overall_cost = neighbour.distance + neighbour.heuristics;
                openSet.push_back(neighbour);
            }
        }

        int bestGuessIndex = 0;
        if(!openSet.empty()) {
            for (int i = 0; i < openSet.size(); i++) {
                //evaluating best guess from open set
                if(openSet[bestGuessIndex].overall_cost > openSet[i].overall_cost) {
                    bestGuessIndex = i;
                }
                // coloring open set in green
                window.draw(openSet[i].show(sf::Color::Green));
            }
            closedSet.push_back(current);
            current = openSet[bestGuessIndex];
            openSet.erase(openSet.begin() + bestGuessIndex);
        }
        // coloring closed set in red
        if (!closedSet.empty()) {
            for (size_t i = 0; i < closedSet.size(); i++){
                window.draw(closedSet[i].show(sf::Color::Red));
            }
        }
        //updating window as long as path wasn't found
        if(current == end) {
            noLoop = true;
        }
        if(!noLoop){
            window.display();
        }
    }
    return 0;
}
