#include "arraylist.h"

#include <stdlib.h>
#include <string.h>
#include "debug.h"

/*
struct arraylist {
	int capacity;
	int size;

	void **data;
};
*/

int list_init(struct arraylist * list) {
	verify(list, RET_WRONG_PARAM, "list is null.");
	
	list->capacity = LIST_INIT_CAP;
	list->size = 0;

	int cap = (list->capacity * sizeof(void *) + 1);
	list->data = (void **)malloc(cap);
	verify(list->data, RET_ACTION_FAIL, "failed to allocate memory.");

	memset(list->data, 0, list->capacity * sizeof(void *) + 1);

	return RET_OK;
}

void *list_get_elem(struct arraylist * list, int index) {
	verify(list, NULL, "list is null.");
	verify((index >= 0 && index < list->size), NULL, "index out of range.");

	verify(list->data, NULL, "list->data is null.");

	return list->data[index];
}

int list_get_size(struct arraylist * list) {
	verify(list, RET_WRONG_PARAM, "list is null.");

	return list->size;
}
int list_get_cap(struct arraylist * list) {
	verify(list, RET_WRONG_PARAM, "list is null.");

	return list->capacity;
}

int list_add(struct arraylist * list, void * element) {
	verify(list, RET_WRONG_PARAM, "list is null.");
	verify(list->data, RET_WRONG_PARAM, "list->data is null.");
	verify(element, RET_WRONG_PARAM, "element is null.");

	if (list->size == list->capacity) {
		// time to allocate more.
		list->capacity <<= 2;

		int new_cap = (list->capacity * sizeof(void*) + 1);
		list->data = (void **)realloc(list->data, new_cap);
		verify(list->data, RET_ACTION_FAIL, "failed to reallocate memory.");
	
		// clear newly allocated part.
		memset(list->data + (new_cap >> 2), 0, (new_cap >> 2));
	}

	// assign.
	list->size += 1;
	*(list->data + list->size - 1) = element;

	return RET_OK;
}

int list_remove(struct arraylist * list, int index) {
}

int list_dump(struct arraylist * list) {
	verify(list, RET_WRONG_PARAM, "list is null.");
	verify(list->data, RET_WRONG_PARAM, "list->data is null.");
	
	int cnt = list->size;
	for (int i = 0; i < cnt; ++i) {
		printf("index[%d]: \"%s\"\n", i, *(list->data + i));	
	}
}

int list_free(struct arraylist * list) {
	verify(list, RET_WRONG_PARAM, "list is null.");
	verify(list->data, RET_WRONG_PARAM, "list->data is null.");
	
	int cnt = list->size;
	for (int i = 0; i < cnt; ++i) {
		free(*(list->data + i));
	}

	return RET_OK;
}

