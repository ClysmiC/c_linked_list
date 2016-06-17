/**
 * CS 2110 - Spring 2014 - Homework #12
 * Edited by: Brandon Whitehead, Andrew Wilder

 * Homework by: Andrew Smith -- asmith379

 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
    struct lnode* prev; /* Pointer to previous node */
    struct lnode* next; /* Pointer to next node */
    void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    node *new_node = malloc(sizeof(node));
    if(new_node == NULL)
    {
        return NULL;
    }

    new_node -> data = data;
    new_node -> next = NULL;
    new_node -> prev = NULL;

    return new_node;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    list *new_list = malloc(sizeof(list));
    if(new_list == NULL)
    {
        return NULL;
    }

    new_list -> head = NULL;
    new_list -> tail = NULL;
    new_list -> size = 0;

    return new_list;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    node *new_node = create_node(data);

    if(is_empty(llist))
    {
        llist -> head = new_node;
        llist -> tail = new_node;
    }
    else
    {
        new_node -> next = llist -> head;
        llist -> head -> prev = new_node;
        llist -> head = new_node;
    }

    llist -> size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
    node *new_node = create_node(data);

    if(is_empty(llist))
    {
        llist -> head = new_node;
        llist -> tail = new_node;
    }
    else
    {
        new_node -> prev = llist -> tail;
        llist -> tail -> next = new_node;
        llist -> tail = new_node;
    }

    llist -> size++;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    if(llist -> head == NULL)
        return NULL;

    return llist -> head -> data;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    if(llist -> tail == NULL)
        return NULL;

    return llist -> tail -> data;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    if (is_empty(llist))
        return -1;

    node *temp = llist -> head;

    //also need to change tail if the size is only 1
    if(size(llist) == 1)
    {
        llist -> head = NULL;
        llist -> tail = NULL;
    }
    else
    {
        llist -> head = llist -> head -> next;
        llist -> head -> prev = NULL;
    }

    free_func(temp -> data);
    free(temp);

    llist -> size--;

    return 0;
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    if (is_empty(llist))
        return -1;

    node *temp = llist -> tail;

    //also need to change tail if the size is only 1
    if(size(llist) == 1)
    {
        llist -> head = NULL;
        llist -> tail = NULL;
    }
    else
    {
        llist -> tail = llist -> tail -> prev;
        llist -> tail -> next = NULL;
    }

    free_func(temp -> data);
    free(temp);

    llist -> size--;

    return 0;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
    list *copy = create_list();
    node *current = llist -> head;

    while(current != NULL)
    {
        push_back(copy, copy_func(current -> data));
        current = current -> next;
    }

    return copy;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    return llist -> size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    node *current = llist -> head;
    node *next_node;
    int count = 0;

    while(current != NULL)
    {
        next_node = current -> next;

        if(pred_func(current -> data))
        {
            count++;

            //remove head
            if(current == llist -> head)
            {
                remove_front(llist, free_func);
            }
            //remove tail
            else if(current == llist -> tail)
            {
                remove_back(llist, free_func);
            }
            //remove general node
            else
            {
                current -> next -> prev = current -> prev;
                current -> prev -> next = current -> next;

                free_func(current -> data);
                free(current);
                llist -> size--;
            }
        }

        current = next_node;
    }

    return count;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    //non-zero size returns false
    //zero size returns true
    return !(llist -> size);
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
    while(llist -> head != NULL)
    {
        remove_front(llist, free_func);
    }
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    node *current = llist -> head;

    while(current != NULL)
    {
        do_func(current -> data);

        current = current -> next;
    }
}
