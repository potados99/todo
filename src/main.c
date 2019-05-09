#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sched.h>
#include "list.h"

struct task
{
    int prio;
    char *title;
    
    // other fields...
    
    struct list_head list;
};


struct list_head *add_new_st(struct task data, struct list_head *head)
{
    if (!head)
        return NULL;
    
    struct task *alloced_st = malloc(sizeof(struct task));
    *alloced_st = data;

    alloced_st->list.next = &(alloced_st->list);
    alloced_st->list.prev = &(alloced_st->list); /* init node at allocated space. */
    
    list_add(&(alloced_st->list), head);

    return &(alloced_st->list);
}

int main(int argc, const char * argv[])
{
    // alloc & init
    LIST_HEAD(H);
    struct list_head *end = &H;
    

    struct task tasks[] = {
        {4, "Low prio one.", NULL},
        {1, "High prio one.", NULL},
        {2, "So so.", NULL},
        {4, "Not important.", NULL}
    };

    
    
    // assign
    for (int i = 0; i < sizeof(tasks) / sizeof(struct task); ++i)
    {
        end = add_new_st(tasks[i], end);
    }
    
    
    // use
    struct task *cur;
    list_for_each_entry(cur, &H, list) {
        printf("%d, %s\n", cur->prio, cur->title); /* entry start from the next to the header. */
    }
    
    // dealloc
    struct list_head *hcur;
    list_for_each(hcur, &H) {
        
    }
    
    
	return 0;
}
