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

        // net::TcpClient client("127.0.0.1", 4242);
        // client.addCommand("msz", net::type_command_t::MSZ, [](std::vector<std::string>& args) {
        //     std::cout << "MSZ" << std::endl;
        //     for (auto& arg : args) {
        //         std::cout << arg << std::endl;
        //     }
        // });
        // client.addCommand("pnw", net::type_command_t::PNW, [](std::vector<std::string>& args) {
        //     std::cout << "PNW" << std::endl;
        //     for (auto& arg : args) {
        //         std::cout << arg << std::endl;
        //     }
        // });
        // client.connection();
        // client.sendRequest("msz\n");
        // while (true) {
        //     client.waitEvent();
        // }
        // client.disconnect();

        while (running) {
            interface->clear();
            interface->draw();
            interface->display();
            gui->update(running);
        }
    } catch (const EGE::Error& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
