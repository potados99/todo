#include "table.h"
#include "ioutil.h"

#include <stdarg.h>

/*
struct table
{
        int             columns;
        int             rows;

	const char 	**column_names;

        table_element   **content;
}
*/

void table_init(struct table * t, const char * column_name, ...) {
	va_list valist;

	char * col_name = NULL;
	int col_index = -1;

	t->column_names = (char **)malloc(20 * sizeof(char *) + 1); // max 10.

	if (column_name) {
		t->column_names[++col_index] = allocate_string(column_name);

		va_start(valist, t);

		while ((col_name = va_arg(valist, char *))) {
			t->column_names[++col_index] = allocate_string(col_name);
		}

		va_end(valist);
	}

	t->columns = col_index + 1;
	t->rows = 0;
}

table_element table_data_get(struct table * t, int row, int column) {
}

int table_data_put(struct table * t, int row, int column, table_element content) {
}

int table_row_addv(struct table * t, table_element * column_data) {
}

int table_row_addl(struct table * t, ...) {
}

void table_row_remove(struct table * t, int row_index) {
}

void table_print(struct table * t) {
	dlog("lets print it.");
	printf("%d columns, %d rows.\n", t->columns, t->rows);
	for (int i = 0; i < t->columns; ++i) printf("[%s] \n", t->column_names[i]);
}

void table_free(struct table * t) {
}

