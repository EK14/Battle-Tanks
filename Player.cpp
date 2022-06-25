//
// Created by Элина Карапетян on 04.06.2022.
//

#include "Player.h"
#include <iostream>
#include <sstream>

Player::Player() {
    this->initVariables();
    this->initSprite();
    this->initFonts();
    this->initText();
}

Player::~Player() {

}

//Functions
void Player::update() {
    this->updateAttack();
    this->updateText();
    this->updateNumOfLives();
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
    this->renderText(*target);
}

void Player::move(float dirX, float dirY) {
    this->sprite.move(this->movementSpeed* dirX, this->movementSpeed* dirY);
}

void Player::updateAttack() {
    if(this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

const bool Player::canAttack() {
    if(this->attackCooldown >= this->attackCooldownMax){
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

//Private Functions

void Player::initSprite() {
    //Resize the sprite
    this->sprite.scale(0.25f, 0.25f);
}

void Player::initVariables() {
    this->direction = 'n';
    this->movementSpeed = 10.f;
    this->attackCooldownMax = 10.f;
    this->attackCooldown = attackCooldownMax;
    this->points = 0;
    this->numOfLivesMax = 5;
    this->numOfLives = this->numOfLivesMax;
}

//Accessor
const sf::Vector2f &Player::getPos() const {
    return this->sprite.getPosition();
}

sf::Vector2f Player::generatePosition() {
    std::vector<int> pos_x = {100, 300, 500, 700, 900, 1100, 1300};
    std::vector<int> pos_y = {300, 500, 700, 900, 1100};
    sf::Vector2f vec(pos_x[rand() % 7], pos_y[rand() % 5]);
    return vec;
}

void Player::initFonts() {
    if(!this->font.loadFromFile("Dosis/Dosis-Light.ttf"))
        std::cout << "ERROR::GAME::INITFONTS::Failed to load" <<"\n";
}

void Player::initText() {
    this->score.setFont(this->font);
    this->score.setCharacterSize(50);
    this->score.setFillColor(sf::Color::Black);
    this->score.setString("NONE");
}

void Player::updateText() {
    std::stringstream ss;

    ss << "Points: " << this->points << "\n";

    this->score.setString(ss.str());
}

void Player::renderText(sf::RenderTarget& target) {
    target.draw(this->score);
}

void Player::updateNumOfLives() {
    if(numOfLives > 0 && damaged)
        --numOfLives;
}
