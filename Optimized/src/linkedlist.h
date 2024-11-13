#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "input-handler.h"

typedef struct node
{
    void *data_ptr;
    struct node *prev;
    struct node *next;
} node_t;

void insert_node(node_t **root, node_t *new_node);
void insert_node_in_order(node_t **root, node_t *new_node);
void delete_node(node_t **root, node_t *node_to_delete);
node_t *create_node(void *data);

/***********************************************************************************
 * Name:       search_node
 *
 * Input:      node_t *root - Pointer to the root node of the linked list where
 *                            the search will begin.
 *             void *key - Pointer to the key that is being searched for.
 *             uint16_t (*cmp)(void *, void *) - Function pointer to a comparison
 *                            function that compares the key with the data in each node.
 *
 * Return:     success node_t* - Returns a pointer to the node where the key was found,
 *             fail    NULL     `NULL` if the key is not found in the list.
 *
 * Description: This function searches through a linked list starting from the root node.
 *              It uses the provided comparison function `cmp` to compare the key
 *              with the data in each node.
 *************************************************************************************/
node_t *search_node(node_t *root, void *key, uint16_t (*cmp)(void *, void *));
void free_everything();

#endif // LINKEDLIST_H_INCLUDED
