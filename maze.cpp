//
// Created by Элина Карапетян on 27.05.2022.
//
#include "maze.h"
#define sizeOfWalls 20
#define windWidth 1420
#define windHeight 1420

Maze::Maze() {
    initVariables();
    mazeGenerator();
}

void Maze::render(sf::RenderTarget* target) {
    int height = (windHeight - 400)/sizeOfWalls;
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(sizeOfWalls, sizeOfWalls));

    for(int i = 0; i < height; ++i){
        for(int j = 0; j < windWidth/sizeOfWalls; ++j){
            cell.setPosition(sizeOfWalls * j, sizeOfWalls * i + 200);
            cell.setFillColor(sf::Color(192, 192, 192));
            if((*cells)[i][j]){
                cell.setPosition(sizeOfWalls * j, sizeOfWalls * i + 200);
                cell.setFillColor(sf::Color(75, 75, 75));
            }
                target->draw(cell);
            }
        }
}

void Maze::mazeGenerator() {
    int height = (windHeight - 400)/sizeOfWalls;

    //Making walls
    float x = sizeOfWalls;
    float y = sizeOfWalls;
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < windWidth/sizeOfWalls; ++j) {
            if(i == 0 || j == 0 || i == height - 1|| j == windWidth/sizeOfWalls - 1 \
            || i % 10 == 0 || j % 10 == 0){
                (*cells)[i][j] = true;
            }
        }
    }



    /*Binary tree algorithm:
     * - https://itnan.ru/post.php?c=1&p=320140 - description of the algorithm
     */

    int goUp = 0; // 1 - break the top wall; 0 - break the right wall

    for (int i = 1; i < height - 1; i+=10) {
        for (int j = 1; j < windWidth / sizeOfWalls - 1; j+=10) {
            if (j % 10 == 1 && i % 10 == 1)
                goUp = rand() % 2;
            if (i < 10 && j < 60) {
                for (int k = i; k < i + 9; ++k) {
                    (*cells)[k][j + (10 - j % 10)] = false;
                }
            } else if ((*cells)[i - 1][j] && !(*cells)[i][j] && i != 1) {
                if (goUp || j > 60) {
                    for (int k = j; k < j + 9; ++k) {
                        (*cells)[i - 1][k] = false;
                    }
                } else {
                    for (int k = i; k < i + 9; ++k) {
                        (*cells)[k][j + (10 - j % 10)] = false;
                    }
                }
            }
        }
    }

}

void Maze::initVariables() {
    int height = (windHeight - 400)/sizeOfWalls;
    cells = new std::vector<std::vector<bool> >(height, std::vector<bool>(windWidth/sizeOfWalls));
}

Maze::~Maze() {
    delete cells;
}


