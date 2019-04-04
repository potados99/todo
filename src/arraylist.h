#ifndef arraylist_h
#define arraylist_h

#define LIST_INIT_CAP 10

struct arraylist {
	int capacity;
	int size;

	void **data;
};

int list_init(struct arraylist * list);

void *list_get_elem(struct arraylist * list, int index);
int  list_get_size(struct arraylist * list);
int  list_get_cap(struct arraylist * list);

int  list_add(struct arraylist * list, void * element);
int  list_remove(struct arraylist * list, int index);

int  list_dump(struct arraylist * list);
int  list_free(struct arraylist * list);

#endif
