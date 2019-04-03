#ifndef table_h
#define table_h

#include <stdio.h>

#include "ioutil.h"

typedef void * table_element;

struct table
{
	int		columns;
	int 		rows;

	char 		**column_names;

	/*
		Refer to the row and column
	 */
	table_element 	**content;
};


void 			table_init(struct table * t, const char * column_name, ...);

table_element	 	table_data_get(struct table * t, int row, int column);
int			table_data_put(struct table * t, int row, int column, table_element content);

int			table_row_addv(struct table * t, table_element * column_data);
int			table_row_addl(struct table * t, ...);
void			table_row_remove(struct table * t, int row_index);

void			table_print(struct table * t);

void			table_free(struct table * t);

#endif
