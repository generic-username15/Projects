#include "class.h"
#include <SFML/OpenGL.hpp>
#include <cmath>
//function calculating euclidean distance between two given points
double distance(std::pair<int,int> A, std::pair<int,int> B){
    return sqrt(pow(A.first - B.first,2) + pow(A.second - B.second,2));
}
//wall constructor function
wall::wall(int x1, int y1, int x2, int y2){
    beg = {x1,y1};
    end = {x2,y2};
}
//function drawing given wall
void wall::show()const{
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(beg.first, beg.second);
    glVertex2f(end.first, end.second);
    glEnd();
}
//ray constructor function
ray::ray(double x1, double y1){
    direction = {x1,y1};
}
//function drawing the given ray
void ray::show()const{
    if(hit_point.first != INT_MAX && hit_point.second != INT_MAX) {
        glBegin(GL_LINES);
        glVertex2f(position.first, position.second);
        glVertex2f(hit_point.first, hit_point.second);
        glColor4b(127,50,50,100);
        glEnd();
    }
}
//function checking if the ray colides witch any wall from given set of walls and returning point of collision,
//or if that doesn't happen {INT_MAX,INT_MAX}
std::pair<int,int> ray::check(const wall & W)const{
    const int x1 = W.beg.first;
    const int y1 = W.beg.second;
    const int x2 = W.end.first;
    const int y2 = W.end.second;

    const int x3 = position.first;
    const int y3 = position.second;
    const double x4 = position.first + direction.first;
    const double y4 = position.second + direction.second;

    const double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (denominator == 0){
        return {INT_MAX,INT_MAX};
    }
    const double t = double(((x1 - x3)*(y3 - y4)-(y1 - y3)*(x3 - x4)))/denominator;
    const double u = -((x1 - x2)*(y1 - y3)-(y1 - y2)*(x1 - x3))/denominator;

    if (t > 0 && t < 1 && u > 0){
        std::pair<int,int> intersection_point;
        intersection_point.first = x1 + t * (x2 - x1);
        intersection_point.second = y1 + t * (y2 - y1);
        return intersection_point;
    }
    return {INT_MAX,INT_MAX};

}

//function updating position and point of collision witch wall of given ray
void ray::update(std::pair<int,int>& pos, const std::vector<wall>& walls){
    position = {pos.first,pos.second};
    set_hit_point(walls);
}
//function returning wall in random spot
wall randomWall(int width, int height){
    const int x1 = rand() % width;
    const int x2 = rand() % width;
    const int y1 = rand() % height;
    const int y2 = rand() % height;
    return wall(x1,y1,x2,y2);
}
//function calculating closest point of collision of the ray witch any wall
void ray::set_hit_point(const std::vector<wall>& walls){
    for (wall W : walls){
        std::pair<int,int> crosspoint = check(W);
        if (distance(position,crosspoint) < distance(position,hit_point)){
            hit_point = crosspoint;
        }
    }
}
//player constructor function
player::player(int x, int y){
    position.first = x;
    position.second = y;
}
//function filling player's "rays" vector witch ray objects
void player::create_rays(){
    for (double i = 0; i < M_PI*2; i += 0.005) {
        rays.push_back(ray(sin(i),cos(i)));
    }
}
//function when called changes player position based on direction in which he is faced
void player::move_forward() {
    if (beg_view + 100 < rays.size()) {
        position.first += rays[beg_view + 100].direction.first * 10;
        position.second += rays[beg_view + 100].direction.second * 10;
    }
    else{
        position.first += rays[(beg_view + 100)%rays.size()].direction.first * 10;
        position.second += rays[(beg_view + 100)%rays.size()].direction.second * 10;
    }
}
//function when called changes player's position in opposite direction he faces
void player::move_backward(){
    position.first -= rays[beg_view + 100].direction.first * 10;
    position.second -= rays[beg_view + 100].direction.second * 10;
}
// function given value and two ranges (0-range_a, 0-range_b) maps value from first range into second one
int map(int val, int range_a, int range_b){
    return (val * range_b)/range_a;
}