#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "arraylist.h"

int main(int argc, const char * argv[]) {
	printf("Hello, world!\n");

	/*
	struct table mytable;

	table_init(&mytable, "ID", "Todo", "Priority", NULL);

	table_row_addl(&mytable, "01", "Go home", "Low", NULL);
	table_row_addl(&mytable, "02", "Have dinner", "Low", NULL);
	table_row_addl(&mytable, "04", "Debug this app.", "High", NULL);

	table_print(&mytable);
*/

	char * a = allocate_string("hello");
	char * b = allocate_string("world");

	struct arraylist mylist;

	list_init(&mylist);

	list_add(&mylist, a);
	list_add(&mylist, b);

	list_dump(&mylist);

	list_free(&mylist);

	return 0;
}
