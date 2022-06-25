//
// Created by Элина Карапетян on 06.06.2022.
//

#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, char dir, float movement_speed) {
    this->shape.setScale(0.1f, 0.1f);
    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x, pos_y);
    this->dir = dir;
    this->direction.x = (dir == 'n' || dir == 's') ? 0.f: dir == 'e' ? 1.f: -1.f;
    this->direction.y = (dir == 'w' || dir == 'e') ? 0.f: dir == 's' ? 1.f: -1.f;
    dir == 'n' ? this->shape.setRotation(0): dir == 'e' ? this->shape.setRotation(90):\
    dir == 's' ? this->shape.setRotation(180): this->shape.setRotation(-90);
    this->movementSpeed = movement_speed;
    initSize();
}

Bullet::~Bullet() {

}

//Functions
void Bullet::update() {
    //Movement
    this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}

//Accessors
const sf::FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}

void Bullet::initSize() {
    this->bulletSize = {
            shape.getTexture()->getSize().x * shape.getScale().x,
            shape.getTexture()->getSize().y * shape.getScale().y};
    this->shape.setOrigin(this->bulletSize.x / 2, this->bulletSize.y / 2);
}

