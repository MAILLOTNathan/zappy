/*
** EPITECH PROJECT, 2024
** gui
** File description:
** main
*/

#include "Gui.hpp"
#include "TcpClient.hpp"
#include "UserInterface.hpp"
#include <thread>

int main()
{
    try {
        bool running = true;
        UserInterface *interface = new UserInterface();


        interface->_menuBar->add(new EGE::Menu("File"));
        interface->_menuBar->add(new EGE::Menu("Edit"));
        interface->_menuBar->add(new EGE::Menu("View"));
        interface->_menuBar->add(new EGE::Menu("Help"));

        interface->_panels.at(0)->add(new EGE::Button("Button", [](){std::cout << "PD_GET" << std::endl;}));
        interface->_panels.at(0)->add(new EGE::Text("Salut a tous bande de gentilles personnes..."));

        std::shared_ptr<Onyx::Gui> gui = std::make_shared<Onyx::Gui>();

        interface->init(interface->_window);

        net::TcpClient client("127.0.0.1", 4242);
        client.addCommand("msz", net::type_command_t::MSZ, [&gui](std::vector<std::string>& args) {
            if (args.size() != 3)
                throw EGE::Error("Wrong number of param.");
            gui->createMap(std::stoi(args[1]), std::stoi(args[2]));
        });
        client.addCommand("pnw", net::type_command_t::PNW, [](std::vector<std::string>& args) {
            for (auto& arg : args) {
                std::cout << arg << std::endl;
            }
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
        });
        client.connection();
        client.sendRequest("msz\n");
        client.sendRequest("mct\n");

        while (running) {
            interface->clear();
            interface->draw();
            interface->display();
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
