/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string_array
*/

#ifndef STRING_ARRAY_H_
    #define STRING_ARRAY_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>

/**
 * @brief Frees the memory allocated for the string array.
 *
 * @param array The string array to be freed.
 */
void free_string_array(char **array);

/**
 * @brief Returns the length of the string array.
 *
 * @param array The string array to get the length of.
 * @return The length of the string array.
 */
int length_string_array(char **array);

/**
 * @brief Appends a string to the end of the string array.
 *
 * @param array The string array to append to.
 * @param string The string to append.
 * @return The updated string array with the appended string.
 */
[[__nodiscard__]] char **append_string_array(char **array, char *string);

/**
 * @brief Removes the last element from the string array.
 *
 * @param array The string array to remove the last element from.
 * @return The updated string array without the last element.
 */
[[__nodiscard__]] char **pop_back_string_array(char **array);

/**
 * @brief Removes the first element from the string array.
 *
 * @param array The string array to remove the first element from.
 * @return The updated string array without the first element.
 */
[[__nodiscard__]] char **pop_front_string_array(char **array);

/**
 * @brief Appends a string to the start of the string array.
 *
 * @param array The string array to append to.
 * @param string The string to append.
 * @return The updated string array with the prepended string.
 */
[[__nodiscard__]] char **prepend_string_array(char **array, char *string);

/**
 * @brief Inserts a string at a specified index in the string array.
 *
 * @param arr The string array to insert the string into.
 * @param str The string to insert.
 * @param idx The index at which to insert the string.
 * @return The updated string array with the inserted string.
 */
[[__nodiscard__]] char **insert_string_array(char **arr, char *str, int idx);

/**
 * @brief Removes an element at a specified index from the string array.
 *
 * @param array The string array to remove the element from.
 * @param index The index of the element to remove.
 * @return The updated string array without the specified element.
 */
[[__nodiscard__]] char **remove_string_array(char **array, int index);

/**
 * @brief Checks if a string is present in the string array.
 *
 * @param array The string array to search in.
 * @param string The string to search for.
 * @return True if the string is present in the array, false otherwise.
 */
bool contains_string_array(char **array, char *string);

/**
 * @brief Converts a string array to a single string, separated by newlines.
 *
 * @param array The string array to convert.
 * @return A single string containing all elements of the array,
 * separated by newlines.
 */
[[__nodiscard__]] char *string_array_to_string(char **array);

/**
 * @brief Converts a string to a string array, using a specified separator.
 *
 * @param str The string to convert.
 * @param sep The separator to use.
 * @return A string array containing the elements of the string,
 * separated by the specified separator.
 */
[[__nodiscard__]] char **string_to_string_array_separator(char *str, char sep);

/**
 * @brief Converts a string to a string array.
 *
 * @param string The string to convert.
 * @return A string array containing the elements of the string,
 * separated by newlines.
 */
[[__nodiscard__]] char **string_to_string_array(char *string);

[[__nodiscard__]] char *string_array_to_string_separator(char **arr, char sep);

#endif /* !STRING_ARRAY_H_ */
