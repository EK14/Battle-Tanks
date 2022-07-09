//
// Created by Элина Карапетян on 27.05.2022.
//

#include "game.h"
#include <math.h>
#include "vector"
#define sizeOfWalls 20

//Game engine

Game::Game(){
    initWindow();
//    initStates();
    initMaze();
    initPlayer();
    initPositions();
    initTexture();
    initLivesTable();
    initTextPosition();
}

Game::~Game() {
    delete window;
    delete maze;
    delete player1;
    delete player2;

    //Delete textures
    for(auto & i: this->textures)
        delete i.second;

    //Delete bullets
    for(auto *i: this->player1->bullets)
        delete i;

    for(auto *i: this->player2->bullets)
        delete i;

//    while(!this->states.empty()) {
//        delete this->states.top();
//        this->states.pop();
//    }
}

void Game::initWindow(){
    videoMode.width = 1420;
    videoMode.height = 1020 + 550;
    window = new sf::RenderWindow(videoMode, "Battle-Tanks", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);
    gameIsOver = false;
}

//Accessors
bool Game::running(){
    return window->isOpen();
}

void Game::update() {
//    if(!this->states.empty()){
//        this->states.top()->update();
//
//        if(this->states.top()->getQuit()){
//            this->states.top()->endState();
//            delete this->states.top();
//            this->states.pop();
//        }
//    }


    pollEvents();
    updateClient();
    updateInputAndCollisions();
    if(!gameIsOver) {
        player1->update();
        player2->update();
    }
    updatePlayer();
    updateBulletCollision(player1->bullets, 1);
    updateBulletCollision(player2->bullets, 2);
}

void Game::render() {
    /*
     * - clear old frame
     * - render new objects
     * - display frame in window
     * Renders the game objects
     */
//    if(!this->states.empty())
//        this->states.top()->render(this->window);

    if(!gameIsOver) {
        window->clear(sf::Color(192, 192, 192));

        //Draw game objects
        this->maze->render(this->window);

        for (auto *bullet: player1->bullets)
            bullet->render(this->window);

        for (auto *bullet: player2->bullets)
            bullet->render(this->window);

        player1->render(this->window);
        player2->render(this->window);

        renderLivesTable();
        window->draw(redTank);
        window->draw(blueTank);
        window->draw(redTankLifes);
        window->draw(blueTankLifes);
    }
    else{
        if(player1->numOfLives == 0) {
            gameOver.setTexture(*textures["BlueWon"]);
        }
        else {
            gameOver.setTexture(*textures["RedWon"]);
        }
        window->draw(gameOver);
    }
    window->display();
}

void Game::pollEvents() {
    //Event Polling
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
        }
    }
}

void Game::initMaze() {
    maze = new Maze();
}

void Game::initPlayer() {
    player1 = new Player();
    player2 = new Player();
}

