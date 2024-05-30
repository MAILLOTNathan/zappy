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
        std::shared_ptr<Onyx::Gui> gui = std::make_shared<Onyx::Gui>();
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
            gui->update(running);
        }
    } catch (const EGE::Error& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
