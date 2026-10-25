// Generic C-style dynamic list container

#ifndef INC_DYNAMIC_LIST
#define INC_DYNAMIC_LIST

#include <stdlib.h>
#include <string.h>

// NOTE:
// ## means concatenate
// malloc and realloc expect sizes in BYTES, so must multiply by sizeof(type)

typedef struct Dynamic_List_Blueprint
{
    void * values;
    size_t capacity;
    size_t size;
} Dynamic_List_Blueprint;

#define DYNAMIC_LIST(type) \
typedef struct Dynamic_List_##type \
{ \
    type * values; \
    size_t capacity; \
    size_t size; \
} Dynamic_List_##type; \
\
typedef struct Dynamic_List_Iterator_##type \
{ \
    type * ptr; \
} Dynamic_List_Iterator_##type; \
\
void Dynamic_List_init_##type(Dynamic_List_##type * list) \
{ \
    list->values = (type *)malloc(10 * sizeof(type)); \
    list->capacity = 10; \
    list->size = 0; \
} \
\
void Dynamic_List_init_cap_##type(Dynamic_List_##type * list, size_t capacity) \
{ \
    list->values = (type *)malloc(capacity * sizeof(type)); \
    list->capacity = capacity; \
    list->size = 0; \
} \
\
void Dynamic_List_grow_if_needed_##type(Dynamic_List_##type * list)\
{ \
    if (list->size == list->capacity) \
    { \
        list->values = (type *)realloc(list->values, sizeof(type)*(list->capacity*2)); \
        list->capacity *= 2; \
    } \
} \
\
void Dynamic_List_push_##type(Dynamic_List_##type * list, type value) \
{ \
    Dynamic_List_grow_if_needed_##type(list); \
    list->values[list->size++] = value; \
} \
\
void Dynamic_List_insert_##type(Dynamic_List_##type * list, type value, size_t pos) \
{ \
    Dynamic_List_grow_if_needed_##type(list); \
    memmove(list->values + pos + 1, list->values + pos, sizeof(type)*(list->size - pos)); \
    list->values[pos] = value; \
    list->size++; \
} \
\
type Dynamic_List_pop_##type(Dynamic_List_##type * list) \
{ \
    return list->values[--list->size]; \
} \
\
void Dynamic_List_free_##type(Dynamic_List_##type * list) \
{ \
    if (list->values) free(list->values); \
    list->values = NULL; \
    list->capacity = 0; \
    list->size = 0; \
} \
\
Dynamic_List_Iterator_##type Dynamic_List_begin_##type(Dynamic_List_##type * list) \
{ \
    Dynamic_List_Iterator_##type iterator = { list->values }; \
    return iterator; \
} \
\
Dynamic_List_Iterator_##type Dynamic_List_end_##type(Dynamic_List_##type * list) \
{ \
    Dynamic_List_Iterator_##type iterator = { list->values + list->size }; \
    return iterator; \
} \
\
void Dynamic_List_Iterator_increment_##type(Dynamic_List_Iterator_##type * iterator) \
{ \
    iterator->ptr++; \
} \
\
short Dynamic_List_Iterator_equal_##type(Dynamic_List_Iterator_##type * iterator1, Dynamic_List_Iterator_##type * iterator2) \
{ \
    return iterator1->ptr == iterator2->ptr; \
} \
\
type * Dynamic_List_Iterator_to_ptr_##type(Dynamic_List_Iterator_##type * iterator) \
{ \
    return iterator->ptr; \
} 

// type-agnostic free function
void Dynamic_List_free(void * list)
{
    Dynamic_List_Blueprint * bp = (Dynamic_List_Blueprint *)list;
    if (bp->values) free(bp->values);
    bp->values = NULL;
    bp->capacity = 0;
    bp->size = 0;
}

#endif