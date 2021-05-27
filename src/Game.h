#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
*
* Game engine
*
*
*/


class Game {
    private:
        //vars
        sf::RenderWindow* window;
        sf::Event ev;
        sf::VideoMode videoMode;
        sf::Color bg_color;
        sf::Texture texture;

        //Mouse
        sf::Vector2f mousePosWindow;
        sf::Vector2f worldPos;
        
        //Game objects
        sf::View view ;


        std::vector<std::pair<int,int>> points;
        std::vector<std::pair<int,int>> velocities;
        //drawing variables

        int points_amt;
        int N ;
        float scale;

        void initVariables(){
            this->window = nullptr;
            this->bg_color = sf::Color(0,0,0,255);
            this->videoMode.height = 1000;
            this->videoMode.width = 1000;
            this->texture.create(N,N);
            for(int i = 0; i < points_amt;i++){
                this->points.push_back(std::make_pair(rand()%N,rand()%N));
            }


        }

        void initWindow(){
            this->window = new sf::RenderWindow(this->videoMode, "My first game", 
	        sf::Style::Titlebar | sf::Style::Close);
            this->window->setFramerateLimit(60);
            this->view = sf::View(sf::FloatRect(0,0,N,N));
            this->window->setView(this->view);
            
            //this->window->setView(view);
        }

       

    public:
        Game(int tN, int tpoints_amt, float tscale){
            this->N = tN;
            this->points_amt = tpoints_amt;
            this->scale = tscale;
            this->initVariables();
            this->initWindow();
        }

        virtual ~Game(){
            delete this->window;
        }

        //Accessors

        const bool running() const{
            return this->window->isOpen();
        }

        void updateMousePositions(){
            this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
            this->worldPos = this->window->mapPixelToCoords(sf::Vector2i(this->mousePosWindow)); 
        }

        void drawGrid(){
            sf::Sprite sprite;
            sf::Uint8 *pixels = new sf::Uint8[N * N * 4]; 
            for(int x = 0; x < N; x++){
                for(int y = 0; y < N; y++){
                    int v = 255 - std::max(0.f,std::min(255.f,d_point(x,y)));
                    
                    pixels[(x + y *N)*4] = v; 
                    pixels[(x + y *N)*4 + 1] = v;
                    pixels[(x + y *N)*4 + 2] = v;
                    pixels[(x + y *N)*4 + 3] = 255;
                   
                   

                }

            }
            //image.create(this->videoMode.width, this->videoMode.height,pixels);
            texture.update(pixels);
            sprite.setTexture(texture);
            this->window->draw(sprite);
            delete pixels;
        }


       



        void drawShapes(){
            //this->window->draw(this->s);
             drawGrid();           




            /*for(auto row : this->grid){
                for(auto cell : row){
                }
            }*/

        }



        void pollEvents(){
            while(this->window->pollEvent(this->ev)){
                
                switch(this->ev.type){
                    
                    case sf::Event::Closed:
                        this->window->close();
                        break;
                    
                    case sf::Event::KeyPressed:
                        if(this->ev.key.code == sf::Keyboard::Escape){
                            this->window->close();
                        }
                        break;
                }
            }
        }

        //update and rendering

        void update(){
            this->pollEvents();
            
            //mouse pos
            this->updateMousePositions();

            for(auto& point : this->points){
                point.first += rand()%20 - 10;
                point.second += rand()%20 - 10;
            }



            //relative to the screen
            //this->s.setPosition(s.getPosition().x + 10, s.getPosition().y+10);

        }

        void render(){
            this->window->clear(this->bg_color);
            //draw game
            this->drawShapes();
            //----
            this->window->display();
        }


        float d_point(int x, int y){
            //float *distance_formula(int,int,int,int) = d2;
            float min_distance = d2(points[0].first,points[0].second,x,y);
            for(auto point : this->points){
                float distance = d2(point.first, point.second, x, y);
                if(distance < min_distance){
                    min_distance = distance ;
                }
            } 
            return min_distance * scale;
        }

        static float d2(int x0, int y0, int x1, int y1){
            return (float) std::sqrt((float) (x0-x1) * (x0-x1) + (float) (y0-y1)*(y0-y1)); 
        }

        static float d_taxi(int x0, int y0, int x1, int y1){
            return std::abs(x0-x1) + std::abs(y0-y1);

        }

        static float d_not(int x0, int y0, int x1, int y1){

            return std::sqrt(std::abs(x0-x1)) + std::sqrt(std::abs(y0-y1));
        }

        static float d_ex(int x0, int y0, int x1, int y1){
            return std::cbrt((x0-x1) * (x0-x1) * (x0-x1) + (y0-y1) * (y0-y1) * (y0-y1));
        }


};