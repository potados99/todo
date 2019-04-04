#include "table.h"
#include "ioutil.h"

#include <stdarg.h>

/*
struct table {
        int                     ncols;
        int                     nrows;

        char                    **col_names;
        int                     *col_spaces;

        struct table_row rows   *rows;;
};

struct table_row {
        int                     id;
        char	           	**fields;
};
 */

void table_init(struct table * t, const char * column_name, ...) {
	va_list 	valist;

	char 		*_each_col_name = NULL;
	int 		_current_col_index = -1;
	const int 	_column_padding = 5;

	/* allocate. */
	t->col_names = (char **)malloc(1 * sizeof(char *) + 1); // max 10.
	t->col_spaces = (int *)malloc(1 * sizeof(int) + 1);	

	t->rows = (struct table_row *)malloc(1 * sizeof(struct table_row) + 1);

	if (column_name) {
		++_current_col_index;
		t->col_names[_current_col_index] = allocate_string(column_name);
		t->col_spaces[_current_col_index] = strlen(column_name) + _column_padding;

		va_start(valist, column_name);

		while ((_each_col_name = va_arg(valist, char *))) {
			/* expand. */
			t->col_names = (char **)realloc(t->col_names, (_current_col_index + 2) * sizeof(char *) + 1);
			t->col_spaces = (int *)realloc(t->col_spaces, (_current_col_index + 2) * sizeof(int) + 1);

			/* assign. */
			++_current_col_index;
			t->col_names[_current_col_index] = allocate_string(_each_col_name);
			t->col_spaces[_current_col_index] = strlen(_each_col_name) + _column_padding;
		}

		va_end(valist);
	}

	t->ncols = _current_col_index + 1;
	t->nrows = 0;
}

char *table_data_get(struct table * t, int row, int column) {
}

int table_data_put(struct table * t, int row, int column, char * content) {
}

int table_row_add(struct table * t, struct table_row row) {
	// realloc.
	t->rows = (struct table_row *)realloc(t->rows, (t->nrows + 1) * sizeof(struct table_row) + 1);

	// assign.
	t->rows[t->nrows - 1] = row;
	
	return 1;
}

int table_row_addv(struct table * t, char ** row_fields) {
}

int table_row_addl(struct table * t, char * row_field, ...) {
	va_list valist;

	char * _each_field;
	int _current_field_index = 0;
	int _sum_rows = 0;
	struct table_row _each_row;

	if (row_field) {
		va_start(valist, row_field);

		_each_row.id = t->rows[t->nrows - 1].id + 1;
		_each_row.fields = (char **)malloc(t->ncols * sizeof(char *));

		while ((_each_field = va_arg(valist, char *))) {
			_each_row.fields[_current_field_index++] = allocate_string(_each_field);

			_sum_rows += table_row_add(t, _each_row);
		}

		va_end(valist);
	}

	return _sum_rows;
}

void table_row_remove(struct table * t, int row_id) {
}

void table_print(struct table * t) {
	int 			_ncols = t->ncols;
	int 			_nrows = t->nrows;

	const char 		**_cols = (const char **)(t->col_names);
	int 			*_col_spcs = t->col_spaces;
	struct table_row 	*_rows = t->rows;

	// Open table.
	fprintln_string_cells_with_token(stdout, NULL, _ncols, "═", _col_spcs, "╔", "╦", "╗");
	
	// Print the column headers.
	fprintln_string_cells_with_token(stdout, _cols, _ncols, " ", _col_spcs, "║", "║", "║");

	// Print rows.
	const char **_each_fields;
	for (int i = 0; i < _nrows; ++i) {
		_each_fields = (const char **)((_rows + i)->fields);	
		fprintln_string_cells_with_token(stdout, _each_fields, _ncols, " ", _col_spcs, "║", "║", "║");
	}

	// End table.
	fprintln_string_cells_with_token(stdout, NULL, _ncols, "═", _col_spcs, "╚", "╩", "╝");

}


void table_free(struct table * t) {
}

