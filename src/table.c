#include "table.h"
#include "ioutil.h"

#include <stdarg.h>
#include <stdio.h>

/*

struct table {
	int			ncols;
	int 			nrows;
	
	struct arraylist	col_spaces;
	struct arraylist	cols;
	struct arraylist 	rows;
};
 
 */

void table_init(struct table * t, const char * column_name, ...) {
	va_list 	valist;
	char		*_col_name = NULL;
	char		*_allocated_name = NULL;
	int		*_allocated_len = NULL;

	// Init struct.
	list_init(&(t->col_spaces));
	list_init(&(t->cols));
	list_init(&(t->rows));
	t->ncols = 0;
	t->nrows = 0;

	if (column_name) {
		va_start(valist, column_name);

		list_add(&(t->cols), allocate_string(column_name));

		while ((_col_name = va_arg(valist, char *))) {
			_allocated_name = allocate_string(_col_name);
			_allocated_len = allocate_int(strlen(_allocated_name) + CELL_PADDING);

			list_add(&(t->cols), _allocated_name);
			list_add(&(t->col_spaces), _allocated_len);

			t->ncols += 1;
		}

		va_end(valist);
	}
}

char *table_data_get(struct table * t, int row, int column) {
}

int table_data_put(struct table * t, int row, int column, char * content) {
}

int table_row_add(struct table * t, struct table_row row) {
	t->nrows += 1;
	
	// realloc.
	t->rows = (struct table_row *)realloc(t->rows, t->nrows * sizeof(struct table_row) + 1);

	// assign.
	t->rows[t->nrows - 1] = row;
	
	return 1;
}

int table_row_addv(struct table * t, char ** row_fields) {
}

int table_row_addl(struct table * t, char * row_field, ...) {
	va_list valist;

	char * _each_field;
	int _current_field_index = -1;
	int _sum_rows = 0;
	struct table_row _this_row;

	if (row_field) {
		va_start(valist, row_field);

		_this_row.id = t->rows[t->nrows - 1].id + 1;
		_this_row.fields = (char **)malloc(t->ncols * sizeof(char *));

		++_current_field_index;
		_this_row.fields[_current_field_index] = allocate_string(row_field);
		
		while ((_each_field = va_arg(valist, char *))) {
			++_current_field_index;
			_this_row.fields[_current_field_index] = allocate_string(_each_field);
			if (strlen(_each_field) + 5 > t->col_spaces[_current_field_index]) 
				t->col_spaces[_current_field_index] = strlen(_each_field) + 5;
		}
		
		_sum_rows += table_row_add(t, _this_row);

		va_end(valist);
	}

	return _sum_rows;
}

void table_row_remove(struct table * t, int row_id) {
}

void table_print(struct table * t) {
	int 			_ncols = t->ncols;
	int 			_nrows = t->nrows;

	const char 		**_cols = (const char **)(t->cols.data);
	int 			*_col_spcs = list_to_int_array(t->col_spaces);
	struct table_row 	**_rows = (struct table_row **)t->rows.data;

	// Open table.
	fprintln_string_cells_with_token(
			stdout, 
			NULL, 
			_ncols, 
			BOX_EDGE_HORIZONTAL, 
			_col_spcs, 
			BOX_CORNER_TOP_LEFT, 
			BOX_INTER_HORIZONTAL_DOWN, 
			BOX_CORNER_TOP_RIGHT);

	// Print the column headers.
	fprintln_string_cells_with_token(
			stdout, 
			_cols, 
			_ncols, 
			" ", 
			_col_spcs, 
			BOX_EDGE_VERTICAL, 
			BOX_EDGE_VERTICAL, 
			BOX_EDGE_VERTICAL);

	// Separator before rows.
	fprintln_string_cells_with_token(
			stdout, 
			NULL, 
			_ncols, 
			BOX_EDGE_HORIZONTAL, 
			_col_spcs, 
			BOX_INTER_VERTICAL_RIGHT, 
			BOX_INTER_CROSS, 
			BOX_INTER_VERTICAL_LEFT);

	// Print rows.
	const char **_each_fields;
	for (int i = 0; i < _nrows; ++i) {
		_each_fields = (const char **)((_rows + i)->fields);	
		fprintln_string_cells_with_token(
				stdout, 
				_each_fields,
				_ncols, 
				" ",
				_col_spcs, 
				BOX_EDGE_VERTICAL, 
				BOX_EDGE_VERTICAL, 
				BOX_EDGE_VERTICAL);
	}

	// Close table.
	fprintln_string_cells_with_token(
			stdout, 
			NULL, 
			_ncols, 
			BOX_EDGE_HORIZONTAL, 
			_col_spcs, 
			BOX_CORNER_BOTTOM_LEFT, 
			BOX_INTER_HORIZONTAL_UP,
			BOX_CORNER_BOTTOM_RIGHT);
}


int table_free(struct table * t) {
	verify(t, RET_WRONG_PARAM, "table is null.");

	list_free(t->col_spaces);
	list_free(t->cols);
	list_free(t->rows);
}