void Game::updateInputAndCollisions() {
    const sf::Vector2f spriteSize(
            player1->sprite.getTexture()->getSize().x * player1->sprite.getScale().x,
            player1->sprite.getTexture()->getSize().y * player1->sprite.getScale().y);
    this->player1->sprite.setOrigin(spriteSize.x + spriteSize.x / 2 + 40, spriteSize.y + spriteSize.y / 2 + 40);
    this->player2->sprite.setOrigin(spriteSize.x + spriteSize.x / 2 + 40, spriteSize.y + spriteSize.y / 2 + 40);
    receiveClientData();

    sf::Vector2f position1 = player1->getPos();
    sf::Vector2f position2 = player2->getPos();

    //Move first player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->player1->sprite.setRotation(-90);
        this->player1->move(-1.f, 0.f);
        this->player1->direction = 'w';
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->player1->sprite.setRotation(0);
        this->player1->move(0.f, -1.f);
        this->player1->direction = 'n';
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->player1->sprite.setRotation(90);
        this->player1->move(1.f, 0.f);
        this->player1->direction = 'e';
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->player1->sprite.setRotation(180);
        this->player1->move(0.f, 1.f);
        this->player1->direction = 's';
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && this->player1->canAttack()){
        this->player1->bullets.push_back(new Bullet(this->textures["BULLET"], this->player1->getPos().x, this->player1->getPos().y, player1->direction, 8.f));
    }

    //Walls collision for first player//
    for(int i = floor(position1.y - spriteSize.y / 2); i < floor(position1.y + spriteSize.y / 3); ++i)
        if((*maze->cells)[floor(i / sizeOfWalls) - 10][floor((position1.x - spriteSize.x / 2) / sizeOfWalls)])
            player1->sprite.setPosition(position1.x + 1, position1.y);
    for(int i = floor(position1.y - spriteSize.y / 2); i < floor(position1.y + spriteSize.y / 2); ++i)
        if((*maze->cells)[floor(i / sizeOfWalls) - 10][floor((position1.x + spriteSize.x / 2) / sizeOfWalls)])
            player1->sprite.setPosition(position1.x - 1, position1.y);
    if((*maze->cells)[floor((position1.y  - spriteSize.y / 2)/ sizeOfWalls) - 10][position1.x / sizeOfWalls])
        player1->sprite.setPosition(position1.x, position1.y + 1);
    for(int i = floor(position1.x - spriteSize.x / 2); i < floor(position1.x + spriteSize.x / 3); ++i)
        if ((*maze->cells)[floor((position1.y + spriteSize.y / 2) / sizeOfWalls) - 10][ceil((float) i / sizeOfWalls)] && !(*maze->cells)[floor((position1.y + spriteSize.y / 2) / sizeOfWalls) - 11][ceil((float) i / sizeOfWalls)])
            player1->sprite.setPosition(position1.x, position1.y - 1);

    //Move second player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->player2->sprite.setRotation(-90);
        this->player2->move(-1.f, 0.f);
        this->player2->direction = 'w';
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->player2->sprite.setRotation(0);
        this->player2->move(0.f, -1.f);
        this->player2->direction = 'n';
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->player2->sprite.setRotation(90);
        this->player2->move(1.f, 0.f);
        this->player2->direction = 'e';
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->player2->sprite.setRotation(180);
        this->player2->move(0.f, 1.f);
        this->player2->direction = 's';
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) && this->player2->canAttack()){
        this->player2->bullets.push_back(new Bullet(this->textures["BULLET"], this->player2->getPos().x, this->player2->getPos().y, player2->direction, 8.f));
    }

    //Walls collision for second player
    for(int i = floor(position2.y - spriteSize.y / 2); i < floor(position2.y + spriteSize.y / 3); ++i)
        if((*maze->cells)[floor(i / sizeOfWalls) - 10][floor((position2.x - spriteSize.x / 2) / sizeOfWalls)])
            player2->sprite.setPosition(position2.x + 1, position2.y);
    for(int i = floor(position2.y - spriteSize.y / 2); i < floor(position2.y + spriteSize.y / 2); ++i)
        if((*maze->cells)[floor(i / sizeOfWalls) - 10][floor((position2.x + spriteSize.x / 2) / sizeOfWalls)])
            player2->sprite.setPosition(position2.x - 1, position2.y);
    if((*maze->cells)[floor((position2.y  - spriteSize.y / 2)/ sizeOfWalls) - 10][position2.x / sizeOfWalls])
        player2->sprite.setPosition(position2.x, position2.y + 1);
    for(int i = floor(position2.x - spriteSize.x / 2); i < floor(position2.x + spriteSize.x / 3); ++i)
        if ((*maze->cells)[floor((position2.y + spriteSize.y / 2) / sizeOfWalls) - 10][ceil((float) i / sizeOfWalls)] && !(*maze->cells)[floor((position2.y + spriteSize.y / 2) / sizeOfWalls) - 11][ceil((float) i / sizeOfWalls)])
            player2->sprite.setPosition(position2.x, position2.y - 1);

    //Collision between two players
    if(player1->sprite.getGlobalBounds().intersects(player2->sprite.getGlobalBounds())) {
        this->player1->sprite.setPosition(position1.x, position1.y);
        this->player2->sprite.setPosition(position2.x, position2.y);
    }
}

void Game::initTexture() {
    //Load a texture from file
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/Bullet.png");

    this->textures["RedTank"] = new sf::Texture();
    this->textures["RedTank"]->loadFromFile("Textures/RedTank.png");

    this->textures["BlueTank"] = new sf::Texture();
    this->textures["BlueTank"]->loadFromFile("Textures/BlueTank.png");

    this->textures["RedTankLives"] = new sf::Texture();
    this->textures["RedTankLives"]->loadFromFile("Textures/RedTankLives.png");

    this->textures["BlueTankLives"] = new sf::Texture();
    this->textures["BlueTankLives"]->loadFromFile("Textures/BlueTankLives.png");

    this->textures["Lives"] = new sf::Texture();
    this->textures["Lives"]->loadFromFile("Textures/lives.png");

    this->textures["Explosion"] = new sf::Texture();
    this->textures["Explosion"]->loadFromFile("Textures/Explosion.png");

    this->textures["BlueWon"] = new sf::Texture();
    this->textures["BlueWon"]->loadFromFile("Textures/BlueWon.png");

    this->textures["RedWon"] = new sf::Texture();
    this->textures["RedWon"]->loadFromFile("Textures/RedWon.png");


    player1->sprite.setTexture(*textures["RedTank"]);
    player2->sprite.setTexture(*textures["BlueTank"]);
    redTank.setTexture(*textures["RedTankLives"]);
    blueTank.setTexture(*textures["BlueTankLives"]);
    redTankLifes.setTexture(*textures["Lives"]);
    blueTankLifes.setTexture(*textures["Lives"]);
    explosion.setTexture(*textures["Explosion"]);
}

void Game::initPositions() {
    sf::Vector2f position;
    player1->sprite.setPosition(player1->generatePosition());
    position = player2->generatePosition();
    while(player1->sprite.getPosition().x == position.x || player1->sprite.getPosition().y == position.y)
        position = player2->generatePosition();
    player2->sprite.setPosition(position);
}

