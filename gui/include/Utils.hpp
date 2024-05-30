/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Utils
*/

#pragma once

#include <fstream>
#include <filesystem>
#include <exception>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Error.hpp"


/**
 * @brief Utility class that provides various helper functions and exception classes.
 *
 * The `Utils` class is a utility class that provides various helper functions and exception classes
 * for common operations such as string manipulation, file handling, and command line argument validation.
 * It also includes exception classes for handling specific error conditions.
 */
class Utils {
    public:
        /**
         * @brief Exception class thrown when attempting to parse a directory.
         */
        class IsDirectoryException : public EGE::Error {
            public:
                IsDirectoryException(const std::string& msg) : Error(msg) {}
        };

        /**
         * @brief Exception class for file not found errors.
         */
        class FileNotFoundException : public EGE::Error {
            public:
                /**
                 * @brief Constructs a FileNotFoundException object with the default error message.
                 * The default error message is "File not found".
                */
                FileNotFoundException(const std::string& msg = "File not found") : Error(msg) {};
        };

        /**
         * @brief Exception class for invalid arguments.
         *
         * This exception is thrown when invalid arguments are provided.
         * It is derived from the base class Error.
         */
        class InvalidArgumentsException : public EGE::Error {
            public:
                /**
                 * @brief Constructs an InvalidArgumentsException object with the given error message.
                 *
                 * @param msg The error message associated with the exception.
                 */
                InvalidArgumentsException(const std::string& msg) : Error(msg) {}
        };

        /**
         * @brief Splits a string into a vector of substrings based on a delimiter.
         *
         * @param str The string to be split.
         * @return std::vector<std::string> A vector containing the substrings.
         */
        static std::vector<std::string> split(const std::string &str);

        /**
         * @brief Splits a string into a vector of substrings based on a separator character.
         *
         * @param str The string to be split.
         * @param sep The separator character.
         * @return std::vector<std::string> A vector containing the substrings.
         */
        static std::vector<std::string> split(const std::string &str, char sep);

        /**
         * Retrieves the content of a file.
         *
         * @param filename The name of the file to read.
         * @return The content of the file as a string.
         */
        static std::string getFileContent(const std::string &filename);

        /**
         * Writes content to a file.
         * 
         * @param filename The name of the file to write to.
         * @param content The content to write to the file.
         * @param append If true, the content will be appended to the file. Otherwise, the file will be overwritten.
         * @throws std::exception if the file cannot be opened.
        */
        static void setFileContent(const std::string &filename, const std::string &content, bool append = false);

        /**
         * Converts a vector of strings to a single string.
         *
         * @param container The vector of strings to be converted.
         * @return The concatenated string.
         */
        static std::string vectorToString(const std::vector<std::string> &container);

        /**
         * @brief Checks the command line arguments.
         *
         * This function is responsible for validating the command line arguments passed to the program.
         *
         * @param argc The number of command line arguments.
         * @param argv An array of C-style strings representing the command line arguments.
         */
        static void checkArgs(int argc, char **argv);
};

