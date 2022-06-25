//
// Created by Элина Карапетян on 06.06.2022.
//

#ifndef BATTLE_TANKS_BULLET_H
#define BATTLE_TANKS_BULLET_H


#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
private:
    float movementSpeed;

    //Private Functions
    void initSize();
public:
    Bullet();
    Bullet(sf::Texture* texture, float pos_x, float pos_y, char dir, float movement_speed);
    virtual ~Bullet();

    //Variables
    sf::Vector2f bulletSize;
    sf::Sprite shape;
    char dir;
    sf::Vector2f direction;

    //Accessor
    const sf::FloatRect getBounds() const;

    //Functions
    void update();
    void render(sf::RenderTarget* target);
};



#endif //BATTLE_TANKS_BULLET_H
