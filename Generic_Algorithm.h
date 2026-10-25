// generic container algorithms

#ifndef INC_GENERIC_ALGORITHM
#define INC_GENERIC_ALGORITHM

// swap two values
#define DECLARE_SWAP(type) \
void swap_##type(type * a, type * b) \
{ \
    type tmp = *a; \
    *a = *b; \
    *b = tmp; \
}

// block that loops over every element
#define for_each(container_type, type, container) \
for ( \
    container_type##_Iterator_##type current = container_type##_begin_##type(&container), \
    end = container_type##_end_##type(&container); \
    !container_type##_Iterator_equal_##type(&current, &end); \
    container_type##_Iterator_increment_##type(&current) ) 

// block that automatically initializes a container and destroys it when scope ends
// like constructors and destructors
#define with_container(container_type, type, name) \
    for (container_type##_##type name, * _i = (void *)1; \
         container_type##_init_##type(&name), _i; \
         container_type##_free_##type(&name), _i = 0)

#endif