#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef RAYCASTING_CLASS_H
#define RAYCASTING_CLASS_H

//wall class manages instances of walls (storing beginning and end coordinates, displaying)
class wall{
public:
    std::pair<int,int> beg;
    std::pair<int,int> end;
    wall(int x1, int y1, int x2, int y2);
    void show()const;
};

class ray{
public:
    std::pair<int,int> position;                            //x, y position of the beginning of the ray
    std::pair<double,double> direction;                     //normal vector storing information about direction which the ray points
    std::pair<int,int> hit_point = {INT_MAX, INT_MAX};      //closest point of collision witch wall
    ray(double x1, double y1);
    //declaration of class methods
    void show()const;
    std::pair<int,int> check(const wall & W)const;
    void update(std::pair<int,int>& pos, const std::vector<wall>& walls);
    void set_hit_point(const std::vector<wall>& walls);
};

class player{
public:
    player(int x, int y);
    std::vector<ray> rays;               //vector storing rays shifted by const angle
    int beg_view = 0;                    //rays array index of the first ray in sight
    int end_view;                        //rays array index of the last ray in sight
    std::pair<int,int>position;
    //declaration of class methods
    void create_rays();
    void move_forward();
    void move_backward();
};

//declaration of functions
double distance(std::pair<int,int> A, std::pair<int,int> B);
wall randomWall(int width, int height);
int map(int val, int range_a, int range_b);

#endif //RAYCASTING_CLASS_H
