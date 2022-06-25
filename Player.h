//
// Created by Элина Карапетян on 04.06.2022.
//

#ifndef BATTLE_TANKS_PLAYER_H
#define BATTLE_TANKS_PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Bullet.h"

class Player {
private:
    float movementSpeed;

    float attackCooldown;
    float attackCooldownMax;

    //Resources
    sf::Font font;

    unsigned numOfLivesMax;


    //Private Functions
    void initVariables();
    void initSprite();
    void initText();
    void initFonts();
public:
    Player();
    virtual ~Player();

    std::vector<Bullet*> bullets;

    //Variables
    sf::Sprite sprite;
    char direction;
    sf::Text score;
    unsigned points;
    unsigned numOfLives;
    bool damaged;

    //Accessor
    const sf::Vector2f& getPos() const;

    //Functions
    void move(float dirX, float dirY);
    const bool canAttack();
    sf::Vector2f generatePosition();
    void updateAttack();
    void update();
    void render(sf::RenderTarget* target);
    void updateText();
    void renderText(sf::RenderTarget& target);
    void updateNumOfLives();
};


#endif //BATTLE_TANKS_PLAYER_H
