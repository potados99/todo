#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

int main(int argc, const char * argv[]) {
	printf("Hello, world!\n");

	struct table mytable;

	table_init(&mytable, "id", "todo", "priority", NULL);

	table_print(&mytable);

	return 0;
}
