//
// Created by Элина Карапетян on 27.05.2022.
//

#ifndef BATTLE_TANKS_GAME_H
#define BATTLE_TANKS_GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "maze.h"
//#include "GameState.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <map>

class Game{
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;

    //Resources
//    std::stack<State*> states;
    std::map <std::string, sf::Texture*> textures;

    //Sprites
    sf::Sprite redTank;
    sf::Sprite blueTank;
    sf::Sprite redTankLifes;
    sf::Sprite blueTankLifes;
    sf::Sprite explosion;
    sf::Sprite gameOver;

    Player* player1;
    Player* player2;

    void initWindow();
    void initMaze();
    void initPlayer();
    void initTexture();
    void initLivesTable();
    void initPositions();
    void initTextPosition();
    void initStates();
public:
    Game();
    virtual ~Game();

    bool gameIsOver;

    Maze* maze;
    sf::TcpSocket socket;
    char button[5];

    //Accessors
    bool running();

    void update();
    void render();
    void receiveClientData();
    void pollEvents();
    void renderLivesTable();
    void updateBulletCollision(std::vector<Bullet*>& bullets, int player);
    void updateInputAndCollisions();
    void updatePlayer();
    void updateClient();
    void explosionAnimation(float pos_x, float pos_y);
};

//void initGame(GAME *game);
//void initWindow();
#endif //BATTLE_TANKS_GAME_H
