#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sched.h>
#include "list.h"

struct st
{
    int a;
    int b;
    
    struct list_head list;
};


struct list_head *add_new_st(struct st data, struct list_head *head)
{
    LIST_HEAD(new_head); /* init is at local. */
    
    struct st *allocated = malloc(sizeof(struct st));
    *allocated = data;
    
    allocated->list = new_head;
    allocated->list.next = &(allocated->list);
    allocated->list.prev = &(allocated->list); /* re-init at allocated space. */

    if (head == NULL)
    {
        // param header is null. init it.
        printf("init: %d\n", allocated->a);
    }
    else
    {
        printf("added: %d\n", allocated->a);
        list_add(&(allocated->list), head);
    }
    
    return &(allocated->list);
}

int main(int argc, const char * argv[])
{
    struct st items[] = {
        {1, 2, NULL},
        {5, 6, NULL},
        {9, 10, NULL}
    };
    
    LIST_HEAD(H);

    struct list_head *end = &H;
    
    for (int i = 0; i < 3; ++i)
    {
        end = add_new_st(items[i], end);
    }
    
    struct st *cur;
    list_for_each_entry(cur, &H, list) {
        printf("%d, %d\n", cur->a, cur->b);
    }
    
	return 0;
}
