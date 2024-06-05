/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** list
*/

/**
 * @file list.h
 * @brief This file contains the definition of the linked_list_t structure.
 */
#ifndef LIST_H_
    #define LIST_H_

    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdio.h>

/**
 * @brief Typedef for a constructor function pointer.
 *
 * This typedef represents a constructor function pointer that takes
 * a va_list pointer
 * as a parameter and returns a void pointer.
 *
 * @param args A va_list pointer containing the arguments for the constructor.
 * @return A void pointer representing the constructed object.
 */
typedef void *(*constructor_t)(va_list *args);

/**
 * @brief Typedef for a destructor function pointer.
 *
 * This typedef represents a destructor function pointer
 * that takes a void pointer
 * as a parameter and does not return a value.
 *
 * @param obj A void pointer representing the object to be destroyed.
 */
typedef void (*destructor_t)(void *obj);

/**
 * @struct linked_list_s
 * @brief Structure representing a linked list node.
 *
 * The linked_list_s structure represents a node in a linked list.
 * It contains a pointer to the data stored in the node, as well as
 * pointers to the next and previous nodes in the list.
 *
 * @param data A void pointer to the data stored in the node.
 * @param next A pointer to the next node in the list.
 * @param prev A pointer to the previous node in the list.
 */
typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
    struct linked_list_s *prev;
} linked_list_t;


/**
 * Adds a new node to the front of the linked list.
 *
 * @param l The pointer to the linked list.
 * @param create The constructor function to create the new node.
 * @param ap The variable argument list for the constructor function.
 * @return true if the node was successfully added, false otherwise.
 */
bool push_front_node(linked_list_t **l, constructor_t create, va_list *ap);

/**
 * Creates a new node for a linked list.
 *
 * @param ap The va_list pointer for the constructor arguments.
 * @param constructor The constructor function for the node.
 * @return A pointer to the newly created linked_list_t node.
 */
linked_list_t *new_node(va_list *ap, constructor_t constructor);

/**
 * Adds a new node to the end of a linked list.
 *
 * @param l         A pointer to the pointer of the linked list.
 * @param create    The constructor function used to create the new node.
 * @param ap        A pointer to the va_list of arguments for the constructor
 * function.
 * @return          Returns true if the node was successfully added,
 * false otherwise.
 */
bool push_back_node(linked_list_t **l, constructor_t create, va_list *ap);

/**
 * @brief Destroys a node in a linked list.
 *
 * This function destroys a node in a linked list by removing it from
 * the list and freeing its memory.
 *
 * @param l A pointer to a pointer to the linked list.
 * @param destroy A function pointer to the destructor function that will
 * be called to free the memory of the node's data.
 */
void destroy_node(linked_list_t **l, destructor_t destroy);

/**
 * @struct list_s
 * @brief Represents a list data structure.
 *
 * The `list_t` structure contains a linked list of nodes,
 * along with function pointers
 * for creating and destroying nodes. It also keeps track
 * of the length of the list.
 * @param nodes A pointer to the linked list of nodes.
 * @param create A function pointer to the constructor function for creating
 * nodes.
 * @param destructor A function pointer to the destructor function
 * for destroying nodes.
 */
typedef struct list_s {
    linked_list_t *nodes;
    constructor_t create;
    destructor_t destructor;
    int len;
} list_t;

/**
 * Removes a node from the linked list at the specified index.
 *
 * @param l The pointer to the pointer of the linked list.
 * @param index The pointer to the node to be removed.
 * @param free_data A boolean indicating whether the data should be freed.
 * @return true if the node was successfully removed, false otherwise.
 */
bool remove_node(list_t **l, linked_list_t *index, bool free_data);

/**
 * Returns the number of elements in the list.
 *
 * @param l The pointer to the list.
 * @return The number of elements in the list.
 */
size_t list_len(list_t *l);

/**
 * Adds an element to the front of the list.
 *
 * @param l The list to which the element will be added.
 * @param ... The element to be added to the list.
 * @return true if the element was successfully added, false otherwise.
 */
bool push_front_list(list_t *l, ...);

/**
 * @brief Destroys a list and frees all allocated memory.
 *
 * This function destroys a list by freeing all the nodes and their
 * associated data.
 * It also frees the memory allocated for the list structure itself.
 *
 * @param l A pointer to a pointer to the list to be destroyed.
 */
void destroy_list(list_t **l);

/**
 * Adds an element to the end of the list.
 *
 * @param l The list to which the element will be added.
 * @param ... The element(s) to be added to the list.
 * @return true if the element(s) were successfully added, false otherwise.
 */
bool push_back_list(list_t *l, ...);

/**
 * @brief Creates a new list.
 *
 * This function creates a new list and returns a pointer to it.
 *
 * @param constructor The constructor function to be used
 * for initializing elements in the list.
 * @param destructor The destructor function to be used
 * for cleaning up elements in the list.
 * @return A pointer to the newly created list.
 */
list_t *create_list(constructor_t constructor, destructor_t destructor);

/**
 * Finds a node in the linked list that matches the given data using
 * the provided comparison function.
 *
 * @param l The linked list to search in.
 * @param data The data to match against.
 * @param cmp The comparison function to use for matching.
 * @return A pointer to the found node, or NULL if no matching node is found.
 */
linked_list_t *list_find_node(list_t *l, void *data,
    bool (*cmp)(void *, void *));


/**
 * Finds a node in the linked list that contains a specific reference.
 *
 * @param l The linked list to search in.
 * @param ref The reference to search for.
 * @return A pointer to the found node, or NULL if not found.
 */
linked_list_t *list_find_node_p(list_t *l, void *ref);


    /**
     * @brief Macro to move the list pointer forward to the next element.
     *
     * This macro updates the list pointer to point to the next
     * element in the list.
     *
     * @param list The list pointer to be moved forward.
     */
    #define LIST_FORWARD(list) (list = list->next)

    /**
     * @brief Macro to cast a variable to a specific type.
     *
     * This macro performs a type cast on the given
     * variable to the specified type.
     *
     * @param type The type to cast the variable to.
     * @param var The variable to be casted.
     * @return The casted variable of the specified type.
     */
    #define CAST(type, var) ((type)var)

#endif /* !LIST_H_ */
