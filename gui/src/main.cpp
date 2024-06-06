/*
** EPITECH PROJECT, 2024
** gui
** File description:
** main
*/

#include "Gui.hpp"
#include "TcpClient.hpp"
#include <thread>

int main()
{
    try {
        bool running = true;

        net::TcpClient client("127.0.0.1", 4242);
        std::shared_ptr<Onyx::Gui> gui = std::make_shared<Onyx::Gui>(client);

        client.addCommand("msz", net::type_command_t::MSZ, [&gui](std::vector<std::string>& args) {
            if (args.size() != 3)
                throw EGE::Error("Wrong number of param.");
            gui->createMap(std::stoi(args[1]), std::stoi(args[2]));
            gui->createWorldPanel();
            gui->createTilePanel();
            gui->createConsolePanel();
            gui->updateConsolePanel(args);
        });
        client.addCommand("pnw", net::type_command_t::PNW, [&gui](std::vector<std::string>& args) {
            if (args.size() != 7)
                throw EGE::Error("Wrong number of param.");
            // 1: player id (need to remove the #)
            // 2: x pos
            // 3: y pos
            // 4: orientation (1: N, 2: E, 3: S, 4: W)
            // 5: level
            // 6: team name

            gui->addPlayer(EGE::Maths::Vector2<int>(std::stoi(args[2]), std::stoi(args[3])), args[6], args[4]);
        });
        client.addCommand("bct", net::type_command_t::MCT, [&gui](std::vector<std::string>& args) {
            if (args.size() != 10)
                throw EGE::Error("Wrong number of param.");
            EGE::Maths::Vector2<int> position(std::stoi(args[1]), std::stoi(args[2]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::FOOD, std::stoi(args[3]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::LINEMATE, std::stoi(args[4]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::DERAUMERE, std::stoi(args[5]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::SIBUR, std::stoi(args[6]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::MENDIANE, std::stoi(args[7]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::PHIRAS, std::stoi(args[8]));
            gui->getMap()->addItem(position, Onyx::Item::TYPE::THYSTAME, std::stoi(args[9]));
            gui->updateWorldPanel();
            gui->updateTilePanel();
            gui->updateConsolePanel(args);
        });
        client.addCommand("sgt", net::type_command_t::SGT, [&gui](std::vector<std::string>& args) {
            if (args.size() != 2)
                throw EGE::Error("Wrong number of param.");
            gui->updateWorldSettings(std::stof(args[1]));
        });
        client.connection();
        client.sendRequest("msz\n");
        client.sendRequest("mct\n");
        client.sendRequest("sgt\n");

        while (running) {
            client.waitEvent();
            gui->update(running);
        }
        client.disconnect();
        exit(0);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
