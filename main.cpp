#include "maze.h"
#include "game.h"
#include <string.h>
#include <map>

using namespace std;
int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init game engine

    Game game;
//
//    bool x;
//
//    std::map <std::string, int> ipPlayer;
//    std::string ipName;
//    sf::Packet packet;
//    sf::IpAddress ip = sf::IpAddress::getLocalAddress();	//Локальный ip Адресс
//    char buffer[2002];
//    size_t received;	//??
//    std::string text = "connect to: ";
//    cout << ip << endl;
//
////***********Подключение***************//
//    sf::TcpListener listener;
//    listener.listen(2010);
//    listener.accept(game.socket);    //который будет содержать новое соединение
//    text += "Server";
//
//    game.socket.send(text.c_str(), text.length() + 1);
//    game.socket.receive(buffer, sizeof(buffer), received);
//    std::cout << buffer << std::endl;
//
//    //Receive the ip of tha player
//    game.socket.receive(packet);
//    packet >> ipName;
//    ipPlayer[ipName] = 1;
//    packet.clear();
//
//    //Send the number of the player
//    packet << ipPlayer[ipName];
//    game.socket.send(packet);
//    packet.clear();
//
//
//    for(int i = 0; i < 51; ++i) {
//        for (int j = 0; j < 71; ++j) {
//            x = game.maze->cells[0][i][j];
//            packet << x;
//            game.socket.send(packet);    //Отправка данных
//            packet.clear();
//        }
//    }
    //Game loop
    while(game.running()){

        //Update
        game.update();

        //Render
        game.render();
    }

    return 0;
}