void Game::initLivesTable() {
    redTank.setScale(0.7f, 0.7f);
    redTank.setPosition(200.f, 1250.f);

    blueTank.setScale(0.7f, 0.7f);
    blueTank.setPosition(900.f, 1250.f);

}

void Game::updateBulletCollision(std::vector<Bullet*>& bullets, int player) {
    int counter = 0;
    for(auto *bullet: bullets) {
        bullet->update();

        if(bullet->dir == 'n' && (*maze->cells)[floor(bullet->shape.getPosition().y / sizeOfWalls) - 10][floor((bullet->shape.getPosition().x - bullet->bulletSize.x / 2) / sizeOfWalls)] ||
                bullet->dir == 's' && (*maze->cells)[floor((bullet->shape.getPosition().y + bullet->bulletSize.y / 2) / sizeOfWalls) - 10][ceil((float) bullet->shape.getPosition().x / sizeOfWalls)] ||
                bullet->dir == 'w' && (*maze->cells)[ceil(bullet->shape.getPosition().y / sizeOfWalls) - 10][ceil((bullet->shape.getPosition().x - bullet->bulletSize.x / 2) / sizeOfWalls)] ||
                bullet->dir == 'e' && (*maze->cells)[floor(bullet->shape.getPosition().y / sizeOfWalls) - 10][floor((bullet->shape.getPosition().x + bullet->bulletSize.x / 2) / sizeOfWalls)]) {
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
            counter--;
        }
        else if(player2->sprite.getGlobalBounds().intersects(bullet->shape.getGlobalBounds()) && player == 1) {
            if(player2->numOfLives - 1 == 0)
                player1->points+=15;
            else
                player1->points+=5;
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
            player2->damaged = true;
            counter--;
            }
        else if(player1->sprite.getGlobalBounds().intersects(bullet->shape.getGlobalBounds()) && player == 2) {
            if(player1->numOfLives - 1== 0)
                player2->points+=15;
            else
                player2->points+=5;
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
            player1->damaged = true;
            counter--;
        }

        counter++;
    }
}

void Game::initTextPosition() {
    player1->score.setPosition(250.f, 50.f);
    player2->score.setPosition(950.f, 50.f);
}

void Game::renderLivesTable() {
    sf::Vector2u textureSize = textures["Lives"]->getSize();
    textureSize.y /= 5;

    redTankLifes.setTexture(*textures["Lives"]);
    blueTankLifes.setTexture(*textures["Lives"]);
    redTankLifes.setScale(2.f, 2.f);
    blueTankLifes.setScale(2.f, 2.f);


    redTankLifes.setTextureRect(sf::IntRect(0, textureSize.y * (5 - player1->numOfLives), textureSize.x,textureSize.y));
    redTankLifes.setPosition(180.f, 1450.f);
    blueTankLifes.setTextureRect(sf::IntRect(0, textureSize.y * (5 - player2->numOfLives), textureSize.x,textureSize.y));
    blueTankLifes.setPosition(880.f, 1450.f);
}

void Game::updatePlayer() {
    sf::Vector2f position;
    if(player1->damaged) {
        explosionAnimation(player1->getPos().x, player1->getPos().y);
        position = player1->generatePosition();
        while(abs(player2->sprite.getPosition().x - position.x) < 100 && abs(player2->sprite.getPosition().y - position.y) < 100)
            position = player1->generatePosition();
        player1->sprite.setPosition(position);
        player1->damaged = false;
    }
    if(player2->damaged) {
        explosionAnimation(player2->getPos().x, player2->getPos().y);
        position = player2->generatePosition();
        while(abs(player1->sprite.getPosition().x -  position.x) < 100 || abs(player1->sprite.getPosition().y - position.y) < 100)
            position = player2->generatePosition();
        player2->sprite.setPosition(position);
        player2->damaged = false;
    }
    if(player1->numOfLives == 0 || player2->numOfLives == 0)
        gameIsOver = true;
}

void Game::explosionAnimation(float pos_x, float pos_y) {
    sf::Vector2u textureSize = textures["Explosion"]->getSize();
    textureSize.x /= 8;

    explosion.setPosition(pos_x - 160, pos_y - 160);
    explosion.setScale(5.f, 5.f);
        for(int j = 0; j < 8; ++j){
            explosion.setTextureRect(sf::IntRect(textureSize.x * j, 0.f, textureSize.x,textureSize.y));
            window->draw(explosion);
            window->display();
        }
}

void Game::updateClient() {
    sf::Packet packet;
    sf::Vector2f vec = player1->getPos();
    packet << vec.x << vec.y;
    socket.send(packet);
    packet.clear();
}

void Game::receiveClientData() {
    size_t received;
    socket.receive(button, sizeof(button), received);
}


//void Game::initStates() {
//    this->states.push(new GameState(this->window));
//}
