/*
** EPITECH PROJECT, 2024
** B-CCP-400-RUN-4-1-theplazza-nathan.maillot
** File description:
** Utils
*/

#include "Utils.hpp"

std::vector<std::string> Utils::split(const std::string &str)
{
    std::string strCpy = str;
    std::vector<std::string> content;
    size_t x = 0;

    for (size_t i = 0; i < strCpy.size(); i++){
        while (std::isspace(strCpy[i]) && i < strCpy.size())
            strCpy.erase(i, 1);
        while (!std::isspace(strCpy[i]) && i < strCpy.size()) {
            i++;
            x++;
        }
        content.push_back(strCpy.substr(i - x, x));
        x = 0;
    }
    return content;
}


std::vector<std::string> Utils::split(const std::string &str, char separator)
{
    std::string instruction;
    std::vector<std::string> content;
    std::istringstream iss = std::istringstream(str);
    while (std::getline(iss, instruction, separator)) {
        content.push_back(instruction);
    }
    return content;
}

std::string Utils::getFileContent(const std::string &filename)
{
    std::ifstream fileStream(filename);
    std::stringstream buffer;
    std::string lines;

    if (std::filesystem::is_directory(std::filesystem::path(filename)))
        throw Utils::IsDirectoryException("You are trying to parse a directory.");
    if (!fileStream.is_open())
        throw Utils::FileNotFoundException("The file " + filename + " was not found.");
    buffer << fileStream.rdbuf();
    lines = buffer.str();
    fileStream.close();

    return lines;
}

void Utils::setFileContent(const std::string &filename, const std::string &content, bool append)
{
    std::ofstream fileStream(filename, append ? std::ios_base::app : std::ios_base::trunc);

    if (!fileStream.is_open())
        throw Utils::FileNotFoundException("The file " + filename + " was not found.");
    fileStream << content;
    fileStream.close();
}

std::string Utils::vectorToString(const std::vector<std::string> &container)
{
    std::string result;

    for (auto &str : container) {
        result += str;
        result += " ";
    }
    result.pop_back();
    return result;
}

void Utils::checkArgs(int argc, char **argv)
{
    if (argc != 4) {
        throw InvalidArgumentsException("Invalid arguments.");
    }
    if (std::stoi(argv[1]) <= 0 || std::stoi(argv[2]) <= 0 || std::stoi(argv[3]) <= 0){
        throw InvalidArgumentsException("Invalid arguments.");
    }
}
