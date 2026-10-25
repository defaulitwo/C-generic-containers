// Generic C-style linked list container

#ifndef INC_LINKED_LIST
#define INC_LINKED_LIST

#include <stdlib.h>

typedef struct Node_Blueprint
{
    void * next;
    // type value;
} Node_Blueprint;

typedef struct Linked_List_Blueprint
{
    void * head;
} Linked_List_Blueprint;

#define LINKED_LIST(type) \
typedef struct Node_##type \
{ \
    struct Node_##type * next; \
    type value; \
} Node_##type; \
\
typedef struct Linked_List_##type \
{ \
    Node_##type * head; \
} Linked_List_##type; \
\
typedef struct Linked_List_Iterator_##type \
{ \
    Node_##type * ptr; \
} Linked_List_Iterator_##type; \
\
void Linked_List_init_##type(Linked_List_##type * list) \
{ \
    list->head = NULL; \
} \
\
void Linked_List_push_##type(Linked_List_##type * list, type value) \
{ \
    Node_##type * new_node = (Node_##type *)malloc(sizeof(Node_##type)); \
    new_node->value = value; \
    new_node->next = NULL; \
    new_node->next = list->head; \
    list->head = new_node; \
} \
\
void Node_free_##type(Node_##type * node)\
{ \
    if (!node) return; \
    Node_free_##type(node->next); \
    free(node); \
} \
\
void Linked_List_free_##type(Linked_List_##type * list)\
{ \
    Node_free_##type(list->head); \
} \
\
Linked_List_Iterator_##type Linked_List_begin_##type(Linked_List_##type * list) \
{ \
    Linked_List_Iterator_##type iterator = { list->head }; \
    return iterator; \
} \
\
Linked_List_Iterator_##type Linked_List_end_##type(Linked_List_##type * list) \
{ \
    Linked_List_Iterator_##type iterator = { NULL }; \
    return iterator; \
} \
\
void Linked_List_Iterator_increment_##type(Linked_List_Iterator_##type * iterator) \
{ \
    iterator->ptr = iterator->ptr->next; \
} \
\
short Linked_List_Iterator_equal_##type(Linked_List_Iterator_##type * iterator1, Linked_List_Iterator_##type * iterator2) \
{ \
    return iterator1->ptr == iterator2->ptr; \
} \
\
type * Linked_List_Iterator_to_ptr_##type(Linked_List_Iterator_##type * iterator) \
{ \
    return &iterator->ptr->value; \
} 

#endif