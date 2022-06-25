//
// Created by Элина Карапетян on 27.05.2022.
//

#ifndef BATTLE_TANKS_MAZE_H
#define BATTLE_TANKS_MAZE_H

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Maze{
private:

    //Private functions
    void initVariables();
public:
    Maze();
    virtual ~Maze();

    std::vector<std::vector<bool>> *cells;

    void mazeGenerator();
    void render(sf::RenderTarget* target);
};

#endif //BATTLE_TANKS_MAZE_H
