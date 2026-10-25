#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Dynamic_List.h"
#include "Linked_List.h"
#include "Generic_Algorithm.h"

DYNAMIC_LIST(int)
DYNAMIC_LIST(char)

LINKED_LIST(int)

int main()
{
    printf("Hello world\n");

    // using generic foreach and with_container macros with different containers

    // with_container initializes the dynamic list at the beginning of the block
    // and destroys it at the end of the block
    with_container (Dynamic_List, int, arr)  
    {        
        Dynamic_List_push_int(&arr, 1);
        Dynamic_List_push_int(&arr, 2);
        Dynamic_List_push_int(&arr, 3);
        Dynamic_List_push_int(&arr, 4);    
        Dynamic_List_insert_int(&arr, 10, 0);
        
        printf("Dynamic List: ");
        
        // foreach loops over all the elements using generic iterators
        for_each (Dynamic_List, int, arr)
        {
            printf("%d ", *Dynamic_List_Iterator_to_ptr_int(&current));
        }
    } // arr is automatically freed

    printf("\n");

    with_container (Linked_List, int, list1)
    {
        Linked_List_push_int(&list1, 10);
        Linked_List_push_int(&list1, 20);
        Linked_List_push_int(&list1, 30);

        printf("Linked List: ");

        for_each(Linked_List, int, list1)
        {
            printf("%d ", *Linked_List_Iterator_to_ptr_int(&current));
        }
    } // list1 is automatically freed
}