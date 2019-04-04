#ifndef table_h
#define table_h

#include "arraylist.h"

#define CELL_PADDING 5

struct table {
	int			ncols;
	int 			nrows;
	
	struct arraylist	col_spaces;
	struct arraylist	cols;
	struct arraylist 	rows;
};

struct table_row {
	int			id;
	char			**fields;
};

void 				table_init(struct table * t, const char * column_name, ...);

char			 	*table_data_get(struct table * t, int row, int column);
int				table_data_put(struct table * t, int row, int column, char * content);

int 				table_row_add(struct table * t, struct table_row row);
int				table_row_addv(struct table * t, char ** row_fields);
int				table_row_addl(struct table * t, char * row_field, ...);
void				table_row_remove(struct table * t, int row_id);

void				table_print(struct table * t);

int				table_free(struct table * t);

#endif
