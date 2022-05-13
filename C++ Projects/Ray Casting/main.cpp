#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "class.h"
#include <vector>
#include <ctime>
#include <cmath>

int main() {
    //setting up the window
    srand(time(NULL));
    sf::RenderWindow win(sf::VideoMode(2400, 1200), "My window");
    glOrtho(0.0, win.getSize().x, win.getSize().y, 0.0, 1.0, -1.0);
    //definition of width, and height consts
    const int height = win.getSize().y;
    const int width = win.getSize().x / 2;
    // definition of Player object
    player Player = player(50,50);
    //filling boundries vector with walls
    std::vector<wall> boundries;
    boundries.emplace_back(wall(0,0,0,height));
    boundries.emplace_back(wall(0,height, width,height));
    boundries.emplace_back(wall(width,height, width,0));
    boundries.emplace_back(wall(width,0,0,0));
    boundries.emplace_back(wall(200,200,200,1000));
    boundries.emplace_back(wall(200,800,0,800));
    boundries.emplace_back(wall(600,0,600,1000));
    boundries.emplace_back(wall(700,300,700,1200));
    boundries.emplace_back(wall(800,300,1200,1200));
//    for (int i = 0; i < 10; i++){
//        boundries.emplace_back(randomWall(width,height));
//    }
    // calling the create rays function for Player object
    Player.create_rays();

    // draw loop
    while (win.isOpen()) {
        //definition of events: closing window, move in 4 directions, and rotate left/right
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.key.code == sf::Keyboard::D)
                Player.beg_view -= 20;
            if (event.key.code == sf::Keyboard::A)
                Player.beg_view += 20;
            if (event.key.code == sf::Keyboard::W)
                Player.move_forward();
            if (event.key.code == sf::Keyboard::S)
                Player.move_backward();
        }
        //when "beg_view" is out of range of rays vector indexes it's setting to 0 or size of rays
        if(Player.beg_view < 0)
            Player.beg_view = Player.rays.size();
        if(Player.beg_view > Player.rays.size())
            Player.beg_view = 0;
        win.clear();


        //calling show function for every wall in boundries vector
        for(wall W : boundries){
            W.show();
        }

        std::vector<ray>sight;          //vector storing rays which create field of view

        //for loop iterating though every ray in rays vector
        int iterator = 0;              //counter of iterations
        for (ray R : Player.rays) {
            R.update(Player.position, boundries);                               //calling update function
            if(Player.beg_view + 150 < Player.rays.size()) {                       //if sight field doesn't exceeds end of rays vector
                Player.end_view = Player.beg_view + 150;                           //end of view equas begining of view + 150
                if ( iterator > Player.beg_view && iterator < Player.end_view) {
                        R.show();                                                  //calling the show function for rays between beg and end of view
                        sight.push_back(R);                                        //pushing rays to sight vector
                }
            }
            else{                                                                  //if sight field doesn't exceeds end of rays vector
                Player.end_view = Player.beg_view + 150 - Player.rays.size();      //end of view equas the number of rays which exceeded rays vector
                if(iterator < Player.end_view || iterator > Player.beg_view){
                        R.show();                                                  //calling the show function for rays between beg and end of view
                        sight.push_back(R);                                        //pushing rays to sight vector
                }
            }
            iterator++;
        }
        //drawing vertical rectangles on the secound half of display window which length represents distance between the ray and it's hit-point
        for(int i = 0; i < sight.size(); i++) {
            int dist = distance(Player.position,sight[i].hit_point);
            glLineWidth(7);
            glBegin(GL_LINES);
            glColor3f(1,1,1);
            glVertex2f(1200+i*7, map(dist,1400,600));
            glVertex2f(1200+i*7,1200 - map(dist,1400,600));
            glEnd();
        }
        //updating the window
        win.display();
    }
}


